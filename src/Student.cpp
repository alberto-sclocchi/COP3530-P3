#include <string>
#include <sstream>
#include "Student.h"

using namespace std;

Student::Student(string _name, int _residence_id)
    : name(_name), residence_id(_residence_id) {}

string Student::getName() const {
    return name;
}

int Student::getResidenceId() const {
    return residence_id;
}

set<string> Student::getClassCodes() const {
    return class_codes;
}

void Student::addClass(const string& code) {
    class_codes.insert(code);
}

bool Student::hasClass(const string& code) const {
    return class_codes.find(code) != class_codes.end();
}

bool Student::removeClass(const string& code) {
    auto it = class_codes.find(code);
    if (it != class_codes.end()) {
        class_codes.erase(it);
        return true;
    }
    return false;
}

int Student::classCount() const {
    return class_codes.size();
}