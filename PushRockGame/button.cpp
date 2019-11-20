#include "button.h"

const Aabb Button::BUTTON_AABB = Aabb(-0.5, 0.5, -0.5, 0.5);

Button::Button(const Pos& pos) : Ent(BUTTON_AABB, pos, EntType::BUTTON) {

}

void Button::draw() {

}