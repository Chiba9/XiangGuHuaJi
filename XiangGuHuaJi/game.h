/* XiangGuHuaJi 2016, game.h
 *
 * ʵ����Ϸ�����߼�
 *    ����һ�غ����У�ѡ�������
 *    ����
 *    �⽻
 *    ս��
 *    ���ʤ��
 * 
 */

#ifndef _XIANGGUHUAJI_GAME_H__
#define _XIANGGUHUAJI_GAME_H__

#include<vector>

#include<opencv2/opencv.hpp>

#include"map.h"
#include"player.h"
#include"definition.h"

namespace XGHJ {

using namespace std;

class Player;

class Game
{
public:
    Game(Map& map, vector<Player>& players);
    ~Game();

    bool Run();

    TRound round;
    TId    PlayerSize;
    
    cv::Mat         MapResource, MapAttack, MapDefense;
    vector<cv::Mat> MilitaryMap;
    cv::Mat         DefensePoints;
    vector<cv::Mat> AttackPointsMap;

private:
    Map& map;
    vector<Player>& players;

};

}


#endif