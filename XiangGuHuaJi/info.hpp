/* XiangGuHuaJi 2016, info.hpp
 *
 */

#ifndef _XIANGGUHUAJI_INFO_H__
#define _XIANGGUHUAJI_INFO_H__

#include<iostream>
#include<vector>

#include "definition.h"

using namespace std;

// Military details about a point
struct PointMilitary
{    
    bool Visible;  
    bool Union;    
    TId Owner;   
 
    vector<TMilitary> Military; // everyone's Military on this point

    TDefense DefensePoints;       // DefensePoints currently
    vector<TAttack> AttackProc; // everyone's AttackProc to this point
};


// All details that AI could reach 
class Info
{
public:
    Info(
        TId             id, 
        TRound          Round, 
        TMapSize        rows,
        TMapSize        cols, 
        TId             PlayerSize,
        vector<vector<TMask> >	OwnershipMask,
        vector<vector<TMask> >  VisibleMask,
        vector<vector<TMask> >  ControlMask,
        vector<vector<TId> >	        GlobalMap,
        vector<vector<TMapPara> >       MapResource,
        vector<vector<TMapPara> >       MapDefenseRatio,
        vector<vector<TMapPara> >       MapAttackRatio,
        vector<vector<vector<TMilitary > > >	MilitaryMap,
        vector<vector<vector<TAttack > > >	    AttackProcMap,
        vector<vector<TDefense> >	            DefensePointsMap,
        vector<TPlayerInfo>	                    PlayerInfoList,
        vector<vector<TDiplomaticStatus> >	    Diplomacy,
        vector<vector<TMilitary> > MilitaryCommand,
        vector<TDiplomaticCommand> DiplomaticCommandList)
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
        AttackProcMap(AttackProcMap),
        DefensePointsMap(DefensePointsMap),
        PlayerInfoList(PlayerInfoList),
        Diplomacy(Diplomacy),
        DiplomaticCommandList(DiplomaticCommandList),
        MilitaryCommand(MilitaryCommand),
        saving(PlayerInfoList[id].Saving)
    {
        for (TId i=0; i<PlayerSize; ++i) DiplomaticCommandList[i] = KeepNeutral;
    }
    
    TId       id;           // your id Number
    TRound    Round;        // the round currently
    TSaving   saving;       // your resource gathered
    TMapSize  rows, cols;   // map
    TId       PlayerSize;   // playersize [Caution] Do not raise OutOfRange Exception 
    
    vector<vector<TMask> >  OwnershipMask;  // your land
    vector<vector<TMask> >	VisibleMask;    // visible area
    vector<vector<TMask> >	ControlMask;    // your and your allian's land

    vector<vector<TDiplomaticStatus> >	Diplomacy;
    vector<vector<TId> >	            GlobalMap;

    vector<vector<TMapPara> >	        MapResource, MapDefenseRatio, MapAttackRatio; // map
    
    PointMilitary                       getPointMilitary(int i, int j) 
    {
        PointMilitary point;
        
        if (VisibleMask[i][j]) point.Visible = true;
        else { point.Visible = false; return point; }

        point.Owner = GlobalMap[i][j];
        point.Union = Diplomacy[id][point.Owner] == Allied;
        
        for (TId t=0; t<PlayerSize; ++t)
        {
            point.Military.push_back(MilitaryMap[t][i][j]);
            point.AttackProc.push_back(AttackProcMap[t][i][j]);
        }
        point.DefensePoints = DefensePointsMap[i][j];

        return point;
    }
    
    TPlayerInfo                         getPlayerInfo(TId targetId)
    {
        TPlayerInfo player;
        player.id = -1;
        if (targetId<0 || targetId>=PlayerSize) return player;
        
        player = PlayerInfoList[targetId];
        switch (Diplomacy[id][targetId])
        {
        case Undiscovered:
        case AtWar:
            player.Visible = player.Union  = false;
            player.Saving = player.MapArea = player.MilitarySummary = 0;
            return player;
        case Neutral:
            player.Visible = true;
            player.Union = false;
            player.Saving = 0; 
            return player;
        case Allied:
            player.Visible = player.Union  = false;
            return player;
        default:
            return player;
        }
    }

    vector<TDiplomaticCommand>        DiplomaticCommandList;
    vector<vector<TMilitary> >        MilitaryCommand;

    //TODO move 
	const static TRound     MAX_ROUND = 20;
    const static TMilitary  MAX_MILITARY = 255;
    const static TSaving    UNIT_SAVING = 10;
    const static TSaving    UNIT_CITY_INCOME = 100;
	const static TRound     TRUCE_TIME = 5; 

private:
// info restricted by the game
    vector<vector<vector<TMilitary > > >	MilitaryMap;
    vector<vector<vector<TAttack > > >	    AttackProcMap;
    vector<vector<TDefense> >	            DefensePointsMap;

    vector<TPlayerInfo>	                PlayerInfoList;

};


#endif
