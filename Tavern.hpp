/*
Name: Kenneth Guillont
Email: Kenneth.guillont83@myhunter.cuny.edu
Professor: Dr. Tiziana Ligorio
Section: CSCI 23500-01

Algorithmic Adventures: 
Into the Recursive Realms

Project 4 - The Tainted Stew

Title: Tavern.hpp
*/
#ifndef TAVERN_
#define TAVERN_


#include "ArrayBag.hpp"
#include "Character.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

class Tavern : public ArrayBag<Character*> {
public:

    /** Parameterized Constructor **/
    Tavern(const std::string& input_file);
    

    /** 
        @param:   A reference to a Character entering the Tavern
        @return:  returns true if a Character was successfully added to items_, false otherwise
        @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
    **/
    bool enterTavern(Character* a_character);

    /** @param:   A reference to a Character leaving the Tavern  
        @return:  returns true if a character was successfully removed from items_, false otherwise
        @post:    removes the character from the Tavern and updates the level sum  and the enemy if the character is an enemy.
    **/
    bool exitTavern(Character* a_character);

   

    /** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int getLevelSum();


    /** 
        @return:  The average level of all the characters in the Tavern
        @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, 
                  and returns the integer value.
    **/
    int calculateAvgLevel();



    /** 
    @return:  The integer enemy count of the Tavern
    **/
    int getEnemyCount();

    /** 
        @return:  The percentage (double) of all the enemy characters in the Tavern
        @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, 
                 and returns the double value.
    **/
    double calculateEnemyPercentage();



    /** @param:   A string reference to a race 
        @return:  An integer tally of the number of characters in the Tavern of the given race
    **/
    int tallyRace(const std::string &race);




    /**
      @post:    Outputs a report of the characters currently in the tavern in the form:
      "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n"
      Note that the average level should be rounded to the NEAREST integer, and the enemy percentage should be rounded to 2 decimal

      Example output: 
      Humans: 3
      Elves: 5
      Dwarves: 8
      Lizards: 6
      Undead: 0

      The average level is: 7
      46.67% are enemies.
    */
    void tavernReport();

    /**
        @post: For every character in the tavern, displays each character's information
    */
    void displayCharacters() const;

    /**
        @param: a string reference to a race
        @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information
    */
    void displayRace(const std::string& race) const;

    /**
        @post: Every character in the tavern eats a tainted stew.
    */
    void taintedStew();


  private:
    int level_sum_; // An integer sum of the levels of all the characters currently in the tavern
    int num_enemies_; //number of enemies currently in the Tavern

};
#endif
