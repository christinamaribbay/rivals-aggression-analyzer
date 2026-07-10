//
// Created by rohan on 7/9/2026.
//

#include "SplayTree.h"

SplayTree::SplayTree() {
    root = nullptr;
}

SplayTree::~SplayTree() {
    clear();
}

SplayTree::SplayNode* SplayTree::rotateRight(SplayNode* node) {
    SplayNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

SplayTree::SplayNode* SplayTree::rotateLeft(SplayNode* node) {
    SplayNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

SplayTree::SplayNode* SplayTree::splay(SplayNode* node, const string& word) {
    if (node == nullptr || node->word == word)
        return node;
    if (word < node->word) {
        if (node->left == nullptr)
            return node;
        if (word < node->left->word) {
            node->left->left = splay(node->left->left, word);
            node = rotateRight(node);
        }
        else if (word > node->left->word) {
            node->left->right = splay(node->left->right, word);
            if (node->left->right != nullptr)
                node->left = rotateLeft(node->left);
        }
        if (node->left == nullptr)
            return node;
        return rotateRight(node);
    }
    else {
        if (node->right == nullptr)
            return node;
        if (word > node->right->word) {
            node->right->right = splay(node->right->right, word);
            node = rotateLeft(node);
        }
        else if (word < node->right->word) {
            node->right->left = splay(node->right->left, word);
            if (node->right->left != nullptr)
                node->right = rotateRight(node->right);
        }
        if (node->right == nullptr)
            return node;
        return rotateLeft(node);
    }
}

SplayTree::SplayNode* SplayTree::insertHelper(SplayNode* node, const string& word, float aggressionFactor) {
    if (node == nullptr)
        return new SplayNode(word, aggressionFactor);

    node = splay(node, word);
    if (node->word == word) {
        node->aggressionFactor = aggressionFactor;
        return node;
    }

    SplayNode* newNode = new SplayNode(word, aggressionFactor);

    if (word < node->word) {
        newNode->right = node;
        newNode->left = node->left;
        node->left = nullptr;
    }
    else {
        newNode->left = node;
        newNode->right = node->right;
        node->right = nullptr;
    }
    return newNode;
}

void SplayTree::insert(const string& word, float aggressionFactor) {
    root = insertHelper(root, word, aggressionFactor);
}

bool SplayTree::search(const string& word, float& aggressionFactor) {
    if (root == nullptr)
        return false;
    root = splay(root, word);
    if (root->word == word) {
        aggressionFactor = root->aggressionFactor;
        return true;
    }
    return false;
}

void SplayTree::clearHelper(SplayNode* node) {
    if (node == nullptr)
        return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

void SplayTree::clear() {
    clearHelper(root);
    root = nullptr;
}