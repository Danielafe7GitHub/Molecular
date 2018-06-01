#include <bits/stdc++.h>

using namespace std;

int main(){
  int n,m; cin >> n >> m;
  for(int i = 0 ; i < n ; ++i)
    cout << char(rand() % 4 + 'A');
  cout << "\n";
  for(int i = 0 ; i < m ; ++i)
    cout << char(rand() % 4 + 'A');
  cout << "\n";
  return 0;
}
