#define SDL_MAIN_HANDLED true
#include <iostream>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>
#include "story.h"
#include "story.cpp"
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __EMSCRIPTEN__
EM_JS(int, canvas_get_width, (), {
return canvas.width;
});

EM_JS(int, canvas_get_height, (), {
return canvas.height;
});
#endif



int main(int argc, char* argv[]) {

    uiElement controllerClass;
    string saveFileName;

    Player playerController;
    //Dialog1 dialogController(&playerController);
    Dialog1 dialogController;
    dialogController.playerReference = &playerController;
    playerController.inventory.resize(1);


    ImVec2 buttSize =  ImVec2(300,75);
    ImVec2 winSize = ImVec2(400,400);

    // Unused argc, argv
    (void) argc;
    (void) argv;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    auto width = 1280;
    auto height = 720;
#ifdef __EMSCRIPTEN__
    width = canvas_get_width();
    height = canvas_get_height();
#endif

    // Setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    SDL_Window *window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    if (!window) {
        std::cout << "Window could not be created!" << std::endl
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        abort();
    }

    // Setup SDL_Renderer instance
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Error creating SDL_Renderer!");
        abort();
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    // Our state
    bool show_inventory_window = false;
    bool show_game_window = false;
    bool show_menu_window = true;
    bool show_save_window = false;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;

    // Declare rect of square
    SDL_Rect squareRect;

    // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
    squareRect.w = std::min(width, height) / 2;
    squareRect.h = std::min(width, height) / 2;

    // Square position: In the middle of the screen
    squareRect.x = width / 2 - squareRect.w / 2;
    squareRect.y = height / 2 - squareRect.h / 2;

    // Event loop
    while (!done) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        //showing the main menu
        if(show_menu_window){
            ImGui::SetNextWindowSize(winSize);
            ImGui::Begin("Main Menu",NULL,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
            if(ImGui::Button("Load Game",buttSize)){
                show_save_window = true;
                show_inventory_window = true;
                show_menu_window = false;
            }
            if(ImGui::Button("Close Game",ImVec2(300,25))){
                exit(0);
            }
            ImGui::End();
        }

        if(show_inventory_window){
            ImGui::SetNextWindowSize(winSize);
            ImGui::Begin("Inventory",NULL,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
            //get inventory items
            ImGui::Text(playerController.getInventory().c_str());

            ImGui::End();
        }

        //showing the save menu
        if(show_save_window){
            int saveSelection = 0;
            ImGui::SetNextWindowSize(winSize);
            ImGui::Begin("Saves",NULL,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
            if(ImGui::Button("Load Save One", buttSize)){
                saveSelection = 1;
                show_game_window = true;
                show_save_window = false;
            } else if(ImGui::Button("Load Save Two",buttSize)) {
                saveSelection = 2;
                show_game_window = true;
                show_save_window = false;
            } else if(ImGui::Button("Load Save Three",buttSize)) {
                saveSelection = 3;
                show_game_window = true;
                show_save_window = false;
            }
            if(ImGui::Button("Close Game",ImVec2(300,25))){
                exit(0);
            }

            //send save selection to story.cpp
            if (saveSelection == 1) {
                saveFileName = "saveFile1.txt";
            }else if(saveSelection == 2) {
                saveFileName = "saveFile2.txt";
            } else if (saveSelection == 3) {
                saveFileName = "saveFile3.txt";
            }

            if (saveSelection != 0) {
                ifstream fin("savefiles/" + saveFileName);
                string item;
                //fin.open("saveFile1.txt");
                if (fin.is_open()) {
                    cout << "save file opened";
                    fin >> item;
                    fin >> dialogController.chapterNum;
                    fin >> dialogController.pageNum;
                    int counter = 0;
                    while (!fin.eof()) {

                        if (!(playerController.inventory.capacity() < counter)) {
                            playerController.inventory.reserve(playerController.inventory.capacity()*2);
                        }
                        getline(fin, item);
                        if (!fin.eof()) {
                            playerController.inventory.push_back(item);
                        }
                        counter++;
                    }
                }

                fin.close();
            }

            ImGui::End();
        }

        //game window maybeeee :3
        if (show_game_window){
            ImGui::SetNextWindowSize(winSize);
            //call story.cpp to get data of what to show on screen
            string allItems;
            dialogController.displayInfo();
            std::string roomDescription = dialogController.dialog[0];//"ROOM DESCRIPTION HERE!!!!";
            std::string buttonOne = dialogController.dialog[1];
            std::string buttonTwo = dialogController.dialog[2];
            std::string buttonThree = dialogController.dialog[3];

            ImGui::Begin("Game Window",NULL,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
            //display description

            //send back player input when u get it
            ImGui::Text(roomDescription.c_str());

            //cout << "this is item number 1: <" << playerController.inventory.at(0) << ">\n" ;
            if (buttonOne != "NA\n" && ImGui::Button(buttonOne.c_str(),buttSize)) {
                dialogController.changePage(1); //selection = 1;
            }

            if (buttonTwo != "NA\n" && ImGui::Button(buttonTwo.c_str(),buttSize)) {
                dialogController.changePage(2); //selection = 2;
            }

            if ( buttonThree != "NA\n" && ImGui::Button(buttonThree.c_str(),buttSize)) {
                dialogController.changePage(3); //selection = 3;
            }
            if (ImGui::Button("Save",ImVec2(300,25))) {
                dialogController.changePage(3); //selection = 3;
            }

            if(ImGui::Button("Close Game",ImVec2(300,25))){
                exit(0);
            }

            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);

        //call story.cpp to get data of what to show on screen
        std::string roomDescription = "ROOM DESCRIPTION HERE!!!!";
        std::string buttonOne = "BUTTON DESCRIPTION HERE";
        std::string buttonTwo = "BUTTON DESCRIPTION HERE";
        std::string buttonThree = "NA";

        // present ui on top of your drawings
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);

        SDL_Delay(0);
    }

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}