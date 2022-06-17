#include <vector> 
#include "addrBookExc.h"

struct menuEntry {
    std::string text;
    char key;
};

class Menu {
    std::string title;
    std::vector<menuEntry> options;

    /**validate - check to see if the user choice is valid or not
     * char option- user enter option
     * return void
     * Algorithm - use try/catch block to check for user choice
     * in try, loop through the vectors of options avail and check to see if the user correct or not
     * if yes, return else, throw the error using exception class
     * In catch, cout error and use what() to display the error and rethrow
    */
    void validate(char option) {
        try {
            for(unsigned int i=0; i < options.size(); i++) {
                if(options[i].key == option) {
                    return;
                }
            }
            throw addrBookExc("invalid menu entry");
        }
        catch(addrBookExc& WrongOption) {
            std::cout << std::endl <<  "ERROR: " << WrongOption.what() << std::endl;
            throw WrongOption;
        }   
    }
    public:
    /**Menu - constructor to set title
     * string title- user title
     * Algo - set the title to title var
    */
    Menu(std::string title) {
        this->title = title;
    }

    /**add - add options into menu
     * string option_text - to add title of options
     * char- key to add key of options
     * return void
     * Algo - create new obj and use it to access priv mem and set value
     * then use options vec to push that obj
    */
    void add(std::string option_text, char key) {
        menuEntry temp;
        temp.key = key;
        temp.text = option_text;
        options.push_back(temp);
    }

    /**DisplayandRead - display the menu and read user choice
     * return char
     * Algo - loop until correct
     * use try and catch to test
     * in try, display the menu and all options and ask for user input
     * call validate() for user choice and if correct, convert to lower capand return it
     * also set the flag to truth to break the loop
     * In catch, cout error
    */
    char displayAndRead() {
        char UserChoice;
        bool CorrectChoice = false;
        char Correct = '\0';

        while(!CorrectChoice){
            try{
                std::cout << std::endl;
                std::cout << title << std::endl;
                std::cout << "===============" << std::endl;
                for(unsigned int i = 0; i < options.size(); i++){
                    std::cout << options[i].text << '\t' << '(' << options[i].key << ')' << std::endl;
                }
                std::cout << std::endl;

                std::cout << "Choice: ";
                std::cin >> UserChoice;
                std::cout << std::endl;
                
                validate(UserChoice);

                CorrectChoice = true;
                Correct = tolower(UserChoice);
                return Correct;
            }
            catch(...){
                std::cout << "try again \n";
            }
        }
        exit(0);
    }
};
