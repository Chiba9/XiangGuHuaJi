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

bool Game::Run()
{
    vector<cv::Mat/*TMatMilitary*/>     MilitaryCommandList(PlayerSize);
    vector<vector<TDiplomaticCommand> > DiplomaticCommandMap(PlayerSize);

    //0. Ԥ���� & ÿһ������ж�
    for (TId id=0; id<PlayerSize; ++id)
    {
        cv::Mat/*TMatMilitary*/	    MilitaryCommand_;
        vector<TDiplomaticCommand>  DiplomaticCommand;
        players[id].Run(*this, MilitaryCommand_, DiplomaticCommand);
        MilitaryCommandList[id]     = MilitaryCommand_;
        DiplomaticCommandMap[id]    = DiplomaticCommand;
    }

    //1.���� ����MilitaryMapList

    //2.�⽻ ����DiplomaticCommandMap

    //3.���� ����DefensePoints,AttackPointsMap

    //4.���� ����PlayerInfoList

    //5.ʤ���ж�

    return true;    
}

}