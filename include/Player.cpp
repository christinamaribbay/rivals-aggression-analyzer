//
// Created by rohan on 7/9/2026.
//

#include "Player.h"

Player::Player() {
    rank = "";
    chatMessage = "";
    chatAgressionScore = 0.0f;
}

Player::Player(const string& rank, const string& chatMessage) {
    this->rank = rank;
    this->chatMessage = chatMessage;
    chatAgressionScore = 0.0f;
}

// get rank
string Player::getRank() const {
    return rank;
}

// get chat message
string Player::getChatMessage() const {
    return chatMessage;
}

// get chat agression score
float Player::getChatAgressionScore() const {
    return chatAgressionScore;
}

// set rank
void Player::setRank(const string &rank) {
    this->rank = rank;
}

// set chat message
void Player::setChatMessage(const string &message) {
    chatMessage = message;
}

// set chat aggression score
void Player::setChatAgressionScore(float score) {
    chatAgressionScore = score;
}
