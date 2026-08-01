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

void CampusCompass::insert(const string& args) {
    istringstream ss(args);
    string id, name, residence_id_str;
    set<string> class_codes;
    string s;
    int count = 0;

    while (getline(ss, s, ' ')) {
        if (count == 0) {
            id = s;
        } else if (count == 1) {
            name = s.substr(1, s.length() - 2);
        } else if (count == 2) {
            residence_id_str = s;
        } else if (count > 2 && count < 9){
            class_codes.insert(s);
        }
        else {
            break; 
        }
        count++;
    }

    if (isValidUfid(id) && isValidName(name)) {
        int residence_id = stoi(residence_id_str);
        students[id] = Student(name, residence_id);

        for (const auto& code : class_codes) {
            if (isValidClassCode(code)) {
                students[id].addClass(code);
            } else {
                cout << "unsuccessful" << endl;
                return;
            }
        }

        cout << "successful" << endl;

    } else {
        cout << "unsuccessful" << endl;
    }
}

void CampusCompass::remove(const string& id) {
    if (isValidUfid(id)) {
        auto it = students.find(id);
        if (it != students.end()) {
            students.erase(it);
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CampusCompass::dropClass(const string& id, const string& code) {
    if (isValidUfid(id) && isValidClassCode(code)) {
        auto it = students.find(id);
        if (it != students.end()) {
            if (it->second.hasClass(code)) {
                it->second.removeClass(code);
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CampusCompass::replaceClass(const string& id, const string& c1, const string& c2) {
    if (isValidUfid(id) && isValidClassCode(c1) && isValidClassCode(c2)) {
        auto it = students.find(id);
        if (it != students.end()) {
            if (it->second.hasClass(c1)) {
                it->second.removeClass(c1);
                it->second.addClass(c2);
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    } else {
        cout << "unsuccessful" << endl;
    }
}