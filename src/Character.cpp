#pragma once
#include "Character.h"

void Character::setID(char ID) {
	this->ID = ID;
}
void Character::setLevel(char level) {
	this->level = level;
}
void Character::setPosition(XY position) {
	this->position = position;
}
void Character::loadGraph(std::string filename) {
	this->CharGraph = LoadGraph(filename.c_str());
}
void Character::setExp(int exp) {
	this->exp = exp;
}
char Character::getID() {
	return ID;
}
char Character::getLevel() {
	return level;
}
XY Character::getPosition() {
	return position;
}
char Character::getX() {
	return position.x;
}
char Character::getY() {
	return position.y;
}
void Character::disp(XY position) {
	DrawGraph(position.x, position.y, CharGraph, TRUE);
}
void Character::move(XY value) {
	position = position + value;
}