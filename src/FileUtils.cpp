#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "FileUtils.h"

using namespace std;

int loadConfig(const char* optionFilename, vector<char*> items){
    string line;
    vector<string> lines;
    ifstream op(optionFilename);
    while(getline(op, line)){
        if(line.size() < 0){
            continue;
        }
        lines.push_back(line);
    }
    op.close();

    if(lines.size() < items.size()){
        return 0;
    }

    for(size_t i = 0; i < items.size(); i++){
        strcpy(items[i], lines[i].c_str());
    }
    return items.size();
}

int loadContracts(const char* optionFilename, vector<string>& contracts){
    string line;
    ifstream op(optionFilename);
    while(getline(op, line)){
        if(line.size() < 0){
            continue;
        }
        contracts.push_back(line);
    }
    op.close();
    return contracts.size();
}