//
// Created by bubble on 2022/3/13.
//
#include <algorithm>
#include <cstdio>
#include "utf8.h"
#include "trieCH.h"

namespace trieCH {
    const int maxBuff = 100000, rootBranch = 7000;
    const double backupRate = 0.05, hashRate = 20;
    char buff[maxBuff];
    int wordCode[maxBuff];

    trieNode::trieNode() {
        cnt = hashCreated = isEnd = 0;
        code = next = -1;
    }

    trieNode* trieNode::builtin_getChild(int code, int isBuild, int endFlag) {
            int ID, lastID;
            if (!hashCreated) {
                if (!isBuild) return nullptr;
                hashCreated = 1;
                hashN = (int) (cnt * hashRate);
                children = new trieNode[(int) (hashN * (1 + backupRate))];
                backupPoint = hashN;
            }
            ID = abs(code) % hashN;
            while (ID != -1 && children[ID].code != -1 && children[ID].code != code) {
                lastID = ID;
                ID = children[ID].next;
            }
            if (ID == -1 || children[ID].code == -1) {
                if (!isBuild) return nullptr;
                if (ID == -1) {
                    ID = backupPoint++;
                    children[lastID].next = ID;
                }
                children[ID].code = code;
                children[ID].cnt = 1;
            } else if (!children[ID].hashCreated && isBuild) children[ID].cnt++;

            if (isBuild) children[ID].isEnd |= endFlag;
            return &children[ID];
        }
    trieNode* trieNode::getChild(int code) {
        return builtin_getChild(code, 0);
    }
    void walkThrough(trieNode* root, int *res, int L, int isWholeWord) {
        trieNode *now = root;
        for (int i = 0; i < L; i++)
            now = now -> builtin_getChild(res[i], 1,(i == L-1) & isWholeWord);
    }

    trieNode* buildTrie(FILE *fin) {
        auto *root = new trieNode();
        root -> cnt = rootBranch;
        int maxWordLength = 0, word_L;
        while (fgets(buff, maxBuff, fin) != NULL) {
            word_L = utf_8::decode(buff, wordCode);
            maxWordLength = std::max(maxWordLength, word_L);
        }
        for (int currentLength = 1; currentLength <= maxWordLength; currentLength++) {
            rewind(fin);
            while (fgets(buff, maxBuff, fin) != NULL) {
                word_L = utf_8::decode(buff, wordCode);
                if (word_L < currentLength) continue;
                walkThrough(root, wordCode, currentLength, word_L == currentLength);
            }
        }
        return root;
    }

}
