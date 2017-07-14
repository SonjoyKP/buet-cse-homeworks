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

double dp[(1<<20)+2];

double weight[1000];
int mask[1000];
double minCost=INF;
vector<int>minCostSetcover;
void printSolution(vector<int> sol)
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
    if(cost<minCost)
    {
        minCostSetcover.clear();
        minCost=cost;
        minCostSetcover=sol;
    }
}


double func(int coveredMask, int nowConsiderIndex,vector<int> solution)
{

    if(dp[coveredMask]!=0)
    {
        return dp[coveredMask];
    }
    if(nowConsiderIndex == M & coveredMask!=(1<<N)-1)
    {

        dp[coveredMask]=INF;
        return INF;
    }
    else if(nowConsiderIndex == M & coveredMask==(1<<N) - 1)
    {
        //printf("--------------returning zero thats mean solution found\n");
        printSolution(solution);
        dp[coveredMask]=0;
        return 0;
    }
    else
    {
        double valNotChoose=func(coveredMask,nowConsiderIndex+1,solution);

        solution.push_back(nowConsiderIndex);
        double valChoose= func(coveredMask|mask[nowConsiderIndex],nowConsiderIndex+1,solution)+weight[nowConsiderIndex];


        dp[coveredMask]=min( valChoose, valNotChoose );
        return min( valChoose, valNotChoose );

    }


}


int main()
{
    freopen("input.txt", "r", stdin);
    mem(mask,0);
    int t;
    cin>>t;
    while(t--)
    {
        minCost=INF;
        mem(dp,0);
        cin>>N>>M;
        for(int i=0; i<M; i++)
        {
            double w;
            int k;
            cin>>w;
            weight[i]=w;
            cin>>k;
            //printf("k=%d\n",k);
            int maskVal=0;
            for(int j=0; j<k; j++)
            {
                int e;
                cin>>e;
                maskVal=maskVal|(1<<(e));

            }
            mask[i]=maskVal;
        }
        vector <int>solution;
        printf("\nfor test case:\n");
        func(0,0,solution);
        printf("\nset cover problem min cost solution\n");
        for(int i=0;i<minCostSetcover.size();i++)
        {
            printf("%d ",minCostSetcover[i]);
        }
        printf("Min Cost=%.2lf\n",minCost);

    }



    return 0;

}

