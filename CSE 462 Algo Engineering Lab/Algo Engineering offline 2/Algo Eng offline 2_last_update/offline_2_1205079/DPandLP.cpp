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

int N,M;

double weight[100]; //for LP
int freq[100];
vector <int>LPsolutionSetCover;
double totalRoundedLPCost=0;


double dp[(1<<16)+2][22];
int mask[100];     //for dp
double DPminCost=INF;
vector<int>DPminCostSetcover;



void printSolution(vector<int> sol) //for dp
{
    double cost=0;

    //printf("------printing solution------");
    for(int i=0; i<sol.size(); i++)
    {
        //printf("%d ",sol[i]);
        cost=cost+weight[sol[i]];
    }
    //printf("  cost=%.2lf",cost);
    //printf("\n");
    if(cost<DPminCost)
    {
        DPminCostSetcover.clear();
        DPminCost=cost;
        DPminCostSetcover=sol;
    }
}


double func(int coveredMask, int nowConsiderIndex,vector<int> solution)
{

    if(dp[coveredMask][nowConsiderIndex]!=0)
    {
        return dp[coveredMask][nowConsiderIndex];
    }
    if(nowConsiderIndex == M & coveredMask!=(1<<N)-1)
    {

        dp[coveredMask][nowConsiderIndex]=INF;
        return INF;
    }
    else if(nowConsiderIndex == M & coveredMask==(1<<N) - 1)
    {
        //printf("--------------returning zero thats mean solution found\n");
        printSolution(solution);
        dp[coveredMask][nowConsiderIndex]=0;
        return 0;
    }
    else
    {
        double valNotChoose=func(coveredMask,nowConsiderIndex+1,solution);

        solution.push_back(nowConsiderIndex);
        double valChoose= func(coveredMask|mask[nowConsiderIndex],nowConsiderIndex+1,solution)+weight[nowConsiderIndex];


        dp[coveredMask][nowConsiderIndex]=min( valChoose, valNotChoose );
        return min( valChoose, valNotChoose );

    }


}






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

        LPsolutionSetCover.clear();
        totalRoundedLPCost=0;
        mem(A,0);
        mem(freq,0);
        mem(mask,0);
        DPminCost=INF;
        mem(dp,0);

        cin>>N>>M;
        int maxFreq=0;

        int maskVal=0;
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

                maskVal=maskVal|(1<<(e));

                freq[e]++;
                if(freq[e]>maxFreq)maxFreq=freq[e];
                A[e][i]=-1;
                A[e][M]=-1;


            }
            mask[i]=maskVal;

            A[N][i]=-w;



        }

        vector <int>DPsolution;
        //printf("\ntest case:\n");
        func(0,0,DPsolution);
        printf("\nSet cover DP=");
        for(int i=0;i<DPminCostSetcover.size();i++)
        {
            printf("%d ",DPminCostSetcover[i]);
        }
        printf("\nMin Cost for DP=%.2lf\n",DPminCost);




        A[N][M]=0; // for LP

        double* b=new double[MAX+7];
        double ans=0;


        long long check=Simplex(N,M,A,b,ans);
        //printf("test case:\n");
        if(check!=1)printf("NOT solve able for LP\n");
        else
        {


            ans=ans*-1;
            //printf("LP cost=%.2lf\n",ans);
            printf("maxFreq=%d\n",maxFreq);
            printf("set covered for Rounded LP = ");

            for(int i=0; i<M; i++)
            {
                int taken;
                if(b[i]>=(1.0/(double)maxFreq))
                {
                    taken=1;
                    //printf("(%.2lf %d %d) ",b[i],taken,i);
                    printf("%d ",i);
                    LPsolutionSetCover.push_back(i);
                }


            }
            printf("\n");

            for(int i=0; i<LPsolutionSetCover.size(); i++)
            {
                totalRoundedLPCost=totalRoundedLPCost+weight[LPsolutionSetCover[i]];
            }
            printf("Cost for LP rounded=%.2lf\n",totalRoundedLPCost);

            printf("Approx Ratio=%.2lf\n\n",totalRoundedLPCost/DPminCost);
        }
    }







    return 0;

}

