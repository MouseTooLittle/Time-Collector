/*
Jason Chiem - Time Collector
ECE 1310 - Final Project

An stopwatch app that logs time spent. That time spent can also be categorized for classes and assignments.

Goals
- TUI using FTXUI
- Full Dates Extension
- Refer to Doc for more

Time - Progress
04/16/2026 - Start

*/

// Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>

enum days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

typedef struct dayTime {
    int timeStamp[4] = {0,0,0,0}; // Weekday,Day,Month,Year
    int startTime[50]; // In Seconds Start From 00:00:00
    int stopTime[50];
    int elapsedTime[50]; // Stop-Start
    int currentElapse = 0;
};

void punchCardRead(std::fstream* f);
void punchCardMake(std::fstream* f);
void punchCardWrite(dayTime* day);

int main(){
    dayTime Week1[7];
    std::fstream punch("punchCard.csv", std::ios::in);
    if(!punch.is_open()){
        punchCardMake(&punch);
    } else {
        punchCardRead(&punch);
    }




    return 0; 
}

void punchCardRead(std::fstream* f){

}

void punchCardMake(std::fstream* f){

}

void punchCardWrite(dayTime* day){
    
}