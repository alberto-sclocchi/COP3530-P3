#pragma once
#include <map>
#include <string>
#include <vector>
#include "Class.h"
#include "Graph.h"
#include "Student.h"

class CampusCompass {
private:
    Graph graph;
    std::map<std::string, Class> classes;      
    std::map<std::string, Student> students;   

    bool isValidUfid(const std::string& s) const;
    bool isValidName(const std::string& s) const;
    bool isValidClassCode(const std::string& s) const;
public:
    CampusCompass();
    bool insert(const std::string& args);
    bool remove(const std::string& id);
    bool dropClass(const std::string& id, const std::string& code);
    bool replaceClass(const std::string& id, const std::string& c1, const std::string& c2);
    int removeClass(const std::string& code);
    bool toggleEdgesClosure(const std::string& args);
    std::string checkEdgeStatus(int a, int b);
    bool isConnected(int a, int b);
    std::map<std::string,int> printShortestEdges(const std::string& id);
    void printStudentZone(const std::string& id);
    void verifySchedule(const std::string& id);

    bool parseCSV(const std::string& edges_filepath, const std::string& classes_filepath);
    bool parseCommand(const std::string& command);
    int toMinutes(const std::string& time);
};