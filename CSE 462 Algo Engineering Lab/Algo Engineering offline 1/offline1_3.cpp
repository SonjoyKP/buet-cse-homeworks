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
    vector<points*>childs;
    points* fatherNode;
};

struct mindistancePoints_it
{
    set<points*>::iterator allpoints_it;
    set<points*>::iterator mstpoints_it;
};




vector<points*>FinalTSPpath;

set<points*>::iterator it;


mindistancePoints_it* findNearestPoint(set<points*> *allPoints,set<points*> *mstPoints)
{
    set<points*>::iterator minofallpoint_it;
    set<points*>::iterator minfrommstpoint_it;

    double mindistance=INF;

    for(set<points*>::iterator i=mstPoints->begin(); i!=mstPoints->end(); i++)
    {
        for(set<points*>::iterator j=allPoints->begin(); j!=allPoints->end(); j++)
        {
            //printf("%.2lf %.2lf %.2lf %.2lf\n",(*i)->x,(*i)->y,(*j)->x,(*j)->y);
            double dist=sqrt(((*i)->x-(*j)->x)*((*i)->x-(*j)->x)+((*i)->y-(*j)->y)*((*i)->y-(*j)->y));
            //printf("dist=%.2lf\n",dist);
            if(dist<mindistance)
            {
                mindistance=dist;
                minofallpoint_it=j;
                minfrommstpoint_it=i;
            }
        }
    }
    mindistancePoints_it* testmindistance_it=new mindistancePoints_it();
    testmindistance_it->allpoints_it=minofallpoint_it;
    testmindistance_it->mstpoints_it=minfrommstpoint_it;
    return testmindistance_it;
}

set<points*>* primsAlgo(set<points*> *allPoints)
{

    set<points*> *mstPoints;
    mstPoints=new set<points*>();

    it=allPoints->begin();

    points* testPoint=new points();
    testPoint=*it;

    mstPoints->insert(testPoint);

    allPoints->erase(it);

    //printf("%.2lf %.2lf\n",testPoint->x,testPoint->y);

    //printf("printing ans\n%.2lf %.2lf\n",(*result_it)->x,(*result_it)->y);
    while(!allPoints->empty())
    {
        mindistancePoints_it* nearPoints=new mindistancePoints_it();
        nearPoints=findNearestPoint(allPoints,mstPoints);

        points* frompoint=new points();
        points* topoint=new points();

        frompoint=*(nearPoints->mstpoints_it);
        topoint=*(nearPoints->allpoints_it);

        mstPoints->insert(topoint);

        frompoint->childs.push_back(topoint);
        topoint->fatherNode=frompoint;

        allPoints->erase(nearPoints->allpoints_it);

    }
    return mstPoints;


}


void display(points* printPoint)
{
    printf("%.0lf %.0lf\n",printPoint->x,printPoint->y);
    FinalTSPpath.push_back(printPoint);
    if(printPoint->childs.size()==0)return;
    //printf("Down all was the child of =%.0lf %.0lf\n",printPoint->x,printPoint->y);
    for(int i=0; i<printPoint->childs.size(); i++)
    {
        display(printPoint->childs[i]);
    }
}

int main()
{
    //freopen("output.txt", "w", stdout);
    freopen("output.txt", "r", stdin);
    set<points*>*setOfpoints,*returnedMST;

    setOfpoints=new set<points*>();
    returnedMST=new set<points*>();

    srand (time(NULL));
    int n;
    cin>>n;

    for(int i=0; i<n; i++)
    {
        double xx,yy;
        // xx=rand()%100-50;
        // yy=rand()%100-50;

        cin>>xx>>yy;

        points *testpoint=new points();
        testpoint->x=xx;
        testpoint->y=yy;
        testpoint->fatherNode=NULL;

        setOfpoints->insert(testpoint);

    }
    for(it=setOfpoints->begin(); it!=setOfpoints->end(); it++)
    {
        printf("%.0lf %.0lf\n",(*it)->x,(*it)->y);
    }
    printf("\n");
    returnedMST=primsAlgo(setOfpoints);
    printf("--printing MST--\n");

    points* rootpoint=new points();

    for(it=returnedMST->begin(); it!=returnedMST->end(); it++)
    {
        if((*it)->fatherNode==NULL)
        {
            rootpoint=(*it);
            break;
        }

    }
    //printpoint=(*it);
    display(rootpoint);
    FinalTSPpath.push_back(rootpoint);
    printf("%.0lf %.0lf\n",rootpoint->x,rootpoint->y);

    double TSPpathDistance=0;
    for(int i=0; i<FinalTSPpath.size()-1; i++)
    {
        TSPpathDistance=TSPpathDistance+sqrt((FinalTSPpath[i+1]->x-FinalTSPpath[i]->x)*(FinalTSPpath[i+1]->x-FinalTSPpath[i]->x)+(FinalTSPpath[i+1]->y-FinalTSPpath[i]->y)*(FinalTSPpath[i+1]->y-FinalTSPpath[i]->y));
    }
    printf("Total path distance=%.2lf\n",TSPpathDistance);

    return 0;


}

