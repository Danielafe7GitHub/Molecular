#include <bits/stdc++.h>
using namespace std;
#define MAXN 10010
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


pair<string,string> justOne(int i , int j, string &st, string &pt){
  // cout << i << " " << j << "\n";
  if(i <= 0 and j <= 0){
    return {"",""};
    //fin
  }
  if(i-1 >= 0 and j-1 >= 0)
    if(DP[i][j] == ( DP[i-1][j-1] + ( (st[i-1] == pt[j-1]) ? 1 : -1) ) ){
      pair<string,string> pp = justOne(i-1,j-1,st,pt);
      // cout << pp.first << " " << pp.second << "\n";
      return {pp.first + st[i-1] , pp.second + pt[j-1]};
    }
  if(i-1 >= 0)
    if(DP[i][j] == (DP[i-1][j] - 2)){
      pair<string,string> pp = justOne(i-1,j,st,pt);
      return { pp.first + st[i-1] , pp.second + "-"};
    }
  if(j-1 >= 0)
    if(DP[i][j] == (DP[i][j-1] - 2)){
      pair<string,string> pp = justOne(i,j-1,st,pt);
      return { pp.first + "-" , pp.second + pt[j-1]};
    }
  // return {"",""};
}

pair<string,string> myDupla;
void trace(int i , int j, string &st, string &pt, pair<string,string> dupla){
  if(i <= 0 and j <= 0){
    rpta.push_back(dupla);
    // myDupla = dupla;
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

int giveScore(vector<string> & msa){
  int scoreFinal = 0;
  for(int i = 0 ; i < msa.size() ; ++i){
    for(int j = i+1 ; j < msa.size() ; ++j){
      for(int k = 0; k < msa[i].size(); ++k){
	if(msa[i][k] == msa[j][k])
	  scoreFinal++;
	else if((msa[i][k] == '-' and msa[j][k] != '-') or (msa[i][k] != '-' and msa[j][k] == '-'))
	  scoreFinal -= 2;
	else if(msa[i][k] != msa[j][k])
	  scoreFinal -= 1;
      }
    }
  }
  return scoreFinal;
}
  
void getMemory(vector<string> & ss){
    int seqLength = sizeof(vector<string>);
    int maxElement = -1;
    for(int i = 0 ;i < ss.size() ; ++i){
      seqLength += ss[i].size();
      maxElement = max(maxElement,int(ss[i].length()));
    }
    int scoreMatrixLength =  sizeof(int) * maxElement * maxElement;
    int totalLength = seqLength + scoreMatrixLength;
    cout << "Las secuencias usaron: " << seqLength << " bytes\n";
    cout << "Las matriz de Score uso: " << scoreMatrixLength << " bytes\n";;
    cout << "En total se usaron: " << totalLength << " bytes\n";	    
}

int main()
{
  init();
  int n; cin >> n;
  vector<string> pat;
  int maxScore=-1,idx=0;
  for(int i =0 ;i < n ; ++i){
    string st; cin >> st;
    pat.push_back(st);
  }

  auto start = std::chrono::system_clock::now();
  for(int i = 0 ;i < n ; ++i){
    int acumScore = 0;
    for(int j = 0 ; j < n ; ++j){
      if(j == i) continue;
      init();
      acumScore += dp(pat[i].size(),pat[j].size(),pat[i],pat[j]);      
    }
    if(acumScore > maxScore){
      maxScore = acumScore;
      idx = i;
    }
  }
  vector< pair<string,string> > vpp;
  for(int i = 0 ; i < n ; ++i){
    if(i == idx)    continue;
    init();
    dp(pat[idx].size(),pat[i].size(),pat[idx],pat[i]);
    vpp.push_back(justOne(pat[idx].size(),pat[i].size(),pat[idx],pat[i]));
  }
  vector<string> msa;
  int maxSize = int(pat[idx].size());
  msa.push_back(pat[idx]);
  for(int i = 0 ;i < vpp.size() ; ++i){
    msa.push_back(vpp[i].second);
    maxSize = max(maxSize,int(vpp[i].second.size()));
  }
  for(int i = 0 ; i < msa.size() ; ++i){
    for(int j = msa[i].length() ; j < maxSize ; ++j)
      msa[i] += '-';
  }
  auto end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("El tiempo para alinear las secuencias: %.9f segundos\n",elapsed);
  cout << "El Score obtenido es: " << giveScore(msa) << "\n";
  getMemory(msa);
  cout << "Las secuencias alineadas:\n";
  for(int i = 0 ;i < msa.size(); ++i){
    cout << msa[i] << "\n";
  }
  
  // auto start = std::chrono::system_clock::now();
  // dp(st.size(),pt.size(),st,pt);
  // auto end = std::chrono::system_clock::now();
  // double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  // printf("El tiempo del Algoritmo Needleman and Wunsch: %.9f segundos\n",elapsed);
  // start = std::chrono::system_clock::now();
  // trace(st.size(),pt.size(),st,pt,{"",""});
  // end = std::chrono::system_clock::now();
  // elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  // printf("El tiempo del Algoritmo de Trazado: %.9f segundos\n",elapsed);
  // printf("Cantidad de posibles alineamientos: %d\n",rpta.size());
  // printf("El Score es: %d\n", DP[st.size()][pt.size()]);

  // printf("La matriz resultante es:\n\n");
  // for(int i = 0 ; i <= st.size() ; ++i){
  //     for(int j = 0 ; j <= pt.size() ; ++j){
  // 	printf("%4d",DP[i][j]);
  // 	// cout << DP[i][j] << " ";
  //     }
  //     printf("\n\n");
  //   }
  
  
  // printf("Las posibles respuestas son:\n\n");
  // for(int i = 0 ; i < rpta.size() ; ++i ){
  //   reverse(rpta[i].first.begin()  , rpta[i].first.end()  );
  //   reverse(rpta[i].second.begin() , rpta[i].second.end() );
  //   printf("%s\n",rpta[i].first.c_str());
  //   printf("%s\n\n",rpta[i].second.c_str());
  // }

  // vector<double> rptaPenalty = gapPenalty(rpta);
  // double minElement = *(min_element(rptaPenalty.begin() , rptaPenalty.end() ));
  // printf("Las respuestas con mejor penalidad por gap son(con penalidad %f): \n",minElement);
  // for(int i = 0 ; i < rpta.size() ; ++i)
  //   if(rptaPenalty[i] == minElement){
  //         printf("%s\n",rpta[i].first.c_str());
  // 	  printf("%s\n\n",rpta[i].second.c_str());
  //   }  
  
}
