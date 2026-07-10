//
// Created by Marina on 7/9/2026.
//

#ifndef RIVALS_AGGRESSION_ANALYZER_HASH_TABLE_H
#define RIVALS_AGGRESSION_ANALYZER_HASH_TABLE_H
#pragma once
#include "Player.h"
#include <vector>

struct HashNode {
    string word;
    float aggressionFactor;
    HashNode* next = nullptr;

    HashNode(string word, float aggressionFactor) {
        this->word = word;
        this->aggressionFactor = aggressionFactor;
        this->next = nullptr;
    };
};

class HashTable {
    int buckets;
    vector<HashNode*> table;

public:
    HashTable(int size = 31);
    ~HashTable();
    bool isEmpty();
    int hashFunction(string key);
    void insertWord(string key, float value);
    float searchWord(string key);

};

#endif //RIVALS_AGGRESSION_ANALYZER_HASH_TABLE_H