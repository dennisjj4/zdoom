/*
** p_terrain.h
**
**---------------------------------------------------------------------------
** Copyright 1998-2006 Randy Heit
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**---------------------------------------------------------------------------
**
*/

#ifndef __P_TERRAIN_H__
#define __P_TERRAIN_H__

#include "s_sound.h"
#include "textures/textures.h"

struct PClass;

extern WORD DefaultTerrainType;


class FTerrainTypeArray
{
public:
	TArray<WORD> Types;

	WORD operator [](FTextureID tex) const
	{
		WORD type = Types[tex.GetIndex()];
		return type == 0xffff? DefaultTerrainType : type;
	}
	WORD operator [](int texnum) const
	{
		WORD type = Types[texnum];
		return type == 0xffff? DefaultTerrainType : type;
	}
	void Resize(unsigned newsize)
	{
		Types.Resize(newsize);
	}
	void Clear()
	{
		memset (&Types[0], 0xff, Types.Size()*sizeof(WORD));
	}
	void Set(int index, int value)
	{
		Types[index] = value;
	}
};

extern FTerrainTypeArray TerrainTypes;

// at game start
void P_InitTerrainTypes ();

struct FSplashDef
{
	FName Name;
	FSoundID SmallSplashSound;
	FSoundID NormalSplashSound;
	const PClass *SmallSplash;
	const PClass *SplashBase;
	const PClass *SplashChunk;
	BYTE ChunkXVelShift;
	BYTE ChunkYVelShift;
	BYTE ChunkZVelShift;
	fixed_t ChunkBaseZVel;
	fixed_t SmallSplashClip;
	bool NoAlert;
};

struct FTerrainDef
{
	FName Name;
	int Splash;
	int DamageAmount;
	FName DamageMOD;
	int DamageTimeMask;
	fixed_t FootClip;
	float StepVolume;
	int WalkStepTics;
	int RunStepTics;
	FSoundID LeftStepSound;
	FSoundID RightStepSound;
	bool IsLiquid;
	bool AllowProtection;
	fixed_t Friction;
	fixed_t MoveFactor;
};

extern TArray<FSplashDef> Splashes;
extern TArray<FTerrainDef> Terrains;

#endif //__P_TERRAIN_H__
