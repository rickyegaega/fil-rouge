#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

char switch_player(char player){
    if (player=='o'){
        player='x';
    }else{
        player='o';
    }
    return player;
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
        return point(table, block, cell)*mul;
    }
    //ビンゴまたは埋まったブロックでない
    if(table[cell][0]=='X'||table[cell][0]=='O'||not_null(table[cell])){
        for(i=0;i<9;i++){
            if(table[i][0]=='X'||table[i][0]=='O')continue;
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
                    if(tmp*(-1*mul)>score_tmp*(mul*-1)){
                        // printf("%c choose %d%d depth %d score %d\n",player, i,j,depth,tmp);
                        best_block=i;
                        best_cell=j;
                        score_tmp=tmp;
                    }
                }
            }
        }
        pc_block=best_block;
        pc_cell=best_cell;
        if(depth==0){
            return score_tmp;
        }
        // printf("%d\n",point(table, block, cell)*mul+score_tmp);
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
                tmp=score(tmp_table,cell,i,depth+1);
                if(tmp*(mul*-1)>score_tmp*(mul*-1)){
                    // printf("%c choose %d%d depth %d score %d\n",player,cell,i,depth,tmp);
                    score_tmp=tmp;
                    if(depth==0){
                        pc_block=cell;
                        pc_cell=i;
                    }
                }
            }
        }
        if(depth==0){
            return score_tmp;
        }
        // printf("%d\n",point(table, block, cell)*mul+score_tmp);
        return point(table, block, cell)*mul+score_tmp;
    }
}
