//1D Cellular Automata discrete state的完整HEADFILE
//k=1,r=2  一共有五個細胞會影響下一個時間的狀態 
//本檔案可以用來計算CA的下列特質
//1.給予Rule number之後可以給予對應的二進位，以及CA 的對應
//2.可以亂數給定狀態，或依據主程式給訂初始狀態
//3.計算CA在經過一定時間之後的最終狀態
//4.可以用來檢視discrete state network隨時間的演進(evolution) 
//**本程式一律按照順序[rule][timestep][n_step] [initial state] 排列 
//**將二維陣列視作一維處理 ->準則 
#ifndef _nt92_class_camajority_
#define _nt92_class_camajority_
#include <cstdlib>
#include <iomanip> 
#include <iostream>
#include <cmath> 
#include <time.h>
#include <conio.h>
#include <stdio.h>
using namespace std; 
class camajority
{        
    int asign[32] ; //運算規則陣列 
    int cellnumber ;// number of cells(L) 
   // int rulenumber ;// 這裡指定是用那種rule 
    int timestep ;//number of time steps
    int *s;//以一維儲存所有資料 
    int *state2; 
 
  
    public: 
    //constructors:
    camajority (){;}; 
  //  carule (int ,int ) ;//ini由亂數給定
    camajority (int ,int ,int * ) ;//主動給予ini 
    ~camajority() { delete [] this->s;    // destructor
                      this->cellnumber = this->timestep = 0;
                    }
    
    //member function 
    void print() const;//出現基本參數以及初始狀態 
    void print(int ) const;//出現某個時間的狀態
    inline int CV(const int i,const int j) const {return(cellnumber*i + j);}
   // void majoritytransf() ; //
    inline int get(const int i, const int j) const  //得到某個時間的陣列值 
                        { return this->s[CV(i,j)]; }                   
    inline int get2(const int timee ) const
                        { return this->state2[timee] ;} 
    inline void set(const int i, const int j, int xx) // 輸入某個時間的陣列值 
                     { this->s[CV(i,j)] = xx; }
    void caevaluate(); //計算狀態隨時間的演進 
    void cadiscrete(); //使用另外一種方法 
    
      };

camajority::camajority(int time,int cell,int *d) 
{
  this-> timestep= time;
  this->cellnumber = cell;
  
  this->s = new int [time*cell+time] ;
  int j;
  for(j = 0;j < cell;j ++)  s[CV(0,j)] = d[j]; 
  
 
   int k =0;
   for(k=0; k < 13;k++)this-> asign[k] =0;
   asign[7] =1; asign[11] = 1;
   k = 0;
   for(k = 13; k < 32;k++) asign[k] =1; 
   asign[24] = 0; asign[20] =0; asign[18] =0; asign[17] =0;asign[16] =0; 
} 
 
void camajority::caevaluate()//依據規則建立狀態隨時間的演化 
{
  int t = 0, j = 0 , k = 0;
  int tim =  this->timestep, n = this->cellnumber; 
  int sum = 0;
  
  for(t=0;t< tim;t++)
  {
    for ( j=0;j<n;j++)
    {
        sum = 1*s[CV(t,(j+2+n)%n)] + 2* s[CV(t,(j+1+n)%n)] + 4* s[CV(t,(j+n)%n)]+8* s[CV(t,(j-1+n)%n)]+16*s[CV(t,((j-2)+n)%n)];
        s[CV(t+1,j)] =this->asign [sum] ;
        sum = 0;          
    }
  } 
}                

void camajority::cadiscrete()
{
 //int sum= (int)  pow(2.0,(double) this-> cellnumber) ; 
 this-> state2 = new int  [this->timestep+2] ;
 
 int m=0 ,cell =0;
 int total = 0; 
 for(m = 0;m < this->timestep ;m++) 
 {
    for(cell = 0;cell < this -> cellnumber; cell++)
    {
           total =  total +  (int) pow(2.0,(double) cellnumber-cell-1) * get(m,cell);
       } 
     this->state2[m]= total; 
     total = 0; 
    // cout << "t=" << m << "  " <<this->state2[m] <<endl; 
 }                   
  
} 
void camajority::print()  const //輸出基本資料 
{
 
// cout << "rulenumber = " << this->rulenumber << endl;
 cout << "n_step = " << this->cellnumber << endl; 
 cout << "time = " << this->timestep << endl;
 
 int i,j;
  cout << "initial state = " ;
  for(i = 0;i < this->cellnumber;i ++)   cout << " " <<this->s[CV(0,i)] ;
  cout << endl;
  for(j = 0;j < 32;j ++)   cout << "RULE " << pow(2.0,32-j)<< " = "<< this->asign[32-j-1] << endl;
  cout << "*******************************" << endl;
 
} 

void camajority::print(int times) const 
{  
     int m=0 ,k,total = 0;
     k = this->cellnumber;
      for(int cell = 0;cell < k; cell++)
    {
           total =  total +  (int) pow(2.0,(double) k-cell-1) * this->s[CV(times,cell)];
       } 
     cout << "t(" << times  << ") =   "; 
     for(m = 0;m < k;m ++)  cout <<  this->s[CV(times,m)]  ; 
     cout << "      ";
     cout << total;
            
     cout << endl;    
} 
#endif
