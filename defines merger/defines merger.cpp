#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;


/* The plan:
* a) we open two files and write down mentioned defines (convert_define_txt() and main())
* b) we check if 'to merge' defines are in the 'base' defines
*   -) if they are -> we add the previous value to the temp var,
                      change string after '=' to the 'to merge' one,
*                     delete that define from 'to merge',
*                     add comment line (--) telling prev value from the temp var
*   -)        else -> we do nothing
* c) we add whats left in 'to merge' to the bottom
*/


map<string, string> convert_define_txt(string adress) {
    /*
    * func gets file adress,
    * returns map<define, define_value(and its comment)>
    */

    ifstream file_defines(adress);
    string buffer = "";

    string define = "";
    string define_value = "";

    map<string, string> return_defines;

    if (file_defines.is_open()) {

        while (getline(file_defines, buffer)) {
            //cout << "Define " << buffer.substr(0, buffer.find('=')) << "\n";
            //cout << "Value  " << buffer.substr(buffer.find('='), buffer.length()) << "\n";
            // debug thingy

            define = buffer.substr(0, buffer.find('='));
            define.erase(remove(define.begin(), define.end(), ' '), define.end());  // removing all ' 's in the define
            define_value = buffer.substr(buffer.find('=') + 1, buffer.length());

            return_defines[define] = define_value;

            define.clear();

        }

    }

    return (return_defines);
}



int main() {
    map<string, string> defines_base = convert_define_txt("defines_base.lua");

    map<string, string> defines_from = convert_define_txt("defines_from.lua");

    ofstream defines_txt("defines_output.lua");

    string buffer = "";

    for (auto pair1 : defines_base) {

        for (auto pair2 : defines_from) {

            if (pair1.first != pair2.first) {
                defines_txt << pair1.first << " = " << pair1.second << endl;
            }
            else {
                defines_txt << pair1.first << " = " << pair2.second << endl;
                defines_txt << "-- previously was '" << pair1.first << " = " << pair1.second << "'. This change was made by Leifee's HOI4 define merger." << endl;
            }

        }

    }

    cout << "end" << endl;

}