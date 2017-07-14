

#include<bits/stdc++.h>

#define forl(i,n) for(int i=0;i<(int)n;i++)
#define pb(x) push_back(x)
#define mem(x,y) memset(x,y,sizeof(x))
#define mp make_pair
#define pii pair<int,int>
#define uu first
#define vv second
#define sdi(x) scanf("%d",&x)
#define sdii(x,y) scanf("%d%d",&x,&y)

using namespace std;

#define MAX 107
#define INF 1000000007
#define EPS (1e-12)


double weight[1000];
int freq[1000];
vector <int>solutionSetCover;
double totalCost=0;

void Pivot( long m,long n,double A[MAX+7][MAX+7],long *B,long *N,long r,long c )
{
    long i,j;
    swap( N[c],B[r] );
    A[r][c] = 1/A[r][c];
    for( j=0; j<=n; j++ ) if( j!=c ) A[r][j] *= A[r][c];
    for( i=0; i<=m; i++ )
    {
        if( i!=r )
        {
            for( j=0; j<=n; j++ ) if( j!=c ) A[i][j] -= A[i][c]*A[r][j];
            A[i][c] = -A[i][c]*A[r][c];
        }
    }
}

long Feasible( long m,long n,double A[MAX+7][MAX+7],long *B,long *N )
{
    long r,c,i;
    double p,v;
    while( 1 )
    {
        for( p=INF,i=0; i<m; i++ ) if( A[i][n]<p ) p = A[r=i][n];
        if( p > -EPS ) return 1;
        for( p=0,i=0; i<n; i++ ) if( A[r][i]<p ) p = A[r][c=i];
        if( p > -EPS ) return 0;
        p = A[r][n]/A[r][c];
        for( i=r+1; i<m; i++ )
        {
            if( A[i][c] > EPS )
            {
                v = A[i][n]/A[i][c];
                if( v<p ) r=i,p=v;
            }
        }
        Pivot( m,n,A,B,N,r,c );
    }
}

long Simplex( long m,long n,double A[MAX+7][MAX+7],double *b,double &Ret )
{
    long B[MAX+7],N[MAX+7],r,c,i;
    double p,v;
    for( i=0; i<n; i++ ) N[i] = i;
    for( i=0; i<m; i++ ) B[i] = n+i;
    if( !Feasible( m,n,A,B,N ) ) return 0;
    while( 1 )
    {
        for( p=0,i=0; i<n; i++ ) if( A[m][i] > p ) p = A[m][c=i];
        if( p<EPS )
        {
            for( i=0; i<n; i++ ) if( N[i]<n ) b[N[i]] = 0;
            for( i=0; i<m; i++ ) if( B[i]<n ) b[B[i]] = A[i][n];
            Ret = -A[m][n];
            return 1;
        }
        for( p=INF,i=0; i<m; i++ )
        {
            if( A[i][c] > EPS )
            {
                v = A[i][n]/A[i][c];
                if( v<p ) p = v,r = i;
            }
        }
        if( p==INF ) return -1;
        Pivot( m,n,A,B,N,r,c );
    }
}



double A[MAX+7][MAX+7];

int main()
{
    freopen("testCase.txt", "r", stdin);

    int t;
    cin>>t;
    while(t--)
    {
        solutionSetCover.clear();
        totalCost=0;
        mem(A,0);
        mem(freq,0);
        int N,M;
        cin>>N>>M;
        int maxFreq=0;
        for(int i=0; i<M; i++)
        {
            double w;
            int k;
            cin>>w;
            weight[i]=w;
            cin>>k;
            int maskVal=0;
            for(int j=0; j<k; j++)
            {
                int e;
                cin>>e;
                freq[e]++;
                if(freq[e]>maxFreq)maxFreq=freq[e];
                A[e][i]=-1;
                A[e][M]=-1;


            }
            A[N][i]=-w;



        }
        A[N][M]=0;




        double* b=new double[MAX+7];
        double ans=0;


        long long check=Simplex(N,M,A,b,ans);
        printf("test case:\n");
        if(check!=1)printf("NOT solve able\n");
        else
        {


            ans=ans*-1;
            printf("LP cost=%.2lf\n",ans);
            printf("maxFreq=%d\n",maxFreq);
            printf("set covered = ");

            for(int i=0; i<M; i++)
            {
                int taken;
                if(b[i]>=(1.0/(double)maxFreq))
                {
                    taken=1;
                    //printf("(%.2lf %d %d) ",b[i],taken,i);
                    printf("%d ",i);
                    solutionSetCover.push_back(i);
                }


            }
            printf("\n");

            for(int i=0; i<solutionSetCover.size(); i++)
            {
                totalCost=totalCost+weight[solutionSetCover[i]];
            }
            printf("Total Cost=%.2lf\n\n",totalCost);
        }
    }







    return 0;

}
