#include <cstdio>
#include "utf8.h"
#include "trieCH.h"

using namespace std;
using namespace trieCH;
const int maxBuff = 1e5+5;
char buff[maxBuff];
int wordCode[maxBuff];
int main()
{
    FILE *testFin = fopen("text.txt","r");
    FILE *vocabFin = fopen("vocab.txt","r");
    FILE *fout = fopen("result.txt","w");
    trieNode *myRoot = buildTrie(vocabFin), *visit;
    while(fgets(buff,maxBuff,testFin)!= nullptr)
    {
        int wordLength, maxMatch = -1, fail = 0;
        wordLength = utf_8::decode(buff, wordCode);
        for (int i = 0, j; i < wordLength; i++) {
            visit = myRoot; maxMatch = i - 1;
            for (j = i; j < wordLength; j++) {
                visit = visit -> getChild(wordCode[j]);
                if (visit == nullptr) break;
                else if (visit -> isEnd) maxMatch = j;
            }
            if (maxMatch < i)
            {
                if (!fail) {
                    fail = 1;
                    fprintf(fout,"<unk>\n");
                }
            }
            else {
                fail = 0;
                utf_8::encode(fout, wordCode + i, maxMatch - i + 1);
                fprintf(fout,"\n");
                i = maxMatch;
            }
        }
    }
    /*
    wordLength = utf_8::decode(buff, wordCode);
    visit = myRoot;
    for (int i = 0; i < wordLength; i++) {
        visit = visit -> getChild(wordCode[i]);
        if (visit == nullptr) {
            printf("<unk>\n"); break;
        }
        printf("Branches = %d endFlag:%d\n",(visit -> cnt) - 1, visit -> isEnd);
    }
     */
    return 0;
}