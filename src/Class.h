#pragma once
#include <string>

class Class {
private:
    int location_id;
    int start_minutes;   
    int end_minutes;
public:
    Class() : location_id(-1), start_minutes(0), end_minutes(0) {}
    Class(int location_id, int start_minutes, int end_minutes);

    int getLocationId() const;
    int getStartMinutes() const;
    int getEndMinutes() const;
};