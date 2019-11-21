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
/*
	Ent end
*/