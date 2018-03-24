#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define INF -5000
int DP[MAXN][MAXN];
vector< pair< string, string > > rpta;

void init()
{
  for(int i = 0 ; i < MAXN ; ++i)
    for(int j = 0 ; j < MAXN; ++j)
      DP[i][j] = INF;
}

int maxThree(int a , int b , int c){
  return max(max(a,b),c);
}

int dp(int i , int j, string &st, string &pt){
  if(i == 0)
    return DP[i][j] = -2 * j;
  if(j == 0)
    return DP[i][j] = -2 * i;
  if(DP[i][j] != INF)
    return DP[i][j];
  return DP[i][j] = maxThree(dp(i,j-1,st,pt) - 2,dp(i-1,j-1,st,pt) + (st[i-1] == pt[j-1] ? 1 : -1 ) , dp(i-1,j,st,pt) -2);
}


void trace(int i , int j, string &st, string &pt, pair<string,string> dupla){
  if(i <= 0 and j <= 0){
    rpta.push_back(dupla);
    return ;
    //fin
  } 
  pair<string,string> mem = dupla;
  if(i-1 >= 0 and j-1 >= 0)
    if(DP[i][j] == ( DP[i-1][j-1] + ( (st[i-1] == pt[j-1]) ? 1 : -1) ) ){
      dupla.first += st[i-1];
      dupla.second += pt[j-1];
      trace(i-1,j-1,st,pt,dupla);
    }
  dupla = mem;
  if(i-1 >= 0)
    if(DP[i][j] == (DP[i-1][j] - 2)){
      dupla.first += st[i-1];
      dupla.second += "-";
      trace(i-1,j,st,pt,dupla);    
    }
  dupla = mem;
  if(j-1 >= 0)
    if(DP[i][j] == (DP[i][j-1] - 2)){
      dupla.first += "-";
      dupla.second += pt[j-1];
      trace(i,j-1,st,pt,dupla);
    }      
}



int main()
{
  init();
  string st, pt; cin >> st >> pt;
  dp(st.size(),pt.size(),st,pt);
  printf("La matriz resultante es:\n\n");
  for(int i = 0 ; i <= st.size() ; ++i){
      for(int j = 0 ; j <= pt.size() ; ++j){
	printf("%4d",DP[i][j]);
	// cout << DP[i][j] << " ";
      }
      printf("\n\n");
    }
  trace(st.size(),pt.size(),st,pt,{"",""});
  printf("Las posibles respuestas son:\n\n");
  for(int i = 0 ; i < rpta.size() ; ++i ){
    reverse(rpta[i].first.begin()  , rpta[i].first.end()  );
    reverse(rpta[i].second.begin() , rpta[i].second.end() );
    printf("%s\n",rpta[i].first.c_str());
    printf("%s\n\n",rpta[i].second.c_str());
  }
}