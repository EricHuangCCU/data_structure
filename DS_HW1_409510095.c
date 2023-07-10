#include<stdio.h>

int graph[1000][1000] ;
int path[1000] ;
int pred[1000] = {-1} ;
int flag[1000] = {0} ;
int result[1000][1000] ;
int src , des ;

void bfs(int,int) ;

int main(){

    int node ,link ,req ;
    int i, j ,k;

    scanf("%d %d %d",&node ,&link ,&req);

    int nid[node][2] ,lid[link][4] ,rid[req][3] ;
    int qm[node] ,channel[node][node] ;
    int start ,end ;
    int temp[node] ;
    int flag[req]  ;

    for(i=0 ;i<node ;i++){
        for(j=0 ;j<node ;j++){
            channel[i][j] = 0 ;
        }
    }

    for(i=0 ;i<req ;i++){
        for(j=0 ;j<node+4 ;j++){
            result[i][j] = -1 ;
        }
    }

    for(i=0 ;i<node ;i++){            //input
        for(j=0 ;j<2 ;j++){
            scanf("%d",&nid[i][j]) ;
        }
        qm[i] = nid[i][1] ;
    }

    for(i=0 ;i<link ;i++){
        for(j=0 ;j<4 ;j++){
            scanf("%d",&lid[i][j]) ;
        }
        channel[lid[i][1]][lid[i][2]] = lid[i][3] ;
        channel[lid[i][2]][lid[i][1]] = lid[i][3] ;
    }

    for(i=0 ;i<req ;i++){
        for(j=0 ;j<3 ;j++){
            scanf("%d",&rid[i][j]) ;
            result[i][j] = rid[i][j] ;
        }
    }

    for(i=0 ;i<node ;i++){           //generate graph
        for(j=0 ;j<node ;j++){
            graph[i][j] = 0 ;
        }
    }

    for(i=0 ;i<link ;i++){
        graph[lid[i][1]][lid[i][2]] = 1 ;
        graph[lid[i][2]][lid[i][1]] = 1 ;
    }

  
    for(i=0 ;i<req ;i++){
        start = rid[i][1] ;
        end = rid[i][2] ;

        bfs(node,start) ;       //run bfs

        for(j=0 ;j<node ;j++){
            temp[j] = -2 ;
        }

        for(k=0 ;k<node ;k++){
            if(end == -1)
                break;
            for(j=0 ;j<node ;j++){
                if(j == end){
                    temp[k] = end ;
                }
            }
            end = pred[end] ;
        }

        
        for(j=0 ;j<node ;j++){          //record result
            result[i][j+3] = temp[j] ;
        }
    }

    int counter = 0 ; 

    for(i=0 ;i<req ;i++){

        start = rid[i][1];
        end = rid[i][2] ;

        flag[i] = 0 ;

        if(result[i][4] < 0){         //if 一條路徑都沒有
            flag[i] = 1 ;
        }

        j=3 ;                           //判斷channel夠不夠
        if(result[i][j+1] == start ){      //if start 到end只有一條channel
            if(channel[result[i][j]][result[i][j+1]]< 1){
                flag[i] = 1;
            }
            
        }

        while(result[i][j+2] > -1){                        //if start到end有多個channel
            if(channel[result[i][j]][result[i][j+1]]< 1){
                flag[i] = 1;
            }
            
            j++ ;
        }

        j=3;
        while(result[i][j] > -1){
            if(result[i][j]==start ||result[i][j] ==end){   //頭尾qm -1
                if(qm[result[i][j]] < 1 ){
                    flag[i] = 1 ;
                }
            }
            else if(qm[result[i][j]] < 2){                  //中間qm-2
                flag[i] = 1 ;
            }
            j++ ;
        }

        if(!flag[i]){
            j = 3 ;
            if(result[i][j+1] == start  ){      //if start 到end只有一條channel
                channel[result[i][j]][result[i][j+1]]-- ;
                channel[result[i][j+1]][result[i][j]]-- ;
                
            }
            
            while(result[i][j+2] > -1 ){
                channel[result[i][j]][result[i][j+1]]-- ;
                channel[result[i][j+1]][result[i][j]]-- ;
                j++ ;
            }

            j=3;

            if(result[i][j+1] == start ){
                qm[result[i][j]]-- ;
                qm[result[i][j+1]]-- ;
                
            }
            while(result[i][j+1] > -1 ){
                qm[result[i][j]]-- ;
                qm[result[i][j+1]]-- ;
                j++;
            }

            counter++ ;
        }
    }


    printf("%d\n",counter) ;

    for(i=0 ;i<req ;i++){               //print result
        src = 0 ;
        des = 3 ;
        if(!flag[i] ){
            printf("%d ",result[i][0]);

            for(j=4 ;j<=node+3 ;j++){
                if(result[i][j] == result[i][1]){
                    src = j ;
                }
            }
            for(j=src ;j>=des ;j--){
                printf("%d ",result[i][j]) ;
            }
            printf("\n") ;
        }
    }

    return 0 ;
}

void bfs(int node,int start){

    int queue[1000] = {-1} ;            // initialize
    int color[1000] ={0} ;              //  =1:grey  =2:black
    int front=0 ,rear=0 ;

    for(int a=0 ;a<=node ;a++){         
        path[a] = -1 ;
        pred[a] = -1 ;
    }

    queue[rear] = start ; 
    color[start] = 1 ;

    while(front <= rear){

        for(int a=0 ;a<node ;a++){    
            if(a != start && color[a] == 0 && graph[queue[front]][a]){
                queue[++rear] = a ;
                color[queue[rear]] = 1 ;
                pred[queue[rear]] = queue[front] ;
            }
        }

        color[queue[front]] = 2 ;
        front ++;                   //pop out
        start = queue[front] ;

    }

}
