//
// Created by mig90 on 11/29/2023.
//
#include "story.h"

using namespace std;

class uiElement {

public:
    string dialog[4];
    //static string choice1;
    //static string choice2;
    //static string choice3;
    string savefileName;

    int chapterNum;
    int pageNum;
    bool programLoop = true;
    bool gameplayLoop = true;
    static int superGoodNumber;
    uiElement() {
        chapterNum = 0;
        pageNum = 0;
        savefileName = "saveFile0";
    }


    virtual void displayInfo() {
        //cout << "this is the dialog box \n";
    }
    virtual void decisionMaker() {
        //cout << "this will eventually intake a decision after \n";
    }


};

// Derived class
class Player : public uiElement {
private:
    string name;
public:
    vector<string> inventory;
    //Player(vector<string> items){
    //    inventory = items;
    //}
    //vector<string> inventory;

    void displayInfo() { //override
        cout << name << ": this might display name? \n";
    }
    bool checkInventory(string desiredItem) {
        //string currentItem;
        for(int i = 0; i < inventory.size(); i++) {
            if (inventory[i] == desiredItem) {
                return true;
            }
        }
        return false;
    }
    string getInventory(){
        stringstream outputStr;
        for(int i = 0; i < inventory.size(); i++) {
            outputStr << inventory[i] << "\n";
        }
        return outputStr.str();
    }
};

// Derived class
class Dialog1 : public uiElement {
private:
public:
    //Dialog1(int chapter, int page){
    //chapterNum = chapter;
    //pageNum = page;
//}
    int decisiontree[21][4] =
            {
                    {22,1,2,0},
                    {22,4,5,0},
                    {22,1,3,0},
                    {22,15,14,0},
                    {22,8,7,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0},
                    {22,0,0,0}
            };
    vector<string> *inventoryPtr;

    bool dialogCheckInventory(string desiredItem) {
        if (inventoryPtr == nullptr) {
            return false; // REMEMBER TO PUT EXCEPTION HANDLING HERE
        }
        for (int i = 0; i < inventoryPtr->size(); i++) {
            if (inventoryPtr->operator[](i) == desiredItem) {
                return true;
            }
        }
        return false;
    }
    void dialogAddToInventory(string item) {
        inventoryPtr->push_back(item);
    }



