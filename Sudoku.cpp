 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sai pranav
 *
 * Created on 22 April, 2023, 2:36 AM
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <bits/stdc++.h>
#include<iostream>
#include <vector>

using namespace std;

/*vector<vector<int>> ssb={
     {5, 3, 0, 0, 7, 0, 0, 0, 0},
     {6, 0, 0, 1, 9, 5, 0, 0, 0},
     {0, 9, 8, 0, 0, 0, 0, 6, 0},
     {8, 0, 0, 0, 6, 0, 0, 0, 3},
     {4, 0, 0, 8, 0, 3, 0, 0, 1},
     {7, 0, 0, 0, 2, 0, 0, 0, 6},
     {0, 6, 0, 0, 0, 0, 2, 8, 0},
     {0, 0, 0, 4, 1, 9, 0, 0, 5},
     {0, 0, 0, 0, 8, 0, 0, 7, 9},
   };*/
/*vector<vector<int>> ssb={
   {0, 0, 0, 0, 5, 1, 4, 0, 6},
   {2, 4, 0, 0, 7, 0, 0, 5, 0},
   {0, 5, 6, 0, 0, 0, 0, 2, 0},
   {0, 0, 0, 5, 3, 9, 1, 0, 7},
   {0, 9, 0, 4, 0, 7, 0, 3, 0}, 
   {4, 0, 3, 8, 1, 2, 0, 0, 0},
   {0, 3, 0, 0, 0, 0, 5, 8, 0},
   {0, 6, 0, 0, 4, 0, 0, 1, 2},
   {8, 0, 2, 3, 9, 0, 0, 0, 0}
};*/
vector<vector<int>> ssb={
   {3, 0, 6, 5, 0, 8, 4, 0, 0},
   {5, 2, 0, 0, 0, 0, 0, 0, 0},
   {0, 8, 7, 0, 0, 0, 0, 3, 1},
   {0, 0, 3, 0, 1, 0, 0, 8, 0},
   {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
   {0, 5, 0, 0, 9, 0, 0, 0, 0},
   {1, 3, 0, 0, 0, 0, 2, 5, 0},
   {0, 0, 0, 0, 0, 0, 0, 7, 4},
   {0, 0, 5, 2, 0, 6, 3, 1, 0}
};
vector<vector<int>> ini;
class Astar{
public:    
   int NC;
   int NE;
   int depth;
class Node{
public:
    int fv,hv,gv; //f(n)=g(n) + h(n)
    int i,j;
    long int nodecount;
    vector<vector<int>> sb;    
    bool vis=false;
    Node(){
    for(int x=0;x<9;x++){
        vector<int> vc;
            for(int y=0;y<9;y++){
                vc.push_back(ssb[x][y]);
            }
        sb.push_back(vc);
         }
    }
  };
vector<pair<int,int>> path;
vector<Node> open;
vector<Node> openchange;
vector<Node> closed;
vector<Node> graph[10000];
map<int,Node> trace;
int hv[9][9];
int hvc[9][9];
int hvg[9][9]={
   {810,800,790,530,520,510,260,250,240},
   {780,770,760,500,490,480,230,220,210},
   {750,740,730,470,460,450,200,190,180},
   {710,700,690,440,430,420,170,160,150},
   {680,670,660,410,400,390,140,130,120}, 
   {650,640,630,380,370,360,110,100,90},
   {620,610,600,350,340,330,80,70,60},
   {590,580,570,320,310,300,50,40,30},
   {560,550,540,290,280,270,20,10,0}
};
Astar(){
    //graph.resize(1,vector<Node>(9));
    int sum=810;
    for(int l=0;l<9;l++){
        for(int m=0;m<9;m++){
            hv[l][m]=sum;
            sum=sum-10;
        }
    }
    sum=810;
    for(int l=0;l<9;l++){
        for(int m=0;m<9;m++){
            hvc[m][l]=sum;
            sum=sum-10;
        }
    }  
    for(int x=0;x<9;x++){
        vector<int> vc;
            for(int y=0;y<9;y++){
                vc.push_back(ssb[x][y]);
            }
          ini.push_back(vc);
        }
    Node In;
    In.fv=0;
    In.hv=810;
    In.i=0;
    In.j=0;
    In.nodecount=0;
    open.push_back(In);
}
bool rowcheck(Node N,int i,int num){
    int n=0;
      for(n=0;n<9;n++){    
             if(N.sb[i][n]!=num)                
                 continue;
             else 
                 break;
        }
      if(n==9)
          return true;
      return false;
}
bool columncheck(Node N,int j,int num){
    int n=0;
     for(n=0;n<9;n++){    
             if(N.sb[n][j]!=num)                
                 continue;
             else 
                 break;
        }
      if(n==9)
          return true;
      return false;
}
bool gridsolver(Node N,int i,int j,int m,int n,int num){
    for(int x=i;x<=m;x++){
        for(int y=j;y<=n;y++){
            if(N.sb[x][y]==num){
                return false;
            }
        }
    }
    return true;
}
int gridsol(Node N,int i,int j,int m,int n){
    int count=0;
    for(int x=i;x<m;x++){
        for(int y=j;y<n;y++){
            if(ssb[x][y]==0){
                count++;
            }
        }
    }
    return count;
}
int grids(Node N,int i,int j){
    if((i>=0 && i<=2) && (j>=0 && j<=2))
        return gridsol(N,0,0,2,2);
    else if((i>=0 && i<=2) && (j>=3 && j<=5))
         return gridsol(N,0,3,2,5);
    else if((i>=0 && i<=2) && (j>=6 && j<=8))
          return gridsol(N,0,0,2,2);
    else if((i>=3 && i<=5) && (j>=0 && j<=2))
          return gridsol(N,3,0,5,2);
    else if((i>=3 && i<=5) && (j>=3 && j<=5))
          return gridsol(N,3,3,5,5);    
    else if((i>=3 && i<=5) && (j>=6 && j<=8))
          return gridsol(N,3,6,5,8);
    else if((i>=6 && i<=8) && (j>=0 && j<=2))
          return gridsol(N,6,0,8,2);
    else if((i>=6 && i<=8) && (j>=3 && j<=5))
          return gridsol(N,6,3,8,5);
    else if((i>=6 && i<=8) && (j>=6 && j<=8))
          return gridsol(N,6,6,8,8);
    
}
bool gridcheck(Node N,int i,int j,int num){
    
    if((i>=0 && i<=2) && (j>=0 && j<=2))
        return gridsolver(N,0,0,2,2,num);
    else if((i>=0 && i<=2) && (j>=3 && j<=5))
         return gridsolver(N,0,3,2,5,num);
    else if((i>=0 && i<=2) && (j>=6 && j<=8))
          return gridsolver(N,0,6,2,8,num);
    else if((i>=3 && i<=5) && (j>=0 && j<=2))
          return gridsolver(N,3,0,5,2,num);
    else if((i>=3 && i<=5) && (j>=3 && j<=5))
          return gridsolver(N,3,3,5,5,num);    
    else if((i>=3 && i<=5) && (j>=6 && j<=8))
          return gridsolver(N,3,6,5,8,num);
    else if((i>=6 && i<=8) && (j>=0 && j<=2))
          return gridsolver(N,6,0,8,2,num);
    else if((i>=6 && i<=8) && (j>=3 && j<=5))
          return gridsolver(N,6,3,8,5,num);
    else if((i>=6 && i<=8) && (j>=6 && j<=8))
          return gridsolver(N,6,6,8,8,num);
}
//first heuristic function
int heuristic_1(Node N,int i,int j,int num,int lev){
   // cout<<"4";
    int count=0;   
    //for(int y=j;y<9;y++){
           if(ssb[i][j]==0)
            {count=hv[i][j]+num;}
    //}  
    return count;
}
int heuristic_2(Node N,int i,int j,int num,int lev){
    int count=0;
    if(ssb[i][j]==0)
        count=hvc[i][j]+num-lev;    
    return count;
}
int heuristic_3(Node N,int i,int j,int num,int lev){
    int count=0;
    if(ssb[i][j]==0)
        count=hvg[i][j]+num;
}
bool sudokugoal(Node N){
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(N.sb[i][j]==0)
                return false;
        }
    }
    return true;
}


