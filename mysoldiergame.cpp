/* File: soldier.cpp
 * Class: COP 3003
 * Dev: Ayleen Roque
 * Desc: Lab 1 for a soldier NPC AI demo if structs and enums
 */

#include <iostream> // console I/O
#include <cstdlib>  // random numbers
#include <ctime>    // random seed
#include "Character.h" // character class
#include <cmath> // math functions

// Constants & Types
//------------------------------------------------------------------
const int START_LEVEL_DIE = 6;
const int HIT_POINT_DIE = 20;
const int ENCOUNTER_DIE = 20;

enum SoldierMode { // enums are like integer constants
    HOMING,
    PATROLLING,
    ATTACKING,
    DEFENDING,
    RETREATING
};

// Function Prototypes
SoldierMode Homing(Character &soldier);
SoldierMode Patrolling(Character *& enemy, Character * soldier);
SoldierMode Attacking(Character *& enemy, Character * soldier);
SoldierMode Defending(Character *& enemy, Character * soldier);
SoldierMode Retreating(Character *& enemy, Character * soldier);

// Function Definitions

int main() {
    // init random numbers
    std::srand(std::time(NULL));

    int level = std::rand() % START_LEVEL_DIE + 1;
    int hitPoint = std::rand() % HIT_POINT_DIE + 1;

    Character soldier(level, hitPoint);

    soldier.setFullHealth();

    std::cout << "\nSoldier health: " << soldier.getHealth() << "\n hit Points " <<
              soldier.getHitPoint() << std::endl;

    Character * enemy = nullptr;

    std::cout << "\nEnemy health: " << enemy->getHealth() << "\n hit Points " <<
               enemy->getHitPoint() << std::endl;

    SoldierMode soldierMode = HOMING;

    // main game loop until soldier dies
    do {
        switch (soldierMode) {
            case HOMING:
                std::cout << "Homing" << std::endl;
                soldierMode = Homing(soldier);
                break;
            case PATROLLING:
                soldierMode = Patrolling(enemy, &soldier);
                break;
            case ATTACKING:
                soldierMode = Attacking(enemy, &soldier);
                break;
            case DEFENDING:
                soldierMode = Defending(enemy, &soldier);
                break;
            default: // RETREATING
                soldierMode = Retreating(enemy, &soldier);
                break;
        }
    }
    while (soldier.getHealth() > 0); // see if soldier is alive

    return 0;
}

/**
 * handle when soldier is at the fort
 * @param soldier - structure for the soldier
 * @return either HOMING or PATROLLING
 */
SoldierMode Homing(Character &soldier)
{
    SoldierMode retMode = HOMING;
    if (soldier.getHealth() == soldier.getLevel() * soldier.getHitPoint()) {
        std::cout << "\nSoldier is at full health" << std::endl;
        retMode = PATROLLING;
    } else {
        std::cout << "\nSoldier needs to heal" << std::endl;
        soldier.heal(soldier.getLevel()); // heal as much as level
    }
    return retMode;
} // end homing



/**
 * Soldier is on patrolling looking for enemies
 * @param enemy
 * @param soldier
 * @return respective mode (PATROLLING, HOMING, ATTACKING, DEFENDING, RETREATING)
 */
SoldierMode Patrolling(Character *& enemy, Character * soldier) {
    SoldierMode retMode = PATROLLING;
    if (soldier->getHealth() < soldier->isFullHealth()){
        soldier->heal(soldier->getLevel() + 5);
        std::cout << "\nSoldier is healing" << std::endl;
    }
    if (enemy->getHealth() == 0) {
        int enemyEncounter = std::rand() % ENCOUNTER_DIE + 1;

        if (enemyEncounter == 1) {
            int level = std::rand() % START_LEVEL_DIE + 1;
            enemy->setLevel(level);
            int hitPoint = std::rand() % HIT_POINT_DIE + 1;
            enemy->setHitPoint(hitPoint);
            enemy->setFullHealth();
            std::cout << "\nSoldier has encountered a " << enemy->getLevel() << " level enemy with "
                      << enemy->getHealth() << " health" << std::endl;
        } // end encounter check
        else {
            std::cout << "\nAll clear" << std::endl;
        }
    } // end no enemy
    else { // there is an enemy
        if (soldier->getHealth() > enemy->getHealth()) {
            std::cout << "\nNever should have come here!" << std::endl;
            retMode = ATTACKING;
        }
        else if (soldier->getHealth() < enemy->getHealth()){
            std::cout << "\nMercy!" << std::endl;
            retMode = RETREATING;
        }
        else {
            std::cout << "\nFor Skyrim!" << std::endl;
            retMode = DEFENDING;
        }
    }
    return retMode;
}

