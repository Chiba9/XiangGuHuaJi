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
    vector<cv::Mat> MilitaryCommandList;
    vector<vector<TDiplomaticCommand> > DiplomaticCommandMap;

    //0. Ԥ���� & ÿһ������ж�

    //1.���� ����MilitaryMapList

    //2.�⽻ ����DiplomaticCommandMap

    //3.���� ����DefensePoints,AttackPointsMap

    //4.���� ����PlayerInfoList

    //5.ʤ���ж�

    return true;    
}

}