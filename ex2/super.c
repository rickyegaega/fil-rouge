#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

FILE* fp;
char full_table[9][9];
char player;
int p_block;
char opponent;
int block;
int cell;

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

int not_null(char *table){
    for(int i=0;i<9;i++){
        if(table[i]=='.')return 0;
    }
    return 1;
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

int palyer_turn(){
    int rtn = 0;
    char area[2];
    char place[3];
    if(p_block==9){
        printf("please enter, any block\n");
    }else{
        printf("please enter, block is %d\n",p_block+1);
    }
    
    rtn = scanf("%s %s", area, place);
    if (rtn == EOF)
    {
        printf("EOF was detected.\n");
        exit (0);
    }
    block=area[0]-48-1;
    cell=(3-(place[1]-48))*3+(place[0]-97);
    // printf("you chose%d %d\n",block,cell);
    if(block<0||block>8||full_table[block][0]=='O'||full_table[block][0]=='X'){
        printf("typing error block\n");
        return 0;
    }
    if(cell<0||cell>8){
        printf("typing error cell\n");
        return 0;
    }
    if (judge_block(block)){
        if(full_table[block][cell]=='.'){
            full_table[block][cell]='o';
            //ビンゴしたブロックがあったら塗りつぶす
            full_table[block][0]=judge(full_table[block]);
            return 1;
        }else{
            printf("cell filled\n");
            return 0;
        }
    }else{
        printf("block error! you shoud play on block%d\n",p_block+1);
        return 0;
    }
}

void pc_turn_any(){
    char* table;
    int i;
    for(i=0;i<9;i++){
        table[i]=full_table[i][0];
    }
    next_table(table,opponent,0);
    printf("end\n");
    i=place;
    next_table(full_table[place],opponent,0);
    full_table[i][place]=opponent+32;
    // 次選べるブロックを選択
    if(full_table[place][0]=='O' || full_table[place][0]=='X' || not_null(full_table[place])){
        p_block=9;
    }else{
        p_block=place;
    }
    
}

void pc_turn_num(){
    next_table(full_table[cell],opponent,0);
    printf("pc played%d %d\n",cell,place);
    full_table[cell][place]=opponent+32;
    // 次選べるブロックを選択
    if(full_table[place][0]=='O' || full_table[place][0]=='X' || not_null(full_table[place])){
        p_block=9;
    }else{
        p_block=place;
    }
}

void pc_turn(){
    printf("pc's turn %d\n",p_block);
    if (p_block==9){
        pc_turn_any();
    }else{
        pc_turn_num();
    }
}

void write_gen(){
    fp = fopen("super_morpion.dot", "w");
    gen_table(full_table);
    fclose(fp);
    if(getenv("SMPATH")!=NULL){
        char command[100];
        snprintf(command, sizeof(command), "dot -Tpng super_morpion.dot -o %s/g.png", getenv("SMPATH"));
        system(command);
    }else{
        system("dot -Tpng super_morpion.dot -o g.png");
    }
    
}

void print_table(){
    int i,j,n;
    for(n=0;n<3;n++){
        printf("---------------------------------------\n");
        for(j=0;j<3;j++){
            for(i=0;i<3;i++){
                if(full_table[3*n+i][0]=='O'){
                    printf("| ■■■■■ |");
                }else if(full_table[3*n+i][0]=='X'){
                    printf("|           |");
                }else{
                    printf("| %c | %c | %c |",full_table[3*n+i][3*j],full_table[3*n+i][3*j+1],full_table[3*n+i][3*j+2]);
                }
            }
            printf("\n");
            for(i=0;i<3;i++){
                if(full_table[3*n+i][0]=='O'||full_table[3*n+i][0]=='X'){
                    printf("             ");
                }else{
                    printf("-------------");
                }
            }
            printf("\n");
        }
    }

    
    printf("\n");
}
// for debug
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
    char* smpath;
    char table[9];
    p_block=9;
    start = 'O';
    opponent='X';
    if(argc>=2){
        for(i=0;i<81;i++){
            full_table[i/9][i%9]='.';
        }
        max_depth=atoi(argv[1]);
    }else{//for debug
        printf("type error\n");
    }
    if(getenv("SMPATH")!=NULL){
        smpath=getenv("SMPATH");
        char command[100];
        snprintf(command, sizeof(command), "mkdir -p %s", smpath);//create directory
        system(command);
        // printf("%s\n",getenv("SMPATH"));
    }
    if(getenv("DEBUG")!=NULL){
        change_type(strtok(argv[2], " "));
        start_player(strtok(NULL, " ")[0]);
    }
    for(i=0; i<81; i++){
        while(1){
            if(palyer_turn()) break;
        }
        for(i=0;i<9;i++){
            table[i]=full_table[i][0];
        }
        judge(table);
        
        //pc turn
        //次選べるブロックを選択
        if(full_table[cell][0]=='O' || full_table[cell][0]=='X' || not_null(full_table[cell])){
            p_block=9;
        }else{
            p_block=cell;
        }
        pc_turn();

        //write dot and gen png
        print_table();
        write_gen();

        for(i=0;i<9;i++){
            table[i]=full_table[i][0];
        }
        judge(table);
    }
    return 0;
}