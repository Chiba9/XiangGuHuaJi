/* XiangGuHuaJi 2016, definition.h
 * 
 */

#ifndef _XIANGGUHUAJI_DEFINITION_H__
#define _XIANGGUHUAJI_DEFINITION_H__


#include "debug.hpp"

typedef unsigned char TId;       //PlayerId
typedef unsigned char TMap;  //x,y
typedef unsigned int  TRound;    //round 

typedef unsigned int  TMoney;   //money unit

typedef unsigned int  TMilitary; //Military

typedef bool TMask;

struct TPosition
{
	TMap x;
	TMap y;
};

enum TDiplomaticStatus
{
    Undiscovered,   // a country that has never appeared in your visible area
    Neutral,        // default status of a newly discovered country
    Allied,          
    AtWar
};
enum TDiplomaticCommand
{
    KeepNeutral, 
    FormAlliance, 
    JustifyWar,
	Backstap
};

struct TMilitaryCommand
{
	TPosition place; //your goal place
	TMilitary bomb_size;
};

//CONSTANTS
const static TRound     MAX_ROUND = 50;//�����޶�
const static TMoney     UNIT_BOMB_COST = 1;
const static float		UNIT_CITY_INCOME = 1.0f;//�ͱ��ı���ϵ��
const static TRound     WAR_JUSTIFICE_TIME = 3;//��ս����������ս��ʱ��
const static float		CORRUPTION_COEF = 0.001f;//�ջ���Դ�ĸ���ϵ��
const static int		MILITARY_KERNEL_SIZE = 5;//Ӱ�������ĵĴ�С
const static float		MILITARY_KERNEL_SIGMA_2 = 2.25f;//Ӱ�������ĵĸ�˹������ϵ��sigma��ƽ��
const static float		MILITARY_KERNEL_GAUSS_COEF = 100.0f;//Ӱ�������ĵĸ�˹����ǰ���ϵ��
const static float		MILITARY_KERNEL_DELTA;//����Ӱ����
const static TMilitary	SUPPESS_LIMIT = 3;//ѹ�����ޣ�����ѹ������֮��ͻ��Ƴǡ���ѹ�ơ���������������FPS��


#endif
