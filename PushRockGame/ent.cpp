#include "game.h"
#include "ent.h"
#define NULL 0

/*
	Aabb start
*/
Aabb::Aabb(float minX, float maxX, float minZ, float maxZ) {
	this->minX = minX;
	this->maxX = maxX;
	this->minZ = minZ;
	this->maxZ = maxZ;
}
/*
	Aabb end
*/

/*
	Pos start
*/
Pos::Pos(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
/*
	Pos end
*/

/*
	Ent start
*/

Ent::Ent(const Aabb &aabb, const Pos &pos, const EntType &type)
	: aabb(aabb), pos(pos), type(type) {
	speed = 0.1;
}

Aabb& Ent::getAabb() {
	return this->aabb;
}
Pos& Ent::getPos() {
	return this->pos;
}
EntType& Ent::getType() {
	return this->type;
}

bool Ent::moveLeft() {
	this->pos.x += speed;
	if (Game::getInstance().checkCollision(this)) {
		reberseMoveLeft();
		return false;
	}
	return true;
}
bool Ent::moveRight() {
	this->pos.x -= speed;
	if (Game::getInstance().checkCollision(this)) {
		reberseMoveRight();
		return false;
	}
	return true;
}
bool Ent::moveUp() {
	this->pos.z += speed;
	if (Game::getInstance().checkCollision(this)) {
		reberseMoveUp();
		return false;
	}
	return true;
}
bool Ent::moveDown() {
	this->pos.z -= speed;
	if (Game::getInstance().checkCollision(this)) {
		reberseMoveDown();
		return false;
	}
	return true;
}

void Ent::reberseMoveLeft() {
	this->pos.x -= speed;
}
void Ent::reberseMoveRight() {
	this->pos.x += speed;
}
void Ent::reberseMoveUp() {
	this->pos.z -= speed;
}
void Ent::reberseMoveDown() {
	this->pos.z += speed;
}

bool Ent::checkCollision(Ent& ent) {
	float aMaxX = aabb.maxX + pos.x;
	float aMinX = aabb.minX + pos.x;
	float aMaxZ = aabb.maxZ + pos.z;
	float aMinZ = aabb.minZ + pos.z;

	float bMaxX = ent.getAabb().maxX + ent.getPos().x;
	float bMinX = ent.getAabb().minX + ent.getPos().x;
	float bMaxZ = ent.getAabb().maxZ + ent.getPos().z;
	float bMinZ = ent.getAabb().minZ + ent.getPos().z;

	if (aMaxX <= bMinX || aMinX >= bMaxX) return false;
	if (aMaxZ <= bMinZ || aMinZ >= bMaxZ) return false;
	return true;
}

bool Ent::collisionEvent(Ent& ent) {
	return true;
}

void Ent::afterCollisionEvent(Ent& ent, bool isCollision) {

}
/*
	Ent end
*/