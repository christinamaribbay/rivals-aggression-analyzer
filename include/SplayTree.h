//
// Created by rohan on 7/9/2026.
//

#ifndef RIVALS_AGGRESSION_ANALYZER_SPLAYTREE_H
#define RIVALS_AGGRESSION_ANALYZER_SPLAYTREE_H
#include <string>
using namespace std;

class SplayTree {
    private:
    struct SplayNode {
        string word;
        float aggressionFactor;
        SplayNode* left;
        SplayNode* right;

        SplayNode(string word, float aggressionFactor) {
            this->word = word;
            this->aggressionFactor = aggressionFactor;
            left = nullptr;
            right = nullptr;
        }
    };
    SplayNode* root;
    SplayNode* rotateRight(SplayNode* node);
    SplayNode* rotateLeft(SplayNode* node);
    SplayNode* splay(SplayNode* node, const string& word);
    SplayNode* insertHelper(SplayNode* node, const string& word, float aggressionFactor);
    void clearHelper(SplayNode* node);

    public:
    SplayTree();
    ~SplayTree();

    void insert(const string& word, float aggressionFactor);
    float search(const string& word);
    void clear();
};

#endif //RIVALS_AGGRESSION_ANALYZER_SPLAYTREE_H
