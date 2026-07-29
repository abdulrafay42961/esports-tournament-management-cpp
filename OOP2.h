#ifndef OOP2_H
#define OOP2_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
void clearScreen();//to clear screen
class Participant {
protected: 
    int id;
    string name;
public:
    Participant() : id(0), name("Unknown") {}
    Participant(int i, string n) : id(i), name(n) {}
    virtual void display() = 0;
    virtual void save(ofstream& out) = 0; 
    string getName() { 
        return name; 
    }
    virtual ~Participant() {}
};
class PlayerClass : public Participant {
    string role; 
public:
    PlayerClass() : Participant(), role("Undefined") {}
    PlayerClass(int i, string n, string r) : Participant(i, n), role(r) {}
    void display() override;
    void save(ofstream& out) override;
};
class Coach : public Participant {
    int exp;
public:
    Coach() : Participant(), exp(0) {}
    Coach(int i, string n, int e) : Participant(i, n), exp(e) {}
    void display() override;
    void save(ofstream& out) override;
};
class Team {
    string teamName;
    string password; 
    PlayerClass* members[5]; 
    Coach* teamCoach;        
    int points;
public:
    Team();
    void setTeamName(string n) { teamName = n; }
    string getTeamName() { return teamName; }
    string getPassword() { return password; } 
    int getPoints() { return points; }
    void setPoints(int p) { points = p; }
    void addPoints(int p) { points += p; }  
    void inputTeamData();
    void displayTeam();
    void saveTeam(ofstream& out);
    ~Team();
};
struct SimpleTeamRecord {
    string name;
    int points;
    string restOfData;
};
bool checkLogin(string filename, string username, string password);
void viewAllTeams();
void handleCheating();
void resetAllPoints(); 
void startTournament();
void viewMatchHistoryMenu();
void teamInfoLogin(); 
void saveTournamentToHistory(string tTourName, SimpleTeamRecord activeTeams[], int totalTeams, string tempHistoryFile);
void viewPastTournament();
#endif
