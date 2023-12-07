//
// Created by mig90 on 11/29/2023.
//
#include "story.h"

using namespace std;

class uiElement {

public:
    vector<string> inventory;
    string dialog[4];
    //static string choice1;
    //static string choice2;
    //static string choice3;
    string savefileName;

    int chapterNum;
    int pageNum;
    bool programLoop = true;
    bool gameplayLoop = true;

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
};

// Derived class
class Dialog1 : public uiElement {
private:
public:
    //Dialog1(int chapter, int page){
    //chapterNum = chapter;
    //pageNum = page;
//}
    void displayInfo() { //override
        //I may turn this into "string displayInfo" instead of void
        // but the idea is a stringstream is created and then somehow
        // the output of that can be used in the UI
        //cout << "this is the dialog text \n";
        //stringstream dstream;
        switch(pageNum){
            case 0:
                dialog[0] = "You are at the enterance to a cave. \n";
                dialog[1] = "1. Check inventory \n";
                dialog[2] = "2. not enter cave \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
                break;
            case 1:
                dialog[0] = "You are at the enterance to a cave. \n";
                dialog[1] = "1. Check inventory \n";
                dialog[2] = "2. not enter cave \n";
                dialog[3] = "NA\n";//"2. enter cave \n";
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