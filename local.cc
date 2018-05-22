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
  if(i == 0 or j == 0)
    return DP[i][j] = 0;
  if(DP[i][j] != INF)
    return DP[i][j];
  return DP[i][j] = max(0,maxThree(dp(i,j-1,st,pt) - 2,dp(i-1,j-1,st,pt) + (st[i-1] == pt[j-1] ? 1 : -1 ) , dp(i-1,j,st,pt) -2));
}


void traceIncorrecto(int i , int j, string &st, string &pt, pair<string,string> dupla){
  if(DP[i][j] == 0){
    rpta.push_back(dupla);
    return ;
    //fin
  }
  pair<string,string> mem = dupla;
  if(i-1 >= 0 and j-1 >= 0)
    if(DP[i][j] == ( DP[i-1][j-1] + ( (st[i-1] == pt[j-1]) ? 1 : -1) ) ){
      dupla.first += st[i-1];
      dupla.second += pt[j-1];
      traceIncorrecto(i-1,j-1,st,pt,dupla);
    }
  dupla = mem;
  if(i-1 >= 0)
    if(DP[i][j] == (DP[i-1][j] - 2)){
      rpta.push_back(dupla);
      return ;
    }
  dupla = mem;
  if(j-1 >= 0)
    if(DP[i][j] == (DP[i][j-1] - 2)){
      rpta.push_back(dupla);
      return ;
    }      
}

void traceCorrecto(int i , int j, string &st, string &pt, pair<string,string> dupla){
  if(DP[i][j] == 0){
    rpta.push_back(dupla);
    return ;
    //fin
  }
  pair<string,string> mem = dupla;
  if(i-1 >= 0 and j-1 >= 0)
    if(DP[i][j] == ( DP[i-1][j-1] + ( (st[i-1] == pt[j-1]) ? 1 : -1) ) ){
      dupla.first += st[i-1];
      dupla.second += pt[j-1];
      traceCorrecto(i-1,j-1,st,pt,dupla);
    }
  dupla = mem;
  if(i-1 >= 0)
    if(DP[i][j] == (DP[i-1][j] - 2)){
      dupla.first += st[i-1];
      dupla.second += "-";
      traceCorrecto(i-1,j,st,pt,dupla);    
    }
  dupla = mem;
  if(j-1 >= 0)
    if(DP[i][j] == (DP[i][j-1] - 2)){
      dupla.first += "-";
      dupla.second += pt[j-1];
      traceCorrecto(i,j-1,st,pt,dupla);
    }      
}

int giveMax(int n , int m)
{
  int res = INF;
  for(int i = 0; i <= n ; ++i)
    for(int j = 0 ; j <= m ; ++j)
      res = max(res,DP[i][j]);
  return res;
}

int giveK(string st)
{
  bool state = 0;
  int k = 0 ;
  for(int i = 0 ; i < st.size() ; ++i)
    {
      if(!state and st[i] == '-'){
	state = 1;
	k++;
      }
      if(state and st[i] != '-'){
	state = 0;
      }	
    }
  return k;
}

double penaltyFunction(int k){
  if(k == 0)
    return 0;
  return 5 + 3 * k;
}

vector<double> gapPenalty(vector< pair< string, string > > & st)
{
  vector<double> rpta;
  for(int i = 0 ; i < st.size() ; ++i)
    {
      int k = max(giveK(st[i].first),giveK(st[i].second));
      rpta.push_back(penaltyFunction(k));
    }
  return rpta;
}


int main()
{
  init();
  string st, pt; cin >> st >> pt;
  auto start = std::chrono::system_clock::now();
  dp(st.size(),pt.size(),st,pt);
  auto end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("El tiempo del Algoritmo Smith and Waterman: %.9f segundos\n",elapsed);
  int maxElement = giveMax(st.size(), pt.size());

  start = std::chrono::system_clock::now();
  for(int i = 0 ; i <= st.size() ; ++i)
    for(int j = 0 ; j <= pt.size() ; ++j)
      if(maxElement == DP[i][j])
	traceCorrecto(i,j,st,pt,{"",""});
  vector< pair< string, string > > rpta1 = rpta;
  rpta.clear();
  end = std::chrono::system_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("El tiempo del Algoritmo de Trazado(segun similaridad): %.9f segundos\n",elapsed);
  
  start = std::chrono::system_clock::now();
  for(int i = 0 ; i <= st.size() ; ++i)
    for(int j = 0 ; j <= pt.size() ; ++j)
      if(maxElement == DP[i][j])
	traceIncorrecto(i,j,st,pt,{"",""});
  end = std::chrono::system_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("El tiempo del Algoritmo de Trazado(segun igualdad): %.9f segundos\n",elapsed);
  
  printf("Cantidad de posibles alineamientos: %d\n",rpta.size());
  printf("El Score es: %d\n", maxElement);

  printf("La matriz resultante es:\n\n");
  for(int i = 0 ; i <= st.size() ; ++i){
      for(int j = 0 ; j <= pt.size() ; ++j){
	printf("%4d",DP[i][j]);
	// cout << DP[i][j] << " ";
      }
      printf("\n\n");
    }  
  
  printf("Las posibles respuestas son(segun similaridad):\n\n");
  for(int i = 0 ; i < rpta1.size() ; ++i ){
    reverse(rpta1[i].first.begin()  , rpta1[i].first.end()  );
    reverse(rpta1[i].second.begin() , rpta1[i].second.end() );
    printf("%s\n",rpta1[i].first.c_str());
    printf("%s\n\n",rpta1[i].second.c_str());
  }

  vector<double> rpta1Penalty = gapPenalty(rpta1);

  double minPenalty = *(min_element(rpta1Penalty.begin() , rpta1Penalty.end()));
  printf("Las respuestas con mejor penalidad por gap son(con penalidad %f): \n",minPenalty);
  for(int i = 0 ; i < rpta1.size() ; ++i)
    if(rpta1Penalty[i] == minPenalty){
          printf("%s\n",rpta1[i].first.c_str());
	  printf("%s\n\n",rpta1[i].second.c_str());
    }  
  printf("Las posibles respuestas son(segun igualdad):\n\n");
  for(int i = 0 ; i < rpta.size() ; ++i ){
    reverse(rpta[i].first.begin()  , rpta[i].first.end()  );
    reverse(rpta[i].second.begin() , rpta[i].second.end() );
    printf("%s\n",rpta[i].first.c_str());
    printf("%s\n\n",rpta[i].second.c_str());
  }
}
