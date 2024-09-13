#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

/*
    TODO in that function:
        0. make another func that will add spaces on every '=' met in the file so ther thing will work propely as i use '>>' to get values
        1. check if there are repeated defines in the file
        2. redo reading to be done up untill '.' to properly split defines
        3. to check if the define_value starts with '{' - that should mean there is upcoming array
*/

void my_erase(string& str, char charToRemove) {
    // FUNCTION that:
    //  deletes char from string
    str.erase(remove(str.begin(), str.end(), charToRemove), str.end());
}

void my_erase(string& str, string& str_2) {
    // FUNCTION that:
    //  deletes string from string
    for (unsigned int i = 0; i < str_2.size(); i++) {
        str.erase(remove(str.begin(), str.end(), str_2[i]), str.end());
    }
}

void my_erase(string& str, char* charsToRemove) {
    // FUNCTION that:
    //  deletes string from string
    for (unsigned int i = 0; i < strlen(charsToRemove); i++) {
        str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
    }
}

map<string, float> convert_define_txt(string adress) {

    // FUNCTION that:
    //      gets file adress
    //      opens the file
    //      gets the first "word" by getting everything into one string untill '=' was met
    //      get the other half of the line and sets it as a float

    ifstream file(adress); // opened a file to read
    map<string, float> output;    // returning dictionary
    string line = "";           // line string
    string buffer = "";           // buffer string
    string define = "";         // the define
    string define_value = "";   // the define value (will be used to converted from to float during the func

    if (file.is_open()) {
        
        while (getline(file, line)) {
            // here we take the line (as much lines as we can from first till the last) 
            // and put the whole line into 'buffer'

            my_erase(line, ',');

            for (char i : line) {
                        
                if (i != '=') {
                    buffer += i;
                }
                else {
                    char charsToDelete{' ', };
                    my_erase(buffer, charsToDelete);
                    define = buffer;
                    my_erase(line, buffer.append(" = "));
                    define_value = line;
                }
            
            }

            output[define] = stof(define_value);

            line.clear();
            buffer.clear();
            define.clear();
            define_value.clear();

        }

    }
    //for (const auto& pair : output)
    //    cout << '[' << pair.first << "] = " << pair.second << "; " << endl;

    return output;
}


int main() {
    map<string, float> defines_base = convert_define_txt("defines_base.lua");

    map<string, float> defines_from = convert_define_txt("defines_from.lua");
    
    ofstream defines_txt("defines_output.lua");

    string buffer = "";


    cout << "WAS :" << endl;
    for (const auto& pair : defines_base)
        cout << '[' << pair.first << "] = " << pair.second << "; " << endl;
    cout << endl;
    for (const auto& pair : defines_from)
        cout << '[' << pair.first << "] = " << pair.second << "; " << endl;

    for (const auto& pair1 : defines_base) {
        
        for (const auto& pair2 : defines_from) {
        
            if (pair1.first != pair2.first) {
                defines_txt << pair1.first + " = " + to_string(pair1.second) << endl;
            }
            else {
                defines_txt << pair1.first << " = " << to_string(pair2.second) << endl 
                            << "-- previously was '" << pair1.first << " = " << pair1.second << "'. This change was made by Leifee's HOI4 define merger." << endl;
            }

            //cout << '[' << pair_2.first << "] = " << pair_2.second << "; " << endl;
        
        }

    }
    
    cout << "end" << endl;

}