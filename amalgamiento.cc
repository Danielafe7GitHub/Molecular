#include <bits/stdc++.h>
#define MAXN 1000
#define COL 7
using namespace std;
vector<string> names;
double matrix[MAXN][COL];
double distancias[MAXN][MAXN],disoc[MAXN];
int padre[MAXN],mark[MAXN],ranking[MAXN];
typedef double (*FUNC_PTR)(double,double);
map<int , vector<int> > cluster;
multiset< pair< int, pair<int, int > > > dists;

double prom(double a, double b){
  return (a + b)/2;
}

double maxim(double a , double b){
  return max(a,b);
}

double minim(double a , double b){
  return min(a,b);
}


inline int find_set(int u){
  if(u == padre[u]){
    return u;
  }
  return padre[u] = find_set(padre[u]);
}

inline void merge_set(int a, int b){
  a = find_set(a);
  b = find_set(b);
  if(a != b){
    // if(rand() % 2)
    //   swap(a,b); 
    padre[b] = a;
  }
}

void getDistances(int n) {
  auto start = std::chrono::system_clock::now();
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
  auto end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("Inicializacion(Distancias,etc) demoro %.9f segundos\n",elapsed);
}

// void llenarSet(){
//   for(int i = 0 ;i < n ; ++i){
//     for(int j  = 0 ; j < n ; ++j){
//       dists.insert( { distancias[i][j] , {i,j} } );
//     }
//   }
// }

// double getMinSet(int &i, int &j, int n ){
//   pair<int , pair<int,int > > val = (*dists.begin());
//   i = padre[val.second.first];
//   j = padre[val.second.second];
//   dists.erase(dists.begin());
//   return val.first;
// }


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

double getMinDSU(int &a, int &b, int n){
  double mini = 1000000;
  for(int i = 0 ; i < n ; ++i){
    for(int j = 0 ; j < n ; ++j){
      int pi = find_set(i), pj = find_set(j);
      if(pi != pj){  
	double last = mini;
	mini = min(distancias[pi][pj],mini);
	if(last != mini){
	  a = min(pi,pj);
	  b = max(pi,pj);
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
  auto start = std::chrono::system_clock::now();
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
  auto end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("Amalgamiento demoro %.9f segundos sin DSU\n",elapsed);
}

// void amalgamientoSet(int  n , int k, FUNC_PTR fnc){
//   auto start = std::chrono::system_clock::now();
//   for(int cnt = 0 ; cnt < k ; ++cnt){
//     int a,b;
//     double minVal = getMinSet(a,b,n);
//     getNewParent(a,b,n);
//     for(int j = 0 ; j < n ; ++j){
//       if(padre[j] != j or padre[j] == a)
// 	continue;
//       double select = fnc(distancias[j][a],distancias[j][b]);
//       // if(distancias[j][a] != select)
//       	// dists.erase(distancias[j][a]);
//       // else
//       // 	dists.erase(distancias[j][b]);
//       distancias[a][j] = distancias[j][a] = fnc(distancias[j][a],distancias[j][b]);
//     }   
//   }
//   auto end = std::chrono::system_clock::now();
//   double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
//   printf("Amalgamiento demoro %.9f segundos sin DSU\n",elapsed);
// }

void amalgamientoDSU(int  n , int k, FUNC_PTR fnc){
  auto start = std::chrono::system_clock::now();
  for(int cnt = 0 ; cnt < k ; ++cnt){
    int a,b;
    double minVal = getMinDSU(a,b,n);
    merge_set(a,b);
    int val = find_set(a); 
    for(int j = 0 ; j < n ; ++j){
      if(padre[j] != j or padre[j] == val)
	continue;
      distancias[val][j] = distancias[j][val] = fnc(distancias[j][a],distancias[j][b]);
    }   
  }
  auto end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("Amalgamiento demoro %.9f segundos con DSU\n",elapsed);
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
vector<int> cola ;
void disociativo(int n, int k, FUNC_PTR fnc){
  auto start = std::chrono::system_clock::now();
  getMinPerRow(n);
  for(int cnt = 0 ; cnt < k-1 ; ++cnt){
    int idx = getMax(n);
    cola.clear();
    cola.resize(0);
    cola.push_back(idx);
    mark[idx] = 1;
    for(int i = 0 ; i < n ; ++i ){
      bool flag=1;
      double nn = distancias[i][cola[0]];
      for(int j = 1 ; j < cola.size() ; ++j){
	double nj = distancias[i][cola[j]];
	nn = fnc(nj,nn);
	if(cola[j] == i)
	  flag=0;
      }
      if(!mark[i] and flag){
	if(disoc[i] - nn >= 0){
	  padre[i] = idx;
	  mark[i] = 1;
	  cola.push_back(i);
	}
      }
    }
  }
  auto end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
  printf("Disociativo demoro %.9f segundos\n",elapsed);
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
  disociativo(n,k,fnc_ptr);
  //amalgamiento(n,k,fnc_ptr);
  //amalgamientoDSU(n,k,fnc_ptr);
  for(int i = 0 ; i < n; ++i){
    if(mark[i])
      cluster[padre[i]].push_back(i);
    else
      cluster[1000].push_back(i);
  }
  int cnt = 0;
  for(auto it = cluster.begin() ; it != cluster.end() ; it++){
    if(it->second.size() >= 1){
      cnt++;
      cout << "\nGrupo " << cnt << ":\n";
      for(int j = 0 ; j < it->second.size() ; ++j)
      	cout << names[(it->second)[j]] << " ";
      cout << "\n*****\n";
    }
  }
  return 0;
}
