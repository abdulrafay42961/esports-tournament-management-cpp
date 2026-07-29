#include "OOP2.h"
int main() {
    int mainChoice;
    ifstream testFile("Tournament_Status.txt");
    if(!testFile.is_open()) {
        ofstream createStat("Tournament_Status.txt");
        createStat << "0" << endl; 
        createStat.close();
    } else {
        testFile.close();
    }
    while (true) {
        clearScreen(); 
        cout << "==================================================" << endl;
        cout << "               TOURNAMENT MAIN MENU" << endl;
        cout << "==================================================" << endl;
        cout << "1. Admin Access" << endl;
        cout << "2. Player Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> mainChoice;
        while (cin.fail() || mainChoice < 1 || mainChoice > 3) {
            cin.clear(); string discard; getline(cin, discard);
            cout << "Invalid! Please enter 1, 2, or 3: ";
            cin >> mainChoice;
        }
        if (mainChoice == 3) {
            clearScreen();
            cout << "\nExiting program. Goodbye!\n" << endl;
            break;
        }
        if (mainChoice == 1) {
            clearScreen();
            string un, pw;
            cout << "==================================================" << endl;
            cout << "                ADMIN LOGIN INFO" << endl;
            cout << "==================================================" << endl;
            cout << "Admin Username: ";
            cin >> un;
            cout << "Admin Password: ";
            cin >> pw;
            if (checkLogin("admin.txt", un, pw)) {
                int adminChoice;
                while (true) {
                    clearScreen();
                    cout << "==================================================" << endl;
                    cout << "                ADMIN SUB-MENU" << endl;
                    cout << "==================================================" << endl;
                    cout << "1. View All Registered Teams" << endl;
                    cout << "2. Punish Cheating Team" << endl;
                    cout << "3. Reset All Teams Points" << endl; 
                    cout << "4. View Past Tournament Logs" << endl; 
                    cout << "5. Logout" << endl;                   
                    cout << "--------------------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> adminChoice;
                    while (cin.fail() || adminChoice < 1 || adminChoice > 5) {
                        cin.clear(); string discard; getline(cin, discard);
                        cout << "Invalid option! Enter 1-5: ";
                        cin >> adminChoice;
                    }
                    if (adminChoice == 5) break;
                    if (adminChoice == 1) viewAllTeams();
                    else if (adminChoice == 2) handleCheating();
                    else if (adminChoice == 3) resetAllPoints(); 
                    else if (adminChoice == 4) viewPastTournament();
                }
            } else {
                cout << "\nInvalid Admin Credentials!!" << endl;
                cout << "\nPress Enter to retry...";
                cin.ignore(); cin.get();
            }
        }
        else if (mainChoice == 2) {
            int playerChoice;
            while (true) {
                clearScreen();
                cout << "==================================================" << endl;
                cout << "                PLAYER MENU" << endl;
                cout << "==================================================" << endl;
                cout << "1. Register Team" << endl;
                cout << "2. Team Info (Credentials Check)" << endl; 
                cout << "3. View Match History Logs" << endl; 
                cout << "4. Start Tournament" << endl; 
                cout << "5. Back" << endl;
                cout << "--------------------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> playerChoice;
                while (cin.fail() || playerChoice < 1 || playerChoice > 5) {
                    cin.clear(); string discard; getline(cin, discard);
                    cout << "Invalid option! Enter 1-5: ";
                    cin >> playerChoice;
                }
                if (playerChoice == 5) break; 
                if (playerChoice == 1) {
                    Team singleTeam;
                    singleTeam.inputTeamData();
                    ofstream loginFile("leaderLogin.txt", ios::app);
                    if(loginFile.is_open()) {
                        loginFile << singleTeam.getTeamName() << " " << singleTeam.getPassword() << endl;
                        loginFile.close();
                    }
                    ofstream outFile("Teams_Database.txt", ios::app);
                    if (outFile.is_open()) {
                        singleTeam.saveTeam(outFile);
                        outFile.close();
                        cout << "\nTeam registered successfully!";
                    } else {
                        cout << "\nFile saving error!!";
                    }
                    cout << "\nPress Enter to continue...";
                    cin.ignore(); cin.get();
                } 
                else if (playerChoice == 2) {
                    teamInfoLogin(); 
                } 
                else if (playerChoice == 3) {
                    viewMatchHistoryMenu(); 
                }
                else if (playerChoice == 4) {
                    startTournament(); 
                }
            }
        } 
    }
    return 0;
}
