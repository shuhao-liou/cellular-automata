//時間永遠是陣列加一! 
//用來完整檢測每個規則的週期 
#include <iomanip>
#include <cstdlib>
#include <vector> 
#include <iostream>
#include <cmath> 
#include <time.h>
//#include <conio.h>
#include <stdio.h>
using namespace std;

class discrete
{        
    int asign[32] ; //運算規則陣列 
    int cellnumber ;// number of cells(L) 
    int rulenumber ;// 這裡指定是用那種rule 
    int timestep ;//number of time steps
    int *s;//以一維儲存所有資料 
    int *state2; 
 
  
    public: 
    //constructors:
    discrete (){;}; 
    discrete (int ,int ,int ,int ) ;//主動給予ini 
    ~discrete() { delete [] this->s;    // destructor
                delete [] this->state2; 
                this->cellnumber = this->timestep = this->rulenumber = 0;
                    }
    
    //member function 
    inline int CV(const int i,const int j) const {return(cellnumber*i + j);}
    inline void rule(int rulee) { this->rulenumber = rulee;} 
    inline void nstep(int cell) { this->cellnumber = cell;}
           void sites(int ) ;  //3008.3.27 adding in!!
    inline void times(int timenumber) { this->timestep = timenumber;} 
    void ruletransf() ; //轉換至二進位 
    inline int get(const int i, const int j) const  //得到某個時間的陣列值 
                        { return this->s[CV(i,j)]; }                   
    inline int get2(const int timee ) const
                        { return this->state2[timee] ;} 
    inline void set(const int i, const int j, int xx) // 輸入某個時間的陣列值 
                     { this->s[CV(i,j)] = xx; }
    //void caevaluate(); //計算狀態隨時間的演進 
    //void cadiscrete2(); //使用另外一種方法 
    
      } ;
discrete::discrete(int rule,int time,int cell,int state) 
{
  this->rulenumber = rule;
  this->timestep   = time;
  this->cellnumber = cell;
  
  ruletransf();
  this->s = new int [time*cell+cell] ;
  this-> state2 = new int  [this->timestep+2] ;
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
delete  a;
delete  b; 
} 

void discrete::sites(int state) 
{
  int* a = NULL; a = new int [cellnumber+3];
  int* b = NULL; b = new int [cellnumber+3];
  a[0]=0; b[0]=state;
  int i = 0, m = 0 ;
   
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
  int t = 0, j = 0;
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
delete  a;
delete  b;  
 int k=0 ,cell =0;
 int total = 0; 
 for(k = 0;k < this->timestep ;k++) 
 {
    for(cell = 0;cell < this -> cellnumber; cell++)
    {
           total =  total +  (int) pow(2.0,(double) cellnumber-cell-1) * get(k,cell);
       } 
     this->state2[k]= total; 
     total = 0; 
 }        
} 

void discrete::ruletransf() //rulenumber轉換成二進位，已修改^^ 
{ 
    int k =0;
   for(k=0; k < 13;k++)this-> asign[k] =0;
   asign[7] =1; asign[11] = 1;
   k = 0;
   for(k = 13; k < 32;k++) asign[k] =1; 
   asign[24] = 0; asign[20] =0; asign[18] =0; asign[17] =0;asign[16] =0; 
} 
int GG(int num1,int num2) 
{
  return (num1*2 + num2 ) ; 
    }
main()
{ 
  
  int time = 6;
  int cell = 7;
  
  int node = (int) pow(2.0,cell) ; 
  int rule = 41;
  int nstate = (int) pow(2.0,(double)cell);
  discrete ca(rule,time,cell,0) ;
  
  FILE *fp;//寫在某個記事本裡面的前置指令 
  fp = fopen("majoruty_cell7.net" ,"w");
  fprintf(fp,"*Vertices %d \n",nstate);
  int g=0;
  double coor = 0.0;
  
  for(g = 1;g < (nstate+1); g++)
  {
   fprintf(fp,"%d  *m0%d*    %e    %e    0.5000 \n",g,g,coor,coor);
  // coor = coor + 0.035714285* g;
  }
  fprintf(fp,"*Arcs \n");
       
  int* statee = NULL; statee = new int [time];
  int* w = NULL; w = new int [cell];
  int in= 0;
  int out=0;
  
  int i=0,t = 0,h = 0,q = 0,m = 0;
  int sum =0, summ =0;//summ是進去 ，sum是出來 (後來達到的狀態) 
 do
   {         
     ca.sites(i);
     for(q=0 ; q<time ;q++)
     { 
       sum = ca.get2(q)+1 ;       	   
       if(q>0)
        {
           if(sum == out && summ == in)
           { 
              goto next;
                  }           
          fprintf(fp,"   %d",summ );
          fprintf(fp,"   %d",sum );
          fprintf(fp,"   1\n");
        } 
       in = summ;
       out = sum;
       summ = sum;
       sum = 0;
     }
     
     next: 
	 sum = 0;    
     //cout << "situation = " << i  <<" " <<endl; // use to check the process    
     i++;      
  }  while(i<node);
  fclose(fp);

  delete [] w;
  delete [] statee;
  system("PAUSE");
  return 0; 
} 
 
