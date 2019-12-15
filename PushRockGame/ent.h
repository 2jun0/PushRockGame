#pragma once
#include <glut.h>

enum class EntType
{
	NONE = 0,
	WALL,
	ROCK,
	PLAYER,
	BUTTON,
};

class Pos {
public:
	float x;
	float y;
	float z;
public:
	Pos(float x, float y, float z);
};

class Aabb {
public:
	float minX;
	float maxX;
	float minZ;
	float maxZ;
public:
	Aabb(float minX, float maxX, float minZ, float maxZ);
};

class Ent {
protected:
	Aabb aabb;
	Pos pos;
	EntType type;
	float speed;
public:
	Ent(const Aabb& aabb, const Pos& pos, const EntType& type);
	
	virtual Aabb& getAabb();
	virtual Pos& getPos();
	virtual EntType& getType();

	virtual bool moveLeft();
	virtual bool moveRight();
	virtual bool moveUp();
	virtual bool moveDown();

	virtual void reberseMoveLeft();
	virtual void reberseMoveRight();
	virtual void reberseMoveUp();
	virtual void reberseMoveDown();

	virtual bool checkCollision(Ent& ent);
	virtual bool collisionEvent(Ent& ent);
	virtual void afterCollisionEvent(Ent& ent, bool isCollision);

	virtual void draw()=0;
	virtual const float* getColor() = 0;
};