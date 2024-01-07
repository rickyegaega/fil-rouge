#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "score.h"

FILE* fp;
char full_table[9][9];
char player;
int p_block=9;

int block;
int cell;
char start;
char opponent;
char player;
int pc_block=100;
int pc_cell=100;
int max_depth;




int max(int* table,int size){
    int n=-1000000;
    for (int i=0; i<size; i++){
        if (table[i]>n){
            n=table[i];
        }
    }
    return n;
}

void gen_minitable(char* table){
    int n = 0;
    int i;
    if(table[0]=='O'){
        fprintf(fp,"<TD bgcolor=\"black\">\n<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"white\">\n  <TR>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  </TR>\n  \n  <TR>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  </TR>\n  \n  <TR>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  <TD bgcolor=\"white\">&nbsp;</TD>\n  </TR>\n</TABLE>\n</TD>\n");
    }else if(table[0]=='X'){
        fprintf(fp,"<TD bgcolor=\"white\">\n<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n  <TR>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  </TR>\n  \n  <TR>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  </TR>\n  \n  <TR>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  <TD bgcolor=\"black\">&nbsp;</TD>\n  </TR>\n</TABLE>\n</TD>\n"); 
    }else{
        if(n%9==0){
            fprintf(fp,"<TD bgcolor=\"white\">\n<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");
        }
        for (i = 0;i<9;i++){
            if(table[i]=='o'){
                if(n%3==0){
                    fprintf(fp,"  <TR>\n");
                }
                fprintf(fp,"  <TD bgcolor=\"white\">o</TD>\n");
                n++;
                if(n%3==0){
                    fprintf(fp,"  </TR>\n");
                }
            }else if(table[i]=='x'){
                if(n%3==0){
                    fprintf(fp,"  <TR>\n");
                }
                fprintf(fp,"  <TD bgcolor=\"white\">x</TD>\n");
                n++;
                if(n%3==0){
                    fprintf(fp,"  </TR>\n");
                }
            }else {
                if(n%3==0){
                    fprintf(fp,"  <TR>\n");
                }
                fprintf(fp,"  <TD bgcolor=\"white\">.</TD>\n");
                n++;
                if(n%3==0){
                    fprintf(fp,"  </TR>\n");
                }
            }
        }
        
        if(n%9==0){
            fprintf(fp,"</TABLE>\n</TD>\n");
        }
    }
}

void gen_table(){
    int i;
    fprintf(fp,"digraph  {\n  a0 [shape=none label=<\n <TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");
    for (i=0; i<9; ){
        if (i%3==0){
            fprintf(fp,"  <TR>\n");
        }
        gen_minitable(full_table[i]);
        i++;
        if (i%3==0){
            fprintf(fp,"  </TR>\n");
        }
    }
    fprintf(fp,"</TABLE>\n>];\n}");
}

int judge_block(int block){
    if(p_block==9){
        return 1;
    }else{
        if (p_block==block){
            return 1;
        }else{
            return 0;
        }
    }
}

void write_gen(){
    fp = fopen("surper_morpion.dot", "w");
    gen_table(full_table);
    fclose(fp);
    system("dot -Tpng surper_morpion.dot -o g.png");
}

void start_player(char player){
    if (player=='x'){
        start = 'x';
        opponent = 'o';
    }else if (player=='o'){
        start = 'o';
        opponent = 'x';
    }else{
        printf("please enter right player\n");
        exit(1);
    }
}

void change_type(char *table){
    int i,j;
    int x=0,y=0;
    for (i=0; i<strlen(table); i++){
        if(table[i]=='O'){
            full_table[x][y]='O';
            x++;
        }else if(table[i]=='X'){
            full_table[x][y]='X';
            x++;
        }else if(table[i]=='x'){
            full_table[x][y]='x';
            y++;
            if(y%9==0){
                y=0;
                x++;
            }
        }else if(table[i]=='o'){
            full_table[x][y]='o';
            y++;
            if(y%9==0){
                y=0;
                x++;
            }
        }else if(table[i]>='1' && table[i]<='9'){
            for(j=0; j<table[i]-48; j++){
                full_table[x][y]='.';
                y++;
                if(y%9==0){
                    y=0;
                    x++;
                }
            }
        }
    }
}

int main(int argc, char* argv[]){
    int i,j;
    int tmp;
    char table[9];
    
    // // 開始時間を記録
    // clock_t start_time = clock();
    if(argc!=3){
        printf("please enter correctly\n");
        return 1;
    }
    max_depth=5;//need to be 2x+1
    int time=atoi(argv[2]);
    if(time>=6){
        max_depth=((int)ceil((log(time/250))+3)*2) + 1;
    }
    change_type(strtok(argv[1], " "));
    tmp = atoi(strtok(NULL, " "));
    block = tmp/10 -1;
    cell = tmp%10 -1;
    start_player(strtok(NULL, " ")[0]);
    score(full_table,block,cell,0);
    // printf("max score is %d\n",score(full_table,block,cell,0));
    printf("%d%d\n",pc_block+1,pc_cell+1);

    // // 終了時間を記録
    // clock_t end_time = clock();
    // // 計測結果を表示
    // double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    // printf("Elapsed time: %f seconds\n", elapsed_time);

    // //write dot and gen png
    // write_gen();
    return 0;
}