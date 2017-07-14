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



struct points
{
    double x,y;
};
vector <points*>setOfpoints,outputSetOfPoint;




int main()
{
    freopen("output.txt", "r", stdin);
    srand (time(NULL));
    int n;
    cin>>n;


    for(int i=0; i<n; i++)
    {
        double xx,yy;
        // xx=rand()%100-50;
         //yy=rand()%100-50;
        cin>>xx>>yy;

        points *testpoint=new points();
        testpoint->x=xx;
        testpoint->y=yy;

        setOfpoints.push_back(testpoint);

    }

    long long c=0;
    double mindistance=INF;
    int sze=setOfpoints.size();
    do
    {
        c++;

        for(int i=0; i<=sze; i++)
        {
            //printf("(%.0lf %.0lf) - ",setOfpoints[i%sze]->x,setOfpoints[i%sze]->y);
        }

        double distance=0;

        for(int i=0; i<sze; i++)
        {
            //printf(" %.2lf %.2lf -",setOfpoints[i]->x,setOfpoints[i]->y);
            distance=distance+sqrt((setOfpoints[(i+1)%sze]->x-setOfpoints[i%sze]->x)*(setOfpoints[(i+1)%sze]->x-setOfpoints[i%sze]->x)+(setOfpoints[(i+1)%sze]->y-setOfpoints[i%sze]->y)*(setOfpoints[(i+1)%sze]->y-setOfpoints[i%sze]->y));

        }
        //printf(" Distance =%.2lf\n",distance);

        if(distance<mindistance)
        {
            mindistance=distance;

            outputSetOfPoint.clear();
            for(int i=0; i<=sze; i++)
            {
                points *test=new points();
                test->x=setOfpoints[i%sze]->x;
                test->y=setOfpoints[i%sze]->y;

                outputSetOfPoint.push_back(test);


            }

        }



    }
    while(next_permutation(setOfpoints.begin(),setOfpoints.end()));



    printf("c=%d\n",c);
    for(int i=0; i<=sze; i++)
    {
        printf("(%.0lf %.0lf) - ",outputSetOfPoint[i%sze]->x,outputSetOfPoint[i%sze]->y);
    }
    printf(" Min distance=%.2lf\n",mindistance);
    printf("\n");


}
