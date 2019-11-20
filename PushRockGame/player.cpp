#include "player.h"

const Aabb Player::PLAYER_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Player::Player(const Pos& pos) : Ent(PLAYER_AABB, pos, EntType::PLAYER) {

}

void Player::draw() {

}