Node successorgenerator(Node N,int i,int j,int lev){  
    //cout<<"3"<<" "; 
    //vector<int> crct;
    map<int,int> mp;
    bool a,b,c;
    // if(ssb[i][j]==0 |
    if(ssb[i][j]==0){    
    for(int m=1;m<=9;m++){
        //rule 1: row Checking
        a=rowcheck(N,i,m);
        b=columncheck(N,j,m);
        c=gridcheck(N,i,j,m);
        if(a && b && c)
        {N.sb[i][j]=m;break;}
      }    
    }
    
     return N;
}

void explorenode(Node N){
    cout<<"fv="<<N.fv<<",("<<N.i<<N.j<<"),nodeexpanded="<<N.nodecount<<"\n";

}
void subroutine(Node v,int u,int l,int m,int lev){   
    graph[u].push_back(v);  
    int tn=0;
    bool a,b,c;
    for(int x=1;x<=9;x++){
       // Node ne;
         a=rowcheck(v,l,x);
         b=columncheck(v,m,x);
         c=gridcheck(v,l,m,x);
        if(a && b && c)    
            {Node ne;
              NC++;
              //ne=successorgenerator(ne,x,y,lev);
              ne.sb[l][m]=x;
              ne.hv=heuristic_3(ne,l,m,x,lev); 
              ne.gv=lev;
              ne.fv=ne.hv+ne.gv;
              ne.i=l;ne.j=m;
              ne.nodecount=NC; 
              explorenode(ne);
              graph[u].push_back(ne);}
    }
     
}



