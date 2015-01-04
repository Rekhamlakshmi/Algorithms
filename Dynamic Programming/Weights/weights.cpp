#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int *A;
int **S;
int *B;
int N;
const int mul=50;
int max_weight=0;

void MaxWeight(int *A,int N)
{
    int i;
    for(i=0;i<N;i++)
    {
        max_weight+=A[i];
    }
}
void Print()
{
    int i,j;
    for(i=0;i<=N;i++)
    {
        cout<<"\n";
        for(j=50;j<=max_weight;j=j+50)
        {
            cout<<" "<<S[i][(j/50)-1];
        }
    }
}
void init(int N,int *A,int no)
{

    int i,j;
    S=new int*[N+1];
    for(i=0;i<=N;i++)
    {
        S[i]=new int[no];
    }

    for(i=1;i<=N;i++)
   {
    for(j=0;j<no;j=j+1)
    {
        S[0][j]=0;
        S[i][j]=0;
    }
   }
   B=new int[no];
    B[0]=mul;
    for(int p=1;p<no;p++)
        B[p]=B[p-1]+mul;

   for(i=1;i<=N;i++)
   {
       for(j=0;j<no;j++)
       {
           if(A[i-1]==B[j])
           {
                S[i][j]=1;
           }
   }
   }
}


void Weight(int no)
{
    int i,j,b,c,a;
    for(i=1;i<=N;i++)
    {
        for(j=0;j<no;j=j+1)
        {
            a=S[i-1][j];
            int m=((B[j]+A[i-1])/mul)-1;
            if(m<no)
            {
                b=S[i-1][m];
            }
            else
                b=0;

            int n=((abs(B[j]-A[i-1]))/mul)-1;

            if(n<no)
            {
                c=S[i-1][n];
            }
            else
                c=0;

            if(S[i][j]!=1)
            {
                if(a==1 || b==1 || c==1 )
                {
                    S[i][j]=1;
                }
                else
                {
                    S[i][j]=0;
                }
            }
        }
    }
}

void Deallocate()
{
    int i;
    for(i=0;i<=N;i++)
    {
        delete[] S[i];
    }
    delete[] S;
    delete[] A;
    delete[] B;

}
int main()
{

    int i,j;
    cout<<"\nWeights Problem: \n";
    cout<<"\nEnter the input sequence\n";
   do
   {
    cout<<"\n";
    cin>>N;
    int count=0;
    if(N==0)
        exit(0);
    A=new int[N];
    for(i=0;i<N;i++)
        cin>>A[i];
    MaxWeight(A,N);
    int no=(max_weight/mul);
    init(N,A,no);
    Weight(no);
    for(j=0;j<no;j=j+1)
   {
       count+=S[N][j];
   }
   cout<<"\n Output: "<<count<<"\n";
   Deallocate();
   }while(N!=0);
    return 0;
}

