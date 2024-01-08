#ifndef _SCORE_H_
#define _SCORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char start;
extern char table[10];
extern int place;
extern int max_depth;
extern char full_table[9][9];
extern char player;
extern int p_block;
extern int block;
extern int cell;

char switch_player(char player);
int max(int* table,int size);
int min(int* table,int size);
int same(int x, int y, int z, char* table);
int judge(char* table);
int next_table(char* table,char player,int depth);
void start_player(char player);


#endif
