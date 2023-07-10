#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef unsigned long ul ;

ul MurmurOAAT32(char *) ;
void query() ;

int str_num , maxlen ;
char **str ;
int *flag ;

ul **tree ;
int level = 0;
int count = 0 ; 


int main(){

    scanf("%d %d",&str_num , &maxlen) ;
    
    while(pow(2,level) < str_num){
        level++ ;
    }
    
    str = (char**)malloc(sizeof(char*) * str_num) ;

    for(int i=0 ; i<str_num ; i++){                        //動態配置字串陣列
        str[i] = (char*)malloc(sizeof(char) * maxlen) ;
    }

    for(int i=0 ; i<str_num ; i++){                         //輸入字串
        scanf("%s",str[i]) ;
    }

    flag = (int*)malloc(sizeof(int) * str_num) ;

    for(int i=0 ; i<str_num ; i++){
        flag[i] = 0 ;
    }

    tree = (ul**)malloc(sizeof(ul*) * (level+1)) ;
    
    for(int i=0 ; i<str_num ; i++){                           //n*n array
        tree[i] = (ul*)malloc(sizeof(ul) * (str_num+1)) ;
    }

    for(int i=0 ; i<level+1 ; i++){
        for(int j=0 ; j<str_num+1 ; j++){                        //初始化
            tree[i][j] = 0 ;
        }
    }

    for(int i=0 ; i<str_num ; i++){
        tree[level][i] = MurmurOAAT32(str[i]) ;           //最後一行存字串資料
    }

    int up = 0 ,down = 0;
    char s[maxlen+1] ;
    for(int i=level-1 ; i >=0 ; i--){                     //往上做hash
        while(tree[i+1][down] != 0){
            if(tree[i+1][down+1] != 0){
                sprintf(s , "%lu" , tree[i+1][down] + tree[i+1][down+1]) ;
                tree[i][up] = MurmurOAAT32(s) ;
                down += 2 ;
                up += 1 ;
            }
            else{
                sprintf(s , "%lu" , tree[i+1][down] + tree[i+1][down]) ;
                tree[i][up] = MurmurOAAT32(s) ;                
                break ;
            }
            
        }
        down = up = 0 ;
    }

    query(0,0) ;

    printf("2 %d\n",count) ;
    for(int i=0 ; i<str_num ; i++){
        if(flag[i]){
            printf("%s\n",str[i]) ;
        }
    }

   
    return 0 ;
}


void query(int current_level , int pos){
    if(current_level <= level && tree[current_level][pos] != 0){
        printf("1 %d %d\n",current_level,pos) ;
        fflush(NULL) ;
        ul correct ;
        scanf("%lu",&correct) ;
        if(tree[current_level][pos] != correct){
            if(current_level == level){
                flag[pos] = 1 ;
                count++ ;
            }
        query(current_level+1 , pos*2) ;
        query(current_level+1 , pos*2 + 1) ;

        }
    }
    
}

ul MurmurOAAT32(char *key){
    ul h = 3323198485ul ;
    for(;*key ; ++key){
        h ^= *key ;
        h *= 0x5bd1e995 ;
        h ^= h >> 15 ;
    }

    return h ;
}

/*
9 50
apple
banana
orange
lemon
grape
guava
strawberry
pineapple
watermelon
*/
