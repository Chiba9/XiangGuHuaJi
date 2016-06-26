/* XiangGuHuaJi 2016, info.hpp
 *
 */

#ifndef _XIANGGUHUAJI_INFO_H__
#define _XIANGGUHUAJI_INFO_H__

#include<iostream>
#include<vector>

using namespace std;


typedef unsigned char TId;       //���Id
typedef unsigned char TMapSize;  //��ͼ�ߴ�(x,y)
typedef int           TMapArea;  //��ͼ���
typedef int           TRound;    //�غ���
typedef int           TPlayerSize; //�������

typedef unsigned char TMapPara;  //��ͼ����(MapResource, MapDefenseRatio, MapAttackRatio)
typedef int           TSaving;   //�û������

typedef unsigned char TDefense;  //���ص���(DefensePoints)
typedef unsigned char TAttack;   //��������(AttackPoints)

typedef unsigned char TMilitary; //һ������õı���
typedef int           TMilitarySummary; //��ҵ��ܱ���


//�⽻��ϵ
enum DiplomaticStatus
{
    Unknown, //δ֪����
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

//��ͼ��ĳһ����ľ������
struct PointMilitary
{    
    bool Visible;  //�˵��Ƿ�ɼ�
    bool Union;    //�˵��Ƿ�Ϊ����(���Ƿ������������Ϸű�)
    TId Owner;     //��Ȩ����
 
    vector<TMilitary> Military; //�˵صķ���������״(�˵ص�ͬ������Ƿֱ�����������˶��ٱ�)

    TDefense DefensePoints;        //�˵�Ĺ�����״
    vector<TAttack> AttackSummary; //�˵�Ĺ�����״
};


//��һ�ȡ��ȫ������
class Info
{
public:
    Info(
        TId id, TRound round, TMapSize x, TMapSize y, TId PlayerSize,
        unsigned char **  mask,
        TMapPara **  MapResource,
        TMapPara **  MapDefenseRatio,
        TMapPara **  MapAttackRatio,
        TId **       Ownership,
        TMilitary *** MilitaryMap,
        TAttack *** AttackPointsMap,
        TDefense ** DefensePointsMap,
        PlayerInfo * PlayerList,
        DiplomaticStatus ** DiplomaticMap)
        : id(id), round(round), x(x), y(y), PlayerSize(PlayerSize),
        mask(mask), DiplomaticMap(DiplomaticMap), Ownership(Ownership),
        MapResource(MapResource), MapDefenseRatio(MapDefenseRatio), MapAttackRatio(MapAttackRatio),
        MilitaryMap(MilitaryMap), AttackPointsMap(AttackPointsMap), DefensePointsMap(DefensePointsMap),
        PlayerList(PlayerList)
    {
        for (TId i=0; i<PlayerSize; ++i) DiplomaticCommandList[i] = KeepNeutral;
    }
    
    const TId       id;    //�Լ���ID
    const TRound    round; //��ǰ�غ���
    const TMapSize  x, y;  //��ͼ�ĳߴ�
    const TId       PlayerSize; //�������
    
    const unsigned char*const*const     mask; //��ǰ�ɼ�����
    const DiplomaticStatus*const*const  DiplomaticMap; //ȫ���⽻״̬
    const TId*const*const Ownership;            //��ͼ��Ȩ
    const TMapPara*const*const MapResource;     //��ͼ��Դ����
    const TMapPara*const*const MapAttackRatio;  //��ͼ��������
    const TMapPara*const*const MapDefenseRatio; //��ͼ��������

    //��ȡһ�������Ϣ
    PointMilitary getPointMilitary(int x, int y) 
    {
        PointMilitary point;
        
        //TODO
        
        return point;
    }

    //��ȡһ����ҵ���Ϣ
    PlayerInfo getPlayerInfo(TId targetId)
    {
        PlayerInfo player;
        player.id = -1;
        if (targetId<0 || targetId>=PlayerSize) return player;
        
        player = PlayerList[targetId];
        switch (DiplomaticMap[id][targetId])
        {
        case Unknown:
        case War:
            player.Visible = player.Union  = false;
            player.Saving = player.MapArea = player.MilitarySummary = 0;
            return player;
        case Neutral:
            player.Visible = true;
            player.Union = false;
            player.Saving = 0; 
            return player;
        case Union:
            player.Visible = player.Union  = false;
            return player;
        default:
            return player;
        }

    }

//�ɹ�д����Ϣ
    vector<DiplomaticCommand> DiplomaticCommandList;
    vector<vector<unsigned char> > MilitaryCommand;

private:
    const TMilitary*const*const*const MilitaryMap;
    const TAttack*const*const*const   AttackPointsMap;
    const TDefense*const*const        DefensePointsMap;
    const PlayerInfo*const            PlayerList;
};


#endif