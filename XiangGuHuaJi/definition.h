/* XiangGuHuaJi 2016, definition.h
 * 
 */

#ifndef _XIANGGUHUAJI_DEFINITION_H__
#define _XIANGGUHUAJI_DEFINITION_H__

typedef unsigned char TId;       //���Id
typedef unsigned char TMapSize;  //��ͼ�ߴ�(x,y)
typedef unsigned int  TMapArea;  //��ͼ���
typedef unsigned int  TRound;    //�غ���

typedef unsigned char TMapPara;  //��ͼ����(MapResource, MapDefenseRatio, MapAttackRatio)
typedef unsigned int  TSaving;   //�û������

typedef unsigned char TDefense;  //���ص���(DefensePoints)
typedef unsigned char TAttack;   //��������(AttackPoints)

typedef unsigned char TMilitary; //һ������õı���
typedef unsigned int  TMilitarySummary; //��ҵ��ܱ���

//�⽻��ϵ
enum DiplomaticStatus
{
    Undiscovered, //δ֪����
    Neutral, //����
    Union,   //ͬ��
    War,     //ս��
    StopWar  //ͣս
};
//�⽻ָ��
enum DiplomaticCommand
{
    KeepNeutral, //��������
    AskForUnion, //����ͬ��
    ClaimWar     //��ս
};

//�����Ϣ
struct PlayerInfo
{    
    TId id; //���ID
    bool Visible; //�����ο���Ϣ: ����һ�����Ϣ�Ƿ����ɼ�
    bool Union;   //�����ο���Ϣ: ����ҵ�������Ϣ�Ƿ����ɼ����Ƿ���ͬ�ˣ�
//������Ϣ
    TMapArea MapArea; //���������
    TMilitarySummary MilitarySummary; //�ѱ����õ��ܱ���
//������Ϣ
    TSaving Saving; //�����
};


#endif