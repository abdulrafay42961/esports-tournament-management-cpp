#include "OOP2.h"
#include <sstream>
void clearScreen() {
#ifdef _WIN32
    system("cls");// Windows ke liye screen clear
#else
    system("clear");// Mac ya Linux ke liye screen clear
#endif
}
void PlayerClass::display() {
    cout << "[" << role << "] ID: " << id << " | Name: " << name << endl; 
}
void PlayerClass::save(ofstream& out) {
    out << id << "," << name << "," << role << "|";
}
void Coach::display() { 
    cout << "[Coach] Name: " << name << " (" << exp << " yrs exp)" << endl; 
}
void Coach::save(ofstream& out) {
    out << name << "," << exp << "|"; 
}
Team::Team() : teamCoach(NULL), points(0), password("") {
    for(int i = 0; i < 5; i++){
        members[i] = NULL; 
    }
}
void Team::inputTeamData() {
    clearScreen();
    cout << "\n\n\n\n\n\n\n"; // Screen ke beech mein text lane ke liye spacing
    cout << "                             ==================================================" << endl;
    cout << "                                         CONFIGURING NEW TEAM            " << endl;
    cout << "                             ==================================================" << endl;
    cout << "                              Enter Team Name : ";   
    /* cin.peek() check karta hai ke agla character newline (\n) toh nahi hai.
       Agar pichle kisi input se '\n' buffer mein reh gaya ho, toh cin.ignore() usko uda deta hai
       taake getline() skip na ho aur user se sahi input le sake.
    */
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, teamName);
    cout << "                              Create Team Password       : ";
    getline(cin, password); 
    string cName; 
    int cExp;
    cout << "                              Enter Coach Name           : "; 
    getline(cin, cName);
    cout << "                              Enter Coach Exp (years)    : "; 
    cin >> cExp;  
    teamCoach = new Coach(0, cName, cExp);
    for(int i = 0; i < 5; i++) {
        int id; 
        string pName;
        string role = (i == 4) ? "Reserve" : "Main"; // 0,1,2,3 Main Player, 4th wala Reserve player
        cout << "\n                             [" << role << " Player " << (i == 4 ? 1 : i+1) << "] ID  : ";
        cin >> id;
        /* cin >> id ke baad jo enter (\n) dabaya jata hai, wo buffer mein reh jata hai.
           cin.ignore(10000, '\n') us enter ko saaf karta hai taake agla getline() sahi se name input le sake.
        */
        cin.ignore(10000, '\n'); 
        cout << "                                 Name: ";
        getline(cin, pName);
        members[i] = new PlayerClass(id, pName, role);
    }
}
void Team::displayTeam() {
    cout << "\n==================================================" << endl;
    cout << "TEAM: " << teamName << " | POINTS: " << points << endl;
    cout << "--------------------------------------------------" << endl;
    if(teamCoach) teamCoach->display();
    for(int i = 0; i < 5; i++) {
        if(members[i]) members[i]->display();
    }
    cout << "==================================================" << endl;
}
void Team::saveTeam(ofstream& out) {
    out << teamName << ":" << points << ":";
    if(teamCoach) teamCoach->save(out);
    for(int i = 0; i < 5; i++){
         if(members[i]) members[i]->save(out);
    }   
    out << endl; 
}
Team::~Team() {
    delete teamCoach;
    for(int i = 0; i < 5; i++){
        delete members[i];
    }
}
bool checkLogin(string filename, string username, string password) {
    ifstream file(filename);
    string fUser, fPass;
    if (file.is_open()) {
        while (file >> fUser) {
            file >> fPass; 
            if (fUser == username && fPass == password) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}
void viewAllTeams() {
    clearScreen();
    ifstream inFile("Teams_Database.txt");
    cout << "==================================================" << endl;
    cout << "            REGISTERED TEAMS DATABASE" << endl;
    cout << "==================================================" << endl;   
    if (!inFile.is_open()) {
        cout << "[Info] No teams registered yet." << endl;
        cout << "==================================================" << endl;
        cout << "\nPress Enter to return...";       
        /* cin.ignore() buffer saaf karta hai aur cin.get() program ko tab tak rokta hai 
           jab tak user Enter key nahi daba deta.
        */
        cin.ignore(); cin.get();
        return;
    }
    string tName, tPoints, remainingData;
    int count = 1;
    while (getline(inFile, tName, ':')) {    
        getline(inFile, tPoints, ':');       
        getline(inFile, remainingData);      
        cout << "[" << count << "] Team: " << tName << endl;
        cout << "    Score: " << tPoints << " Points" << endl;
        cout << "--------------------------------------------------" << endl;
        count++;
    }
    inFile.close();
    cout << "\nPress Enter to return...";
    // User ke Enter dabane ka wait karne ke liye
    cin.ignore(); cin.get();
}
void handleCheating() {
    clearScreen();
    string cheatTeam, opponentTeam;
    int severity;   
    cout << "==================================================" << endl;
    cout << "              ANTI-CHEAT ENFORCEMENT PANEL" << endl;
    cout << "==================================================" << endl;
    cout << "Enter Cheating Team Name: ";   
    // Input buffer se purani newline (\n) saaf karne ke liye taake getline skip na ho
    if (cin.peek() == '\n') cin.ignore(); 
    getline(cin, cheatTeam);
    cout << "Enter Opponent Team Name: ";
    getline(cin, opponentTeam);
    cout << "Select Cheat Severity Level (1-3): ";
    cin >> severity;
    ifstream inFile("Teams_Database.txt");
    ofstream tempFile("Temp_Database.txt"); 
    if (!inFile.is_open()) return;
    string tName, tPointsStr, restOfData;
    bool cheatTeamFound = false;
    bool opponentTeamFound = false;
    while (getline(inFile, tName, ':')) { // ':' delimiter hai jo data ko alag karta hai
        getline(inFile, tPointsStr, ':');  
        getline(inFile, restOfData);       
        int tPoints = stoi(tPointsStr);
        if (tName == cheatTeam) {
            cheatTeamFound = true; 
            if (severity == 1) tempFile << tName << ":" << tPoints << ":" << restOfData << endl;
            else if (severity == 2) tempFile << tName << ":" << (tPoints - 2) << ":" << restOfData << endl; 
            else if (severity == 3) tempFile << tName << ":" << 0 << ":" << restOfData << endl;           
        } 
        else if (tName == opponentTeam) {
            opponentTeamFound = true; 
            if (severity == 1) tPoints += 1;
            else if (severity == 2) tPoints += 2;  
            tempFile << tName << ":" << tPoints << ":" << restOfData << endl; 
        } 
        else {
            tempFile << tName << ":" << tPoints << ":" << restOfData << endl;
        }
    }
    inFile.close();
    tempFile.close();
    if (!cheatTeamFound || !opponentTeamFound) {
        remove("Temp_Database.txt"); 
        cout << "\n[Error] Data update failed!" << endl;
        if (!cheatTeamFound) {
            cout << "--> Team '" << cheatTeam << "' does not exist!" << endl;
        }
        if (!opponentTeamFound) {
            cout << "--> Team '" << opponentTeam << "' does not exist!" << endl;
        }
    } 
    else {
        remove("Teams_Database.txt");
        rename("Temp_Database.txt", "Teams_Database.txt");
        cout << "\n[Success] Penalties applied successfully!" << endl;
    }
    cout << "\nPress Enter to return...";
    // Screen hold karne aur enter handle karne ke liye
    if (cin.peek() == '\n') cin.ignore(); 
    cin.get();
}
void resetAllPoints() {
    clearScreen();
    ifstream inFile("Teams_Database.txt");
    ofstream tempFile("Temp_Database.txt");
    if (!inFile.is_open()) {
        cout << "\nDatabase file not found!!" << endl;
        cout << "\nPress Enter to return...";
        cin.ignore(); 
        cin.get();
        return;
   }
    string tName, tPointsStr, restOfData;
    int resetCount = 0;
    while (getline(inFile, tName, ':')) {
        getline(inFile, tPointsStr, ':'); 
        getline(inFile, restOfData);      
        tempFile << tName << ":" << 0 << ":" << restOfData << endl;
        resetCount++;
    }
    inFile.close();
    tempFile.close();
    remove("Teams_Database.txt");
    rename("Temp_Database.txt", "Teams_Database.txt");
    ofstream resetStatus("Tournament_Status.txt");
    resetStatus << "0" << endl;
    resetStatus.close();
    ofstream resetHistory("Match_History.txt"); 
    resetHistory.close();
    cout << "==================================================" << endl;
    cout << "[Success] Resetted points for " << resetCount << " teams to 0!" << endl;
    cout << "History logs and tournament status cleared." << endl;
    cout << "==================================================" << endl;
    cout << "\nPress Enter to return...";
    cin.ignore(); cin.get();
}
void saveTournamentToHistory(string tTourName, SimpleTeamRecord activeTeams[], int totalTeams, string tempHistoryFile) {
    ofstream historyFile("Tournament_History.txt", ios::app); // ios::app taake purana data delete na ho aur naya append ho
    if (!historyFile.is_open()) return;
    historyFile << "START_TOURNAMENT:" << tTourName << endl;
    historyFile << "TEAMS_COUNT:" << totalTeams << endl;
    int maxPoints = -1;
    for (int i = 0; i < totalTeams; i++) {
        historyFile << "TEAM_SCORE:" << activeTeams[i].name << "," << activeTeams[i].points << endl;
        if (activeTeams[i].points > maxPoints) maxPoints = activeTeams[i].points;
    }
    for (int i = 0; i < totalTeams; i++) {
        if (activeTeams[i].points == maxPoints) {
            historyFile << "WINNER:" << activeTeams[i].name << endl;
        }
    }
    ifstream tempHist(tempHistoryFile);
    string line;
    historyFile << "MATCHES_START" << endl;
    while (getline(tempHist, line)) {
        if (!line.empty()) {
            historyFile << "MATCH:" << line << endl;
        }
    }
    tempHist.close();
    historyFile << "END_TOURNAMENT:" << tTourName << endl << endl;
    historyFile.close();
}
void startTournament() {
    clearScreen();
    ifstream inFile("Teams_Database.txt");
    if (!inFile.is_open()) {
        cout << "\nNo team Found !!\nRegister teams first!!" << endl;
        cout << "\nPress Enter to return...";
        cin.ignore(); 
        cin.get();
        return;
    }
    SimpleTeamRecord activeTeams[50];
    int totalTeams = 0;
    string tName, tPointsStr, restOfData;
    while (getline(inFile, tName, ':') && totalTeams < 50) {
        getline(inFile, tPointsStr, ':');
        getline(inFile, restOfData);
        activeTeams[totalTeams].name = tName;
        activeTeams[totalTeams].points = stoi(tPointsStr);
        activeTeams[totalTeams].restOfData = restOfData;
        totalTeams++;
    }
    inFile.close();
    if (totalTeams < 2) {
        cout << "\nA minimum of 2 teams is required to proceed!" << endl;
        cout << "\nPress Enter to return...";
        cin.ignore(); 
        cin.get();
        return;
    }
    string tournamentName;
    cout << "\nEnter Tournament Name: ";   
    // Buffer clear check taake agla getline() seedha execute ho bina skip huay
    if (cin.peek() == '\n') cin.ignore(); 
    getline(cin, tournamentName);
    ofstream statusOut("Tournament_Status.txt");
    statusOut << 1 << endl;
    statusOut.close();
    ofstream clearHistory("Temp_Current_Match_History.txt");
    clearHistory.close();
    ofstream historyOut("Temp_Current_Match_History.txt", ios::app); 
    cout << "================================" << endl;
    cout << "      TOURNAMENT: " << tournamentName << " STARTED" << endl;
    cout << "================================" << endl;
    for (int i = 0; i < totalTeams; i++) {
        for (int j = i + 1; j < totalTeams; j++) {
            int attempt = 1;
            int finalOutcome = 0; 
            while (attempt <= 3) {
                if (attempt == 1) {
                    cout << "\nMATCH: " << activeTeams[i].name << " VS " << activeTeams[j].name << endl;
                } else {
                    cout << "\nREMATCH (" << attempt << "/3): " << activeTeams[i].name << " VS " << activeTeams[j].name << endl;
                }
                cout << " 1. " << activeTeams[i].name << " WINS" << endl;
                cout << " 2. " << activeTeams[j].name << " WINS" << endl;
                cout << " 3. DRAW" << endl;
                cout << " Choice (1-3): ";
                int matchResult;
                cin >> matchResult;
                /* VALIDATION LOOP: 
                   cin.fail() tab true hota hai agar user number ki jagah koi alphabet/character daal de.
                   matchResult < 1 || matchResult > 3 check karta hai ke option sirf 1, 2 ya 3 ho.
                */
                while (cin.fail() || matchResult < 1 || matchResult > 3) {
                    cin.clear(); // cin ki error state ko reset karta hai
                    string discard;
                    getline(cin, discard); // buffer mein mojood galat input ko nikal deta hai
                    cout << "Invalid! Enter choice 1, 2, or 3 only: ";
                    cin >> matchResult;
                }
                if (matchResult == 1) { 
                    finalOutcome = 1; 
                    break; 
                } 
                else if (matchResult == 2) { 
                    finalOutcome = 2; 
                    break; 
                }
                else { 
                    if (attempt < 3) {
                        cout << "[Draw declared] Rematch required!" << endl;
                        attempt++;
                    } else {
                        finalOutcome = 3;
                        break;
                    }
                }
            }
            if (finalOutcome == 1) {
                activeTeams[i].points += 2;
                if (historyOut.is_open()) historyOut << activeTeams[i].name << ":" << activeTeams[j].name << ":" << activeTeams[i].name << "_WINS" << endl;
            } 
            else if (finalOutcome == 2) {
                activeTeams[j].points += 2;
                if (historyOut.is_open()) historyOut << activeTeams[i].name << ":" << activeTeams[j].name << ":" << activeTeams[j].name << "_WINS" << endl;
            } 
            else if (finalOutcome == 3) {
                cout << "\nPermanent Tie! Both get 1 point." << endl;
                activeTeams[i].points += 1;
                activeTeams[j].points += 1;
                if (historyOut.is_open()) historyOut << activeTeams[i].name << ":" << activeTeams[j].name << ":DRAW" << endl;
            }
        }
    }
    historyOut.close();
    int maxPoints = -1;
    for (int i = 0; i < totalTeams; i++) {
        if (activeTeams[i].points > maxPoints) maxPoints = activeTeams[i].points;
    }
    cout << "\n==================================================" << endl;
    cout << "                    TOURNAMENT WINNERS" << endl;
    cout << "==================================================" << endl;
    for (int i = 0; i < totalTeams; i++) {
        if (activeTeams[i].points == maxPoints) {
            cout << "CHAMPION: " << activeTeams[i].name << " (Score: " << maxPoints << ") " << endl;
        }
    }
    cout << "==================================================" << endl;
    saveTournamentToHistory(tournamentName, activeTeams, totalTeams, "Temp_Current_Match_History.txt");
    remove("Match_History.txt");
    rename("Temp_Current_Match_History.txt", "Match_History.txt");
    ofstream outFile("Teams_Database.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < totalTeams; i++) {
            outFile << activeTeams[i].name << ":" << 0 << ":" << activeTeams[i].restOfData << endl;
        }
        outFile.close();
    }
    ofstream resetStatus("Tournament_Status.txt");
    resetStatus << "0" << endl;
    resetStatus.close();
    cout << "\n[System] Tournament data archived. Points reset to 0!";
    cout << "\nPress Enter to return to menu...";
    // Menu par wapis jane ke liye input hold
    cin.ignore(); cin.get();
}
void viewMatchHistoryMenu() {
    clearScreen();
    cout << "==================================================" << endl;
    cout << "            GLOBAL MATCH HISTORY LOGS" << endl;
    cout << "==================================================" << endl;
    ifstream histFile("Match_History.txt");
    if (!histFile.is_open()) {
        cout << "[Info] No history logs found." << endl;
        cout << "==================================================" << endl;
        cout << "\nPress Enter to return...";
        cin.ignore(); cin.get();
        return;
    }
    string line;
    int matchCounter = 1;
    bool foundAny = false;
    while (getline(histFile, line)) {
        if (line.empty() || line == "\r" || line == "\n") continue; // Khali lines ko skip karne ke liye
        stringstream ss(line);
        string tA, tB, outcome;
        if (getline(ss, tA, ':') && getline(ss, tB, ':') && getline(ss, outcome)) {
            // Windows style file endings (\r\n) mein se \r hatane ke liye check
            if (!outcome.empty() && outcome[outcome.length() - 1] == '\r') {
                outcome.erase(outcome.length() - 1);
            }
            foundAny = true;
            cout << "[" << matchCounter << "] FIXTURE: " << tA << " VS " << tB << endl;
            if (outcome == "DRAW") {
                cout << "    RESULT : Tied" << endl;
            } else if (outcome == tA + "_WINS") {
                cout << "    RESULT : Winner -> " << tA << endl;
            } else if (outcome == tB + "_WINS") {
                cout << "    RESULT : Winner -> " << tB << endl;
            } else {
                cout << "    RESULT : " << outcome << endl;
            }
            cout << "--------------------------------------------------" << endl;
            matchCounter++;
        }
    }
    histFile.close();
    if (!foundAny) cout << "[Info] Zero entries found." << endl;
    cout << "==================================================" << endl;
    cout << "\nPress Enter to return...";
    cin.ignore(); cin.get();
}
void teamInfoLogin() {
    clearScreen();
    string logTeamName, logPassword;
    cout << "==================================================" << endl;
    cout << "             TEAM DASHBOARD & STATS PORTAL" << endl;
    cout << "==================================================" << endl;
    cout << "Enter Team Name: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, logTeamName);
    cout << "Enter Password : ";
    getline(cin, logPassword); 
    if (!checkLogin("leaderLogin.txt", logTeamName, logPassword)) {
        cout << "\nAccess Denied! Credentials mismatch." << endl;
        cout << "\nPress Enter to return...";
        cin.get();
        return;
    }
    ifstream dbFile("Teams_Database.txt");
    if (!dbFile.is_open()) {
        cout << "[Error] Teams Database file missing!" << endl;
        cout << "\nPress Enter to return...";
        cin.get();
        return;
    }
    clearScreen();
    cout << "\n";
    cout << "==================================================" << endl;
    cout << "         ACCESS GRANTED! WELCOME " << logTeamName << endl;
    cout << "==================================================" << endl;
    string tName, tPointsStr, restOfData;
    bool teamFoundInDB = false;
    while (getline(dbFile, tName, ':')) {
        getline(dbFile, tPointsStr, ':');
        getline(dbFile, restOfData);
        if (tName == logTeamName) {
            teamFoundInDB = true;
            cout << "[TEAM " << logTeamName << " & DETAILS]" << endl;
            cout << "Current Points: " << tPointsStr << endl;
            cout << "--------------------------------------------------" << endl;
            stringstream ss(restOfData);
            string entity;
            if (getline(ss, entity, '|')) {
                stringstream coachSS(entity);
                string cName, cExp;
                if(getline(coachSS, cName, ',') && getline(coachSS, cExp, ',')) {
                    cout << "Coach: " << cName << " (" << cExp << " Years Exp)" << endl;
                }
            }
            cout << "Players:" << endl;
            while (getline(ss, entity, '|')) {
                if(entity.empty() || entity == "\r" || entity == "\n") continue;
                stringstream playerSS(entity);
                string pId, pName, pRole;
                if (getline(playerSS, pId, ',') && getline(playerSS, pName, ',') && getline(playerSS, pRole, ',')) {
                    cout << "  -> [" << pRole << "] ID: " << pId << " | Name: " << pName << endl;
                }
            }
            break;
        }
    }
    dbFile.close();
    if (!teamFoundInDB) {
        cout << "[Warning] Team details not found in Database." << endl;
    }
    cout << "==================================================" << endl;
    cout << "[MATCH HISTORY SUMMARY]" << endl;
    cout << "--------------------------------------------------" << endl;
    ifstream histFile("Match_History.txt");
    if (!histFile.is_open()) {
        cout << "[Info] Match History file not found." << endl;
    } else {
        string line;
        int totalMatches = 0, wins = 0, losses = 0, draws = 0;
        while (getline(histFile, line)) {
            if (line.empty() || line == "\r" || line == "\n") continue;
            stringstream ss(line);
            string tA, tB, outcome;
            if (getline(ss, tA, ':') && getline(ss, tB, ':') && getline(ss, outcome)) {
                if (!outcome.empty() && outcome[outcome.length() - 1] == '\r') {
                    outcome.erase(outcome.length() - 1);
                }
                if (tA == logTeamName || tB == logTeamName) {
                    totalMatches++;
                    if (outcome == "DRAW") {
                        draws++;
                    } else if (outcome == logTeamName + "_WINS") {
                        wins++;
                    } else if (outcome == tA + "_WINS" || outcome == tB + "_WINS") {
                        losses++; 
                    }
                }
            }
        }
        histFile.close();
        if (totalMatches == 0) {
            cout << "No matches recorded for this team yet." << endl;
        } else {
            cout << "Total Matches Played : " << totalMatches << endl;
            cout << "Matches Won : " << wins << endl;
            cout << "Matches Lost : " << losses << endl;
            cout << "Matches Drawn : " << draws << endl;
        }
    }
    cout << "==================================================" << endl;
    cout << "\nPress Enter to return...";
    cin.get();
}
void viewPastTournament() {
    clearScreen();
    string searchName;
    cout << "==================================================" << endl;
    cout << "            SEARCH PAST TOURNAMENT LOGS" << endl;
    cout << "==================================================" << endl;
    cout << "Enter Tournament Name to Search: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, searchName);
    ifstream file("Tournament_History.txt");
    if (!file.is_open()) {
        cout << "\n[Info] No past tournament history found." << endl;
        cout << "\nPress Enter to return...";
        cin.get();
        return;
    }
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line == "START_TOURNAMENT:" + searchName) {
            found = true;
            clearScreen();
            cout << "==================================================" << endl;
            cout << "         HISTORICAL DATA: " << searchName << endl;
            cout << "==================================================" << endl;
            cout << "[FINAL STANDINGS & SCORES]" << endl;
            while (getline(file, line) && line != "END_TOURNAMENT:" + searchName) {
                stringstream ss(line);
                string key, value;
                getline(ss, key, ':');
                getline(ss, value);
                if (key == "TEAM_SCORE") {
                    stringstream teamSS(value);
                    string tName, tPoints;
                    getline(teamSS, tName, ',');
                    getline(teamSS, tPoints);
                    cout << "  -> Team: " << tName << " | Final Score: " << tPoints << " Points" << endl;
                }
                else if (key == "WINNER") {
                    cout << "--------------------------------------------------" << endl;
                    cout << "CHAMPION/WINNER: " << value << endl;
                    cout << "--------------------------------------------------" << endl;
                    cout << "[MATCH FIXTURES & RESULTS]" << endl;
                }
                else if (key == "MATCH") {
                    stringstream matchSS(value);
                    string tA, tB, outcome;
                    getline(matchSS, tA, ':');
                    getline(matchSS, tB, ':');
                    getline(matchSS, outcome);
                    cout << "Match: " << tA << " VS " << tB << endl;
                    if (outcome == "DRAW") {
                        cout << "Result: Tied (Draw)" << endl;
                    } else if (outcome == tA + "_WINS") {
                        cout << "Result: Winner -> " << tA << " | Loser -> " << tB << endl;
                    } else if (outcome == tB + "_WINS") {
                        cout << "Result: Winner -> " << tB << " | Loser -> " << tA << endl;
                    }
                    cout << "............................................." << endl;
                }
            }
            cout << "==================================================" << endl;
            break;
        }
    }
    if (!found) {
        cout << "\n[Error] Tournament '" << searchName << "' not found in logs!" << endl;
    }
    file.close();
    cout << "\nPress Enter to return...";
    cin.get();
}
