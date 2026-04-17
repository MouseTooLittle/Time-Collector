/*
Jason Chiem - Time Collector
ECE 1310 - Final Project

An stopwatch app that logs time spent. That time spent can also be categorized for classes and assignments.

Goals
- TUI using FTXUI
- Full Dates Extension
- Refer to Doc for more

Time - Progress
04/15/2026 - Start
04/16/2026 - Create File, Read File, Parse File
04/16/2026 - Output One Day of Data

*/

// Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>

struct dayTime {
    int timeStamp[4] = {0,0,0,0}; // Weekday,Day,Month,Year
    int startTime[50] = {0}; // In Seconds Start From 00:00:00
    int stopTime[50] = {0};
    int elapsedTime[50] = {0}; // Stop-Start
    int currentElapse = 0;
};

void punchCardRead(dayTime* day);
void punchCardMake();
void punchCardWrite(dayTime* day);
void punchCardDaily(dayTime* day, int weekDay);

const char* days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
enum weekDate {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
const char punchCardFile[] = "punchCard.csv";
const int numberDays = 7;

int main(){
    dayTime Week[numberDays];
    std::fstream read(punchCardFile, std::ios::in);
    if(!read.is_open()){
        punchCardMake();
    } else {
        punchCardRead(Week);
    }

    punchCardDaily(Week,0);
    

    return 0; 
}

void punchCardDaily(dayTime* day, int weekDay){
    for(int i = 0; i<4; i++){
        if(i==0){
            std::cout << days[day[weekDay].timeStamp[0]];
            std::cout << ", DAY:MONTH:YEAR -> ";
        } else {
        std::cout << day[weekDay].timeStamp[i] << " , ";
        }
    }
    std::cout << std::endl;

    std::cout << "Start Times  (seconds from 00:00:00) : ";
    for(int i = 0;i<10; i++){
        std::cout << day[weekDay].startTime[i] << " , ";
    }
    std::cout << std::endl;

    std::cout << "Stop Times   (seconds from 00:00:00) : ";
    for(int i = 0;i<10; i++){
        std::cout << day[weekDay].stopTime[i] << " , ";
    }
    std::cout << std::endl;

    std::cout << "Elapsed Time (seconds from 00:00:00) : ";
    for(int i = 0;i<10; i++){
        std::cout << day[weekDay].stopTime[i] - day[weekDay].startTime[i] << " , ";
    }
    std::cout << std::endl;

    std::cout << "Remaining Time (seconds) : ";
    std::cout << day[weekDay].currentElapse << std::endl;
}

void punchCardRead(dayTime* t){
    std::string oneLine;
    std::ifstream read(punchCardFile);
    std::string temp;
    
    for(int i = 0; i < numberDays; i++){ //Loop For everyday of week
        for(int j = 0; j < 3; j++){ // Loop For every line
            switch(j){
                case 0: {
                    read >> oneLine;
                    std::stringstream oneLineStream(oneLine);
                    int count = 0;
                    while(std::getline(oneLineStream, temp, ',')){
                        if(count<4){
                            t[i].timeStamp[count] = std::stoi(temp);
                        } else {
                            t[i].currentElapse = std::stoi(temp);
                        }
                        count++;
                    }
                break;
                }
                case 1: {
                    read >> oneLine;
                    std::stringstream oneLineStream(oneLine);
                    int count = 0;
                    while(std::getline(oneLineStream, temp, ',')){
                        t[i].startTime[count] = std::stoi(temp);
                        count++;
                    }
                }
                break;
                case 2: {
                    read >> oneLine;
                    std::stringstream oneLineStream(oneLine);
                    int count = 0;
                    while(std::getline(oneLineStream, temp, ',')){
                        t[i].stopTime[count] = std::stoi(temp);
                        count++;
                    }
                }
                break;
            }
        }
    }
}

void punchCardMake(){
    std::ofstream file(punchCardFile);
    file.close();
}

void punchCardWrite(dayTime* day){
    
}