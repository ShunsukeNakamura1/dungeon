#pragma once
#include "Character.h"

/* struct Character */
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
	return (char)position.x;
}
char Character::getY() {
	return (char)position.y;
}
void Character::disp(XY position) {
	DrawGraph(position.x, position.y, CharGraph, TRUE);
}
void Character::move(XY value) {
	position = position + value;
}

/* struct Object */
void Object::setID(int ID) {
	this->ID = ID;
}
void Object::setPosition(XY position) {
	this->position = position;
}
void Object::loadGraph(std::string filename) {
	this->CharGraph = LoadGraph(filename.c_str());
}
int Object::getID() {
	return ID;
}
XY Object::getPosition() {
	return position;
}
char Object::getX() {
	return (char)position.x;
}
char Object::getY() {
	return (char)position.y;
}
void Object::disp(XY position) {
	DrawGraph(position.x, position.y, CharGraph, TRUE);
}