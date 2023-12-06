#include "story.h"
#include "story.cpp"

using namespace std;



int main() {
    //std::cout << "Hello, World!" << std::endl;
string item;
string saveFileName = "saveFile1.txt";
int chpter;
int page;

uiElement controllerClass;
    while (controllerClass.programLoop) {
    //
    int save = 0;
    cout << "file selection\n";

    while (save != 1 && save != 2 && save != 3 && save != 4) {
        cin >> save;
    }
        if (save == 4) {
            cout << "goodbye";
            return 0;
        }

        ifstream myfile;
    //switch(save) {
    //    case 1:

    //}
    myfile.open (saveFileName);
        myfile >> item;
        myfile >> controllerClass.chapterNum;
        myfile >> controllerClass.pageNum;
        while (!myfile.eof()) {
            getline(myfile, item, ',');
            controllerClass.inventory.push_back(item);
        }
        myfile.close();
    controllerClass.gameplayLoop = true;
    //
        Player playerController(controllerClass.inventory);
        //if (true) {
            Dialog1 dialogController(controllerClass.chapterNum, controllerClass.pageNum);
       // } else {
           // Dialog2 dialogController;
        //}

        while (controllerClass.gameplayLoop) {
            //hello

        }
        ofstream writefile;
        writefile.open (saveFileName);
        writefile << "Name\n";
        writefile << controllerClass.chapterNum;
        writefile << controllerClass.pageNum;

        for(int i = 0; i < controllerClass.inventory.size(); i++) {
            writefile << controllerClass.inventory[i] << ",";
        }
        writefile.close();
    }

    return 0;
}
