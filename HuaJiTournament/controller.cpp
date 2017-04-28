/* XiangGuHuaJi 2016, controller.cpp
 *
 */

#include "controller.h"

#include <fstream>

#define min(a,b) ((a)<(b)?(a):(b))

namespace XGHJ
{
    using namespace std;

    static const int FLAG_ID_1 = -8930218;

    static float rand_f(){
        return (float)rand()/RAND_MAX;
    }

	void Controller::run()
	{

        TId playerSize = game_.getPlayerSize();
		TRound round = game_.getRound();

        if (file_output_enabled_ && !ofs.is_open()) {
            char buffer[1024];
            time_t t = time(0);
            int st = rand_f() * 99;
            strftime(buffer, sizeof(buffer), "log_%Y%m%d_%H%M%S",localtime(&t));
            log_filename = buffer+to_string(st) + ".txt";
            ofs.open(log_filename.c_str());
        }

        if (!silent_mode_) cout << "-=-=-=-=-=-=-=-=-=-=-= Controller: Round[" << round << "] =-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;

		if (round != 0)
		{
			vector<vector<TMilitaryCommand> > MilitaryCommandMap(playerSize);
			vector<vector<TDiplomaticCommand> > DiplomaticCommandMap(playerSize);
			vector<TPosition > NewCapitalList(playerSize);

            // ÿ����ҿ�ʼ����
			for (TId id=0; id<playerSize; ++id)
			{
                Player& player = players_[id];

                Info info = game_.generateInfo(id);
                if (player.isValid() && game_.isAlive(id))
                {
                    // �������ִ��
                    if (!silent_mode_) cout << "Calling Player " << (int)id << "'s Run() method" << endl;
                    
                    // TODO
                    players_[id].run(info);
                    // TODO
                }
                else
                {
                    players_[id].kill();
                }

                
                DiplomaticCommandMap[id] = info.DiplomaticCommandList;	
                MilitaryCommandMap[id] = info.MilitaryCommandList;
                NewCapitalList[id] = info.newCapital;            


                // ֱ���������ҵĲ���
                if (file_output_enabled_) {
                    for (int i=0; i<playerSize; ++i) ofs<<" "<<(int)info.DiplomaticCommandList[i];
                    for (int i=0; i<min(info.MilitaryCommandList.size(),MILITARY_COUNT_LIMIT); ++i) 
                        ofs<<" "<<(int)info.MilitaryCommandList[i].place.x 
                           <<" "<<(int)info.MilitaryCommandList[i].place.y
                           <<" "<<(int)info.MilitaryCommandList[i].bomb_size; 
                    ofs << " -1 " << (int)info.newCapital.x << " " << (int)info.newCapital.y << "\t" ;
                }
			}
            if (file_output_enabled_) ofs << endl;

            // ����game
			if (!game_.Run(MilitaryCommandMap, DiplomaticCommandMap, NewCapitalList))
                if (!silent_mode_) cout << "-=-=-=-=-=-=-=-=-=-=-= GAME OVER ! =-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			
			isValid_ = game_.isValid();
		}
		else
        {
            // ��0�غϾ��۽׶�
            if (!silent_mode_) cout << "Bidding......" << endl;
            vector<TMoney> bidPrice;
            vector<std::tuple<float, TId> > bidPriceTuple;

            srand(time(NULL));

            // ���þ���
            for (TId id=0; id<playerSize; ++id) {
                Player& player = players_[id];
                TMoney price = 0;
                if (player.isValid()) {
                    if (!silent_mode_) cout << "Calling Player " << (int)id << "'s birthplacePrice() method" << endl;
                    players_[id].run(price, &(game_.map));
                }
                if (price<0) price = 0;
                if (price>INITIAL_PLAYER_MONEY) price = INITIAL_PLAYER_MONEY;
                bidPriceTuple.push_back(std::make_tuple(price + rand_f(), id));  // �ھ���������0~1�������
                bidPrice.push_back(price);
            }
            
            // ���򲢽���ѡ������
            std::sort(bidPriceTuple.begin(), bidPriceTuple.end(), 
                [](const std::tuple<float, TId> &a, const std::tuple<float, TId> &b) -> bool { return std::get<0>(a) > std::get<0>(b);  }
            );
            if (!silent_mode_) cout << "Choosing birthplace......" << endl;
            vector<TPosition> posChoosed;
            for (TId i=0; i<playerSize; ++i) {
                TId id = std::get<1>(bidPriceTuple[i]);
                Player& player = players_[id];
                TPosition pos = INVALID_POSITION;
                if (player.isValid()) {
                    if (!silent_mode_) cout << "Calling Player " << (int)id << "'s birthplacePrice() method" << endl;
                    players_[id].run(pos, posChoosed, &(game_.map));
                }
                posChoosed.push_back(pos);
            }

            // �ܽ�����
            vector<TPosition> posChoosedSorted(playerSize);
            for (TId i=0; i<playerSize; ++i) {
                TId id = std::get<1>(bidPriceTuple[i]);
                posChoosedSorted[id] = posChoosed[i];
            }

            if (file_output_enabled_) {
                ofs << FLAG_ID_1 << endl;
                ofs << (int)playerSize << endl;
                for (int i=0; i<playerSize; ++i) ofs << players_[i].getName() << endl;

                for (int i=0; i<playerSize; ++i) ofs<<" "<<(int)bidPrice[i];
                ofs << endl;
                for (int i=0; i<playerSize; ++i) ofs<<" "<<(int)posChoosedSorted[i].x << " " << (int)posChoosedSorted[i].y;
                ofs << endl;
            }

			// ��game���е�1�غ�
			game_.Start(bidPrice, posChoosedSorted);
		}

        // check if killed
        for (TId i=0; i<playerSize; ++i)
            if (!game_.isAlive(i))
                players_[i].kill();

	}
}
