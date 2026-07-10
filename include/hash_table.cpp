//
// Created by Marina on 7/9/2026.
//

#include "hash_table.h"

HashTable::HashTable(int size) {
    this->buckets = size;
    table.assign(buckets, nullptr);
}


HashTable::~HashTable() {
    for (int i = 0; i < buckets; i++) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* prev = current;
            current = current->next;
            delete prev;
        }
    }
}

bool HashTable::isEmpty() {
    for (int i = 0; i < buckets; i++) {
        if (table[i] != nullptr) {
            return false;
        }
    }
    return true;
}


int HashTable::hashFunction(string key) {
    unsigned int hashcode = 0;
    for (int i = 0; i < key.length(); i++) {
        hashcode = (hashcode * 31 + key[i]) % buckets;
    }
    return hashcode;
}

void HashTable::insertWord(string key, float value) {
    int hashValue = hashFunction(key);
    HashNode* current = table[hashValue];
    while (current != nullptr) {
        if (current->word == key) {
            current->aggressionFactor = value;
            return;
        }
        current = current->next;
    }

    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[hashValue];
    table[hashValue] = newNode;
}

float HashTable::searchWord(string key) {
    int index = hashFunction(key);
    HashNode* current = table[index];
    while (current != nullptr) {
        if (current->word == key) {
            return current->aggressionFactor;
        }
        current = current->next;
    }

    return -1.0f;
}
