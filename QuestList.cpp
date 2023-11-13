/*
Kenneth Guillont
Profoessor Ligorio
CSCI 235 Fall 2023

Algorithmic Adventures: 
Into the Recursive Realms

Project 5  - Quest Management with Doubly Linked Lists

Questline.cpp
*/

#include "QuestList.hpp"
#include <fstream>
#include <sstream>

/**
        Default Constructor
        @post: Creates a new Quest object with default values (zero-initialized)
*/
Quest::Quest()
    : completed_(false), experience_points_(0) {}

/*
    @param: A reference to string reference to a quest title
    @param: A reference to string reference to a quest description
    @param: A reference to boolean representing if the quest is completed
    @param: An reference to int indicating the experience points
    @param: A reference to vector of Quest pointers representing the quest's dependencies
    @param: A reference to vector of Quest pointers representing the quest's subquests
    @post: Creates a new Quest object with the given parameters
*/
Quest::Quest(const std::string &title, const std::string &description, bool completed, int experience_points,
             const std::vector<Quest *> &dependencies, const std::vector<Quest *> &subquests)
    : title_(title), description_(description), completed_(completed),
      experience_points_(experience_points), dependencies_(dependencies), subquests_(subquests) {}

/**
    Default Constructor
*/
QuestList::QuestList() {}

/**
    @param: a reference to string name of an input file
    @pre: Formatting of the csv file is as follows:
        Title: A string
        Description: A string
        Completion Status: 0 (False) or 1 (True)
        Experience Points: A non negative integer
        Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
        Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The dependencies and subquests are separated by a semicolon and may be NONE.
        - The dependencies and subquests may be in any order.
        - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
            - Title: The title of the quest
            - Description: "NOT DISCOVERED"
            - Completion Status: False
            - Experience Points: 0
            - Dependencies: An empty vector
            - Subquests: An empty vector
        - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
        Hint: update as needed using addQuest()
        

    @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

*/
QuestList::QuestList(const std::string &filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Skip header

        while (std::getline(file, line)) {
            // Parse quest information from the line
            std::stringstream ss(line);
            std::string title, description, completionStatus, experiencePoints, dependencies, subquests;
            std::getline(ss, title, ',');
            std::getline(ss, description, ',');
            std::getline(ss, completionStatus, ',');
            std::getline(ss, experiencePoints, ',');
            std::getline(ss, dependencies, ',');
            std::getline(ss, subquests, ',');

            bool completed = (completionStatus == "1");
            int expPoints = std::stoi(experiencePoints);

            // Create a new quest and add it to the list
            Quest quest(title, description, completed, expPoints, {}, {});
            addQuest(&quest);
        }

        file.close();
    } 
}

/**
    @param: A string reference to a quest title
    @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
*/
int QuestList::getPosOf(const std::string &quest_title) const
{
    Node<Quest*>* current = first_;
    int position = 0;

    while (current != nullptr)
    {
        if (current->getItem()->title_ == quest_title)
        {
            return position;
        }
        current = current->getNext();
        position++;
    }

    return -1;
}

/**
    @param: A string reference to a quest title
    @return: True if the quest with the given title is already in the QuestList
*/
bool QuestList::contains(const std::string &quest_title) const
{
    return getPosOf(quest_title) != -1;
}

/**
    @pre: The given quest is not already in the QuestList
    @param:  A pointer to a Quest object
    @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
           
    @return: True if the quest was added or updated successfully, False otherwise
*/
bool QuestList::addQuest(const Quest *quest)
{
    if (contains(quest->title_))
    {
        Node<Quest*>* current = first_;
        while (current != nullptr)
        {
            if (current->getItem()->title_ == quest->title_)
            {
                // Update the quest details, including the completed_ field
                current->getItem()->title_ = quest->title_;
                current->getItem()->description_ = quest->description_;
                current->getItem()->completed_ = quest->completed_;
                current->getItem()->experience_points_ = quest->experience_points_;
                current->getItem()->dependencies_ = quest->dependencies_;
                current->getItem()->subquests_ = quest->subquests_;

                return true;
            }
            current = current->getNext();
        }
    }

    else
    {
        Quest* newQuest = new Quest(*quest);
        insert(getLength(), newQuest);  

        for (Quest *dep_quest : newQuest->dependencies_)
        {
            addQuest(dep_quest);
        }

        for (Quest *subquest : newQuest->subquests_)
        {
            addQuest(subquest);
        }

        return true;
    }

    return false;
}

