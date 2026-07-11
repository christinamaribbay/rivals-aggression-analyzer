#include "SplayTree.h"
#include "hash_table.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

vector<string> parseMessage(const string &chatMessage) {
    vector<string> words;
    stringstream ss(chatMessage);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}


int main() {
    //initialize data structures with words
    HashTable hash;
    SplayTree splayTree;
    const vector<string> TOXIC_WORDS = {"trash", "diff", "uninstall", "noob", "report", "thrower", "useless", "bot", "afk", "suck", "garbage", "garbo", "quit", "ez"};
    const vector<string> SAFE_WORDS = {"wp", "gg", "nice", "clean", "clutch", "save", "glhf", "mb", "good"};
    const vector<string> FILLER_WORDS = {"team", "you", "are", "my", "the", "bro", "mid", "game", "play", "stop"};
    //insert words and aggression factors
    for (auto word : TOXIC_WORDS) {
        hash.insertWord(word, 1.0);
        splayTree.insert(word, 1.0);
    }
    for (auto word : SAFE_WORDS) {
        hash.insertWord(word, 0.0);
        splayTree.insert(word, 0.0);
    }
    for (auto word : FILLER_WORDS) {
        hash.insertWord(word, 0.5);
        splayTree.insert(word, 0.5);
    }

    //parse player data
    ifstream file("players_dataset.txt");
    if (!file.is_open()) {
        cerr<<"Error opening file"<<endl;
        return 1;
    }
    //if data file opens successfully, prepare to read data
    vector<Player> players;
    string line;

    getline(file,line);
    while (getline(file,line)) {
        stringstream ss(line);
        string rank;
        string chatMessage;
        getline(ss, rank, '|');
        getline(ss, chatMessage,'|');

        Player player(rank, chatMessage);
        players.push_back(player);
    }
    file.close();

    //terminal interface loop
    bool active = true;
    int option;
    cout << "******** Welcome to the Rivals Aggression Analyzer ********" << endl;
    cout << "Please select an option from the menu." << endl;
    cout << "1.) See rank aggression score distribution"<< endl;
    cout << "2.) Get aggression score for a message "<< endl;
    cout << "3.) Compare splay and hash performance" << endl;
    cout << "4.) Quit" << endl;
    cin >> option;
    while (active) {
        if (option == 1) {
            for (auto& p : players) {
                string message = p.getChatMessage();
                vector<string> words = parseMessage(message);
                float aggFactor = 0.0;
                //for each word calculate aggressionFactor
                for (auto word : words) {
                    if (hash.searchWord(word) == -1.0f) {
                        aggFactor += 0.5;
                    } else {
                        aggFactor += hash.searchWord(word);
                    }
                }
                aggFactor /= words.size();
                p.setChatAgressionScore(aggFactor);
            }//end of player vector - all players should now have an aggression factor
            map<string, float> aggPerRank;
            map<string, int> numPerRank;
            for (const auto& p : players) {
                aggPerRank[p.getRank()] += p.getChatAgressionScore(); //add total aggression scores per rank to get overall rank aggScore
                numPerRank[p.getRank()]++; //add up amound of players in each rank
            }
            //print ranks in order and use above 2 maps to calculate avg per rank
            vector<string> orderedRanks = {"Bronze", "Silver", "Gold", "Platinum", "Diamond", "Grandmaster", "Celestial"};
            cout << "Average aggression scores per rank: " << endl;
            for (const auto& rank : orderedRanks) {
                float avgScore = aggPerRank[rank] / numPerRank[rank];
                cout << fixed << setprecision(2);
                cout << rank << ": " << avgScore << endl;
            }
        }
        else if (option == 2) {
            string message;
            cout << "Enter message to calculate aggression score: ";
            cin.ignore(10000, '\n');
            getline(cin, message);
            vector<string> words = parseMessage(message);
            float aggScore = 0.0;
            for (auto word : words) {
                if (hash.searchWord(word) == -1.0f) {
                    aggScore += 0.5;
                } else {
                    aggScore += hash.searchWord(word);
                }
            }
            aggScore /= words.size();
            cout << fixed << setprecision(2);
            cout << "Aggression Score: " << aggScore << endl;
        }
        else if (option == 3) {
            //time hash
            auto startHash = high_resolution_clock::now();
            for (auto& p : players) {
                string message = p.getChatMessage();
                vector<string> words = parseMessage(message);
                float aggFactor = 0.0;

                for (auto word : words) {
                    if (hash.searchWord(word) == -1.0f) {
                        aggFactor += 0.5;
                    } else {
                        aggFactor += hash.searchWord(word);
                    }
                }
            }

            auto stopHash = high_resolution_clock::now();
            auto hashTime = duration_cast<milliseconds>(stopHash - startHash);

            //time splay
            auto startSplay = high_resolution_clock::now();

            for (auto& p : players) {
                string message = p.getChatMessage();
                vector<string> words = parseMessage(message);
                float aggFactor = 0.0;

                for (auto word : words) {
                    if (splayTree.search(word) == -1.0f) {
                        aggFactor += 0.5;
                    } else {
                        aggFactor += splayTree.search(word);
                    }
                }
            }

            auto stopSplay = high_resolution_clock::now();
            auto splayTime = duration_cast<milliseconds>(stopSplay - startSplay);

            //print the times
            cout << "------ Performance -----" << endl;
            cout << "Hash Time: " << hashTime.count() << " microseconds" << endl;
            cout << "Splay Time: " << splayTime.count() << " microseconds" << endl;

        } else if (option == 4) {
            cout << "Thank you for using the Rivals Aggression Analyzer!";
            active = false;
            return 0;
        } else {
            cout << "Invalid option. Please select an option from the menu." << endl;
            cin >> option;
        }

        cout << endl <<"Please select another menu option." << endl;
        cout << "1.) See rank aggression score distribution"<< endl;
        cout << "2.) Get aggression score for a message "<< endl;
        cout << "3.) Compare splay and hash performance" << endl;
        cout << "4.) Quit" << endl;
        cin >> option;
    }

}