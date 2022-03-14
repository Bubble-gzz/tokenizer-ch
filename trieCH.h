/*
    Created by bubble on 2022/3/13.
*/

#ifndef TOKENIZER_CH_TRIECH_H
#define TOKENIZER_CH_TRIECH_H

#include "utf8.h"
namespace trieCH{
    struct trieNode{
        int cnt, code, isEnd, hashCreated, next;
        int hashN, backupPoint;
        trieNode* children;
        trieNode();
        trieNode* builtin_getChild(int code, int isBuild, int endFlag = 0);
        trieNode* getChild(int code);
    };
    void walkThrough(trieNode *root, int *res, int L, int isWholeWord = 0);
    trieNode* buildTrie(FILE *fin);
}
#endif
