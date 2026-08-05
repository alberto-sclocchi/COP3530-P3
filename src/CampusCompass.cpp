#include "CampusCompass.h"
#include <fstream>
#include <string>
#include <map>
#include "Class.h"
#include <sstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include <set>

using namespace std;

CampusCompass::CampusCompass() {}

int CampusCompass::toMinutes(const string& time) {
    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));
    return hours * 60 + minutes;
}


bool CampusCompass::parseCSV(const string& edges_filepath, const string& classes_filepath) {
    ifstream classes_file("../" + classes_filepath);
    if (!classes_file.is_open()) {
        classes_file.clear();
        classes_file.open(classes_filepath);
        if (!classes_file.is_open()){
            cout<<"Error: Classes file could not open."<<endl;
            return false;
        }
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

    ifstream edges_file("../" + edges_filepath);
    if (!edges_file.is_open()) {
        edges_file.clear();
        edges_file.open(edges_filepath);
        if(!edges_file.is_open()){
            cout<<"Error: Edges file could not open."<<endl;
            return false;
        }
    }

    getline(edges_file, line);
    while (getline(edges_file, line)) {
        istringstream ss(line);
        string from, to, wt;
        string discard;
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, discard, ',');
        getline(ss, discard, ',');
        getline(ss, wt, ',');

        graph.addEdge(stoi(from), stoi(to), stoi(wt));
    }

    return true;
}

bool CampusCompass::parseCommand(const string &command) {
   
    bool is_valid = true; // replace with your actual validity checking

    istringstream ss(command);
    string cmd = command.substr(0, command.find(' '));

    if(command.length() < 6 || command[cmd.length()] != ' ') return false;

    if(cmd == "insert") {

        insert(command.substr(cmd.length() + 1));

    } else if (cmd == "remove") {

        remove(command.substr(cmd.length() + 1));

    } else if (cmd == "dropClass") {

        istringstream ss(command.substr(cmd.length() + 1));
        string id, code;
        ss >> id >> code;
        dropClass(id, code);

    } else if (cmd == "replaceClass") {

        istringstream ss(command.substr(cmd.length() + 1));
        string id, c1, c2;
        ss >> id >> c1 >> c2;
        replaceClass(id, c1, c2);

    } else if (cmd == "removeClass") {

        removeClass(command.substr(cmd.length() + 1));

    } else if (cmd == "toggleEdgesClosure") {

        toggleEdgesClosure(command.substr(cmd.length() + 1));

    } else if (cmd == "checkEdgeStatus") {

        istringstream ss(command.substr(cmd.length() + 1));
        int a, b;
        ss >> a >> b;
        checkEdgeStatus(a, b);

    } else if (cmd == "isConnected") {

        istringstream ss(command.substr(cmd.length() + 1));
        int a, b;
        ss >> a >> b;
        isConnected(a, b);

    } else if (cmd == "printShortestEdges") {

        printShortestEdges(command.substr(cmd.length() + 1));

    } else if(cmd == "printStudentZone"){

        printStudentZone(command.substr(cmd.length() + 1));

    } else if(cmd == "verifySchedule"){

        verifySchedule(command.substr(cmd.length() + 1));

    } else {

        is_valid = false; 
        
    }

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
    regex isValidClassCode = regex("^[A-Z]{3}[0-9]{4}$");
    if (!regex_match(s, isValidClassCode)) {
        return false;
    }
    return true; 
}