bool search(Node N){
    for(int x=0;x<open.size();x++){
        Node t=open[x];
        if(t.fv<=N.fv && t.i==N.i && t.j==N.j && t.vis==true){
            return true;
        }
    }
    return false;
}
bool search_close(Node N){
    for(int x=0;x<closed.size();x++){
        Node t=closed[x];
        if(t.fv<=N.fv && t.i==N.i && t.j==N.j && t.vis==true){
            return true;
        }
    }
    return false;
}
vector<int> findnextempty(){
    vector<int> vc;
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
            if(ssb[x][y]==0)
            {
                vc.push_back(x);
                vc.push_back(y);
                
            }
        }
    }
    return vc;
}
vector<int> findnextemptyc(){
vector<int> vc;
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
            if(ssb[y][x]==0)
            {
                vc.push_back(x);
                vc.push_back(y);
                break;
            }
        }
    }
    return vc;

}
vector<int> findnextemptyg(){
    vector<int> vp;
     
    for(int y=0;y<9;y++){
        for(int x=0;x<=2;x++){
            if(ssb[y][x]==0){
                vp.push_back(y);
                vp.push_back(x);
                return vp;
            }
        }
    }
    for(int y=0;y<9;y++){
        for(int x=3;x<=5;x++){
            if(ssb[y][x]==0){
                vp.push_back(y);
                vp.push_back(x);
                return vp;
            }
        }
    }
    for(int y=0;y<9;y++){
        for(int x=6;x<=8;x++){
            if(ssb[y][x]==0){
                vp.push_back(y);
                vp.push_back(x);
                return vp;
            }
        }
    }
    return vp;
}
void Astar_1search(int i,int j,int lev){
    Node y;
    y=open.back();
    
    for(int g=0;g<9;g++){
            for(int h=0;h<9;h++){
                ssb[g][h]=y.sb[g][h];
            }
        } 
    trace.insert({y.hv,y});
    open.pop_back();
    subroutine(y,0,0,1,0);
     vector<Node>::iterator it;
        Node x;
        int k=1;
        int u=y.nodecount;
        for(it=graph[u].begin();it!=graph[u].end();it++){
            x=*it;
            if(k>1)
            {   if(sudokugoal(x))
                   {break;}
               if((search(x)==true)||(search_close(x)==true))
                 {continue;}
               else
                 {open.push_back(x);}          
            }            
            k++;
        } 
    
        y.vis=true;
        closed.push_back(y);

}