    void displayInfo() { //override
        //I may turn this into "string displayInfo" instead of void
        // but the idea is a stringstream is created and then somehow
        // the output of that can be used in the UI
        //cout << "this is the dialog text \n";
        //stringstream dstream;
        switch(pageNum){
            case 0:
                dialog[0] = "You are at the enterance to a cave. \n"
                            "What will you do?\n";
                dialog[1] = "1. not enter cave \n";
                dialog[2] = "2. enter cave \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 1:
                dialog[0] = "You realize that entering the cave was a\n"
                            "silly idea. You start to walk back the path you\n"
                            "came but you reach see a cool secret passage \n"
                            "to your right you didn't see before.. \n";
                dialog[1] = "1. ignore it and keep going forward \n";
                dialog[2] = "2. investigate because it's cool \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 2:
                dialog[0] = "You have stepped foot inside the cave. \n"
                            "You realize it's real dark and scary in here. \n";
                dialog[1] = "1. change your mind and leave the cave \n";
                dialog[2] = "2. march on forward \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 3:
                dialog[0] = "Being the brave soul you are, you keep\n"
                            "marching into the cave. after a while you encounter\n"
                            "a crate of abandoned supplies \n";
                dialog[1] = "1. Ignore it \n";
                dialog[2] = "2. investigate \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 4:
                dialog[0] = "That path just looked way too suspicous\n"
                            "to go on without any knowledge of where it goes.\n"
                            "You reach a fork in he road and remeber that if\n"
                            "you go right there is supposed to be a shortcut\n"
                            "back to your house, on the other hand the path\n"
                            "on the left is the path you've always taken back to \n"
                            "your house. What will you do? \n";
                dialog[1] = "1. Go left (trusty ol road) \n";
                dialog[2] = "2. Go right (new fancy shortcut?) \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 5:
                dialog[0] = "This path is pretty strange but along\n"
                            "the way you find this cool looking key.\n"
                            "You wonder if you should take it. \n";
                dialog[1] = "1. Take it \n";
                dialog[2] = "2. Don't take it \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 6:
                dialog[0] = "The path you were walking on seems to\n"
                            "connect to a different more well traveled path.\n"
                            "It looks like the path you heard might be a\n"
                            "shortcut to your house.. \n";
                dialog[1] = "1. Continue on \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 7:
                dialog[0] = "This path isn't really interesting nor\n"
                            "are there any special landmarks to talk about. \n";
                dialog[1] = "1. Continue on \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 8:
                dialog[0] = "\"If it ain't broke, dont fix it!\" is\n"
                            "what you think to yourself, theres no\n"
                            "harm in trusting in the path you've always known. \n";
                dialog[1] = "1. look left and appriciate that cool tree you always pass by \n";
                dialog[2] = "2. look right and admire the frog that has found it's way there \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 9:
                dialog[0] = "You feel like you're getting closer \n"
                            "to your house, and faster that usual. \n";
                dialog[1] = "1. It's boring i probably won't take it again \n";
                dialog[2] = "2. I'll definitely using this path again \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 10:
                dialog[0] = "You encounter a strange box with a lock on it\n"
                            "What will you do with it? \n";
                dialog[1] = "1. ignore it \n";
                dialog[2] = "2. ive yet to impliment something here lol \n";
                if (dialogCheckInventory("key")) {
                    dialog[3] = "3. Use the key you found!\n";
                } else {dialog[3] ="NA\n";}
                break;
            case 11:
                dialog[0] = "You realize you don't even have any way\n"
                            "to even open the box so you ignore it\n"
                            "and continue on your way. By the looks of it \n"
                            "this shortcut does does actually seem to\n"
                            "be quicker. \n";
                dialog[1] = "1. oh well \n";
                dialog[2] = "NA \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 12:
                dialog[0] = "Realizing you have a key you put\n"
                            "it in the lock. It fits! After unlocking\n"
                            "the box you realize there's literally nothing \n"
                            "in there but at the very least you now \n"
                            "have a new cool box \n";
                dialog[1] = "1. Walk back with your new cool box \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 13:
                dialog[0] = "You eventually keep walking untill you have\n"
                            "made it home. It was a nice day for a walk\n"
                            "You're thirsty for a nice warm drink,\n"
                            "and think to yourself:\n";
                dialog[1] = "1. \"I could really go for some tea right now\" \n";
                dialog[2] = "2. \"I could really go for some coffee right now\" \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 14:
                dialog[0] = "You find a spool of rope in the supplies\n"
                            "- rope has been added to your inventory - \n";
                dialog[1] = "1. continue \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 15:
                dialog[0] = "You keep walking and realize it's\n"
                            "strangly light in here, maybe it has\n"
                            "something to do with these cool glowing rocks\n";
                dialog[1] = "1. that's cool \n";
                dialog[2] = "2. thats interesting \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 16:
                dialog[0] = "You encounter what looks like a broken\n"
                            "bridge. Theres a lot of stalactites too.\n"
                            "You're starting to think there might be a way across \n";
                dialog[1] = "1. ignore the not-bridge \n";
                dialog[2] = "2. JUMP ACROSS \n";
                if (dialogCheckInventory("rope")) {
                    dialog[3] = "3. Use the rope you found!\n";
                } else {dialog[3] ="NA\n";}
                break;
            case 17:
                dialog[0] = "After deciding to not make the stupid \n"
                            "decision to cross the giant gap you turn around and find a \n"
                            "turtle waiting to be rescued. You take the turtle \n"
                            "with you as you head back home.\n"
                            "The turtle will be forever greatful. \n";
                dialog[1] = "1. continue \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 18:
                dialog[0] = "You attempt to jump across the giant gap\n"
                            "but you fall to your death because there was\n"
                            "no way you were ever going to jump\n"
                            "that far. what are you final thoughts? \n";
                dialog[1] = "1. man that sucks \n";
                if (dialogCheckInventory("bubble gum")) {
                    dialog[2] = "2. at least I have my bubble gum\n";
                } else {dialog[2] ="NA\n";}
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 19:
                dialog[0] = "After retrieving the rope you found, you manage \n"
                            "to swing across indiana jones-style using \n"
                            "the rope you found. on the other side You have found \n"
                            "a treasure chest thats full of gold and rare gems!\n";
                dialog[1] = "1. incredible \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 20:
                dialog[0] = "THE END\n"
                            "\n"
                            "Thank you for playing my game \n";
                dialog[1] = "1. exit game \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            default:
                dialog[0] = "ERROR\n"
                            "\n"
                            "we've encounter an error in displaying\n"
                            "the dialog\n";
                dialog[1] = "1. exit game \n";
                dialog[2] = "NA\n";
                dialog[3] = "NA\n";//"2. enter cave \n";
        }
    }

    //void takeInput(int input) {
        //
        //bool valid = false;
        //int input;

        //while (valid == false) {
        //cout << "enter selection: ";
        //cin >> input;

        //valid = validInputCheck(input);
        //}
        //changePage(input);

