/* XiangGuHuaJi 2016, ai.h
 *
 */

#ifndef _XIANGGUHUAJI_AI_H__
#define _XIANGGUHUAJI_AI_H__

#include "definition.h"

//AI��Ҫʵ�ֵĺ���

extern "C" _declspec(dllexport) TMoney birthplacePrice(BaseMap* map);
extern "C" _declspec(dllexport) TPosition birthplace(vector<TPosition> posSelected, BaseMap* map);

extern "C" _declspec(dllexport) void player_ai(Info& info);

#endif