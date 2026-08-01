#include <string>
#include <sstream>
#include "Class.h"

using namespace std;


Class::Class(int _location_id, int _start_minutes, int _end_minutes)
    : location_id(_location_id), start_minutes(_start_minutes), end_minutes(_end_minutes) {}

int Class::getLocationId() const {
    return location_id;
}   

int Class::getStartMinutes() const {
    return start_minutes;
}

int Class::getEndMinutes() const {
    return end_minutes;
}
