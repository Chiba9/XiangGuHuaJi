/* XiangGuHuaJi 2016, game.cpp
 * 
 */

#include "game.h"

namespace XGHJ 
{

inline float x2plusy2(float x, float y){return x*x+y*y;}


Game::Game(Map& map, int playersize)
	: map(map), playerSize(playersize), playerSaving(playersize, INITIAL_PLAYER_MONEY),
      playerArea(playersize, 0), round(0), isValid(true)
{
	rows = map.getRows();
	cols = map.getCols();
	//init all the vectors using vector::resize
	globalMap.resize(cols);
	isSieged.resize(cols);
	for (int i=0; i<cols; i++)
	{
		globalMap[i].resize(rows);
		isSieged[i].resize(rows);
		for (int j=0; j<rows; j++)
		{
			globalMap[i][j] = NEUTRAL_PLAYER_ID;
			isSieged[i][j] = false;
		}
	}
	diplomacy.resize(playerSize);
	for (TId i=0; i<playersize; i++)
	{
		diplomacy[i].resize(playerSize);
		for (TId j=0; j<playersize; j++)
		{
			if (i == j)
			{
				diplomacy[i][j] = Allied;
			}
			else
			{
				diplomacy[i][j] = Undiscovered;
			}
		}
	}

	const float pi = 3.1416f;
	MilitaryKernel.resize(2*MILITARY_KERNEL_SIZE-1);
	for (int i=0; i<2*MILITARY_KERNEL_SIZE-1; i++)
	{
		MilitaryKernel[i].resize(2*MILITARY_KERNEL_SIZE-1);
		for (int j=0; j<2*MILITARY_KERNEL_SIZE-1; j++)
		{
			float f = x2plusy2((float)(i-MILITARY_KERNEL_SIZE+1),(float)(j-MILITARY_KERNEL_SIZE+1));
			f /= -2*MILITARY_KERNEL_SIGMA_2;
			f = (float)exp(f);
			f /= 2*MILITARY_KERNEL_SIGMA_2*pi;
			MilitaryKernel[i][j] = f;
		}
	}
	printVecMat<float>(MilitaryKernel, "MilitaryKernel");
}

Game::~Game()
{
    
}

// Round<0>
//TODO  init the player, call each player to select their birthplace
bool Game::Start()
{
	round = 0;
	++round;

	//TODO
	//ѡ�������
	//�����׶�ΪĬ�ϳ�����

	return true;
}

//Game Logic
bool Game::Run(vector<vector<TMilitaryCommand> > & MilitaryCommandMap,
	vector<vector<TDiplomaticCommand> > & DiplomaticCommandMap)
{
    DiplomacyPhase(DiplomaticCommandMap);
    MilitaryPhase(MilitaryCommandMap);
    ProducingPhase();

    ++round;
    if (round>=MAX_ROUND) isValid=false;

    return isValid;    
}

//Diplomacy Phase (Deal with DiplomaticCommandMap)
bool Game::DiplomacyPhase(vector<vector<TDiplomaticCommand> > & DiplomaticCommandMap)
{
	//TODO
	//�⽻

	//��ȡDiplomaticCommandMap
	//����Diplomacy���ǵ�ս����Ҫ��WAR_JUSTIFY_TIME�غϣ���Ҫ����ά���б�
	//�ǵÿ�Ǯ������Ҫ��WAR_JUSTIFY_PRICE��Ǯ��

	//����Ĺ��ȴ�����ܿ��Ը��ã�Ƥ����������о�һ����û������
	/*
    for (TId i=0; i<PlayerSize; ++i)
        for (TId j=0; j<PlayerSize; ++j)        
            if (TruceTreaty[i][j]>0) 
            {
                --TruceTreaty[i][j];
                --TruceTreaty[i][j];
                if (0==TruceTreaty[i][j])
                    Diplomacy_[i][j] = Diplomacy_[j][i] = Neutral;
            }
	
    for (TId i=0; i<PlayerSize; i++)
	{
		for (TId j=0; j<i; j++)
		{
			{
				switch (Diplomacy_[i][j])
				{
				case Neutral:
                    if (DiplomaticCommandMap[i][j] == FormAlliance 
						&& DiplomaticCommandMap[j][i] == FormAlliance)
					{
						//allied
						Diplomacy_[i][j] = Allied;
						Diplomacy_[j][i] = Allied;
					}
					else if (DiplomaticCommandMap[i][j] != DeclareWar 
						&& DiplomaticCommandMap[j][i] != DeclareWar)
					{
						//neutral
						Diplomacy_[i][j] = Neutral;
						Diplomacy_[j][i] = Neutral;
					}
					else
					{
						//at war
						Diplomacy_[i][j] = AtWar;
                        Diplomacy_[j][i] = AtWar;
					}
					break;
				case AtTruce:
					if (DiplomaticCommandMap[i][j] == FormAlliance
                        && DiplomaticCommandMap[j][i] == FormAlliance)
                    {
                        Diplomacy_[i][j]  = Diplomacy_[j][i]  = Allied;
                        TruceTreaty[i][j] = TruceTreaty[j][i] = 0;
                    }
                    //at truce
					//solved at begin
					break;
				case Undiscovered:
					//Discovery will be solved in Military Phase
					break;
				case Allied:
					if (DiplomaticCommandMap[i][j] == FormAlliance 
						&& DiplomaticCommandMap[j][i] == FormAlliance)
					{
						//allied
						;
					}
					else
					{
						//at truce
						Diplomacy_[i][j]  = Diplomacy_[j][i]  = AtTruce;
						TruceTreaty[i][j] = TruceTreaty[j][i] = TRUCE_TIME;
						//TODO units on the used-to-be allied islands should be destroyed
					}
					break;
				case AtWar:
					if (DiplomaticCommandMap[i][j] == DeclareWar 
						|| DiplomaticCommandMap[j][i] == DeclareWar)
					{
						//at war
						;
					}
					else
					{
						//at truce
                        Diplomacy_[i][j]  = Diplomacy_[j][i]  = AtTruce; 
                        TruceTreaty[i][j] = TruceTreaty[j][i] = TRUCE_TIME;
					}
					break;
				}
			}
		}
	}
	*/
    return false; //TODO
}

bool Game::MilitaryPhase(vector<vector<TMilitaryCommand> > & MilitaryCommandList)
{
	//TODO
	//ȫ��opencv���룬һ�㶼û�����ã������������ʵʵд����

	//��ȡMilitaryCommandList���ҿ�UNIT_BOMB_COST��Ǯ

	//����GlobalMap��ʹ��MilitaryKernel

	//��ֵȡSUPPESS_LIMIT���������һ����ǿ�аѵش������

	//������׶�
	//Ҫ���޷��������׶����Ͱ����׶���λ���趨ΪinvalidPos

	//����Χ
	//����isSieged
	
    return false; //TODO
}

//Producing Phase (Deal with MapResource, PlayerInfoList)
bool Game::ProducingPhase()
{
	
    for (TId id=0; id<playerSize; ++id)
	{
		playerArea[id] = 0;
		// lowest income
		TMoney new_saving = 1;

        // map income 
        for (TMap j=0; j<map.getRows(); ++j)
            for (TMap i=0; i<map.getCols(); ++i)
                if (globalMap[i][j] == id) 
				{
					new_saving+=map.getMapRes()[i][j];
					playerArea[id]++;
				}
        // city income
		if (isPosValid(playerCapital[id]))
		{
			new_saving += (TMoney)(UNIT_CITY_INCOME * (float)round);
		}

        // corruption 
        playerSaving[id] = (TMoney)((1-(float)(playerArea[id])*CORRUPTION_COEF) * (float) playerSaving[id]);
		playerSaving[id] += new_saving;
    }

    return false; //TODO
}

//Check the winner and the loser (Deal with PlayerInfoList)
bool Game::CheckWinner()
{
	//TODO
	//���ʤ��
    return false; //TODO
}

PlayerInfo Game::getPlayerInfo(TId id) const
{
	//TODO
	PlayerInfo p;
	return p;
}
MapPointInfo Game::getMapPointInfo(TPosition pos) const
{
	//TODO
	MapPointInfo mp;
	return mp;
}

Info Game::generateInfo(TId id) const
{
	//TODO
	Info i;
	return i;
}

}
