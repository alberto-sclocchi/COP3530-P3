#include "CampusCompass.h"
#include <fstream>
#include <string>
#include <map>
#include "Class.h"
#include <sstream>

using namespace std;

CampusCompass::CampusCompass() {

}



bool CampusCompass::parseCSV(const string& edges_filepath, const string& classes_filepath) {
    ifstream classes_file(classes_filepath);
    if (!classes_file.is_open()) {
        return false;
    }

    string line;
    getline(classes_file, line);            
    while (getline(classes_file, line)) {
        istringstream ss(line);
        string code, loc, start, end;
        getline(ss, code,  ',');
        getline(ss, loc,   ',');
        getline(ss, start, ',');
        getline(ss, end,   ',');
        Class class_ex (stoi(loc), toMinutes(start), toMinutes(end));
        classes[code] = class_ex;
    }

    return true;
}

bool CampusCompass::parseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}
