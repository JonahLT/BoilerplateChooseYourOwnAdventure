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
    Dialog1 dialogController;
    Player playerController;
    playerController.inventory.resize(40);
    //dialogController.inventoryPtr = &(playerController.inventory);


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
    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
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

    //
    //
    //
    //////
    //
    //
    //



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

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        //showing the menu
        if(show_menu_window){
            ImGui::Begin("Main Menu");
            if(ImGui::Button("Load Game")){
                show_save_window = true;
                show_menu_window = false;
            }
            ImGui::End();
        }

        //showing the menu
        if(show_save_window){
            bool wow = true;
            int saveSelection = 0;
            ImGui::Begin("Saves");
            if(ImGui::Button("Load Save One")){

                saveSelection = 1;
                ifstream fin("savefiles/saveFile1.txt");
                string item;
                //fin.open("saveFile1.txt");
                if (fin.is_open()) {
                    cout << "save file opened";
                    fin >> item;
                    fin >> dialogController.chapterNum;
                    fin >> dialogController.pageNum;
                    int counter = 0;
                    while (!fin.eof()) {

                        if (!(playerController.inventory.size() < counter)) {
                            playerController.inventory.resize(playerController.inventory.size()*2);
                        }
                        getline(fin, item);
                        cout << "item: <" << item << ">\n";
                        if (!fin.eof()) {
                            playerController.inventory.push_back(item);
                        }
                        cout << "this is item number 1: <" << playerController.inventory.at(0) << ">\n";
                        counter++;
                    }
                }

                fin.close();
                show_game_window = true;
                show_save_window = false;
            } else if(ImGui::Button("Load Save Two")) {
                show_game_window = true;
                show_save_window = false;
                saveSelection = 2;
            } else if(ImGui::Button("Load Save Three")) {
                show_game_window = true;
                show_save_window = false;
                saveSelection = 3;
            }
            //cout << "this is good\n";
            //send save selection to story.cpp
            if (saveSelection == 1) {
                saveFileName = "saveFile1.txt";
            }else if(saveSelection == 2) {
                saveFileName = "saveFile2.txt";
            } else if (saveSelection == 3) {
                saveFileName = "saveFile3.txt";
            }
            if(show_save_window == false) {

            }

            ImGui::End();
        }

        //game window maybeeee :3
        if (show_game_window){
            //call story.cpp to get data of what to show on screen
            string allItems;
            dialogController.displayInfo();
            std::string roomDescription = dialogController.dialog[0];//"ROOM DESCRIPTION HERE!!!!";
            std::string buttonOne = dialogController.dialog[1];
            std::string buttonTwo = dialogController.dialog[2];
            std::string buttonThree = dialogController.dialog[3];


            ImGui::Begin("Game Window");

            //display description

            //send back player input when u get it

            ImGui::Text("This is where the game is lol");
            ImGui::Text(roomDescription.c_str());// Display some text (you can use a format strings too)

            //get inventory items
            //stops at 39 for some reason before going again
           // for(int i = 0; i < playerController.inventory.size(); i++){
                //cout << "iteration " + to_string(i) << endl;
                //allItems += playerController.inventory.at(0) + "\n";
           // }
            //ImGui::Text(playerController.inventory.at(0).c_str());
            //cout << "this is item number 1: <" << playerController.inventory.at(0) << ">\n" ;
            if (buttonOne != "NA\n" && ImGui::Button(buttonOne.c_str())) {
                dialogController.changePage(1); //selection = 1;
            }

            if (buttonTwo != "NA\n" && ImGui::Button(buttonTwo.c_str())) {
                dialogController.changePage(2); //selection = 2;
            }

            if ( buttonThree != "NA\n" && ImGui::Button(buttonThree.c_str())) {
                dialogController.changePage(3); //selection = 3;
            }

            ImGui::End();
        }


        // Rendering
        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);

        // todo: add your game logic here to be drawn before the ui rendering

        //call story.cpp to get data of what to show on screen
        std::string roomDescription = "ROOM DESCRIPTION HERE!!!!";
        std::string buttonOne = "BUTTON DESCRIPTION HERE";
        std::string buttonTwo = "BUTTON DESCRIPTION HERE";
        std::string buttonThree = "NA";
        //display buttons

        //display description

        //send back player input when u get it


        // Set renderer color red to draw the square
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        // Draw filled square
        SDL_RenderFillRect(renderer, &squareRect);

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