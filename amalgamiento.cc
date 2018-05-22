#include <bits/stdc++.h>
#define MAXN 1000
#define COL 7
using namespace std;
vector<string> names;
double matrix[MAXN][COL];
double distancias[MAXN][MAXN],disoc[MAXN];
int padre[MAXN],mark[MAXN];
typedef double (*FUNC_PTR)(double,double);
map<int , vector<int> > cluster;

double prom(double a, double b){
  return (a + b)/2;
}

double maxim(double a , double b){
  return max(a,b);
}

double minim(double a , double b){
  return min(a,b);
}

void getDistances(int n) {
  for(int i = 0 ; i < n ; ++i){
    for(int j = 0 ; j < n ; ++j){
      double value = 0;
      for(int k = 0 ; k < COL ; ++k)
	value += (matrix[i][k] - matrix[j][k]) * (matrix[i][k] - matrix[j][k]);
      distancias[i][j] = sqrt(value);
    }
  }
  for(int i = 0 ; i < n ; ++i)
    padre[i] = i;
  memset(mark,0,sizeof mark);
}

double getMin(int &a, int &b, int n){
  double mini = 1000000;
  for(int i = 0 ; i < n ; ++i){
    for(int j = 0 ; j < n ; ++j){
      if(padre[j] != padre[i]){
	double last = mini;
	mini = min(distancias[padre[i]][padre[j]],mini);
	if(last != mini){
	  a = min(padre[i],padre[j]);
	  b = max(padre[j],padre[i]);
	}
      }
    }
  }
  return mini;
}

void getNewParent(int parent,int child, int n ){ // puede mejorarse con dsu
  for(int i = 0 ;i < n; ++i){
    if(padre[i] == child)
      padre[i] = parent;
  }
}

void amalgamiento(int  n , int k, FUNC_PTR fnc){
  for(int cnt = 0 ; cnt < k ; ++cnt){
    int a,b;
    double minVal = getMin(a,b,n);
    getNewParent(a,b,n);
    for(int j = 0 ; j < n ; ++j){
      if(padre[j] != j or padre[j] == a)
	continue;
      distancias[a][j] = distancias[j][a] = fnc(distancias[j][a],distancias[j][b]);
    }   
  }
}

void getMinPerRow(int n){
  for(int i  = 0 ; i < n ; ++i){
    double value = 10000;
    for(int j = 0 ; j < n ; ++j){
      if(j != i )
	value = min(value,distancias[i][j]);
    }
    disoc[i] = value;
  }
}

int getMax(int n){
  double value = -10000,idx=0;
  for(int i= 0 ; i < n ; ++i)
    if(!mark[i] && value < disoc[i]){
      idx = i;
      value = disoc[i];
    }
  return idx;
}

void disociativo(int n, int k){
  getMinPerRow(n);
  for(int cnt = 0 ; cnt < k ; ++cnt){
    int idx = getMax(n);
    mark[idx] = 1;
    for(int i = 0 ; i < n ; ++i ){
      if(!mark[i] and i != idx){
	if(disoc[i] - distancias[i][idx] >= 0){
	  padre[i] = idx;
	  mark[i] = 1;
	}
      }
    }    
  }
}

int main(){
  int n,k,c; cin >> n >> k >> c;
  names.resize(n);
  for(int i = 0 ; i < n ; ++i) { 
    cin >> names[i];
    for(int j = 0 ; j < COL ; ++j){
      cin >> matrix[i][j];
    }
  }
  getDistances(n);
  double (*fnc_ptr)(double,double);
  switch(c){
  case 0:
     fnc_ptr= &minim;
  case 1:
    fnc_ptr= &maxim;
  case 2:
    fnc_ptr= &prom;
  }
  disociativo(n,k);
  // amalgamiento(n,k,fnc_ptr);
  for(int i = 0 ; i < n; ++i){
    cluster[padre[i]].push_back(i);
  }
  for(auto it = cluster.begin() ; it != cluster.end() ; it++){
    if(it->second.size() > 1){
      cout << "\nGrupo:\n";
      for(int j = 0 ; j < it->second.size() ; ++j)
      	cout << names[(it->second)[j]] << " ";
      cout << "\n*****\n";
    }
  }
  return 0;
}
