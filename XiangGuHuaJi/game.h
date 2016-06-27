/* XiangGuHuaJi 2016, game.h
 *
 * ʵ����Ϸ�����߼�
 *    ����һ�غ����У�ѡ�������
 *    ����
 *    �⽻
 *    ս��
 *    ����
 *    ���ʤ��
 * 
 */

#ifndef _XIANGGUHUAJI_GAME_H__
#define _XIANGGUHUAJI_GAME_H__


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<opencv2/opencv.hpp>

#include"definition.h"
#include"matrix.hpp"

#include"map.h"
#include"player.h"


namespace XGHJ {

using namespace std;

class Player;

class Game
{
public:
    Game(Map& map, vector<Player>& players);
    ~Game();

    bool Run();

    TRound       round;
    const TId    PlayerSize;
    
    TMapSize     x,y;

    Map&                map;
    vector<cv::Mat>     MilitaryMap;
    cv::Mat             DefensePointsMap;
    vector<cv::Mat>     AttackPointsMap;
    vector<PlayerInfo>  PlayerInfoList;
    cv::Mat             Ownership;

    DiplomaticStatus**  DiplomaticMap;

private:
    
    vector<Player>& players;

};

}


#endif