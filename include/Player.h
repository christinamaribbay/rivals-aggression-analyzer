//
// Created by rohan on 7/9/2026.
//

#ifndef RIVALS_AGGRESSION_ANALYZER_PLAYER_H
#define RIVALS_AGGRESSION_ANALYZER_PLAYER_H
#include <string>
using namespace std;

class Player {
private:
    string rank;
    string chatMessage;
    float chatAgressionScore;

public:
    Player();
    Player(const string& rank, const string& chatMessage);

    string getRank() const;
    string getChatMessage() const;
    float getChatAgressionScore() const;

    void setRank(const string& rank);
    void setChatMessage(const string& message);
    void setChatAgressionScore(float score);
};


#endif //RIVALS_AGGRESSION_ANALYZER_PLAYER_H
