/*
     Created by bubble on 2022/3/12.
*/

#ifndef TOKENIZER_CH_UTF8_H
#define TOKENIZER_CH_UTF8_H

enum {
    NONE,
    PIECE,
    RESULT
};
enum {
    CHARFORM,
    INTFORM
};
namespace utf_8 {
    const int maxBit = 32;
    int decode(char *buff,int *res);
    void encode(FILE *fout, const int *res, int res_L, int mode = CHARFORM);
}
#endif
