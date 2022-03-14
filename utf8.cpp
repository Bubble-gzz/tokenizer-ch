//
// Created by bubble on 2022/3/12.
//
#include <iostream>
#include <cstring>
#include <cstdio>
#include "utf8.h"
namespace utf_8 {
    int decode(char *buff,int *res) {
        char bin[maxBit+1]; int bin_L = 0, bit8;
        int buff_L = (int)strlen(buff) - 1, res_L = 0;
        int piece = 0, headParsing = 1, pieceCount = 0, bit;
        for (int i = 0; i < buff_L; i++)
        {
            bit8 = (unsigned char)buff[i];  // 11010111 -> 00..00 11010111
            itoa(bit8,bin,2);
            bin_L=(int)strlen(bin);

            for (int j = bin_L - 8; j < bin_L; j++)
                if (j<0) { // English characters less than 8-bit
                    headParsing = 0;
                    pieceCount = 1;
                    piece <<= 1;
                   // if (debugMode == PIECE) printf("0");
                }
                else {
                    bit = (bin[j] == '1');

                    if (headParsing) {
                        if (bit) pieceCount++;
                        else headParsing = 0;
                    }
                    piece = (piece << 1) | bit;
                //    if (debugMode == PIECE) printf("%d", bit );
                }

            //if (debugMode == PIECE) printf(" ");

            pieceCount--;
            if (pieceCount < 1) {
                res[res_L++] = piece;
                headParsing = 1;
                piece = pieceCount = 0;
            //    if (debugMode == PIECE) printf("\n");
            }
        }
        return res_L;
    }

    void encode(FILE *fout, const int *res, int res_L, int mode) {
        int bin[maxBit+1], bin_L = 0;
        int utf8_piece = 0;
        char ch;
        for (int i = 0; i < res_L ; i++)
        {
            int piece = res[i];

            if (mode == INTFORM) {
                fprintf(fout,"%d ",piece);
                //if (debugMode == RESULT) printf("%d ",piece);
                continue;
            }


            bin_L = 0;
            while (piece) {
                bin[bin_L++] = (piece & 1);
                piece >>= 1;
            }
            while (bin_L<8) bin[bin_L++] = 0;
            for (int j = bin_L - 1, cnt = 0; j >= 0; j--) {
                cnt++;
                utf8_piece = (utf8_piece << 1) | bin[j];
                if (cnt == 8) {
                    ch = (char)utf8_piece;
                    if (mode == CHARFORM) fprintf(fout,"%c", ch);
                    utf8_piece = cnt = 0;
                }
            }
            //fprintf(fout," ");
        }
    }
}