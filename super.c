#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
char full_table[9][9];
char player;
int p_block=9;
char start = 'o';

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

int not_null(char *table){
    for(int i=0;i<9;i++){
        if(table[i]=='.')return 0;
    }
    return 1;
}

char same(int x, int y, int z, char* table){
    if(table[x]==table[y]&&table[x]==table[z]){
        if(table[x]=='o'){
            return 'O';
        }else if(table[x]=='x'){
            return 'X';
        }else if(table[x]=='O'){
            printf("you win\n");
            exit(0);
        }else if(table[x]=='X'){
            printf("you lose\n");
            exit(0);
        }
    }
    return '-';
}

char judge(char* table){
    if(same(0,1,2,table)!='-')return same(0,1,2,table);
    if(same(3,4,5,table)!='-')return same(3,4,5,table);
    if(same(6,7,8,table)!='-')return same(6,7,8,table);
    if(same(0,4,8,table)!='-')return same(0,4,8,table);
    if(same(0,3,6,table)!='-')return same(0,3,6,table);
    if(same(1,4,7,table)!='-')return same(1,4,7,table);
    if(same(2,5,8,table)!='-')return same(2,5,8,table);
    if(same(2,4,6,table)!='-')return same(2,4,6,table);
    return table[0];
}

int main(int argc, char* argv[]){
    fp = fopen("surper_morpion.dot", "w");
    int i,j;
    int tmp;
    int flag;
    char winner;
    char area[2];
    char place[3];
    int block;
    int cell;
    char table[9];
    int rtn = 0;
    for(i=0;i<81;i++){
        full_table[i/9][i%9]='.';
    }
    for(i=0; i<81; i++){
        while(1){
            printf("please enter, block is %d\n",p_block);
            rtn = scanf("%s %s", area, place);
            if (rtn == EOF)
            {
                printf("EOF was detected.\n");
                exit (0);
            }
            block=area[0]-48;
            cell=(3-(place[1]-48))*3+(place[0]-97);
            if(block<0||block>8){
                printf("typing error block\n");
                continue;
            }
            if(cell<0||cell>8){
                printf("typing error cell\n");
                continue;
            }
            if (judge_block(block)){
                if(full_table[block][cell]=='.'){
                    full_table[block][cell]='o';
                    //ビンゴしたブロックがあったら塗りつぶす
                    full_table[block][0]=judge(full_table[block]);
                    break;
                }else{
                    printf("cell filled\n");
                    continue;
                }
            }else{
                printf("block error! you shoud play on block%d\n",p_block);
            }
        }
        fp = fopen("surper_morpion.dot", "w");
        gen_table(full_table);
        
        for(i=0;i<9;i++){
            table[i]=full_table[i][0];
        }
        judge(table);

        //次選べるブロックを選択
        if(full_table[cell][0]=='O' || full_table[cell][0]=='X' || not_null(full_table[cell])){
            p_block=9;
        }else{
            p_block=cell;
        }

        //pcがプレー
        printf("pc's turn %d\n",p_block);
        if (p_block==9){
            flag=0;
            for(i=0;i<9;i++){
                if(full_table[i][0]=='O'||full_table[i][0]=='X'){
                    i++;
                }
                for(j=0;j<9;j++){
                    if(full_table[i][j]=='.'){
                        full_table[i][j]='x';
                        //ビンゴしたブロックがあったら塗りつぶす
                        full_table[i][0]=judge(full_table[i]);
                        printf("pc choose %d %d\n",i,j);
                        if(full_table[j][0]=='O' || full_table[j][0]=='X'|| not_null(full_table[j])){
                            p_block=9;
                        }else{
                            p_block=j;
                        }
                        flag=1;
                        break;
                    }
                }
                if(flag){
                    break;
                }
            }
        }else{
            for (i=0;i<9;i++){
                if(full_table[cell][i]=='.'){
                    full_table[cell][i]='x';
                    printf("changed %c\n",full_table[cell][i]);
                    //ビンゴしたブロックがあったら塗りつぶす
                    full_table[cell][0]=judge(full_table[cell]);
                    printf("pc choose %d %d\n",cell,i);
                    if(full_table[i][0]=='O' || full_table[i][0]=='X'|| not_null(full_table[i])){
                        p_block=9;
                    }else{
                        p_block=i;
                    }
                    break;
                }
            }
        }
        fclose(fp);
        fp = fopen("surper_morpion.dot", "w");
        gen_table(full_table);
        
        fclose(fp);
        system("dot -Tpng surper_morpion.dot -o g.png");
        for(i=0;i<9;i++){
            table[i]=full_table[i][0];
        }
        judge(table);
    }
    
    return 0;
}