    //}
/// wowowowowowo
    void changePage(int choice) {
        //
        //if (choice = 0) assign to save game button maybe?
        switch (pageNum)
        {
            case 0:
                if (choice == 1)
                {
                    pageNum = 1;
                }
                else if (choice == 2)
                {
                    pageNum = 2;
                }
                break;
            case 1:
                if (choice == 1)
                {
                    pageNum = 4;
                }
                else if (choice == 2)
                {
                    pageNum = 5;
                }
                break;
            case 2:
                if (choice == 1)
                {
                    pageNum = 1;
                }
                else if (choice == 2)
                {
                    pageNum = 3;
                }
                break;
            case 3:
                if (choice == 1)
                {
                    pageNum = 15;
                }
                else if (choice == 2)
                {
                    dialogAddToInventory("rope");
                    pageNum = 14;
                }
                break;
            case 4:
                if (choice == 1)
                {
                    pageNum = 8;
                }
                else if (choice == 2)
                {
                    pageNum = 7;
                }
                break;
            case 5:
                if (choice == 1)
                {
                    dialogAddToInventory("key");
                    pageNum = 6;
                }
                else if (choice == 2)
                {
                    pageNum = 6;
                }
                break;
            case 6:
                if (choice == 1 || choice == 2)
                {
                    pageNum = 9;
                }
                break;
            case 7:
                if (choice == 1 || choice == 2)
                {
                    pageNum = 9;
                }
                break;
            case 8:
                if (choice == 1)
                {
                    pageNum = 13;
                }
                else if (choice == 2)
                {
                    pageNum = 13;
                }
                break;
            case 9:
                if (choice == 1)
                {
                    pageNum = 10;
                }
                else if (choice == 2)
                {
                    pageNum = 10;
                }
                break;
            case 10:
                if (choice == 1 || choice == 2)
                {
                    pageNum = 11;
                }
                else if (choice == 3)
                {
                        dialogAddToInventory("a really cool box");
                        pageNum = 12;
                }
                break;
            case 11:
                pageNum = 20;
                break;
            case 12:
                pageNum = 20;
                break;
            case 13:
                pageNum = 20;
                break;
            case 14:
                if (choice == 1)
                {
                    pageNum = 15;
                }
                else
                {
                    pageNum = 15;
                }
                break;
            case 15:
                if (choice == 1)
                {
                    pageNum = 16;
                }
                else if (choice == 2)
                {
                    pageNum = 16;
                }
                break;
            case 16:
                if (choice == 1)
                {
                    dialogAddToInventory("turtle");
                    pageNum = 17;
                }
                else if (choice == 2)
                {
                    pageNum = 18;
                } else if (choice == 3){
                    dialogAddToInventory("lots of riches");
                    pageNum = 19;
                }
                break;
            case 17:
                pageNum = 20;
                break;
            case 18:
                pageNum = 20;
                break;
            case 19:
                pageNum = 20;
                break;
            case 20:

                break;
            default:
                cout << "oops error lol";
        }

    }


};
// Derived class
class Dialog2 : public uiElement {
private:
public:
    void displayInfo() { //override
        //cout << "this is the dialog text \n";
        switch(pageNum) {
            default:
                cout << "error";
        }
    }

    void takeInput(int input) {
        //
        bool valid = false;
        //int input;

        //while (valid == false) {
        //cout << "enter selection: ";
        //cin >> input;

        valid = validInputCheck(input);
        //}
        changePage(input);

    }

    void changePage(int choice) {
        //
        switch(pageNum){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                break;
            case 9:

                break;
            case 10:

                break;
            case 11:

                break;
            case 12:

                break;
            case 13:

                break;
            case 14:

                break;
            case 15:

                break;
            case 16:

                break;
            case 17:

                break;
            case 18:

                break;
            case 19:

                break;
            case 20:

                break;
            default:
                cout << "oops error lol";
        }

    }

    bool validInputCheck(int choice) {
        switch(pageNum){
            case 0:
                //dstream << "You are at the enterance to a cave. \n"
                //        << "What will you do? \n"
                //        << "0. Check inventory \n"
                //        << "1. not enter cave \n"
                //        << "2. enter cave \n";
                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:
                //if (whaterver how to check if something is in vrcetor ) {
                //    you can do taht option
                //}
                //elkse {
                //    this option doesnt work
                //};
                break;
            case 9:

                break;
            case 10:

                break;
            case 11:

                break;
            case 12:

                break;
            case 13:

                break;
            case 14:

                break;
            case 15:

                break;
            case 16:

                break;
            case 17:

                break;
            case 18:

                break;
            case 19:

                break;
            case 20:

                break;
            default:
                return true;
        }
    }
};