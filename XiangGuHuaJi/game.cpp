/* XiangGuHuaJi 2016, game.cpp
 * 
 */

#include"game.h"

namespace XGHJ 
{

Game::Game(Map& map, vector<Player>& players)
    : map(map), players(players), PlayerSize(players.size()),
    Round(0)
{
}

Game::~Game()
{
    
}


//��Ϸ�߼�
bool Game::Run()
{
    vector<cv::Mat/*TMatMilitary*/>     MilitaryCommandList(PlayerSize);
    vector<vector<TDiplomaticCommand> > DiplomaticCommandMap(PlayerSize);

    
    Run_0();
    Run_1(MilitaryCommandList, DiplomaticCommandMap);
    Run_2(MilitaryCommandList);
    Run_3(DiplomaticCommandMap);
    Run_4(MilitaryCommandList);
    Run_5();
    Run_6();

    //7.����������
    ++Round;
    
    return true;    
}

//0.Ԥ����MilitaryMap,AttackPointsMap,DefensePointsMap
bool Game::Run_0()
{
    MilitaryMap.clear();
    for (TId id=0; id<PlayerSize; ++id) {
        vector<vector<TMilitary> > sub_MilitaryMap;
        convertMat<TMilitary>(MilitaryMap_[id], sub_MilitaryMap);
        MilitaryMap.push_back(sub_MilitaryMap);
    }
    AttackPointsMap.clear();
    for (TId id=0; id<PlayerSize; ++id) {
        vector<vector<TAttack> > sub_AttackPointMap;
        convertMat<TAttack>(AttackPointsMap_[id], sub_AttackPointMap);
        AttackPointsMap.push_back(sub_AttackPointMap);
    }
    convertMat<TDefense>(DefensePointsMap_, DefensePointsMap);
    
    return true;
}

//1.ÿ������ж�
bool Game::Run_1(vector<cv::Mat/*TMatMilitary*/> &     MilitaryCommandList,
                 vector<vector<TDiplomaticCommand> > & DiplomaticCommandMap )
{    
    for (TId id=0; id<PlayerSize; ++id)
    {
        cv::Mat/*TMatMilitary*/	    MilitaryCommand_;
        vector<TDiplomaticCommand>  DiplomaticCommand;
        players[id].Run(*this, MilitaryCommand_, DiplomaticCommand);
        MilitaryCommandList[id]     = MilitaryCommand_;
        DiplomaticCommandMap[id]    = DiplomaticCommand;
    }
	return false; //TODO
}

//2.���� ����MilitaryMapList
bool Game::Run_2(vector<cv::Mat/*TMatMilitary*/> & MilitaryCommandList)
{
    return false; //TODO
}

//3.�⽻ ����Diplomatic
bool Game::Run_3(vector<vector<TDiplomaticCommand> > & DiplomaticCommandMap)
{
    return false; //TODO
}

//4.���� ����DefensePoints,AttackPointsMap
bool Game::Run_4(vector<cv::Mat/*TMatMilitary*/> & MilitaryCommandList)
{
    return false; //TODO
}

//5.���� ����PlayerInfoList
bool Game::Run_5()
{
    return false; //TODO
}

//6.ʤ���ж�
bool Game::Run_6()
{
    return false; //TODO
}

}