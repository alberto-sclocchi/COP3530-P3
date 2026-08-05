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

    void insert(const std::string& args);
    void remove(const std::string& id);
    void dropClass(const std::string& id, const std::string& code);
    void replaceClass(const std::string& id, const std::string& c1, const std::string& c2);
    void removeClass(const std::string& code);
    void toggleEdgesClosure(const std::string& args);
    void checkEdgeStatus(int a, int b);
    void isConnected(int a, int b);
    void printShortestEdges(const std::string& id);
    void printStudentZone(const std::string& id);
    void verifySchedule(const std::string& id);

public:
    CampusCompass();
    bool parseCSV(const std::string& edges_filepath, const std::string& classes_filepath);
    bool parseCommand(const std::string& command);
    int toMinutes(const std::string& time);
};