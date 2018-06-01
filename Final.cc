#include <bits/stdc++.h>
using namespace std;
typedef unsigned char byte;
#define BYTESIZE 8
#define BYTEHALF 4
#define MAXVALUE 255


class pointMatrix{
public:
  vector< vector<byte> >  matrix;
  int n,m;
  pointMatrix(int n, int m){
    matrix.resize(n);
    this->n = n;
    this->m = m;
    for(int i = 0 ;i < n ; ++i){
      matrix[i].resize(ceil(float(m)/(float(BYTEHALF))));
    }
  }

  void setBit(byte & b, short pos){
    pos = BYTESIZE - pos - 1;
    b |= (1<<pos);
  }

  void unsetBit(byte & b, short pos){
    pos = BYTESIZE - pos - 1;
    b &= ~(1<<pos);
  }

  int getBit(byte b, short pos){
    pos = BYTESIZE - pos - 1;
    return ( (b & (1<<pos)) != 0);
  }

  void print(){
    cout << "Point Matrix:\n";
    for(int i = 0 ; i < n ; ++i){
      for(int j = 0 ; j < m ; ++j){
	cout << getValue(i,getPosY(j),getPosZ(j)) << " ";
      }
      cout << "\n";
    }
    cout << "Byte Matrix\n";
    for(int i = 0 ; i < matrix.size() ; ++i){
      for(int j = 0 ;j <  matrix[i].size() ; ++j){
	cout << int(matrix[i][j]) << " ";
      }
      cout << "\n";
    }
  }
  
  short getValue(int posx, int posy, int posz){
    short fstBit = short(getBit(matrix[posx][posy],2 * posz)) *2;
    short sndBit = getBit(matrix[posx][posy],2 * posz+1);
    return fstBit + sndBit;
  }

  bool setValue(int posx,int posy, int posz, short value){
    if( (value / 2) == 1)
      setBit(matrix[posx][posy],2 * posz);
    else
      unsetBit(matrix[posx][posy], 2 * posz);
    if( (value % 2) == 1)
      setBit(matrix[posx][posy],2* posz+1); 
    else
      unsetBit(matrix[posx][posy],2 * posz+1);
    return true;
  }

  bool setValue(int posx, int posyraw, int value){
    int posy = getPosY(posyraw);
    int posz = getPosZ(posyraw);
    if( (value / 2) == 1)
      setBit(matrix[posx][posy],posz * 2);
    else
      unsetBit(matrix[posx][posy],posz * 2);
    if( (value % 2) == 1)
      setBit(matrix[posx][posy],2*posz+1); 
    else
      unsetBit(matrix[posx][posy],2*posz+1);
    return true;
  }

  int getPosY(int element){
    return ceil( float(element/BYTEHALF) )  ;// pos dle char en el que esta
  }

  short getPosZ(int element){
    return (element%BYTEHALF);
  }

  int getSize(){
    int val = 0;
    for(int i  = 0 ; i < matrix.size()  ; ++i)
      val += sizeof(vector<byte>) +  matrix[i].size() * sizeof(char);
    return val + sizeof(vector < vector < byte > > );
  }

  void changePosition(int & a, int &b, short myValue){
    switch(myValue){
    case 1:
      --a;
      break;
    case 2:
      --b;
      --a;
      break;
    case 3:
      --b;
      break;
    }    
  }
  void getNextChar(string &a, string & b,int myValue, int actX, int actY , pair<string,string> & ans){
    // cout << actX << " " << actY << "\n";
    char fst = (myValue == 3 ? '-' : a[actX]);
    char snd = (myValue == 1 ? '-' : b[actY]);
    ans.first += fst;
    ans.second += snd;
  }
  
  pair<string,string>  getSequence(string &a, string &b){
    int actX = n-1, actY = m-1;
    pair< string, string > ans = {"",""};
    short myValue = getValue(actX,getPosY(actY),getPosZ(actY));
    while(myValue != 0){
      changePosition(actX,actY,myValue);
      getNextChar(a,b,myValue,actX,actY,ans);
      myValue = getValue(actX,getPosY(actY),getPosZ(actY));
    }
    return ans;
  }
};

class NW{
public:
  vector<int> score[2];
  pointMatrix * pm;
  int n,m;
  NW(int n,int m){
    this->n = n ; // cuidado;
    this->m = m ;
    score[0].resize(this->m);
    score[1].resize(this->m);
    pm = new pointMatrix(this->n,this->m);
  };

  int solve(string & a , string &b){
    pm->setValue(0,0,0);
    score[0][0] = 0;
    for(int i = 1 ; i < m ; ++i){
      score[0][i] = i * -2;
      pm->setValue(0,i,3);
      
    }
    // for(int i = 0 ; i < m; ++i)
    //   printf("%4d ", score[0][i]);
    // printf("\n");
    for(int i  = 1 ; i < n ; ++i){
      int ni = i % 2, nia = (i % 2)  -  1 >= 0 ? (i%2) - 1 : 1;
      pm->setValue(i,0,1);
      score[ni][0] = 2 * -i;
      for(int j = 1 ; j < m ; ++j ){
    	int sum;
    	if(a[i-1] == b[j-1])
    	  sum = 1;
    	else
    	  sum = -1;
    	int fuckluv = max( score[ni][j-1]  - 2 , max(score[nia][j] - 2 , score[nia][j-1] + sum));
    	score[ni][j] = fuckluv;
    	if(fuckluv == score[ni][j-1] - 2)
    	  pm->setValue(i,j,3);
    	else if(fuckluv == score[nia][j] - 2)
    	  pm->setValue(i,j,1);
    	else
    	  pm->setValue(i,j,2);
      }
      // for(int j = 0 ; j < m ; ++j)
      // 	printf("%4d ", score[ni][j]);
      // printf("\n");
      
    }
    // pm->print();
    cout << score[(n-1)%2][m-1] << "\n";
    pair<string, string> pp =  pm->getSequence(a,b);
    cout << "El mejor alineamiento\n";
    cout << pp.first << "\n" << pp.second << "\n";
    cout << "Memoria usada para score: " << 2 * m * sizeof(sizeof(int)) << " bytes \n";
    cout << "Memoria sin optimizacion: " << n * m * sizeof(sizeof(int)) << " bytes \n";
    cout << "Memoria usada para point: " << pm->getSize() << " bytes \n";
    cout << "Memoria sin optimizacion: " << sizeof(int) * n * m  << " bytes \n";
    cout << "Mejora en memoria:  " << (sizeof(int) * n * m) / pm->getSize() << " veces mejor \n";
    return score[(n-1)%2][m-1] ;    
  }  
  
};
  


int main(){
  int n; cin >> n;
  for(int i = 0 ;i < n ; ++i){
    string a;
    cin >> a;
  }
  
  // int n,m; cin >> n >> m;
  
  // pointMatrix dame(n,m);
  // for(int i = 0 ;i < n ; ++i){
  //   for(int j = 0 ; j < m ; ++j){
  //     int val ; cin >> val;
  //     dame.setValue(i,j,val);
  //   }
  // }
  // dame.print();
  return 0;
}
