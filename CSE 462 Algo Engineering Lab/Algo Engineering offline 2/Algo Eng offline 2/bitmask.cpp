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
#define INF (1<<28)

//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);

typedef long long ll;
using namespace std;
int N,M;
int si=(1<<20);
double dp[(1<<20)+2];

double weight[1000];


int Set(int N,int pos){return N=N | (1<<pos);}


int mask[100000];

void printSolution(vector<int> sol)
{
    double cost=0;
    printf("\n------printing solution----------------");
    for(int i=0;i<sol.size();i++)
    {
        printf("%d ",sol[i]);
        cost=cost+weight[sol[i]];
    }
    printf("cost=%.2lf",cost);
    printf("\n");
}


double func(int coveredMask, int nowConsiderIndex,vector<int> solution)
{
    printf("Calling for %d %d\n",coveredMask,nowConsiderIndex);
    if(dp[coveredMask]!=0)
    {
        printf("found in dp table %.2lf\n",dp[coveredMask]);
        return dp[coveredMask];
    }
    if(nowConsiderIndex == M & coveredMask!=(1<<N)-1)
    {
        printf("retuning inf\n");
        dp[coveredMask]=INF;
        return INF;
    }
    else if(nowConsiderIndex == M & coveredMask==(1<<N) - 1)
    {
        printf("--------------returning zero thats mean solution found\n");
        printSolution(solution);
        dp[coveredMask]=0;
        return 0;
    }
    else
    {
        double valNotChoose=func(coveredMask,nowConsiderIndex+1,solution);
        cout<<"not choos="<<valNotChoose<<"\n";

        solution.push_back(nowConsiderIndex);
        double valChoose= func(coveredMask|mask[nowConsiderIndex],nowConsiderIndex+1,solution)+weight[nowConsiderIndex];
        cout<<"choose="<<valChoose<<"\n";


        dp[coveredMask]=min( valChoose, valNotChoose );
        return min( valChoose, valNotChoose );

    }


}


int main()
{

    mem(mask,0);
    int t;
    //cin>>t;


        cin>>N>>M;
        for(int i=0;i<M;i++)
        {
            double w;
            int k;
            cin>>w;
            weight[i]=w;
            cin>>k;
            printf("k=%d\n",k);
            int maskVal=0;
            for(int j=0;j<k;j++)
            {
                int e;
                cin>>e;
                printf("1<<e=%d\n",1<<e);
                maskVal=maskVal|(1<<(e));

            }
            printf("mask value=%d\n",maskVal);
            mask[i]=maskVal;
        }
    vector <int>solution;
    printf("ans= %d %lf\n",(1<<N)-1,dp[(1<<N)-1]);
    func(0,0,solution);

    printf("ans= %d %lf\n",(1<<N)-1,dp[(1<<N)-1]);

    return 0;

}

