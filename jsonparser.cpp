#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int main()
{
    std::ifstream inFile;
    inFile.open("test.json");

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str = strStream.str();

    map<string, string> jsonMap;

    for(std::string::size_type i = 0; i < str.size(); ++i) {

        if (str[i] == '{')
            continue;

        if (str[i] == '}')
            break;

        if (str[i] == '"') {
            string key;
            string value;
            int j = i + 1;
            while (str[j] != '"') {
                key += str[j];
                j++;
            }
            j = j + 2;

            if (str[j] == '"') {
                j++;
                while (str[j] != '"') {
                    value += str[j];
                    j++;
                }
            }
            else {
                while (str[j] != ',') {

                    if (str[j] == '}')
                        break;

                    if (str[j] == '\n')
                        break;

                    value += str[j];
                    j++;
                }
            }
            jsonMap[key] = value;
            i = j;
        }
    }


    for (auto it = jsonMap.begin(); it != jsonMap.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
}