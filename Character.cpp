/* File: Character.cpp
 * Class: COP 3003
 * Dev: Ayleen Roque
 * Desc: Implementation of a Character class object
 */
//------------------------------------------------------------------

#include "Character.h"
#include <ctime>    // random seed
#include <cstdlib>  // random numbers

// Constructors
//--------------------------------------------------------------
Character::Character(){
    level = 0;
    hitPoint = 0;
    health = 0;
} // default constructor

Character::Character(int level, int hitPoint){
    this->level = level;
    this->hitPoint = hitPoint;
    this->health = health;
} // property constructor

// Accessors and setters
//--------------------------------------------------------------
int Character::getLevel(){return level; }
void Character::setLevel(int value){
    level = value; }

int Character::getHitPoint(){
    return hitPoint; }
void Character::setHitPoint(int value){
    hitPoint = value; }

int Character::getHealth(){
    return health; } // user will never input the health
int Character::setHealth(int value) {
    health = value;
}

// Methods
//--------------------------------------------------------------
void Character::setFullHealth() {
    health = level * hitPoint;
}

bool Character::isFullHealth() {
    return health == level * hitPoint;
}

void Character::heal(int health) {
    this->health += health;
}

void Character::takeDamage(int damage) {
    health -= damage;
}

bool Character::doesHitOccur() {
    int getHit;
    srand(time(0));
    getHit = (rand() % 6 + 1);
    if (getHit == 1){
        return true;
    }
    else {
        return false;
    }
}