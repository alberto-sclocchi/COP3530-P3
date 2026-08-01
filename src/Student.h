#pragma once
#include <set>
#include <string>

class Student {
private:
    std::string name;
    int residence_id;
    std::set<std::string> class_codes;  
public:
    Student() : residence_id(-1) {}
    Student(std::string name, int residence_id);

    std::string getName() const;
    int getResidenceId() const;
    std::set<std::string> getClassCodes() const;

    bool hasClass(const std::string& code) const;
    void addClass(const std::string& code);
    bool removeClass(const std::string& code);  
    int classCount() const;
};