/**
    @param:  A reference to string representing the quest title
    @param:  A reference to string representing the quest description
    @param:  A reference to boolean representing if the quest is completed
    @param:  An reference to int representing experience points the quest rewards upon completion 
    @param:  A reference to vector of Quest pointers representing the quest's dependencies
    @param:  A reference to vector of Quest pointers representing the quest's subquests
    @post:   Creates a new Quest object and inserts a pointer to it into the QuestList. 
             If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
             Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
             

    @return: True if the quest was added or updated successfully, False otherwise

*/
bool QuestList::addQuest(const std::string &title, const std::string &description,
                          const bool &completed, const int &experience_points,
                         const std::vector<Quest *> &dependencies,
                         const std::vector<Quest *> &subquests)
{
    Quest newQuest(title, description, completed, experience_points, dependencies, subquests);
    return addQuest(&newQuest);
}

/**
    @param:  A Quest pointer
    @return: A boolean indicating if all the given quest's dependencies are completed
*/
bool QuestList::dependenciesComplete(const Quest *quest) const
{
    for (const Quest *dependency : quest->dependencies_)
    {
        if (!dependency->completed_)
        {
            return false;
        }
    }
    return true;
}

/**
    @param: A Quest pointer
    @return: A boolean if the given quest is available.
    Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
*/

bool QuestList::questAvailable(const Quest *quest) const
{
    return !quest->completed_ && dependenciesComplete(quest);
}

/**
    @param: A Quest pointer
    @post: Prints the quest title and completion status
    The output should be of the form:
    [Quest Title]: [Complete / Not Complete]
    [Quest Description]\n\n
*/
void QuestList::printQuest(const Quest *quest) const
{
    std::cout << quest->title_ << ": " << (quest->completed_ ? "Complete" : "Not Complete") << "\n";
    std::cout << quest->description_ << "\n\n";
}

/**
    @param: A string reference to a quest title
    @post:  Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
            If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests. 
            The indentation for incomplete quests is 2 spaces: "  "    
            The format of the list should be of the following forms for each different case:

            Query: [Quest Title]
            No such quest.
    
            Query: [Quest Title]
            Quest Complete
    
            Query: [Quest Title]
            Ready: [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
              [Quest Title]
            
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Dependency2]
              [Quest Title]
              
     If the given quest title is not found in the list, print "No such quest."
*/
void QuestList::questQuery(const std::string &quest_title) const
{
    std::cout << "Query: " << quest_title << "\n";

    int pos = getPosOf(quest_title);
    if (pos == -1)
    {
        std::cout << "No such quest.\n";
    }
    else
    {
        Node<Quest*>* current = first_;
        while (current != nullptr)
        {
            if (current->getItem()->title_ == quest_title)
            {
                if (current->getItem()->completed_)
                {
                    std::cout << "Quest Complete\n";
                }
                else if (dependenciesComplete(current->getItem()))
                {
                    std::cout << "Ready: " << quest_title << "\n";
                }
                else
                {
                    std::cout << "Not Ready: " << quest_title << "\n";

                    // Print out incomplete dependencies
                    for (const Quest *dependency : current->getItem()->dependencies_)
                    {
                        if (!dependency->completed_)
                        {
                            std::cout << "  Not Ready: " << dependency->title_ << "\n";
                        }
                    }
                }
                break;
            }
            current = current->getNext();
        }
    }
}


/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
int QuestList::calculateGainedExperience() const
{
    int total_experience = 0;
    Node<Quest*>* current = first_;

    while (current != nullptr)
    {
        if (current->getItem()->completed_)
        {
            total_experience += current->getItem()->experience_points_;
        }
        current = current->getNext();
    }

    return total_experience;
}


/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
    Note: Also consider the experience gained if a completed subquest itself has subquests.  
