#include <iostream>
#include <string>
using namespace std;

class Player {
private:
    string name;
    int votes;

public:
    Player() : name(""), votes(0) {}

    void setName(const string& n) { name = n; }
    void addVote() { votes++; }
    string getName() const { return name; }
    int getVotes() const { return votes; }
};

class VotingSystem {
private:
    Player players[50];
    int playerCount;

    void sortByVotes() {
        for (int i = 0; i < playerCount - 1; i++) {
            for (int j = i + 1; j < playerCount; j++) {
                if (players[j].getVotes() > players[i].getVotes()) {
                    Player temp = players[i];
                    players[i] = players[j];
                    players[j] = temp;
                }
            }
        }
    }

public:
    VotingSystem() : playerCount(0) {}

    void addPlayer(const string& name) {
        if (playerCount < 50) {
            players[playerCount].setName(name);
            playerCount++;
            cout << "Player added: " << name << " (Index: " << playerCount << ")\n";
        } else {
            cout << "Player list is full!\n";
        }
    }

    void vote(int index) {
        if (index >= 0 && index < playerCount) {
            players[index].addVote();
            cout << "Vote counted for: " << players[index].getName() << "\n";
        } else {
            cout << "Invalid player index!\n";
        }
    }

    void showRankings() {
        sortByVotes();
        int totalVotes = 0;
        for (int i = 0; i < playerCount; i++) totalVotes += players[i].getVotes();

        cout << "\n--- Player Rankings ---\n";
        for (int i = 0; i < playerCount; i++) {
            double percentage = (totalVotes == 0) ? 0 : (players[i].getVotes() * 100.0 / totalVotes);
            cout << i + 1 << ". " << players[i].getName()
                 << " - " << players[i].getVotes() << " votes"
                 << " (" << percentage << "% )\n";
        }
    }

    void listPlayers() {
        if (playerCount == 0) {
            cout << "No players added yet.\n";
            return;
        }
        cout << "\nCurrent Players:\n";
        for (int i = 0; i < playerCount; i++) {
            cout << i + 1 << ") " << players[i].getName() << "\n";
        }
    }
};

int main() {
    VotingSystem system;
    int choice;

    while (true) {
        cout << "\n===== Ballon d'Or Voting Menu =====\n";
        cout << "1. Add Player\n2. Vote\n3. Show Rankings\n4. List Players\n0. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        cin.ignore(10000, '\n'); // Clear input buffer

        if (choice == 0) break;
        switch (choice) {
            case 1: {
                string name;
                cout << "Enter player name: ";
                getline(cin, name);
                if (!name.empty()) system.addPlayer(name);
                else cout << "Name cannot be empty.\n";
                break;
            }
            case 2: {
                system.listPlayers();
                int index;
                cout << "Enter player index to vote for: ";
                if (cin >> index) system.vote(index - 1);
                else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input.\n";
                }
                break;
            }
            case 3:
                system.showRankings();
                break;
            case 4:
                system.listPlayers();
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    cout << "\nThank you for using the Ballon d'Or Voting System!\n";
    return 0;
}
