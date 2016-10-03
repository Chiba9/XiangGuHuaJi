/* XiangGuHuaJi 2016, game.h
 * 
 */

#ifndef _XIANGGUHUAJI_GAME_H__
#define _XIANGGUHUAJI_GAME_H__


#include <string>
#include <cmath>
#include <vector>

#include "definition.h"
#include "map.h"


using std::vector;

namespace XGHJ {
class Game
{
public:
    Game(Map& map, int playersize);
    ~Game();

    bool Start();
	bool Run(vector<vector<TMilitaryCommand> > & MilitaryCommandMap,
		vector<vector<TDiplomaticCommand> > & DiplomaticCommandMap);
    bool DiplomacyPhase(vector<vector<TDiplomaticCommand> > & DiplomaticCommandMap);
    bool MilitaryPhase(vector<vector<TMilitaryCommand> > & MilitaryCommandList);
    bool ProducingPhase();
    bool CheckWinner();

    Map& map;  

	PlayerInfo getPlayerInfo(TId id) const;
	MapPointInfo getMapPointInfo(TPosition pos) const;
	Info generateInfo(TId id) const;

	inline TRound getRound() {return round ;}
	inline TId getPlayerSize() {return playerSize ;}
	bool                isValid;
protected:
	TMap				rows,cols;
	TId                 playerSize;
	//��Ҫ���浽�»غϵ��м����
	TRound              round;
	vector<vector<TId> > globalMap;//ownership of the lands
	vector<vector<bool> > isSieged;
	vector<TPosition>	playerCapital;
	vector<TMoney>		playerSaving;
	vector<int>			playerArea;
	vector<vector<TDiplomaticStatus> >	diplomacy;
	//���ǻ���Ҫһ��������ʵ��justify war���Ҿ�����д��@pierre
private:
	//�����²���ʹ�õĸ�˹��
	vector<vector<float> > MilitaryKernel;
	//�����Լ���ӵ�С������д������
};

}


#endif
