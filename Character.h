/* File: Character.h
 * Class: COP 3003
 * Dev: Ayleen Roque
 * Desc: Declaration of a Character class object
 */
//------------------------------------------------------------------
// HEADER GUARD
#ifndef SOLDIERGAME_CHARACTER_H
#define SOLDIERGAME_CHARACTER_H

class Character {
private:
    int level;
    int hitPoint;
    int health;
public:
    // Constructors
    //--------------------------------------------------------------
    Character(); // default constructor

    Character(int level, int hitPoint); // property constructor

    // Accessors
    //--------------------------------------------------------------
    int getLevel();
    void setLevel(int value);

    int getHitPoint();
    void setHitPoint(int value);

    int getHealth();
    int setHealth(int value);

    // Methods
    //--------------------------------------------------------------
    void setFullHealth();
    bool isFullHealth();
    void heal(int health);
    void takeDamage(int damage);
    bool doesHitOccur();
};

#endif //SOLDIERGAME_CHARACTER_H
