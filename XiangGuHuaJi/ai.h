/* XiangGuHuaJi 2016, ai.h
 *
 */

#ifndef _XIANGGUHUAJI_AI_H__
#define _XIANGGUHUAJI_AI_H__

#include "definition.h"

//AI��Ҫʵ�ֵĺ���
#ifdef _MSC_VER
extern "C" _declspec(dllexport) void player_ai(Info& info);
#endif
#ifdef __GNUC__
extern "C" void player_ai(Info& info);
#endif

#endif