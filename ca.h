//1D Cellular Automata discrete state的完整HEADFILE
//本檔案可以用來計算CA的下列特質
//1.給予Rule number之後可以給予對應的二進位，以及CA 的對應
//2.可以亂數給定狀態，或依據主程式給訂初始狀態
//3.計算CA在經過一定時間之後的最終狀態
//4.可以用來檢視discrete state network隨時間的演進(evolution) 
//**本程式一律按照順序[rule][timestep][n_step] [initial state] 排列 
//**將二維陣列視作一維處理 ->準則 
//**97.3.17 adding: class->discrete,array  ytlu->class->carray
//**97.3.19 使得操作上變得簡潔， delete the class named "discrete"
#ifndef _nt92_class_ca_
#define _nt92_class_ca_
#include <cstdlib>
#include <iomanip> 
#include <iostream>
#include <vector> 
#include <cmath> 
//#include <conio.h>
#include <time.h>
#include <stdio.h>
#define MAXDIM  300000
using namespace std; 
typedef unsigned int ULI;
class carule 
{        
    int asign[8] ; //運算規則陣列 
    int cellnumber ;// number of cells(L) 
    int rulenumber ;// 這裡指定是用那種rule 
    int timestep ;//number of time steps
    int *s;//以一維儲存所有資料 
    int *state2; 
 
  
    public: 
    //constructors:
    carule (){;}; 
    //carule (int ,int ,int ) ;//ini由亂數給定
    carule (int ,int ,int ,int ) ;//主動給予ini 
    ~carule() { delete [] this->s;    // destructor
                delete [] this->state2; 
                this->cellnumber = this->timestep = this->rulenumber = 0;
                    }
    
    //member function 
    void print() const;//出現基本參數以及初始狀態 
    void print(int ) const;//出現某個時間的狀態
    inline int CV(const int i,const int j) const {return(cellnumber*i + j);}
    inline void rule(int rulee) { this->rulenumber = rulee;} 
    inline void nstep(int cell) { this->cellnumber = cell;}
           void sites(int ) ; 
    inline void times(int timenumber) { this->timestep = timenumber;} 
    void ruletransf() ; //轉換至二進位 
    inline int get(const int i, const int j) const  //得到某個時間的陣列值 
                        { return this->s[CV(i,j)]; }                   
    inline int get2(const int timee ) const
                        { return this->state2[timee] ;} 
    inline void set(const int i, const int j, int xx) // 輸入某個時間的陣列值 
                     { this->s[CV(i,j)] = xx; }
    void caevaluate(); //計算狀態隨時間的演進 
    void cadiscrete2(); //使用另外一種方法 
    
      } ;
/* 
carule::carule(int a,int b,int c) 
{
  this->rulenumber =   a;
  this->timestep = b;
  this->cellnumber = c;

// 亂數給定初始值 
  srand((unsigned)time(NULL));
  this->s = new int [b*c+c];
  int i= 0;
  for(i = 0; i < c ; i++)
  {
    if ( rand() % 2 == 0 )s[CV(0,i)]= 1;//一開始的時間是0 
    else this->s[CV(0,i)] = 0;
  }
  ruletransf();
} 
*/
carule::carule(int rule,int time,int cell,int state) 
{
  this->rulenumber = rule;
  this->timestep   = time;
  this->cellnumber = cell;
  
  ruletransf();
  this->s = new int [time*cell+cell] ;
  this-> state2 = new int  [this->timestep+2] ;
  //s(time*cell+cell) ; 
  int* a = NULL; a = new int [cellnumber+3];
  int* b = NULL; b = new int [cellnumber+3];

  int n=0;    
  a[0]=0; b[0]=state;
  int i = 0, k =0, m = 0 ;
   
   for (i = 1; i < (cellnumber+1);i ++)
   {
       a[i]=(int)fmod((double)b[i-1] ,(double) 2);
       b[i]=b[i-1] / 2; 
   }
  
   for(m=0;m<cellnumber;m++)
   {
     
     if(a[m+1]>0.0) s[CV(0,m)]=1;
       else  s[CV(0,m)]=0;
     }      
//delete [] a;
//delete [] b; 
} 

void carule::sites(int state) 
{
  int* a = NULL; a = new int [cellnumber+3];
  int* b = NULL; b = new int [cellnumber+3];
  a[0]=0; b[0]=state;
  int i = 0, k =0, m = 0 ;
   
  for (i = 1; i < (cellnumber+1);i ++)
   {
       a[i]=(int)fmod((double)b[i-1] ,(double) 2);
       b[i]=b[i-1] / 2; 
   }
  
  for(m=0;m<cellnumber;m++)
   {     
     if(a[m+1]>0.0) s[CV(0,m)]=1;
       else  s[CV(0,m)]=0;
     //cout << "s[m] = " << s[m]  << endl; 
     }          
   
//delete [] a;
//delete [] b; 
} 

