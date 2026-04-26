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
04/24/2026 - Write File, Finished File Structure
04/25/2026 - Menu /help, /clockIn, /viewPunch, /exit
04/25/2026 - Commented and Cleanup
                Subnote: Assignment End (Time Constraint and this is already more than enough)

*/

// Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

// One Day's Structure
struct dayTime {
    int timeStamp[4] = {0,0,0,0}; // Weekday,Day,Month,Year
    int startTime[50] = {0}; // In Seconds Start From 00:00:00
    int stopTime[50] = {0};
    int groupTime[50] = {0};
    //int elapsedTime[50] = {0}; // Stop-Start
    int currentElapse = 0;
};

// Prototypes
void punchCardRead(dayTime* day);
void punchCardMake();
void punchCardWrite(dayTime* day);
void punchCardDaily(dayTime* dayStruct, int weekDay);
std::string secondToTimeStamp(int t);
int timeNowSeconds();
void debugStruct(dayTime* dayStruct);

// Constants
const char* validCommands[] = {"/help", "/clockIn", "/editPunch", "/viewPunch", "/exit"};
int numCommands = 5;
const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
enum weekDate {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
const char punchCardFile[] = "punchCard.csv";
const int numberDays = 7;

int main(){
    // Run bool's
    bool run = 1;
    
    // clockIn Menu Var's
    int clockInMenu;
    int clockInEntry;
    bool clockInRun = 1;
    bool clockInStarted =0;

    // general Input Var's
    bool validInput;
    bool clockInEntryFound;
    std::string promptOne;
    int menu;
    
    // Program start date
    time_t now = time(NULL);
    struct tm* localTime = localtime(&now);

    // Creates struct for a week
    dayTime Week[numberDays];

    // Start-up File Manager
    std::ifstream read(punchCardFile);
    if(!read.is_open()){
        punchCardMake();
    } else {
        punchCardRead(Week);
    }

    // Set-Up Struct for today
    Week[localTime->tm_wday].timeStamp[0] = localTime->tm_wday;
    Week[localTime->tm_wday].timeStamp[1] = localTime->tm_mday;
    Week[localTime->tm_wday].timeStamp[2] = localTime->tm_mon + 1;
    Week[localTime->tm_wday].timeStamp[3] = localTime->tm_year + 1900;

    // Main Program Loop
    while(run){
        // Greetings
        system("cls");
        std::cout <<  "\033[1;33m" << "Welcome to Time Collector,\nWill you be productive today?"    << "\033[0m" << std::endl;
        std::cout << "Either input commands or type " <<  "\033[1;31m" << "\'/help\'." <<  "\033[0m" << std::endl;

        // User Terminal w/ checker
        validInput = 0;
        while(validInput==0){
            std::cin >> promptOne;
            for(int i = 0; i < numCommands; i++){
                if(promptOne == validCommands[i]){
                    validInput = true;
                    menu = i;
                break;
                }
            }
            if(validInput==0){
                std::cout << "\033[A\033[2K\r"; // delete invalid input line
                //std::cout << "Either input commands or type " <<  "\033[1;31m" << "\'/help\'." <<  "\033[0m" << std::endl;
            } else {
                system("cls");
            }
        }

        // User Command Switch
        switch (menu)
        {
        case 0: { // Help Menu
                system("cls");
                // Output all commands
                std::cout <<  "\033[1;33m" << "Time Collector: Help Menu"    << "\033[0m" << std::endl;
                std::cout << "----------------------" << std::endl;
                std::cout << "Possible Commands: " << std::endl;
                std::cout << "\033[1;31m" << "/help\n/clockIn\n/editPunch\n/viewPunch\n/exit" << std::endl << std::endl;
                std::cout << "\033[31m" << "Press enter to exit." << "\033[0m" << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
            break;

        case 1: { // Clock In
            // clockIn Menu Bool Var's
            validInput = 0;
            clockInRun = 1;
            clockInStarted = 0;
            clockInEntry = 0;

            // clockIn Menu Loop
            while(clockInRun){
                // clockIn Menu Greeting
                system("cls");
                std::cout <<  "\033[1;33m" << "Time Collector: Clock In"    << "\033[0m" << std::endl;
                std::cout << "----------------------" << std::endl;
                std::cout << "Possible Commands: " << std::endl;
                std::cout << "\033[1;31m" << "/clockIn\n/clockOut\n/menu" << "\033[0m" << std::endl << std::endl;

                std::cout << "Current Time: " << secondToTimeStamp(timeNowSeconds()) << std::endl << std::endl;

                // clockIn Time Status
                if(clockInStarted){
                    std::cout << "You are clocked in." << std::endl;
                } else {
                    std::cout << "You are clocked out." << std:: endl << std::endl;
                }


                // clockIn Menu Command's w/ checker
                std::cout << "Command Line:" << std::endl;

                while(!validInput){
                    std::cin >> promptOne;
                    if(promptOne == "/clockIn" || promptOne == "/clockOut" || promptOne == "/menu"){
                        validInput = 1;
                        if(promptOne == "/clockIn") clockInMenu = 0;
                        if(promptOne == "/clockOut") clockInMenu = 1;
                        if(promptOne == "/menu") clockInMenu = 2;
                    }
                    if(validInput==0){
                        std::cout << "\033[A\033[2K\r";
                    } else {
                        system("cls");
                    }
                }
                validInput = 0;

                // clockIn Menu options
                switch (clockInMenu)
                {
                case 0:{ //clockIn command
                        int count = 0;
                        clockInEntryFound = 0;
                        while(!clockInEntryFound){
                            // Checks for next empty entry and logs it for current and end times
                            if(Week[localTime->tm_wday].startTime[count] == 0) clockInEntry = count;
                            if(Week[localTime->tm_wday].startTime[count] == 0) clockInEntryFound = 1;
                            count++;
                        }
                        // end check loop
                        clockInStarted = 1;
                        Week[localTime->tm_wday].startTime[clockInEntry] = timeNowSeconds();
                    }
                    break;

                case 1:{ //clockOut command
                    // Ends time and logs it
                    clockInStarted = 0;
                    Week[localTime->tm_wday].stopTime[clockInEntry] = timeNowSeconds();
                    // Allows user to choose group to log into
                    std::cout << "What group would you like to put this punch under? : ";
                    std::cin >> Week[localTime->tm_wday].groupTime[clockInEntry];
                    }
                    break;
                case 2:{ //menu command
                    // End clockIn Menu Loop
                        clockInRun = 0;
                    }
                    break;
                default:
                    break;
                }
                }
            }
            break;

        case 2: { // Edit Punch
            // Not implemented for assignment due to time constraint
            }
            break;

        case 3: { // View Punch
            // viewPunch Menu Bool Var's
            validInput = 0;
            clockInRun = 1;
            clockInStarted = 0;
            clockInEntry = 0;

            while(clockInRun){
                // viewPunch Greeting
                system("cls");
                std::cout <<  "\033[1;33m" << "Time Collector: Punch Viewer"    << "\033[0m" << std::endl;
                std::cout << "----------------------" << std::endl;
                std::cout << "Possible Commands: " << std::endl;
                std::cout << "\033[1;31m" << "/viewDay\n/viewGroup\n/menu" << "\033[0m" << std::endl << std::endl;

                // viewPunch User Command Line w/ validity
                std::cout << "Command Line:" << std::endl;

                while(!validInput){
                    std::cin >> promptOne;
                    if(promptOne == "/viewDay" || promptOne == "/viewGroup" || promptOne == "/menu"){
                        validInput = 1;
                        if(promptOne == "/viewDay") clockInMenu = 0;
                        if(promptOne == "/viewGroup") clockInMenu = 1;
                        if(promptOne == "/menu") clockInMenu = 2;
                    }
                    if(validInput==0){
                        std::cout << "\033[A\033[2K\r";
                    }
                }
                validInput = 0;

                // viewPunch Switch
                switch (clockInMenu)
                {
                case 0:{ // viewDay command
                        // Input and Checks for validity
                        clockInEntryFound = 0;
                        std::cout << std::endl << std::endl;
                        std::cout << "What day would you like to view? (Week Day)\n";
                        while(!clockInEntryFound){
                            int count = 0;
                            std::cin >> promptOne;
                            for(int i = 0; i < 7; i++){
                                if(promptOne == days[i]){
                                    clockInEntry = i;
                                    clockInEntryFound = 1;
                                    std::cout << std::endl << std::endl;
                                }
                            }
                            if(!clockInEntryFound) std::cout << "\033[A\033[2K\r";
                            //Outputs and exit code
                        }
                        punchCardDaily(Week,clockInEntry);
                        std::cout << "\033[31m" << "Press enter to exit." << "\033[0m" << std::endl;
                        std::cin.ignore();
                        std::cin.get();
                    }
                break;

                case 1:{ //viewGroup
                    // time collection var's
                    int week[7] = {0,0,0,0,0,0,0};
                    int weekTotal = 0;
                    // user input
                    std::cout << std::endl << std::endl;
                    std::cout << "\033[1;33m" << "What group would you like to view total time? :\n" << "\033[0m";
                    std::cin >> clockInEntry;
                    // loop all entries and log's if correct group
                    for(int i = 0; i < numberDays; i++){
                        for(int j = 0; j < 50; j++){
                            if(Week[i].groupTime[j] == clockInEntry){
                                weekTotal += (Week[i].stopTime[j]-Week[i].startTime[j]);
                                week[i] += (Week[i].stopTime[j]-Week[i].startTime[j]);
                            }
                        }
                    }

                    // output all pretty
                    std::cout << std::endl;
                    std::cout << "\033[1;33m" << "Group " << clockInEntry << " Summary" << "\033[0m" << std::endl;
                    std::cout << "----------------------" << std::endl;

                    for(int i = 0; i < 7; i++){
                        if(week[i] > 0){
                            std::cout << "\033[37m" << std::setw(12) << days[i] << " : ";
                            std::cout << "\033[36m" << secondToTimeStamp(week[i]) << "\033[0m" << std::endl;
                        }
                    }

                    std::cout << "----------------------" << std::endl;
                    std::cout << "\033[37m" << "Total : ";
                    std::cout << "\033[1;32m" << secondToTimeStamp(weekTotal) << "\033[0m" << std::endl;

                    std::cout << "\033[31m" << "Press enter to exit." << "\033[0m" << std::endl;
                    std::cin.ignore();
                    std::cin.get();

                    }
                    break;
                case 2:{ //menu command
                        clockInRun = 0;
                    }
                    break;
                default:
                    break;
                }
                }
            }
            break;

        case 4: { // Exit Program
            // goodbye
                std::cout <<  "\033[1;33m" << "Time Collector: Exit"    << "\033[0m" << std::endl;
                std::cout << "----------------------" << std::endl;
                std::cout << "\033[1;32m" << "Thank you for using." << std::endl << std::endl;
                std::cout << "\033[0m" << "Data Saved" << std::endl;
            // log file and exit
                punchCardWrite(Week);
                exit(0);
            }
            break;
        default:
            break;
        }
    }

    // another write for protection
    punchCardWrite(Week);
    return 0; 
}

void punchCardDaily(dayTime* dayStruct, int weekDay){
    for(int i = 0; i<4; i++){
        if(i==0){
            std::cout << "\033[1;33m";
            std::cout << days[weekDay];
            std::cout << ", DAY:MONTH:YEAR -> ";
        } else {
        std::cout << dayStruct[weekDay].timeStamp[i] << " , ";
        
        }
    }
    std::cout << "\033[0m";
    std::cout << std::endl;

    std::cout << "\033[32m";
    std::cout << "Start Times  (seconds from 00:00:00) : ";
    for(int i = 0;i<50; i++){
        if(dayStruct[weekDay].startTime[i]>0){
            std::cout << secondToTimeStamp(dayStruct[weekDay].startTime[i]) << " , ";
        }
    }
    std::cout << "\033[0m";
    std::cout << std::endl;

    std::cout << "\033[31m";
    std::cout << "Stop Times   (seconds from 00:00:00) : ";
    for(int i = 0;i<50; i++){
        if(dayStruct[weekDay].stopTime[i]>0){
            std::cout << secondToTimeStamp(dayStruct[weekDay].stopTime[i]) << " , ";
        }
    }
    std::cout << "\033[0m";
    std::cout << std::endl;

    std::cout << "\033[36m";
    std::cout << "Elapsed Time (seconds from 00:00:00) : ";
    for(int i = 0;i<50; i++){
        if(dayStruct[weekDay].startTime[i]>0){
            std::cout << secondToTimeStamp(dayStruct[weekDay].stopTime[i] - dayStruct[weekDay].startTime[i]) << " , ";
        }
    }
    std::cout << "\033[0m";
    std::cout << std::endl;

    std::cout << "\033[35m";
    std::cout << "Time Groups                          : ";
    for(int i = 0; i < 50; i++){
        if(dayStruct[weekDay].groupTime[i] > 0){
            std::cout << "        " << dayStruct[weekDay].groupTime[i] << " , ";
        }
    }
    std::cout << "\033[0m";
    std::cout << std::endl;

    std::cout << "Remaining Time (seconds) : ";
    std::cout << dayStruct[weekDay].currentElapse << std::endl;
}

void punchCardRead(dayTime* t){
    std::string oneLine;
    std::ifstream read(punchCardFile);
    std::string temp;
    int weekDay;
    
    for(int i = 0; i < numberDays; i++){ //Loop For everyday of week
        for(int j = 0; j < 4; j++){ // Loop For every line
            switch(j){
                case 0: {
                    read >> oneLine;
                    std::stringstream oneLineStream(oneLine);
                    int count = 0;
                    while(std::getline(oneLineStream, temp, ',')){
                        if(count<1){
                            weekDay = std::stoi(temp);
                            t[weekDay].timeStamp[0] = weekDay;
                        }else if(count<4){
                            t[weekDay].timeStamp[count] = std::stoi(temp);
                        } else {
                            t[weekDay].currentElapse = std::stoi(temp);
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
                        t[weekDay].startTime[count] = std::stoi(temp);
                        count++;
                    }
                }
                break;
                case 2: {
                    read >> oneLine;
                    std::stringstream oneLineStream(oneLine);
                    int count = 0;
                    while(std::getline(oneLineStream, temp, ',')){
                        t[weekDay].stopTime[count] = std::stoi(temp);
                        count++;
                    }
                }
                break;
                case 3: {
                    read >> oneLine;
                    std::stringstream oneLineStream(oneLine);
                    int count = 0;
                    while(std::getline(oneLineStream, temp, ',')){
                        t[weekDay].groupTime[count] = std::stoi(temp);
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

void punchCardWrite(dayTime* dayStruct){
    std::ofstream write(punchCardFile);
    
    for(int i = 0; i < numberDays; i++){ //Loop For everyday of week
        for(int j = 0; j < 4; j++){ // Loop For every line
            switch(j){
                case 0: {
                    for(int k = 0; k < 4; k++){
                        write << dayStruct[i].timeStamp[k] << ",";
                    }
                    write << dayStruct[i].currentElapse << std::endl;
                break;
                }
                case 1: {
                    for(int k = 0; k < 50; k++){
                        write << dayStruct[i].startTime[k] << ",";
                    }
                    write << std::endl;
                }
                break;
                case 2: {
                    for(int k = 0; k < 50; k++){
                        write << dayStruct[i].stopTime[k] << ",";
                    }
                    write << std::endl;
                }
                break;
                case 3: {
                    for(int k = 0; k < 50; k++){
                        write << dayStruct[i].groupTime[k] << ",";
                    }
                    write << std::endl;
                }
                break;
            }
        }
    }

}

std::string secondToTimeStamp(int t){

    int hours   = t / 3600;
    int minutes = (t % 3600) / 60;
    int seconds = t % 60;

    char buffer[9]; // "HH:MM:SS\0"
    std::sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

    return std::string(buffer);
}

int timeNowSeconds(){
    time_t now = time(NULL);
    struct tm* localTime = localtime(&now);
    int currentSeconds = localTime->tm_hour * 3600 + localTime->tm_min* 60 + localTime->tm_sec;
    return currentSeconds;
}

void debugStruct(dayTime* dayStruct){
    for(int i = 0; i < numberDays; i++){
        punchCardDaily(dayStruct,i);
    }
}