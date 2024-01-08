#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

char start;
char table[10];
int place;
int max_depth;

char switch_player(char player){
    if (player=='O'){
        player='X';
    }else{
        player='O';
    }
    return player;
}

int max(int* table,int size){
    int n=-10;
    for (int i=0; i<size; i++){
        if (table[i]>n){
            n=table[i];
            place=i;
        }
    }
    return n;
}

int min(int* table, int size){
    int n=100;
    for (int i=0; i<size; i++){
        if (table[i]<n){
            n=table[i];
            place=i;
        }
    }
    return n;
}

int same(int x, int y, int z, char* table){
    if(table[x]==table[y]&&table[x]==table[z]){
        if(table[x]==start||table[x]==start+32){
            return 1;
        }else if(table[x]!='.'){
            return -1;
        }
    }
    return 10;
}

int judge(char*table){
    if(same(0,1,2,table)!=10)return same(0,1,2,table);
    if(same(3,4,5,table)!=10)return same(3,4,5,table);
    if(same(6,7,8,table)!=10)return same(6,7,8,table);
    if(same(0,4,8,table)!=10)return same(0,4,8,table);
    if(same(0,3,6,table)!=10)return same(0,3,6,table);
    if(same(1,4,7,table)!=10)return same(1,4,7,table);
    if(same(2,5,8,table)!=10)return same(2,5,8,table);
    if(same(2,4,6,table)!=10)return same(2,4,6,table);
    for(int i=0;table[i]!='\0';i++){
        if(table[i]=='.'){
            return 10;
        }
    }
    return 0;
}

int next_table(char* table,char player,int depth){
    char tmp[10];
    int change[9];
    int i,n,num;
    char now_player=player;
    // printf("called\n");
    if(depth>=max_depth){
        return 0;
    }
    for (i=0,n=0;i<9;i++){
        if (table[i]=='.'){
            change[n]=i;
            n++;
        }
    }
    if(n==0||judge(table)!=10){
        return judge(table);
    }else{
        int score[n];
        player=switch_player(player);
        for (i=0;i<n;i++){
            strncpy(tmp,table,9);
            tmp[change[i]]=now_player+32;//小文字に変換
            score[i]=next_table(tmp,player,depth+1);
        }
        // for(i=0;i<n;i++){
        //     printf("%d ",score[i]);
        // }
        // printf("\n");

        // printf("score list %d\n",*score);
        //minmax
        if(player!=start){
            return max(score,n);
        }else{
            return min(score,n);
        }
    }    
}

void start_player(char player){
    if (player=='x'){
        start = 'X';
    }else if (player=='o'){
        start = 'O';
    }else{
        printf("please enter right player\n");
        exit(1);
    }
}