void carule::print()  const //輸出基本資料 
{
 
 cout << "rulenumber = " << this->rulenumber << endl;
 cout << "n_step = " << this->cellnumber << endl; 
 cout << "time = " << this->timestep << endl;
 
 int i,j;
  cout << "initial state = " ;
  for(i = 0;i < this->cellnumber;i ++)   cout << " " <<this->s[CV(0,i)] ;
  cout << endl;
  for(j = 0;j < 8;j ++)   cout << "RULE " << pow(2.0,7-j)<< " = "<< this->asign[j] << endl;
  cout << "*******************************" << endl;
 
} 

void carule::print(int times) const 
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

void carule::ruletransf() //rulenumber轉換成二進位，已修改^^ 
{ 
   int a[9];
   int b[9]; 
   a[0] = 0;b[0] = this->rulenumber;
   int i = 0, j = 0, k =0;
   
   for (i = 1; i < 9;i ++)
   {
       a[i]=(int)fmod((double)b[i-1] ,(double) 2);
       b[i]=b[i-1] / 2;       
   }
   for (j = 0;j < 8;j++) this->asign[7-j] = a[j+1];
   
} 

void carule::caevaluate()//依據規則建立狀態隨時間的演化 
{
  int t = 0, j = 0;
  int tim =  this->timestep, n = this->cellnumber; 
  int sum = 0;
  
  for(t=0;t< tim;t++)
  {
    for ( j=0;j<n;j++)
    {
        sum = 1*s[CV(t,(j+1)%n)] + 2* s[CV(t,j)] + 4*s[CV(t,((j-1)+n)%n)];
        s[CV(t+1,j)]= this->asign[7-sum] ;  //new method    
        sum = 0;          
     }
  } 
}                

