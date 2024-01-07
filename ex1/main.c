#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char start;
char table[10];

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
        }
    }
    return n;
}

int min(int* table, int size){
    int n=100;
    for (int i=0; i<size; i++){
        if (table[i]<n){
            n=table[i];
        }
    }
    return n;
}

int same(int x, int y, int z, char* table){
    if(table[x]==table[y]&&table[x]==table[z]){
        if(table[x]==start){
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

int write_dot(char* table,int head,int prev,char player,int place){
    static int t_n=-1;
    int i,j;
    char *color;
    if(head){
        fprintf(stdout,"  m_init [shape=none label=<\n <TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");
    }else{
        fprintf(stdout,"  m_%d [shape=none label=<\n <TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n",t_n);
    }
    for(i=0;i<3;i++){
        fprintf(stdout,"  <TR>\n");
        for(j=1;j<4;j++){
            fprintf(stdout,"  <TD bgcolor=\"white\">%c</TD>\n",table[3*i+j-1]);
        }
        fprintf(stdout,"  </TR>\n");
    }
    if(head){
        fprintf(stdout,"  <TR>\n  <TD bgcolor=\"green\" colspan=\"3\">m_init</TD></TR>\n  </TABLE>>];\n");
    }else{
        if(player==start){
            color="green";
        }else{
            color="red";
        }
        fprintf(stdout,"  <TR>\n  <TD bgcolor=\"%s\" colspan=\"3\">m_%d</TD></TR>\n  </TABLE>>];\n",color,t_n);
        if(prev==-1){
            fprintf(stdout,"m_init-> m_%d [label=\" %d,%d\"];",t_n, place/3, place%3);
        }else{
            fprintf(stdout,"m_%d-> m_%d [label=\" %d,%d\"];\n",prev, t_n, place/3, place%3);
        }
    }
    t_n++;
    return t_n-1;
}

int next_table(char* table,char player,int now){
    char tmp[10];
    int change[9];
    int i,n;
    char now_player=player;
    for (i=0,n=0;i<9;i++){
        if (table[i]=='.'){
            change[n]=i;
            n++;
        }
    }
    if(n==0||judge(table)!=10){
        fprintf(stdout,"m_%d [xlabel=\"%d\"]\n",now,judge(table));
        return judge(table);
    }else{
        int score[n];
        player=switch_player(player);
        for (i=0;i<n;i++){
            strcpy(tmp,table);
            tmp[change[i]]=now_player;
            score[i]=next_table(tmp,player,write_dot(tmp,0,now,player,change[i]));
        }
        score[i+1]='\0';
        //minmax
        if(player!=start){
            if(now==-1){
                fprintf(stdout,"m_init [xlabel=\"%d\"]\n",max(score,n));
                return max(score,n);
            }else{
                fprintf(stdout,"m_%d [xlabel=\"%d\"]\n",now,max(score,n));
                return max(score,n);
            } 
        }else{
            fprintf(stdout,"m_%d [xlabel=\"%d\"]\n",now,min(score,n));
            return min(score,n);
        }
    }    
}

char* rotate(char* tmp){
    table[0]=tmp[6];
    table[1]=tmp[3];
    table[2]=tmp[0];
    table[3]=tmp[7];
    table[4]=tmp[4];
    table[5]=tmp[1];
    table[6]=tmp[8];
    table[7]=tmp[5];
    table[8]=tmp[2];
    table[9]='\0';
    return table;
}

void to_table(char* init){
    char tmp[9];
    int num,i,n;
    for (n=0,i=0 ; i<9; n++, i++){
        if (init[n]=='x'){
            tmp[i]='X';
        }else if (init[n]=='o'){
            tmp[i]='O';
        }else if(init[n] <='9'&& init[n]>'0'){
            for (num = init[n]+'0';num>96;num--, i++){
                tmp[i] = '.';
            }
            i--;
        }else{
            printf("init error\n");
            exit(1);
        }
    }
    rotate(tmp);
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

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Please enter init table, player and output file\n");
        return 1;
    }
    fprintf(stdout,"digraph  {\n");
    to_table(strtok(argv[1], " "));
    start_player(strtok(NULL, " ")[0]);
    write_dot(table,1,-1,start,0);
    next_table(table,start,-1);
    fprintf(stdout,"}");
    return 0;
}

