#include<stdio.h>
#include<math.h>

typedef struct Node{
    int id ;
    double x ;
    double y ;
} Node;

typedef struct edge{
    int u ;
    int v ;
    double weight ;
}edge;

typedef struct edge_list{
    edge data[10000];
    int num ;
}edge_list;

edge_list ed_list , spanlist;

double graph[10000][10000] ;
int visited[10000] ;
int record[10000];
int seq ;
int result[10000][10000];

void kruskal(int nodes);
int find();
void punion();
void sorting();
void dfs();



int main(){
    
    int nodes ;
    double B ;

    scanf("%d %lf",&nodes , &B) ;

    Node node[nodes] ;
    for(int i=0 ; i<nodes ; i++){
        scanf(" %d %lf %lf" , &node[i].id , &node[i].x , &node[i].y) ; //input imformation
    }

    // counting distence of each node 
    
    
    for(int i=0 ; i<nodes ; i++){
        for(int j=0 ; j<nodes ; j++){
            graph[i][j] = -1 ;                    //initialize

            if(i != j){
                graph[i][j] = sqrt(pow((node[i].x - node[j].x),2) + pow((node[i].y - node[j].y),2)) ;
                graph[j][i] = graph[i][j] ;
            }
        }
    }

    kruskal(nodes) ;

    for(int i=0 ; i<nodes ; i++){
        for(int j=0 ; j<nodes ; j++){
            graph[i][j] = 0 ;    
        }
    }
    
    //generate new graph for dfs
    for(int i=0 ; i<spanlist.num ; i++){
        graph[spanlist.data[i].u][spanlist.data[i].v] = spanlist.data[i].weight;
        graph[spanlist.data[i].v][spanlist.data[i].u] = spanlist.data[i].weight;
    }


    dfs(0) ;

    for(int i=0 ; i<nodes ; i++){
        for(int j=0 ; j<nodes ; j++){
            result[i][j] = -1 ;
        }
    }

    for(int i=0 ; i<nodes ; i++){
        for(int j=0 ; j<nodes ; j++){
            graph[i][j] = -1 ;                    //initialize
        }
    }

    for(int i=0 ; i<nodes ; i++){
        graph[record[i]][record[i+1]] = sqrt(pow((node[record[i]].x - node[record[i+1]].x),2) + pow((node[record[i]].y - node[record[i+1]].y),2)) ;
        graph[record[i+1]][record[i]] = graph[record[i]][record[i+1]] ;
    }

    double cost = 0 ;

    int uav = 0 ;
    int n = 0;
    int count = 0 ;
    int x = 1 ;

    while(n < nodes){
        result[uav][0] = uav ;
        while(cost <= B/2 && n < nodes){
        
            result[uav][x++] = record[n] ;
            cost += graph[record[n]][record[n+1]] ;
            n++ ;
        }
        count++ ;
        uav++ ;
        x = 1 ;
        cost = 0 ;
    }
    
    printf("%d\n",count) ;
    for(int i=0 ;i<count ; i++){
        for(int j=0 ; j<nodes ; j++){
            if(result[i][j] != -1){
                printf("%d ",result[i][j]);
            }
        }
        printf("\n");
    }
  
    return 0 ;
}

void kruskal(int nodes){
    int parent[nodes] ;
    int e1 , e2 ;
    ed_list.num = 0 ;

    for(int i=0 ; i<nodes ;i++){
        for(int j=0 ; j<i ; j++){
            if(graph[i][j] != -1){
                ed_list.data[ed_list.num].u = i ;
                ed_list.data[ed_list.num].v = j ;
                ed_list.data[ed_list.num].weight = graph[i][j] ;
                ed_list.num++ ;
            }
        }
    }

    sorting();

    for(int i=0 ; i<nodes ; i++){
        parent[i] = i ;
    }

    spanlist.num = 0 ;

    for(int i=0 ; i<ed_list.num ; i++){
        e1 = parent[ed_list.data[i].u];
        e2 = parent[ed_list.data[i].v];

        if(e1 != e2){
            spanlist.data[spanlist.num] = ed_list.data[i] ;
            spanlist.num++ ;
            punion(parent , e1 , e2 ,nodes);
        }
    }
}


void sorting(){
    edge temp ;

    for(int i=0 ; i< ed_list.num ; i++){
        for(int j=0 ; j< ed_list.num ; j++){
            if(ed_list.data[j].weight > ed_list.data[j + 1].weight){
                temp = ed_list.data[j];
                ed_list.data[j] = ed_list.data[j + 1] ;
                ed_list.data[j + 1] = temp ;
            }
        }
    }
}


void punion(int parent[] , int e1 , int e2 , int n){
    for(int i=0 ; i<n ; i++){
        if(parent[i] == e2){
            parent[i] = e1 ;
        }
    }
}

void dfs(int i){
    
    record[seq++] = i ;
    visited[i] = 1 ;

    for(int j=0 ; j<=spanlist.num ; j++){
        if(!visited[j] && graph[i][j] != 0){
            dfs(j);
        }
    }
    
}
