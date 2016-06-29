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
    vector<TAttack> AttackPoints; //�˵�Ĺ�����״
};


//��һ�ȡ��ȫ������
class Info
{
public:
    Info(
        TId             id, 
        TRound          Round, 
        TMapSize        rows,
        TMapSize        cols, 
        TId             PlayerSize,
        vector<vector<unsigned char> >	OwnershipMask,
        vector<vector<unsigned char> >  VisibleMask,
        vector<vector<unsigned char> >  ControlMask,
        vector<vector<TId> >	        GlobalMap,
        vector<vector<TMapPara> >       MapResource,
        vector<vector<TMapPara> >       MapDefenseRatio,
        vector<vector<TMapPara> >       MapAttackRatio,
        vector<vector<vector<TMilitary > > >	MilitaryMap,
        vector<vector<vector<TAttack > > >	    AttackPointsMap,
        vector<vector<TDefense> >	            DefensePointsMap,
        vector<TPlayerInfo>	                    PlayerInfoList,
        vector<vector<TDiplomaticStatus> >	    Diplomatic,
        vector<vector<TMilitary> > & MilitaryCommand,
        vector<TDiplomaticCommand> & DiplomaticCommandList)
        :
        id(id),
        Round(Round),
        rows(rows), cols(cols),
        PlayerSize(PlayerSize),
        OwnershipMask(OwnershipMask),
        VisibleMask(VisibleMask),
        ControlMask(ControlMask),
        MapResource(MapResource),
        MapDefenseRatio(MapDefenseRatio),
        MapAttackRatio(MapAttackRatio),
        GlobalMap(GlobalMap),
        MilitaryMap(MilitaryMap),
        AttackPointsMap(AttackPointsMap),
        DefensePointsMap(DefensePointsMap),
        PlayerInfoList(PlayerInfoList),
        DiplomaticCommandList(DiplomaticCommandList),
        MilitaryCommand(MilitaryCommand),
        saving(PlayerInfoList[id].Saving)
    {
        for (TId i=0; i<PlayerSize; ++i) DiplomaticCommandList[i] = KeepNeutral;
    }
    
    TId       id;           //�Լ���ID
    TRound    Round;        //��ǰ�غ���
    TSaving   saving;       //��ǰ���
    TMapSize  rows, cols;         //��ͼ�ĳߴ�
    TId       PlayerSize;   //�������
    
    vector<vector<unsigned char> >  OwnershipMask;  //�������
    vector<vector<unsigned char> >	VisibleMask;    //��ǰ�ɼ�����
    vector<vector<unsigned char> >	ControlMask;    //����Էű��ĵ���

    vector<vector<TDiplomaticStatus> >	Diplomatic;
    vector<vector<TId> >	            GlobalMap;

    vector<vector<TMapPara> >	    MapResource, MapDefenseRatio, MapAttackRatio; //��ͼ����

    //��ȡһ�������Ϣ
    PointMilitary getPointMilitary(int i, int j) 
    {
        PointMilitary point;
        
        if (VisibleMask[i][j]) point.Visible = true;
        else { point.Visible = false; return point; }

        point.Owner = GlobalMap[i][j];
        point.Union = Diplomatic[id][point.Owner] == Union;
        
        for (TId t=0; t<PlayerSize; ++t)
        {
            point.Military.push_back(MilitaryMap[t][i][j]);
            point.AttackPoints.push_back(AttackPointsMap[t][i][j]);
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
        switch (Diplomatic[id][targetId])
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
    vector<vector<vector<TMilitary > > >	MilitaryMap;
    vector<vector<vector<TAttack > > >	    AttackPointsMap;
    vector<vector<TDefense> >	            DefensePointsMap;

    vector<TPlayerInfo>	PlayerInfoList;

};


#endif