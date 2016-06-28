/* XiangGuHuaJi 2016, info.hpp
 *
 */

#ifndef _XIANGGUHUAJI_INFO_H__
#define _XIANGGUHUAJI_INFO_H__

#include<iostream>
#include<vector>

#include "definition.h"

using namespace std;

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
        const TId id, 
        const TRound round, 
        const TMapSize x, const TMapSize y, 
        const TId PlayerSize,
        unsigned char **  mask,
        unsigned char **  control,
        TMapPara **  MapResource,
        TMapPara **  MapDefenseRatio,
        TMapPara **  MapAttackRatio,
        TId **       Ownership,
        vector<TMilitary**> MilitaryMap,
        vector<TAttack**> AttackPointsMap,
        TDefense ** DefensePointsMap,
        vector<TPlayerInfo> PlayerInfoList,
        TDiplomaticStatus ** DiplomaticMap,
        vector<TDiplomaticCommand> & DiplomaticCommandList,
        vector<vector<TMilitary> > & MilitaryCommand)
        :
        id(id), round(round), x(x), y(y), PlayerSize(PlayerSize), saving(PlayerInfoList[id].Saving),
        mask(mask), control(control), DiplomaticMap(DiplomaticMap), Ownership(Ownership),
        MapResource(MapResource), MapDefenseRatio(MapDefenseRatio), MapAttackRatio(MapAttackRatio),
        MilitaryMap(MilitaryMap), AttackPointsMap(AttackPointsMap), DefensePointsMap(DefensePointsMap),
        PlayerInfoList(PlayerInfoList),
        DiplomaticCommandList(DiplomaticCommandList), MilitaryCommand(MilitaryCommand)
    {
        for (TId i=0; i<PlayerSize; ++i) DiplomaticCommandList[i] = KeepNeutral;
    }
    
    const TId       id;    //�Լ���ID
    const TRound    round; //��ǰ�غ���
    const TSaving   saving;//��ǰ���
    const TMapSize  x, y;  //��ͼ�ĳߴ�
    const TId       PlayerSize; //�������
    
    const unsigned char*const*const     mask;    //��ǰ�ɼ�����
    const unsigned char*const*const     control; //����Էű��ĵ���

    const TDiplomaticStatus*const*const DiplomaticMap; //ȫ���⽻״̬
    const TId*const*const      Ownership;             //��ͼ��Ȩ
    const TMapPara*const*const MapResource;     //��ͼ��Դ����
    const TMapPara*const*const MapAttackRatio;  //��ͼ��������
    const TMapPara*const*const MapDefenseRatio; //��ͼ��������

    //��ȡһ�������Ϣ
    PointMilitary getPointMilitary(int i, int j) 
    {
        PointMilitary point;
        
        if (mask[i][j]) point.Visible = true;
        else { point.Visible = false; return point; }

        point.Owner = Ownership[i][j];
        point.Union = DiplomaticMap[id][point.Owner] == Union;
        
        for (TId t=0; t<PlayerSize; ++t)
        {
            point.Military.push_back(MilitaryMap[t][i][j]);
            point.AttackSummary.push_back(AttackPointsMap[t][i][j]);
        }
        point.DefensePoints = DefensePointsMap[i][j];

        return point;
    }
    //��ȡһ����ҵ���Ϣ
    TPlayerInfo getPlayerInfo(TId targetId)
    {
        TPlayerInfo player;
        player.id = -1;
        if (targetId<0 || targetId>=PlayerSize) return player;
        
        player = PlayerInfoList[targetId];
        switch (DiplomaticMap[id][targetId])
        {
        case Undiscovered:
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

    vector<TDiplomaticCommand> & DiplomaticCommandList;
    vector<vector<TMilitary> > & MilitaryCommand;

private:
//�ܵ���Ϸ�������Ƶ���Ϣ
    vector<TMilitary**>   MilitaryMap;
    vector<TAttack**>     AttackPointsMap;
    TDefense**            DefensePointsMap;
    vector<TPlayerInfo>    PlayerInfoList;
};


#endif