void carule::cadiscrete2()
{
 int sum= (int)  pow(2.0,(double) this-> cellnumber) ; 
 
 
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
//2008.3.24加上對vector的分割
 //全部是二維陣列 
 /*
//class cvector{
      public: 
      vector< vector<int> >  cvector0; 
      vector< vector<int> >  cvector1;
      vector< vector<int> >  cvector2;
      vector< vector<int> >  cvector3;
      vector< vector<int> >  cvector4;
      vector< vector<int> >  cvector5;
      vector< vector<int> >  cvector6;
      vector< vector<int> >  cvector7;
      vector< vector<int> >  cvector8;
      int claim; 
      
      //constructor  
      cvector(){;}
      cvector(int  ) ;
      
      //memberfunction
      int get(int ,int );
      void set(int ,int ,int );
      int size(int );
      void push_back(int ,int ); 
      
      }; 

cvector::cvector(int totalnumber) 
{
  int i = 0;
  this->cvector0 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector0[i] = vector<int>(0); 
  i = 0;
  this->cvector1 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector1[i] = vector<int>(0); 
  i = 0;
  this->cvector2 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector2[i] = vector<int>(0); 
  i = 0;
  this->cvector3 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector3[i] = vector<int>(0); 
  i = 0;
  this->cvector4 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector4[i] = vector<int>(0); 
  i = 0;
  this->cvector5 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector5[i] = vector<int>(0); 
  i = 0;
  this->cvector6 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector6[i] = vector<int>(0);
  i = 0;
  this->cvector7 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector7[i] = vector<int>(1);
  i = 0;
  this->cvector8 = vector< vector<int> >(totalnumber);
  for ( i = 0; i < totalnumber; i++)  this->cvector8[i] = vector<int>(1);
  i = 0;
  this->claim = totalnumber; 
                     } 

int cvector::get(int row,int col)
{
    int n1=0,n2=0;
    n1 = row / this->claim;
    n2 = row % this->claim;
     if(n1 == 0) return cvector0[n2][col];
     if(n1 == 1) return cvector1[n2][col];
     if(n1 == 2) return cvector2[n2][col];
     if(n1 == 3) return cvector3[n2][col];
     if(n1 == 4) return cvector4[n2][col];
     if(n1 == 5) return cvector5[n2][col];
     if(n1 == 6) return cvector6[n2][col];
     if(n1 == 7) return cvector7[n2][col];
     if(n1 == 8) return cvector8[n2][col];
     return 0;
}

void cvector::set(int row,int col,int number) 
{
     int n1=0,n2 = 0;    
     n1 = row / this->claim;
     n2 = row % this->claim;
     if(n1 == 0) cvector0[n2][col] = number;
     if(n1 == 1) cvector1[n2][col] = number;
     if(n1 == 2) cvector2[n2][col] = number;
     if(n1 == 3) cvector3[n2][col] = number;  
     if(n1 == 4) cvector4[n2][col] = number;  
     if(n1 == 5) cvector5[n2][col] = number;  
     if(n1 == 6) cvector6[n2][col] = number;  
     if(n1 == 7) cvector7[n2][col] = number;  
     if(n1 == 8) cvector8[n2][col] = number;  
} 

int cvector::size(int row) 
{
    int n1=0,n2=0;
     n1 = row / this->claim;
     n2 = row % this->claim;
     if(n1 == 0) return cvector0[n2].size(); 
     if(n1 == 1) return cvector1[n2].size();
     if(n1 == 2) return cvector2[n2].size(); 
     if(n1 == 3) return cvector3[n2].size(); 
     if(n1 == 4) return cvector4[n2].size();
     if(n1 == 5) return cvector5[n2].size();
     if(n1 == 6) return cvector6[n2].size(); 
     if(n1 == 7) return cvector7[n2].size(); 
     if(n1 == 8) return cvector8[n2].size();
     return 0;
     } 

void cvector::push_back(int row,int push_site) 
{
   int n1=0,n2=0;
   n1 = row / this->claim;
   n2 = row % this->claim;    
     if(n1 == 0) this->cvector0[n2].push_back(push_site);
     if(n1 == 1) this->cvector1[n2].push_back(push_site); 
     if(n1 == 2) this->cvector2[n2].push_back(push_site);
     if(n1 == 3) this->cvector3[n2].push_back(push_site); 
     if(n1 == 4) this->cvector4[n2].push_back(push_site);
     if(n1 == 5) this->cvector5[n2].push_back(push_site);
     if(n1 == 6) this->cvector6[n2].push_back(push_site); 
     if(n1 == 7) this->cvector7[n2].push_back(push_site);
     if(n1 == 8) this->cvector8[n2].push_back(push_site);
     } 

//nt92 add:分割成四個陣列 
class array{
      int* array1;
      int* array2;
      int* array3;
      int* array4;
      int* array5;
      int totall;
      
      public:
      array(){;}
      array(int  );//asign the lattice length
      ~array()
      {
         delete []array1;
         delete []array2;
         delete []array3;
         delete []array4;
         delete []array5;
        this->totall =  0;
          }
      
      int get(int );
      int get(int ,int );
      int set(int ,int );
      int set(int ,int ,int  );
      
      void collapse();
       };
array::array(int total)
{
 this->totall=total;
 this->array1=new int [total];
 this->array2=new int [total]; 
 this->array3=new int [total];
 this->array4=new int [total];
 this->array5=new int [total];
                 }

int array::get(int sum) 
{
  int distin = 0,site = 0;
  distin = sum / this->totall;
  site = (int)fmod((double)sum ,(double)this->totall);
  switch(distin)
  {
    case 0:
         return array1[site];
         break;
    case 1:
         return array2[site];
         break;
    case 2:
         return array3[site];
         break;
    case 3:
         return array4[site];
         break;
    case 4:
         return array5[site];
         break;
                }
  return 0;
    } 
int array::get(int num1,int num2)
      {
        int nt;
        nt=this->get(num1*2+num2);
        return nt;
        }
int array::set(int sum,int setnumber) 
{
  int distin = 0,site = 0;
  distin = sum / this->totall;
  if(distin > 4)//stop the program to check again
  {
    printf("out of memory!!Close the program!!\n");
    system("PAUSE");
  }
  site = (int)fmod((double)sum ,(double)this->totall);
  switch(distin)
  {
    case 0:
         this->array1[site]= setnumber;
        break;
    case 1:
         this->array2[site]= setnumber;
         break;
    case 2:
         this->array3[site]= setnumber;         
         break;
    case 3:
         this->array4[site]= setnumber;
         break;
    case 4:
         this->array5[site]= setnumber;       
         break;
                }
  return 0;
    } 
int array::set(int num1,int num2,int value)
       {
        int ntt;
        ntt=this->set(num1*2+num2,value);
        return ntt;
        }
void array::collapse()
{
     delete []array1;
     delete []array2;
     delete []array3;
     delete []array4;
     delete []array5;
 }
*/
#endif
