/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef FLYING_PIECE_HDR
#define FLYING_PIECE_HDR

#if !defined(USE_MMGR) && !(defined(USE_GML) && GML_ENABLE_SIM)
#include "mmgr.h"
#include "MemPool.h"
#endif

#include "System/float3.h"
#include "System/GlobalUnsynced.h"

class CVertexArray;
struct S3DOPrimitive;
struct S3DOPiece;
struct SS3OVertex;

struct FlyingPiece {
	#if !defined(USE_MMGR) && !(defined(USE_GML) && GML_ENABLE_SIM)
	inline void* operator new(size_t size) { return mempool.Alloc(size); }
	inline void operator delete(void* p, size_t size) { mempool.Free(p, size); }
	#endif

public:
	FlyingPiece(int team, float3 pos, float3 speed, const S3DOPiece* object, const S3DOPrimitive* piece)
	{
		Init(team, pos, speed);

		//! 3D0
		prim = piece;
		object = object;
	}

	FlyingPiece(int team, float3 pos, float3 speed, int textureType, SS3OVertex* verts)
	{
		Init(team, pos, speed);

		//! S30
		verts = verts;
		texture = textureType;
	}

	~FlyingPiece();

	void Draw(int, size_t*, size_t*, CVertexArray*);

public:
	const S3DOPrimitive* prim;
	const S3DOPiece* object;

	SS3OVertex* verts;
	size_t texture;

	float3 pos;
	float3 speed;
	float3 rotAxis;
	float rot;
	float rotSpeed;

	size_t team;

private:
	void Init(int _team, float3 _pos, float3 _speed)
	{
		prim   = NULL;
		object = NULL;
		verts  = NULL;

		pos   = _pos;
		speed = _speed;

		texture = 0;
		team    = _team;

		rotAxis  = gu->usRandVector().ANormalize();
		rotSpeed = gu->usRandFloat() * 0.1f;
		rot = 0;
	}
};

#endif
