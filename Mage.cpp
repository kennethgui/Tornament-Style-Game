/*
Name: Kenneth Guillont
Email: Kenneth.guillont83@myhunter.cuny.edu
Professor: Dr. Tiziana Ligorio
Section: CSCI 23500-01

Algorithmic Adventures: 
Into the Recursive Realms

Project 4 - The Tainted Stew

Title: Mage.cpp
*/

#include "Mage.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
    Default character name: "NAMELESS". Booleans are default-initialized to False. 
    Default school of magic and weapon: "NONE". 
*/
Mage::Mage() : Character(), school_of_magic_{"NONE"}, weapon_{"NONE"}, can_summon_incarnate_{false}
{
}

/**
    Parameterized constructor.
    @param      : The name of the character (a string)
    @param      : The race of the character (a const string reference)
    @param      : The character's vitality (an integer)
    @param      : The character's max armor level (an integer)
    @param      : The character's level (an integer)
    @param      : A flag indicating whether the character is an enemy
    @param      : The character's school of magic (a string). Valid schools: [ELEMENTAL, NECROMANCY, ILLUSION]. 
                 String inputs can be in lowercase, but must be converted to uppercase when setting the variable.
                 If the school name is invalid, set it to "NONE"
    @param      : The character's choice of weapon (a string). Valid weapons: [WAND, STAFF]
                  String inputs can be in lowercase, but must be converted to 
				  uppercase when setting the variable.
				  If the weapon is invalid, set it to "NONE"
    @param      : A flag indicating whether the character is able to summon an incarnate
    @post       : The private members are set to the values of the corresponding parameters.
                  If the school of magic or weapon is not provided or valid, the variables should be set to "NONE". 
*/
Mage::Mage(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, const std::string& school_of_magic, const std::string& weapon, bool can_summon_incarnate) 
: Character(name, race, vitality, armor, level, enemy), can_summon_incarnate_{can_summon_incarnate}
{
    if (!setSchool(school_of_magic))
    {
        school_of_magic_ = "NONE";
    }
    if(!setCastingWeapon(weapon))
    {
        weapon_ = "NONE";
    }
}

/**
    @param  : a reference to a string representing the school of magic
    @post   : sets the private member variable to the value of the parameter. 
              If the provided school of magic is not one of the following: [ELEMENTAL, NECROMANCY, ILLUSION], 
              do nothing and return false.
              String inputs can be in lowercase, but must be converted to uppercase when setting the variable.
    @return  : true if setting the variable was successful, false otherwise.
**/
bool Mage::setSchool(const std::string& school_of_magic)
{
    std::string school_upper = school_of_magic;
    for(int i = 0;i<school_of_magic.size();i++)
    {
        if(isalpha(school_of_magic[i]))
        {
            school_upper[i] = toupper(school_of_magic[i]); 
        }
    }
    if(school_upper == "ELEMENTAL" || school_upper == "NECROMANCY" || school_upper == "ILLUSION")
    {
        school_of_magic_ = school_upper;
        return true;
    }
    else
    {
        return false;
    }
}


/**
    @return  : the string indicating the character's school of magic
**/
std::string Mage::getSchool() const
{
    return school_of_magic_;
}


/**
    @param  : a reference to a string representing the character's weapon
    @post   : sets the private member variable to the value of the parameter. 
              String inputs can be in lowercase, but must be converted to uppercase when setting the variable.
              If the provided weapon is not one of the following: [WAND, STAFF], do nothing and return false.
    @return  : true if setting the variable was successful, false otherwise.
**/
bool Mage::setCastingWeapon(const std::string& weapon)
{
    std::string weapon_upper = weapon;
    for(int i = 0;i<weapon.size();i++)
    {
        if(isalpha(weapon[i]))
        {
            weapon_upper[i] = toupper(weapon[i]); 
        }
    }
    if(weapon_upper == "WAND" || weapon_upper == "STAFF")
    {
        weapon_ = weapon_upper;
        return true;
    }
    else
    {
        return false;
    }
}


/**
    @return  : the string indicating the character's weapon
**/
std::string Mage::getCastingWeapon() const
{
    return weapon_;
}

/**
    @param  : a reference to boolean
    @post   : sets the private member variable indicating whether the character can summon an incarnate
**/
void Mage::setIncarnateSummon(const bool& can_summon_incarnate)
{
    can_summon_incarnate_ = can_summon_incarnate;
}

/**
    @return  : the summon-incarnate flag
**/
bool Mage::hasIncarnateSummon() const
{
    return can_summon_incarnate_;
}

void Mage::display() const
{
    std::string enemyStatus = isEnemy() ? "an enemy." : "not an enemy.";
    std::string incarnateStatus = can_summon_incarnate_ ? "can summon an Incarnate." : "cannot summon an Incarnate.";

    std::cout << getName() << " is a Level " << getLevel() << " " << getRace() << " MAGE." << std::endl;
    std::cout << "Vitality: " << getVitality() << std::endl;
    std::cout << "Armor: " << getArmor() << std::endl;
    std::cout << "They are " << enemyStatus << "." << std::endl;
    std::cout << "School of Magic: " << school_of_magic_ << std::endl;
    std::cout << "Weapon: " << weapon_ << std::endl;
    std::cout << incarnateStatus << std::endl;
    std::cout << std::endl;
}

void Mage::eatTaintedStew()
{
    if (getRace() == "UNDEAD")
    {
        setVitality(getVitality() + 3);
    }
    else
    {
        setVitality(1);

        if (weapon_ == "WAND")
        {
            setVitality(getVitality() + 2);
        }
        else if (weapon_ == "STAFF")
        {
            setVitality(getVitality() + 3);
        }

        if (can_summon_incarnate_)
        {
            setVitality(getVitality() + 1);
        }
    }
}