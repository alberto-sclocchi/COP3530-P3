#include "CampusCompass.h"
#include <fstream>
#include <string>
#include <map>
#include "Class.h"
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

CampusCompass::CampusCompass() {

}

int toMinutes(string time) {
    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));
    return hours * 60 + minutes;
}


bool CampusCompass::parseCSV(const string& edges_filepath, const string& classes_filepath) {
    ifstream classes_file("../" + classes_filepath);
    if (!classes_file.is_open()) {
        cout<<"Error: Classes file could not open."<<endl;
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

    ifstream classes_file("../" + edges_filepath);
    if (!classes_file.is_open()) {
        cout<<"Error: Edges file could not open."<<endl;
        return false;
    }


    return true;
}

bool CampusCompass::parseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}

bool CampusCompass::isValidUfid(const string& s) const {
    regex isValidUFIRegex = regex("^[0-9]{8}$");
    if (!regex_match(s, isValidUFIRegex)) {
        return false;
    }
    return true; 
}

bool CampusCompass::isValidName(const string& s) const {
    regex isValidName = regex("^[A-Za-z ]+$");
    if (!regex_match(s, isValidName)) {
        return false;
    }
    return true; 
}

bool CampusCompass::isValidClassCode(const string& s) const {
    regex isValidClassCode = regex("^[A-Z]{3}[0-9]{3}$");
    if (!regex_match(s, isValidClassCode)) {
        return false;
    }
    return true; 
}