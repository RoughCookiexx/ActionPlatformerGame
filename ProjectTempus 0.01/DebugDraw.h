#include <Box2D\Box2D.h>
#include "World.h"
#include "Physics.h"

#pragma once

class World;

class DebugDraw : public b2Draw
{
private: 
	World *world;
public: 
	DebugDraw(World *world);
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) ;
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
    void DrawTransform(const b2Transform& xf) {}
};