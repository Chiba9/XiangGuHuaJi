// *********************************************************
//                 �벻Ҫ�޸Ļ��ύ���ļ�
//            Do NOT edit or commit this file
// *********************************************************

// FC14ѡ�ֹ��߰�
// �Զ����� auto_military ��һ���Ĳο���ֵŶ
// Created by sugar10w, 2017.03
// Last modified by sugar10w, 2017.03.17

#include "user_toolbox.h"


// ���²��� ���Ը�����3��������ai.cpp�������������ĳ�my_military
// *********************************************************
// �ҵĵ�ͼ��
struct MyMapPointInfo {
    TPosition pos;
    MapPointInfo mpi;
    int enemy_count;
    int friend_count;
};
// �Ե�Ĺ���
static int evaluate(MyMapPointInfo& t) {
    int value = 10;
    for (TPosition p : BRIGDES) if (get_distance(p, t.pos)<=2) value*=2;
    return value;
}
// �Զ�����
vector<TMilitaryCommand> auto_military(const Info& info, TMaskMap& mask, int money, int size)
{
    vector<TMilitaryCommand> MilitaryCommandList;
    vector<TMilitaryCommand> candidates;
    MaxHeap<float, MyMapPointInfo> heap;
    int summary_value = 0;
    int count_command = 0;
    const int MIN_MONEY = 25;

    // ���� money �� size
    if (money < MIN_MONEY) return MilitaryCommandList;
    if (MIN_MONEY * size > money) size = money / MIN_MONEY;
    if (size > MILITARY_COUNT_LIMIT) size = MILITARY_COUNT_LIMIT;

    // ���mask�Ƿ�Ϸ�
    if (!check_mask_validity(mask, info))
        mask = get_border_TMaskMap(info);

    for (int i = 0; i < info.cols; ++i)
        for (int j = 0; j < info.rows; ++j) 
            if (mask[i][j]) {
                const MapPointInfo& mpi=info.mapPointInfo[i][j];
                MyMapPointInfo temp = { {i,j}, mpi, 
                    count_enemy(i,j,info), count_friend(i,j,info)}; //���ɴ˵�ľֲ���Ϣ
                heap.add(evaluate(temp)+rand_f(), temp);  //���۲�ѹ������
            }

    // ȡ��������ߵ�size��ָ��
    for (int _=0; _<size; ++_) {
        MyMapPointInfo temp;
        int value = heap.getMax(temp);
        heap.removeMax();
        if (value>0) {
            TMilitaryCommand tmc = {temp.pos, value};
            candidates.push_back(tmc);
            summary_value += value;
        }
        else break;
    }

    // ��һ�� bomb_size
    if (candidates.size() > 0) {
        for (TMilitaryCommand& tmc : candidates) {
            tmc.bomb_size = int ((float)money * (float)tmc.bomb_size / (float)summary_value);
            if (tmc.bomb_size < MIN_MONEY) tmc.bomb_size = MIN_MONEY;
            MilitaryCommandList.push_back(tmc);
            
            money -= tmc.bomb_size;
            if (money <=0 ) break;
        }
    }

    return MilitaryCommandList;

}
// *********************************************************

// Implementation  ------------------------------------------------------------------

// �������
float rand_f(){
    return (float)rand()/RAND_MAX;
}

// ��ȡ TMaskMap
TMaskMap new_TMaskMap(size_t x, size_t y) {
    return vector<vector<bool> > (x, vector<bool>(y, false));
}
TMaskMap new_TMaskMap(const Info& info) {
    return new_TMaskMap(info.cols, info.rows);
}
TMaskMap get_border_TMaskMap(const Info& info) {
    TMaskMap map = new_TMaskMap(info);
    for(int i = 0; i < info.cols; i++)
		for (int j = 0; j < info.rows; j++) {
			const MapPointInfo& mpi = info.mapPointInfo[i][j];
            if (mpi.owner == info.id || 
                    (mpi.owner < info.playerSize && info.playerInfo[mpi.owner].dipStatus == Allied))  //������Լ��������ѵĵ�
                if (count_enemy(i,j,info) > 0) map[i][j] = true;
		}
    return map;
}
// ���TMaskMap
bool check_mask_validity(const TMaskMap& mask, const Info& info) {
    if (mask.size() != info.cols) return false;
    for (const vector<bool>& v : mask) if (v.size() != info.rows) return false;
    return true;
}

// ��ȡ�����پ���
unsigned int get_distance(TPosition a, TPosition b) {
    return abs((int)a.x-(int)b.x)+abs((int)a.y-(int)b.y);
}
// ���������Ƿ�Ϸ�
bool check_birth_pos_validity(vector<TPosition>& posSelected, TPosition pos) {
    for (int i=0; i<posSelected.size(); ++i)
        if (get_distance(posSelected[i], pos) < MIN_ABS_DIST_BETWEEN_CAP) 
			return false;
    return true;
}
// ����ɨ�ף������Χ8���ж�������/�жԵ�
int count_enemy(int x,int y, const Info& info) {
    TPosition dd[] = {
        {1, 0}, {-1, 0}, {0, -1}, {0, 1},
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
    };
	int border_count = 0;

    // ����8������
    for(TPosition d : dd) {
        int fx = x + d.x;
        int fy = y + d.y;
        if (info.map->isPosValid(fx,fy) ) // ��Ҫ������ͼ
            if (info.map->getMapAtk(fx,fy)>0) // ����ˮ��
            {
                TId owner = info.mapPointInfo[fx][fy].owner;

                if (owner == NEUTRAL_PLAYER_ID)  
                    ++border_count; //�����ĵ�
                else if (owner<info.playerSize) { 
                    if (info.playerInfo[owner].dipStatus == AtWar) ++border_count; // �ںʹ���Ҵ��
                }

            }
	}
	return border_count;
}
int count_friend(int x,int y, const Info& info) {
    TPosition dd[] = {
        {1, 0}, {-1, 0}, {0, -1}, {0, 1},
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
    };
	int border_count = 0;

    // ����8������
    for(TPosition d : dd) {
        int fx = x + d.x;
        int fy = y + d.y;
        if (info.map->isPosValid(fx,fy) ) // ��Ҫ������ͼ
            if (info.map->getMapAtk(fx,fy)>0) // ����ˮ��
            {
                TId owner = info.mapPointInfo[fx][fy].owner;

                if (owner == NEUTRAL_PLAYER_ID)  
                    continue; //�����ĵ�
                else if (owner<info.playerSize) { 
                    if (owner==info.id || info.playerInfo[owner].dipStatus == Allied) ++border_count; // �ѷ�����
                }

            }
	}
	return border_count;
}


// ��������ص�
TPosition random_birthplace(vector<TPosition> posSelected, BaseMap* map) {
    srand(time(NULL));
    while (true) {
        TPosition p = {rand() % map->getCols(), rand() % map->getRows()};
        if (map->getMapAtk(p.x, p.y)>0 && check_birth_pos_validity(posSelected, p)) return p;
    }
}

// �Զ��׶�
TPosition auto_capital(const Info& info) {
    
    TPosition best_capital = {0, 0};    
    int best_score = -10000;
    
    for (int i=0; i<info.cols; ++i)
        for (int j=0; j<info.rows; ++j)
            if (info.mapPointInfo[i][j].owner == info.id) {
                
                TPosition p = {i,j};
                if (info.map->getMapAtk(i,j)==0) continue;

                int score = 10 *  count_friend(i,j,info) * info.map->getMapDef(i,j) / info.map->getMapAtk(i,j);
                if (score>best_score) {
                    best_score = score;
                    best_capital = p;
                }
        }

    return best_capital;
}