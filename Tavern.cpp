/*
Name: Kenneth Guillont
Email: Kenneth.guillont83@myhunter.cuny.edu
Professor: Dr. Tiziana Ligorio
Section: CSCI 23500-01

Algorithmic Adventures: 
Into the Recursive Realms

Project 4 - The Tainted Stew

Title: Tavern.cpp
*/
#include "Tavern.hpp"
#include "Mage.hpp"
#include "Ranger.hpp"
#include "Scoundrel.hpp"
#include "Barbarian.hpp"
#include <fstream>
#include <sstream>
#include <string>


Tavern::Tavern(const std::string& file_name) {
  std::ifstream fin(file_name);

  std::string junk = "";
  std::string empty_str = "";
  std::string s[14];
  std::getline(fin, junk);
  
  while(std::getline(fin, empty_str)) {
    std::stringstream readeachline(empty_str);
    for(int i = 0; i < 14; i++) {
      std::getline(readeachline, s[i], ',');
    }
    int level = std::stoi(s[3]);
    int vitality = std::stoi(s[4]);
    int armor = std::stoi(s[5]);
    int enemy = std::stoi(s[6]);
    int summon = std::stoi(s[7]);
    int disguise = std::stoi(s[8]);
    int enrage = std::stoi(s[13]);

    if(s[2] == "BARBARIAN"){
      Barbarian* barbarian = new Barbarian(s[0], s[1], vitality, armor, level, enemy, s[7], s[8],enrage);
      enterTavern(barbarian);
    }
    else if(s[2] == "MAGE"){
      Mage* mage = new Mage(s[0], s[1], vitality, armor, level, enemy, s[9], s[7], summon);
    }
    else if(s[2] == "SCOUNDREL"){
      Scoundrel* scoundrel = new Scoundrel(s[0], s[1], vitality, armor, level, enemy, s[7], s[9], disguise);
    }
    else if(s[2] == "RANGER")
    {
      std::vector<Arrows> arrows = {};
      std::vector<std::string> affinities = {};

      while(std::getline(readeachline, s[7], ';'))
      {
        std::stringstream parsed_str(s[7]);
        for(int i = 0; i < 2; i++)
        {
          std::getline(parsed_str, s[i], ';');
        }
        int quantity = std::stoi(s[1]);
      }
      Ranger* ranger = new Ranger(s[0], s[1], vitality, armor, level, enemy, arrows, affinities);
      enterTavern(ranger);
      for(int i = 0; i < arrows.size(); i++)
      {
        arrows.pop_back();
      }
      for(int i = 0; i < affinities.size(); i++)
      {
        affinities.pop_back();
      }
    }
  }
}


  /** 
      @param:   A reference to a Character entering the Tavern
      @return:  returns true if a Character was successfully added to items_, false otherwise
      @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
  **/
  bool Tavern::enterTavern( Character* a_character)
  {
    if(add(a_character))
    {
      level_sum_ += a_character->getLevel();
      if(a_character->isEnemy())
        num_enemies_++;
      
      return true;
    }
    else
    {
      return false;
    }
  }

  /** @param:   A reference to a Character leaving the Tavern  
      @return:  returns true if a character was successfully removed from items_, false otherwise
      @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
  **/
  bool Tavern::exitTavern( Character* a_character)
  {
    if(remove(a_character))
    {
      level_sum_ -= a_character->getLevel();
      if(a_character->isEnemy())
        num_enemies_--;
        
      return true;
    }
    return false;
  }
/** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int Tavern::getLevelSum()
    {
      return level_sum_;
    }



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 
    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0;
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index]->getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}

/**
    @post: For every character in the tavern, displays each character's information
*/
void Tavern::displayCharacters() const {
    for (int i = 0; i < item_count_; i++) {
        items_[i]->display();
    }
}

/**
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information
*/
void Tavern::displayRace(const std::string& race) const{
    for (int i = 0; i < item_count_; i++) {
        if (items_[i]->getRace() == race) {
            items_[i]->display();
        }
    }
}

/**
    @post: Every character in the tavern eats a tainted stew.
*/
void Tavern::taintedStew() {
    for (int i = 0; i < item_count_; i++) {
        items_[i]->eatTaintedStew();
    }
}