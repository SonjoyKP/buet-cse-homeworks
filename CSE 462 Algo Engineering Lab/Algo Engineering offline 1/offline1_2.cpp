#include<bits/stdc++.h>


#define INF (1<<28)

//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);

typedef long long ll;
using namespace std;

int n;

double bestSOfar=INF;

double newBound;
struct point
{
    double x,y;
};
vector<point> allPoints;

point bestsoFarPoint;

struct retunToFindNearPoint
{
    int mstPos,AllPos;
    double minimumDistance;
};

double dista(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

retunToFindNearPoint findNearestPoints(vector<point>all,vector<point> mst)
{
    double minDistance=INF;
    retunToFindNearPoint testReturn;
    for(int i=0;i<mst.size();i++)
    {
        for(int j=0;j<all.size();j++)
        {
            double dist=dista(mst[i],all[j]);
            if(dist<minDistance)
            {
                minDistance=dist;
                testReturn.AllPos=j;
                testReturn.mstPos=i;
                testReturn.minimumDistance=minDistance;
            }
        }
    }
    return testReturn;
}


double mst(vector<point> all)
{
    double mstcost=0;
    vector<point>mst;

    point firstpoint=all[0];
    mst.push_back(firstpoint);
    all.erase(all.begin());



    while(!all.empty())
    {
        retunToFindNearPoint retunedNearest;

        retunedNearest=findNearestPoints(all,mst);
        mst.push_back(all[retunedNearest.AllPos]);
        all.erase(all.begin()+retunedNearest.AllPos);
        mstcost=mstcost+retunedNearest.minimumDistance;

    }
    return mstcost;
}

double Findcost(vector<point>S)
{
    double cost=0;
    for(int i=0;i<S.size()-1;i++)
    {
        cost=cost+dista(S[i],S[i+1]);
    }
    return cost;
}

double findRootConnectingCost(vector<point>S,vector<point>V_S)
{
    point x=S[0];
    double mindist=INF;
    for(int i=0;i<V_S.size();i++)
    {
        double dis=dista(x,V_S[i]);
        if(dis<mindist)mindist=dis;
    }
    return mindist;
}

double findleefConnetingCost(vector<point>S,vector<point>V_S)
{
    point x=S[S.size()-1];
    double mindist=INF;
    for(int i=0;i<V_S.size();i++)
    {
        double dis=dista(x,V_S[i]);
        if(dis<mindist)mindist=dis;
    }
    return mindist;
}

void travarse(vector<point>S,vector<point>V_S,double bound)
{
    /*
    printf("printing S\n");
    for(int i=0;i<S.size();i++)
    {
        printf("(%.2lf %.2lf) ",S[i].x,S[i].y);
    }
    printf("\n");

    printf("printing V_S\n");
    for(int i=0;i<V_S.size();i++)
    {
        printf("(%.2lf %.2lf) ",V_S[i].x,V_S[i].y);
    }
    printf("\n");

    */

    if(V_S.empty())
    {
        if(bestSOfar>newBound)
        {
            bestSOfar=newBound;
            bestsoFarPoint.x=S[S.size()-1].x;
            bestsoFarPoint.y=S[S.size()-1].y;
        }
        //printf("returning beause we are in leef--------------------------------\n");
        return;
    }


    newBound=mst(V_S)+Findcost(S)+findRootConnectingCost(S,V_S)+findleefConnetingCost(S,V_S);
    //printf("mst=%lf findCostof S=%lf find Root=%lf find leff =%lf\n",mst(V_S),Findcost(S),findRootConnectingCost(S,V_S),findleefConnetingCost(S,V_S));

    //printf("bestsoFar=%.2lf new bound=%.2lf\n",bestSOfar,newBound);

    if(newBound<bestSOfar)
    {
        for(int i=0;i<V_S.size();i++)
        {
            point x=V_S[i];
            S.push_back(x);
            V_S.erase(V_S.begin()+i);
            travarse(S,V_S,newBound);
            point y=S[S.size()-1];
            V_S.push_back(y);
            S.erase(S.begin()+(S.size()-1));
        }
    }
    else return;//printf("-----------------Returning beacuse bound exited\n");
}


int main()
{
    freopen("output.txt", "w", stdout);
    srand (time(NULL));

    cin>>n;

    for(int i=1; i<=n; i++)
    {
        int xx=rand()%100-50;
        int yy=rand()%100-50;

        point testpoint;
        testpoint.x=xx;
        testpoint.y=yy;

        //printf("%d %d\n",xx,yy);

        allPoints.push_back(testpoint);

    }
    printf("%d\n",n);
    for(int i=0;i<allPoints.size();i++)
    {
        printf("%.2lf %.2lf\n",allPoints[i].x,allPoints[i].y);
    }

    vector<point>s;

    point x=allPoints[0];
    s.push_back(x);
    allPoints.erase(allPoints.begin());

    travarse(s,allPoints,INF);

    printf("Best so far=%.2lf\n",bestSOfar);



    return 0;
}