*/
int QuestList::calculatePathwayExperience(const Quest *main_quest) const
{
    int total_experience = 0;

    for (const Quest *subquest : main_quest->subquests_)
    {
        total_experience += calculatePathwayExperience(subquest);
    }

    if (main_quest->completed_)
    {
        for (const Quest *subquest : main_quest->subquests_)
        {
            total_experience += calculateGainedExperience();
        }
    }

    return total_experience;
}


/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
    Note: Also consider the potential experience if a subquest itself has subquests.
*/
int QuestList::calculateProjectedExperience(const Quest *main_quest) const
{
    int total_experience = 0;

    total_experience += calculatePathwayExperience(main_quest);

    return total_experience;
}

/**
    @param: A string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every quest in the list.
           With filter "COMPLETE":   Only print out the completed quests in the list.
           With filter "INCOMPLETE": Only print out the incomplete quests in the list.
           With filter "AVAILABLE":  Only print out the available quests in the list.
           If an invalid filter is passed, print "Invalid Filter\n"
    Printing quests should be of the form:
    [Quest title]: [Complete / Not Complete]  
    [Quest description]\n
*/
void QuestList::questHistory(const std::string &filter) const
{
    Node<Quest*>* current = first_;

    while (current != nullptr)
    {
        bool print_quest = false;

        if (filter == "COMPLETE" && current->getItem()->completed_)
        {
            print_quest = true;
        }
        else if (filter == "INCOMPLETE" && !current->getItem()->completed_)
        {
            print_quest = true;
        }
        else if (filter == "AVAILABLE" && questAvailable(current->getItem()))
        {
            print_quest = true;
        }
        else if (filter == "NONE")
        {
            print_quest = true;
        }

        if (print_quest)
        {
            printQuest(current->getItem());
        }

        current = current->getNext();
    }

    if (filter != "COMPLETE" && filter != "INCOMPLETE" && filter != "AVAILABLE" && filter != "NONE")
    {
        std::cout << "Invalid Filter\n";
    }
}

/**
    @param: A quest pointer representing the main quest for which the subquests pathway is printed.
    @param: An integer indicating the level of indentation for formatting.
    @post: Outputs the subquest pathway, displaying quest names with two spaces ("  ") of indentation for each subquest, printed recursively.
           Additionally, prints the percentage of experience gained in this pathway, rounded down to the lower integer.
           The format follows:
           [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
               [Subquest0]: [Complete / Not Complete]
                   [Sub-Subquest01]: [Complete / Not Complete]
                       [Sub-Subquest011]: [Complete / Not Complete]
                   [Subquest02]: [Complete / Not Complete]
*/
void QuestList::subquestsRecursive(const Quest *quest, int indentation) const
{
    for (const Quest *subquest : quest->subquests_)
    {
        for (int i = 0; i < indentation; ++i)
        {
            std::cout << "  ";
        }

        std::cout << subquest->title_ << ": " << (subquest->completed_ ? "Complete" : "Not Complete") << "\n";

        // Recursively print subquests
        subquestsRecursive(subquest, indentation + 1);
    }
}



/**
    @param: A quest pointer to a main quest
    @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
            Also print the percentage of experience gained in this pathway, rounded down to the lower integer.
            The format should be of the form:
            [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
                [Subquest0]: [Complete / Not Complete]
                    [Sub-Subquest01]: [Complete / Not Complete]
                        [Sub-Subquest011]: [Complete / Not Complete]
                    [Subquest02]: [Complete / Not Complete]
            Hint: You can write a helper function to print the subquests recursively. If the given quest is already marked as completed, you can assume that all of its subquests are also completed.
*/
void QuestList::printQuestDetails(const Quest *main_quest) const
{
    int projectedExperience = calculateProjectedExperience(main_quest);
    int pathwayExperience = calculatePathwayExperience(main_quest);

    int completionPercentage = (projectedExperience > 0) ? (pathwayExperience * 100 / projectedExperience) : 0;

    std::cout << main_quest->title_ << " (" << completionPercentage << "% Complete)\n";

    subquestsRecursive(main_quest, 1);

    std::cout << std::endl;
}