void Astar_Search(){
    int lev=0;    
    while(!open.empty()){         
        sort(open.begin(),open.end(),[](const Node& a,const Node& b){return a.fv<b.fv;});
        Node q;
        q=open.back();        
        for(int g=0;g<9;g++){
            for(int h=0;h<9;h++){
                ssb[g][h]=q.sb[g][h];
            }
        }        
       q.vis=true;
        map<int,Node>::iterator its;
        for(its=trace.begin();its!=trace.end();its++){
            if(its->first<q.hv){
                its->second.vis=false;
            }
        }
        trace.insert({q.hv,q});
        open.pop_back();
        
        int u=q.nodecount;
        if(lev<=q.gv)
        {lev++;depth++;}
        else
        {NE++;}
          // vector<int> vp=findnextempty();     // first heuristic
          //vector<int> vp=findnextemptyc();   //second heuristic
         vector<int> vp=findnextemptyg();   //third heuristic
           subroutine(q,u,vp[0],vp[1],lev);   //generating successors
          //subroutine(q,u,vp[1],vp[0],lev);   //second heuristic
         // subroutine(q,u,vp[0],vp[1],lev);
      //  q.vis=true;
          
        vector<Node>::iterator it;
        Node x;
        int k=1;
        for(it=graph[u].begin();it!=graph[u].end();it++){
            x=*it;
            if(k>1)
            {               
               if(sudokugoal(x))
                   {break;}
               if((search(x)==true)||(search_close(x)==true))
                 {continue;}
               else if(x.sb[x.i][x.j]!=0)
                 {open.push_back(x);}   
               else{
                   graph[u].erase(it);
               }
                
            }
            // searching for correct node                        
            k++;
        }//cout<<"done\n";  
           closed.push_back(q);        
    }    
}
void displays(Node N){
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
          cout<<N.sb[x][y]<<" ";        
        }    
        cout<<"\n";
    }
}
void display(){
    Node nes;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(ssb[i][j]==0){
                for(int x=1;x<=9;x++){
                   bool a,b,c;
                   a=rowcheck(nes,i,x);
                   b=columncheck(nes,j,x);
                   c=gridcheck(nes,i,j,x);                   
                   if(a && b && c)
                   { ssb[i][j]=x; break;}
                       
                }
            } 
        }
    }
    cout<<"\n";
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
          cout<<ssb[x][y]<<" ";        
        }    
        cout<<"\n";
    }
        
        vector<Node>::iterator it;
        int si=0;
        for(int u=0;u<NC;u++){
             si+=graph[u].size();
         }
         cout<<"Number of nodes explored= "<<NE<<"\n";
         cout<<"Number of nodes generated= "<<si<<" \n";
         cout<<"Height of the tree= "<<depth<<" ";
         cout<<"The Branching factor of the b*= "<<(si/depth);
}
void totalpath(){
    cout<<"\n"<<" The trace of the solution"<<"\n";
    int i=0;
    map<int,Node>::iterator it;
    
    while(i<closed.size()){
        Node x=trace[closed[i].hv];
        if(x.vis==true){
            cout<<"fv="<<x.fv<<",("<<x.i<<x.j<<"),node="<<x.nodecount<<"\n";;
        }
        i++;
    }
}
};
int main(int argc, char** argv) {   
    Astar A;  
    A.Astar_1search(0,0,0);
    A.Astar_Search();
    A.display();
    A.totalpath();
   // cout<<A.NC<<" ";
    ssb.clear();    
    return 0;
}

 
