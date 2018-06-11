#include <bits/stdc++.h>

using namespace std;

int main(){
  string ss = "ACGT";
  int n,m; cin >> n >> m;
  cout << n << "\n";
  for(int i = 0 ;i < n ; ++i){
    for(int i = 0 ; i < m ; ++i)
      cout << ss[rand()%4];
    cout << "\n";
  }
  return 0;
}
