#include<bits/stdc++.h>

#define INF (1<<28)
#define startV 1
#define endV 2
#define splitV 3
#define mergeV 4
#define regularV 5

using namespace std;


struct point
{
    int point_id;
    double x,y;
    int PointType;
};

bool operator <(const point& a, const point& b) {
    return  a.y>b.y;
}

struct vec
{
    double vx,vy;

};

struct edge
{
    point pa,pb;
    int edge_id;
};

vector<point>allPoints;
int number_of_points;

int checkTurn(point prev,point now,point next)
{
    point vector_prev_now;
    vector_prev_now.x=now.x-prev.x;
    vector_prev_now.y=now.y-prev.y;

    point vector_now_next;
    vector_now_next.x=next.x-now.x;
    vector_now_next.y=next.y-now.y;


    double turn=vector_prev_now.x*vector_now_next.y-vector_now_next.x*vector_prev_now.y;
    if(turn>0)return 1;
    if(turn<0)return -1;
    if(turn==0)return 0;
}

void pointsTypeFinding()
{
    for(int i=0;i<number_of_points;i++)
    {
        int prevPos=(i-1+number_of_points)%number_of_points;
        int nextPos=(i+1)%number_of_points;
        double y_cordi_i=allPoints[i].y;
        double y_cordi_prev=allPoints[prevPos].y;
        double y_cordi_next=allPoints[nextPos].y;
        if(y_cordi_prev<=y_cordi_i and y_cordi_next<=y_cordi_i)
        {
            if(checkTurn(allPoints[prevPos],allPoints[i],allPoints[nextPos])==1)
            {
                allPoints[i].PointType=startV;

            }
            else if(checkTurn(allPoints[prevPos],allPoints[i],allPoints[nextPos])==-1)
            {
                allPoints[i].PointType=splitV;
            }
        }
        else if(y_cordi_prev>=y_cordi_i and y_cordi_next>=y_cordi_i)
        {
            if(checkTurn(allPoints[prevPos],allPoints[i],allPoints[nextPos])==1)
            {
                allPoints[i].PointType=endV;

            }
            else if(checkTurn(allPoints[prevPos],allPoints[i],allPoints[nextPos])==-1)
            {
                allPoints[i].PointType=mergeV;
            }

        }
        else if((y_cordi_prev>y_cordi_i and y_cordi_next<y_cordi_i) or (y_cordi_prev<y_cordi_i and y_cordi_next>y_cordi_i))
        {
            allPoints[i].PointType=regularV;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //printf("Enter number of points=");
    scanf("%d",&number_of_points);
    //printf("mod=%d",(-1+number_of_points)%number_of_points);
    for(int i=0;i<number_of_points;i++)
    {
        double x_cordi,y_cordi;
        cin>>x_cordi>>y_cordi;
        point testPoint;
        testPoint.x=x_cordi;
        testPoint.y=y_cordi;
        testPoint.point_id=i;

        allPoints.push_back(testPoint);


    }
    pointsTypeFinding();
    sort(allPoints.begin(),allPoints.begin()+number_of_points);
    for(int i=0;i<number_of_points;i++)
    {
        printf("x=%.2lf y=%.2lf ",allPoints[i].x,allPoints[i].y);
        int type=allPoints[i].PointType;
        if(type==1)printf("Start\n");
        else if(type==2)printf("end\n");
        else if(type==3)printf("split\n");
        else if(type==4)printf("merge\n");
        else if(type==5)printf("regular\n");
    }


}
