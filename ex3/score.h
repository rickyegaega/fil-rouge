#ifndef _SCORE_H_
#define _SCORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char start;
extern char opponent;
extern char player;
extern int pc_block;
extern int pc_cell;
extern int max_depth;

char switch_player(char player);
int not_null(char *table);
char same(int x, int y, int z, char* table);
char judge(char* table);
int bingo(int x, int y ,int z, char *table);
int bingo_point(char* table, int n);
int reach(int x, int y, int z, char* table);
char reach_point(char* table, int n);
int point(char full_table_tmp[9][9], int block, int cell);
int score(char table[9][9], int block, int cell, int depth);

#endif