/**
 * handles soldier and enemy fighting
 * @param soldier - structure for the soldier
 * @param enemy - structure for the enemy
 * @return either HOMING, PATROLLING, DEFENDING
 */
void combatMode(Character * soldier, Character *& enemy) {
    SoldierMode retMode;
    srand(time(0));
    int damage = (rand() % 5 + 1); // damage
    int soldierHealth = soldier->getHealth();
    soldier->doesHitOccur();
    if (soldier->doesHitOccur() == true) {
        std::cout << "\nSoldier has taken a hit of " << damage << std::endl;
        soldierHealth -= damage;
        soldier->setHealth(soldierHealth);
        std::cout << "\nSoldier has current health of " << soldier->getHealth();
        if (soldier->getHealth() < 0){
            std::cout << "\nSoldier has died \nWe get a new soldier " << std::endl;
            retMode = HOMING;
        }
        else if (soldier->getHealth() == round((soldier->getHealth()/2))) { // health is equal to half of full health
            std::cout << "\nSoldier is losing, Defending" << std::endl;
            retMode = DEFENDING;
        }
    }
    int enemyHealth = enemy->getHealth();
    enemy->doesHitOccur();
    if (enemy->doesHitOccur() == true) {
        std::cout << "\nEnemy has taken a hit of " << damage << std::endl;
        enemyHealth -= damage;
        enemy->setHealth(enemyHealth);
        std::cout << "\nEnemy has current health of " << enemy->getHealth() << std::endl;
    }
    if (enemy->getHealth() <= 0){ // no enemy / dead enemy
        std::cout << "\nEnemy is killed, back to Patrolling" << std::endl;
        retMode = PATROLLING;
    }
}

/**
 * handle when soldier is attacking
 * @param soldier - structure for the soldier
 * @return either HOMING, PATROLLING OR DEFENDING
 */
SoldierMode Attacking(Character *& enemy, Character * soldier){
    SoldierMode retMode = ATTACKING;
    std::cout << "\nSoldier is Attacking" << std::endl;
    do {

        combatMode(soldier, enemy);
    }
    while ((enemy->getHealth() > 0) && (soldier->getHealth() > (soldier->getHealth()/2)));

    if (soldier->getHealth() < 0){
        retMode = HOMING;
    }
    else if (soldier->getHealth() < round((soldier->getHealth()/2))) {
        retMode = DEFENDING;
        enemy->heal(enemy->getLevel());
    }
    else if (enemy->getHealth() <= 0){
        retMode = PATROLLING;
    }
    else {
        std::cout << "No enemy around" << std::endl; // enemy check
        if (soldier->getHealth() < soldier->isFullHealth()){
            soldier->heal(soldier->getLevel());
            std::cout << "\nSoldier is healing" << std::endl;
        }
    }
    return retMode;
}

/**
 * handle when soldier is defending
 * @param soldier - structure for the soldier
 * @return either HOMING, PATROLLING or RETREATING
 */
SoldierMode Defending(Character *& enemy, Character * soldier) {
    SoldierMode retMode = DEFENDING;
    do {
        combatMode(soldier, enemy);
    } while ((enemy->getHealth() > 0) && (soldier->getHealth() > (soldier->getHealth()/2)));
    if (soldier->getHealth() < 0){ // if soldier is dead
        retMode = HOMING;
    }
    else if (soldier->getHealth() < (soldier->getHealth()/2)) { // if soldier health is less than half
        std::cout << "\nSoldier is retreating!" << std::endl;
        retMode = RETREATING;
        enemy->heal(enemy->getLevel());  // heal some
        soldier->heal(soldier->getLevel()); // heal some
        std::cout << "\nSoldier and enemy are healing" << std::endl;
    }
    else if (enemy->getHealth() <= 0){ // if enemy is dead
        retMode = PATROLLING;
    }

    return retMode;
}

/**
 * handle when soldier is retreating
 * @param soldier - structure for the soldier
 * @return either HOMING, PATROLLING, DEFENDING
 */
SoldierMode Retreating(Character *& enemy, Character * soldier) {
    SoldierMode retMode = RETREATING;
    do {
        combatMode(soldier, enemy);
    } while ((enemy->getHealth() > 0) && (soldier->getHealth() > (soldier->getHealth()/2)));
    if (soldier->getHealth() < 0){
        retMode = HOMING;
    }
    else if (soldier->getHealth() >= round((soldier->getHealth()/2))) { // if soldier health is equal/more than half
        std::cout << "\nSoldier is back to defending!" << std::endl;
        retMode = DEFENDING;
        enemy->heal(enemy->getLevel());
        soldier->heal(soldier->getLevel());
        std::cout << "\nSoldier and enemy are healing" << std::endl;
    }
    else if (enemy->getHealth() <= 0){ // if enemy is dead
        retMode = HOMING;
    }

    return retMode;
}