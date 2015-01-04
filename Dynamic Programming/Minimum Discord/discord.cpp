#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int N;
int K;
const int INFIN=32768;

char *U;
int *A;
int *val;
int **kval;
int **Discord;
double MIN;
double MAX;

int discrepancy(int i,int j)
{
    int m,diff=0;
    int cnt=j-i+1;
    if(cnt<MIN || cnt>MAX)
        return INFIN;
    if(i>j)
        return INFIN;
    else
    {
        for(m=i;m<=j;m++)
        {
                diff+=A[m];
        }
        diff=(abs)(diff);
        if(j!=1&&i==j)
        {
            if(diff<MIN || diff>MAX)
            return INFIN;
        else
            return diff;
        }
        else
         return diff;
    }
}

void init(int N,int K)
{
    int i,j;
    double DN=N;
    double DK=K;
    A[0]=0;
    for(i=1;i<=N;i++)
    {
        Discord[i][0]=INFIN;
        kval[i][0]=0;
        if(U[i-1]=='R')
            A[i]=1;
        else
            A[i]=-1;
    }

    for(j=0;j<=K;j++)
    {
        Discord[0][j]=0;
        kval[0][j]=0;
    }
    MIN=ceil(((2*DN)/(3*DK)));
    MAX=floor(((4*DN)/(3*DK)));


}

void Deallocate()
{
    int i;
    delete []A;
    delete []U;
    delete []val;
    for(i=0;i<=N;i++)
    {
        delete[] Discord[i];
        delete[] kval[i];
    }
    delete[] Discord;
    delete[] kval;


}
void calculate_discord(int n,int r)
{
    int d,q,p,k,v=0, v1,v2,kvalue;
    for(d=1;d<=n;d++)
    {
        if(r==1)
        {
            Discord[d][r]=discrepancy(1,d)*discrepancy(1,d);
            kval[d][1]=0;
        }

        else
        {
            for(p=1;p<=r;p++)
            {

              q=INFIN;
              int ctr=0;
             if(p==1 && p!=r && d>=MIN && d<=MAX)
              {
                  int c=discrepancy(1,d);
                  Discord[d][p]=c*c;
                  kval[d][p]=0;
              }
              else
              {
               for(k=1;k<=d;k++)
               {
                  ctr++;
                  v1=Discord[k][p-1];
                  v2=discrepancy(k+1,d);
                  if(v1!=INFIN && v2!=INFIN)
                  {
                       v=v1+(v2*v2);

                  }
                   else
                  v=v1+v2;


               if(v<q)
                {
                    q=v;
                    kvalue=k;
                }
               }
               Discord[d][p]=q;
               kval[d][p]=kvalue;
              }
            }

        }
    }
}

void Print()
{
    int i,j;
    for(i=0;i<=N;i++)
    {
        cout<<"\n";
        for(j=0;j<=K;j++)
        {
            cout<<"\t"<<Discord[i][j];
        }
    }
}

void Print_Output()
{
    int g=0;
    val[0]=0;
    val[1]=0;
    val[K]=kval[N][K];
    for(g=K-1;g>1;g--)
    {
       val[g] =kval[val[g+1]][g];
    }
    cout<<"\n"<<Discord[N][K];
    for(g=2;g<=K;g++)
    {
       cout<<"\t"<<val[g]-val[g-1];
    }
}

int main()
{
     int o;
    cout<<"\n Minimizing Discord Problem\n";
    cout<<"\n Enter the input:\n";
    do
    {
        cout<<"\n";
        cin>>N>>K;
        if(N==0)
        {
            exit(0);
        }
        U=new char[N+1];
        A=new int[N+1];
        val=new int[K+1];
        kval=new int*[N+1];
        Discord=new int*[N+1];
        for(o=0;o<=N;o++)
        {
            kval[o]=new int[K+1];
            Discord[o]=new int[K+1];
        }
      //  cout<<"\n\n Enter the sequence:\n";
        cin>>U;
        U[N]='\0';
        init(N,K);
   // cout<<"\n Min is "<<MIN;
   // cout<<"\n Max is "<<MAX;
        calculate_discord(N,K);
  // Print();
        Print_Output();
        cout<<"\n";
    }while(N!=0);
    return 0;
}
