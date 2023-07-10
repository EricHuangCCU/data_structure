#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

    int user_num ;
    int res_y,res_x ;

    scanf("%d %d %d" ,&res_y ,&res_x ,&user_num) ;

    int user_id[user_num] ;
    char str[3000] ;
    int res[res_y][res_x] ;

    const char s[3] = " x" ;
    char *token ;
    int size[user_num][3000] ;
    int temp  = 0 ;


    for(int i=0 ;i<user_num ;i++){
        for(int j=0 ;j<100 ;j++){
            size[i][j] = -1 ;
        }
    }

    for(int i=0 ;i<user_num ;i++){
        scanf("%d ",&user_id[i]) ;
    
        scanf("%[^\n]",str)  ;
   
        token = strtok(str,s ) ;
        while(token != NULL){
            size[i][temp] =atoi(token) ;

            temp++ ;
            token = strtok(NULL,s) ;
        }
        temp = 0 ;
        
    }

    int start_x = -1 ;    
    int start_y = -1 ;     
    int rec_x[user_num] ;
    int rec_y[user_num] ;
    int flag[user_num] ;
    int counter = 0;
    int tempy[user_num] ;
   
    for(int i=0 ;i<user_num ;i++){
        flag[i] = 0;
        if(start_x + size[i][1]  < res_x && start_y + size [i][0] < res_y){
            flag[i] = 1;
            counter++ ;
            tempy[i] = start_y + size[i][0] ;
            rec_y[i] = start_y +1  ;
            rec_x[i] = start_x +1 ;
            start_x += size[i][1] ;
        }
    }
    

    for(int i=0 ;i<user_num ;i++){
        for(int j=0 ;j<user_num ;j++){
            if(flag[i] == 0 && flag[j] == 1 && size[i][0] == size[j][0] && size[i][1] == size[j][1] && tempy[j] + size[i][0] < res_y){    
                flag[i] = 2 ;
                counter++ ;
                rec_y[i] = tempy[j] + 1 ;
                rec_x[i] = rec_x[j] ; 
                tempy[j] += size[i][0] ;
            }
        }

    }

    printf("%d\n",counter) ;
    for(int i=0 ;i<user_num ;i++){
        if(flag[i]==1 || flag[i] == 2){
            printf("%d %dx%d %d %d\n",user_id[i] ,size[i][0],size[i][1],rec_y[i],rec_x[i]);
        }
    }

    return 0 ;
}