void CampusCompass::insert(const string& args) {
    istringstream ss(args);
    string id, name, residence_id_str, num_classes_str;
    size_t num_classes;
    set<string> class_codes;
    string s;
    int count = 1;

    getline(ss, name, '"');
    getline(ss, name, '"');
    ss.get();

    while (getline(ss, s, ' ')) {
        if (count == 1) {
            id = s;
        } else if (count == 2) {
            residence_id_str = s;
        } else if (count == 3) {
            num_classes_str = s;

            try{
                num_classes = stoi(num_classes_str);
            } catch (const exception& e) {
                cout << "unsuccessful" << endl;
                return;
            }

            if(num_classes <= 0 || num_classes >= 7) {
                cout << "unsuccessful" << endl;
                return; 
            }
        } else {
            class_codes.insert(s);
            continue;
        }
        count++;
    }

    if (count != 4 || class_codes.size() != num_classes) {
        cout << "unsuccessful" << endl;
        return; 
    }
    if (isValidUfid(id) && isValidName(name) && students.find(id) == students.end()) {
        try{
            int residence_id = stoi(residence_id_str);
            students[id] = Student(name, residence_id);
        } catch (const exception& e) {
            cout << "unsuccessful" << endl;
            return;
        }

        for (const auto& code : class_codes) {
            if (isValidClassCode(code)) {
                students[id].addClass(code);
            } else {
                students.erase(id);
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
        if (it != students.end() && classes.find(code) != classes.end()) {
            if (it->second.hasClass(code)) {
                it->second.removeClass(code);
                if (it->second.classCount() == 0) {
                    students.erase(it);
                }
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
            if (it->second.hasClass(c1) && !it->second.hasClass(c2) && classes.find(c2) != classes.end()) {
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

void CampusCompass::removeClass(const string& code) {
    int canceled_count = 0;
    if (isValidClassCode(code) && classes.find(code) != classes.end()) {
        auto it = students.begin();
        while (it != students.end()) {
            if (it->second.hasClass(code)) {
                it->second.removeClass(code);
                canceled_count++;
            }

            if (it->second.classCount() == 0) {
                it = students.erase(it);
            } else {
                ++it;
            }
        }
        cout << (canceled_count == 0 ? "unsuccessful" : to_string(canceled_count)) << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CampusCompass::toggleEdgesClosure(const string& args) {
    istringstream ss(args);
    string n_str;
    int n;
    getline(ss, n_str, ' ');

    try {
        n = stoi(n_str);
    } catch (const exception& e) {
        cout << "unsuccessful" << endl;
        return;
    }

    string a_str, b_str;

    int counter = 0;

    while (getline(ss, a_str, ' ') && getline(ss, b_str, ' ') && counter < n) {
        int a = stoi(a_str);
        int b = stoi(b_str);
        graph.toggleEdge(a, b);
        counter++;
    }

    cout << "successful" << endl;

}


void CampusCompass::checkEdgeStatus(int a, int b) {
    int status = graph.getEdgeStatus(a, b);
    if (status == -1) {
        cout << "DNE" << endl;
    } else {
        cout << (status == 1 ? "closed" : "open") << endl;
    }
}

void CampusCompass::isConnected(int a, int b) {
    if (graph.isConnected(a, b)) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CampusCompass::printShortestEdges(const string& id) {
    auto student = students[id];
    int residence_id = student.getResidenceId();
    auto shortest_paths = graph.dijkstra(residence_id);

    cout<<"Time For Shortest Edges: "<<student.getName()<<endl;

    for (const string& student_class : student.getClassCodes()) {
        if (classes.find(student_class) != classes.end()) {
            int class_location = classes[student_class].getLocationId();
            int shortest_time = shortest_paths[class_location].first;
            cout<<student_class<<": "<<shortest_time<<endl;
        }
    }
}

void CampusCompass::printStudentZone(const string& id) {
    auto student = students[id];
    int residence_id = student.getResidenceId();
    auto shortest_paths = graph.dijkstra(residence_id);

    set<int> zone_locations;
    zone_locations.insert(residence_id);


    for (const string& student_class : student.getClassCodes()) {
        if (classes.find(student_class) != classes.end()) {
            int class_location = classes[student_class].getLocationId();
            int shortest_time = shortest_paths[class_location].first;

            if(shortest_time == -1) continue;

            int curr = class_location;
            while(curr != residence_id){
                zone_locations.insert(curr);
                curr = shortest_paths[curr].second;
            }

        }
    }

    int mst_cost = graph.mstCost(zone_locations);

    cout<<"Student Zone Cost For " << student.getName() <<": "<< mst_cost<<endl;

}

void CampusCompass::verifySchedule(const string& id){
    auto student = students[id];
    set<string> class_codes = student.getClassCodes();
    vector<string> schedule;
    for (const string& code : class_codes) {
        if (classes.find(code) != classes.end()) {
            schedule.push_back(code);
        }
    }

    if(schedule.size() < 2){
        cout<<"unsuccessful"<<endl;
        return;
    }

    sort(schedule.begin(), schedule.end(), [this](const string& a, const string& b){
        int start_time_a = classes[a].getStartMinutes();
        int start_time_b = classes[b].getStartMinutes();
        if(start_time_a != start_time_b) return start_time_a < start_time_b;
        return a < b;
    });
    
    cout << "Schedule Check for " << student.getName() << ":" << endl;

    for (int i = 0; i < schedule.size() - 1; i++) {
        int class_location_1 = classes[schedule[i]].getLocationId();
        int class_location_2 = classes[schedule[i + 1]].getLocationId();

        auto shortest_times = graph.dijkstra(class_location_1);
        int next_class_shortest_time = shortest_times[class_location_2].first;
        int gap_classes = classes[schedule[i + 1]].getStartMinutes() - classes[schedule[i]].getEndMinutes();
        bool is_possible = gap_classes >= next_class_shortest_time && next_class_shortest_time != -1;
        cout<<schedule[i]<<" - "<<schedule[i + 1]<<": "<<(is_possible ? "successful" : "unsuccessful") << endl;
    }
}