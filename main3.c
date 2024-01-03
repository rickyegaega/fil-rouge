#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
char full_table[9][9];
char player;
int p_block=9;
char start;
char opponent;
int block;
int cell;
int max_depth=2;
int pc_block;
int pc_cell;

char switch_player(char player){
    if (player=='o'){
        player='x';
    }else{
        player='o';
    }
    return player;
}

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

int not_null(char *table){
    for(int i=0;i<9;i++){
        if(table[i]=='.')return 0;
    }
    return 1;
}

char same(int x, int y, int z, char* table){
    if(table[x]==table[y]&&table[x]==table[z]){
        if(table[x]==start){
            return start-32;
        }else if(table[x]==opponent){
            return opponent-32;
        }else if(table[x]==start+32){
            printf("you win\n");
            exit(0);
        }else if(table[x]==opponent+32){
            printf("you lose\n");
            exit(0);
        }
    }
    return '.';
}

char judge(char* table){
    if(same(0,1,2,table)!='.')return same(0,1,2,table);
    if(same(3,4,5,table)!='.')return same(3,4,5,table);
    if(same(6,7,8,table)!='.')return same(6,7,8,table);
    if(same(0,4,8,table)!='.')return same(0,4,8,table);
    if(same(0,3,6,table)!='.')return same(0,3,6,table);
    if(same(1,4,7,table)!='.')return same(1,4,7,table);
    if(same(2,5,8,table)!='.')return same(2,5,8,table);
    if(same(2,4,6,table)!='.')return same(2,4,6,table);
    return table[0];
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

int bingo(int x, int y ,int z, char *table){
    char c = same(x,y,z,table);
    if(c==start||c==opponent){
        return 5;
    }else if(c==start-32||c==opponent-32){
        return 10000;
    }
    return 0;
}

int bingo_point(char* table, int n){
    switch (n)
    {
    case 0:
        if(bingo(0,1,2,table)!=0)return bingo(0,1,2,table);
        if(bingo(0,4,8,table)!=0)return bingo(0,4,8,table);
        if(bingo(0,3,6,table)!=0)return bingo(0,3,6,table);
        break;
    case 1:
        if(bingo(0,1,2,table)!=0)return bingo(0,1,2,table);
        if(bingo(1,4,7,table)!=0)return bingo(1,4,7,table);
        break;
    case 2:
        if(bingo(0,1,2,table)!=0)return bingo(0,1,2,table);
        if(bingo(2,5,8,table)!=0)return bingo(2,5,8,table);
        if(bingo(2,4,6,table)!=0)return bingo(2,4,6,table);
        break;
    case 3:
        if(bingo(0,3,6,table)!=0)return bingo(0,3,6,table);
        if(bingo(3,4,5,table)!=0)return bingo(3,4,5,table);
        break;
    case 4:
        if(bingo(0,4,8,table)!=0)return bingo(0,4,8,table);
        if(bingo(1,4,7,table)!=0)return bingo(1,4,7,table);
        if(bingo(2,4,6,table)!=0)return bingo(2,4,6,table);
        if(bingo(3,4,5,table)!=0)return bingo(3,4,5,table);
        break;
    case 5:
        if(bingo(2,5,8,table)!=0)return bingo(2,5,8,table);
        if(bingo(3,4,5,table)!=0)return bingo(3,4,5,table);
        break;
    case 6:
        if(bingo(0,3,6,table)!=0)return bingo(0,3,6,table);
        if(bingo(6,7,8,table)!=0)return bingo(6,7,8,table);
        break;
    case 7:
        if(bingo(1,4,7,table)!=0)return bingo(1,4,7,table);
        if(bingo(6,7,8,table)!=0)return bingo(6,7,8,table);
        break;
    case 8:
        if(bingo(0,4,8,table)!=0)return bingo(0,4,8,table);
        if(bingo(2,5,8,table)!=0)return bingo(2,5,8,table);
        if(bingo(6,7,8,table)!=0)return bingo(6,7,8,table);
        break;
    default:
        break;
    }
    return 0;
}

int reach(int x, int y, int z, char* table){
    if(table[z]=='.'){
        table[z]=switch_player(table[x]);
    }
    if(table[y]=='.'){
        table[y]=switch_player(table[x]);
    }
    if(table[x]==table[y]&&bingo_point(table, z)==0){//リーチかつ敵のリーチと一致していない
        if(table[x]==start||table[x]==opponent){
            return 2;
        }else if(table[x]==start-32||table[x]==opponent-32){
            return 4;
        }
    }
    if(table[x]==table[z]&&bingo_point(table, y)==0){
        if(table[x]==start||table[x]==opponent){
            return 2;
        }else if(table[x]==start-32||table[x]==opponent-32){
            return 4;
        }
    }
    return 0;
}

char reach_point(char* table, int n){
    switch (n)
    {
    case 0:
        if(reach(0,1,2,table)!=0)return reach(0,1,2,table);
        if(reach(0,4,8,table)!=0)return reach(0,4,8,table);
        if(reach(0,3,6,table)!=0)return reach(0,3,6,table);
        break;
    case 1:
        if(reach(1,0,2,table)!=0)return reach(1,0,2,table);
        if(reach(1,4,7,table)!=0)return reach(1,4,7,table);
        break;
    case 2:
        if(reach(2,1,0,table)!=0)return reach(2,1,0,table);
        if(reach(2,5,8,table)!=0)return reach(2,5,8,table);
        if(reach(2,4,6,table)!=0)return reach(2,4,6,table);
        break;
    case 3:
        if(reach(3,0,6,table)!=0)return reach(3,0,6,table);
        if(reach(3,4,5,table)!=0)return reach(3,4,5,table);
        break;
    case 4:
        if(reach(4,0,8,table)!=0)return reach(4,0,8,table);
        if(reach(4,1,7,table)!=0)return reach(4,1,7,table);
        if(reach(4,2,6,table)!=0)return reach(4,2,6,table);
        if(reach(4,3,5,table)!=0)return reach(4,3,5,table);
        break;
    case 5:
        if(reach(5,2,8,table)!=0)return reach(5,2,8,table);
        if(reach(5,4,3,table)!=0)return reach(5,4,3,table);
        break;
    case 6:
        if(reach(6,3,0,table)!=0)return reach(6,3,0,table);
        if(reach(6,7,8,table)!=0)return reach(6,7,8,table);
        break;
    case 7:
        if(reach(7,4,1,table)!=0)return reach(7,4,1,table);
        if(reach(7,6,8,table)!=0)return reach(7,6,8,table);
        break;
    case 8:
        if(reach(8,4,0,table)!=0)return reach(8,4,0,table);
        if(reach(8,5,2,table)!=0)return reach(8,5,2,table);
        if(reach(8,7,6,table)!=0)return reach(8,7,6,table);
        break;
    default:
        break;
    }
    return 0;
}

int point(char full_table_tmp[9][9], int block, int cell){
    int total_point=0;
    char table[9];
    //中央セルを選んだ場合
    if(cell==4){
        total_point += 3;
    }
    //ブロックをとった場合
    if(bingo_point(full_table_tmp[block],cell)!=0){
        total_point += 5;
        //corner or center
        if(block==4)total_point += 10;
        if(block==0,block==2,block==6,block==8)total_point += 3;

        for(int i=0;i<9;i++){
            if(full_table_tmp[i][0]=='O'||full_table_tmp[i][0]=='X'){
                table[i]=full_table_tmp[i][0];
            }else{
                table[i]='.';
            }
        }
        if(bingo_point(table,block)!=0){
            return 1000000;
        }else{
            total_point += reach_point(table, block);
        }
    }else{
        total_point += reach_point(full_table_tmp[block],cell);
    }
    return total_point;
}

int score(char table[9][9], int block, int cell, int depth){
    int i,j,n,mul;
    char tmp_table[9][9];
    int tmp;
    int score_tmp=0;
    int best_block;
    int best_cell;

    if(depth%2==1){
        player=start;
        mul=1;
    }else{
        mul=-1;
        player=opponent;
    }

    if(depth==max_depth){
        // printf("point is %d mul is %d\n",point(table, block, cell),mul);
        return point(table, block, cell);
    }
    //ビンゴまたは埋まったブロックでない
    if(table[cell][0]=='X'||table[cell][0]=='O'||not_null(table[cell])){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                if(table[i][j]=='.'){

                    //テーブルのコピー
                    for(n=0;n<9;n++){
                        strcpy(tmp_table[n],table[n]);
                    }
                    tmp_table[i][j]=player;
                    //ビンゴの塗りつぶし
                    tmp_table[i][0]=judge(tmp_table[i]);
                    tmp=score(tmp_table,i,j,depth+1);
                    // printf("score is %d mul is %d\n",tmp,mul);
                    if(tmp>score_tmp*mul){
                        best_block=i;
                        best_cell=j;
                        score_tmp=tmp*mul;
                    }
                }
            }
        }
        pc_block=best_block;
        pc_cell=best_cell;
        if(depth==0){
            return score_tmp;
        }
        // printf("%d mul is %d\n",point(table, block, cell),mul);
        return point(table, block, cell)*mul+score_tmp;
    }else{
        for(i=0;i<9;i++){
            if(table[cell][i]=='.'){
                //テーブルのコピー
                for(n=0;n<9;n++){
                    strcpy(tmp_table[n],table[n]);
                }
                tmp_table[cell][i]=player;
                //ビンゴの塗りつぶし
                tmp_table[cell][0]=judge(tmp_table[cell]);
                tmp=score(tmp_table,cell,i,depth+1)*mul;
                // printf("score is %d mul is %d\n",tmp,mul);
                if(tmp>score_tmp*mul){
                    score_tmp=tmp*mul;
                    best_block=cell;
                    best_cell=i;
                }
            }
        }
        pc_block=best_block;
        pc_cell=best_cell;
        if(depth==0){
            return score_tmp;
        }
        // printf("%d mul is %d\n",point(table, block, cell),mul);
        return point(table, block, cell)*mul+score_tmp;
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
    if(argc!=2){
        printf("please enter correctly\n");
        return 1;
    }
    change_type(strtok(argv[1], " "));
    tmp = atoi(strtok(NULL, " "));
    block = tmp/10 -1;
    cell = tmp%10 -1;
    start_player(strtok(NULL, " ")[0]);
    score(full_table,block,cell,0);
    // printf("max score is %d\n",score(full_table,block,cell,0));
    printf("best is %d %d\n",pc_block+1,pc_cell+1);

    //write dot and gen png
    write_gen();
    return 0;
}
