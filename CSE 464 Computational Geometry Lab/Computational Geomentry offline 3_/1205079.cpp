#include<bits/stdc++.h>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define pi (2*acos(0.0))
#define INF (1<<28)
#define startV 1
#define endV 2
#define splitV 3
#define mergeV 4
#define regularV 5

#define pi (2*acos(0.0))



using namespace std;

double cameraHeight;
double cameraAngle;
int drawaxes;

int number_of_points;
int total_edge_count=0;

int printEdgeCount=0;

struct point
{


    double x,y;
    int point_id;
    bool validPoint=true;

    bool operator==(const point& b) const
    {
        return ((int)x ==(int)b.x && (int)y ==(int)b.y);
    }

};






struct edge
{
    point s,e,a,b;
    int edge_id;
    bool edge_validity=true;
};


point allPoints[200];

point P_1,P_2;

point topmostRightmostPoint,rightMostPoint;




int allEdgeId[200][200];


edge edgeList[200];


vector<point> allValidPoints,allInputPoints;

int validEdgeCount()
{
    int c=0;
    for(int i=0; i<total_edge_count; i++)
    {
        if(edgeList[i].edge_validity)c++;

    }
    return c;
}


void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    {

        glColor3f(0, 0, 255);
        glVertex3f( 200,0,0);
        glVertex3f(0,0,0);
        glColor3f(255, 255, 255);
        glVertex3f(-200,0,0);
        glVertex3f(0,0,0);


        glColor3f(0, 255, 0);
        glVertex3f(0, 200,0);
        glVertex3f(0,0,0);
        glColor3f(255, 255, 255);
        glVertex3f(0,-200,0);
        glVertex3f(0,0,0);



        glColor3f(255,0,0);
        glVertex3f(0,0, 200);
        glVertex3f(0,0,0);
        glColor3f(255, 255, 255);
        glVertex3f(0,0,-200);
        glVertex3f(0,0,0);
    }
    glEnd();

}

void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0,0,255);
    //generate points
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0; i<segments; i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawAllLines()
{
    glColor3f(255,0,0);
    //printf("Total valid edge=%d\n",validEdgeCount());
    //int c=0;
    printEdgeCount=0;
    for(int i=0; i<total_edge_count; i++)
    {
        //if(edgeList[i].a==P_1 and edgeList[i].b==P_2 or edgeList[i].a==P_2 and edgeList[i].b==P_1)continue;
        if(edgeList[i].s==P_1 or edgeList[i].e==P_1 or edgeList[i].e==P_2 or edgeList[i].s==P_2)continue;
        //if(edgeList[i].a==P_1 or edgeList[i].b==P_1)continue;
        //if(edgeList[i].a==P_2 or edgeList[i].b==P_2)continue;
        if(edgeList[i].edge_validity==false)continue;
        glBegin(GL_LINES);
        {
            printEdgeCount++;
            glVertex3f(edgeList[i].s.x,edgeList[i].s.y,0);
            glVertex3f(edgeList[i].e.x,edgeList[i].e.y,0);
        }
        glEnd();
    }
    //printf("Total printed edge=%d\n",c);
    glColor3f(0,255,0);

}

void drawAllPoints()
{
    for(int i=0; i<allInputPoints.size(); i++)
    {
        glPushMatrix();
        {
            glTranslatef(allInputPoints[i].x,allInputPoints[i].y,0);
            drawCircle(1,20);

        }
        glPopMatrix();


    }
}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {


    case '1':

        break;
    case '2':
        break;
    case '3':

        break;
    case '4':
        break;
    default:
        break;
    }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {

    case GLUT_KEY_DOWN:		//down arrow key
        cameraHeight -= 3.0;
        break;
    case GLUT_KEY_UP:		// up arrow key
        cameraHeight += 3.0;
        break;

    case GLUT_KEY_RIGHT:
        cameraAngle += 0.03;
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.03;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:

        break;
    case GLUT_KEY_END:

        break;

    default:
        break;
    }
}


void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:

        break;

    case GLUT_RIGHT_BUTTON:
        //........
        break;

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}



void display()
{

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?

    gluLookAt(0,0,100,	0,0,0,	0,1,0);
    //gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(300,300,-300,	0,0,0,	0,0,1);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes();
//    drawGrid();


    //glScalef(5,5,5);
    glPushMatrix();
    {

        drawAllLines();
        glColor3f(0,255,0);

        //printf("valid=%d total=%d\n",validEdgeCount(),printEdgeCount);


    }
    glPopMatrix();

    drawAllPoints();







    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{

    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init()
{
    //codes for initialization

    drawaxes=1;
    cameraHeight=200.0;
    cameraAngle=1.0;


    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80,	1,	1,	1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance

}







double area(point pt, point s,point e)
{
    return abs((pt.x*(s.y-e.y) + s.x*(e.y-pt.y)+ e.x*(pt.y-s.y))/2.0);
}
double P_dist(point p1,point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double findAngel(point center,point left,point rig)
{

    //printf("point ids=%d %d %d\n",center.point_id,left.point_id,rig.point_id);
    double value=(P_dist(center,left)*P_dist(center,left)+P_dist(center,rig)*P_dist(center,rig)-P_dist(left,rig)*P_dist(left,rig))/(2*P_dist(center,left)*P_dist(center,rig));
    //cout<<"val="<<value<<endl;
    double angle= acos(value)*180.0/pi;
    cout<<"angle="<<angle<<endl;
    return angle;
}

/*
float sign (point p1, point p2, point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}
*/


/*
bool PointInTriangle (point pt, point v1, point v2, point v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}
*/

/*
bool PointInLine(point pt, point s,point e)
{
    //cout<<"whole dist="<<P_dist(s,e)<<endl;
    //cout<<"sum dist="<<P_dist(pt,s)+P_dist(pt,e)<<endl;

    //if((int)P_dist(s,e)==(int)(P_dist(pt,s)+P_dist(pt,e)))return true;

    double a=area(pt,s,e);
    cout<<"area"<<a<<endl;
    if((int)a==0)return true;
    else return false;

}
*/

double cross(point v1,point v2)
{
    return v1.x*v2.y-v2.x*v1.y;
}
point vect(point a,point b)
{
    point v;
    v.x=b.x-a.x;
    v.y=b.y-a.y;
    return v;
}
int isInside(point pt, point v1, point v2, point v3) // 1 for on the edge,2 for inside,3 for outside
{
    //if(tr.a.x==inf && tr.a.y==inf) return 3;

    //vect(tr.s,pt),v2(tr.s,tr.e);

    point vv1,vv2;

    vv1.x=pt.x-v1.x;
    vv1.y=pt.y-v1.y;

    vv2.x=v2.x-v1.x;
    vv2.y=v2.y-v1.y;

    int cr=vv1.x*vv2.y-vv2.x*vv1.y;
    //cout<<"cross="<<cr<<endl;
    if(cr==0)
    {
        printf("returning 1\n");
        return 1;
    }
    else
    {
        double t1=cross(vv1,vv2);
        cout<<"cross="<<t1<<endl;
        vv1=vect(v2,pt);vv2=vect(v2,v3);
        double t2=cross(vv1,vv2);
        cout<<"cross="<<t2<<endl;
        vv1=vect(v3,pt);vv2=vect(v3,v1);
        double t3=cross(vv1,vv2);
        cout<<"cross="<<t3<<endl;
        if((t1>0&&t2>0&&t3>0) || (t1<0&&t2<0&&t3<0))
        {
            printf("returning 2\n");
            return 2;
        }
    }
    printf("returning 3\n");
    return 3;
}

/*int findOtheredge(point ss,point ee)
{

    for(int i=0; i<total_edge_count; i++)
    {
        if(edgeList[i].edge_validity==false)continue;
        if((int)edgeList[i].s.x==(int)ss.x and (int)edgeList[i].s.y==(int)ss.y and (int)edgeList[i].e.x==(int)ee.x and (int)edgeList[i].e.y==(int)ee.y or (int)edgeList[i].e.x==(int)ss.x and (int)edgeList[i].e.y==(int)ss.y and (int)edgeList[i].s.x==(int)ee.x and (int)edgeList[i].s.y==(int)ee.y)
        {
            return i;
            break;
        }
    }
}
*/

/*int findAnedge(edge ed)
{
   for(int i=0; i<total_edge_count; i++)
    {
    if((int)edgeList[i].s.x==(int)ed.s.x and (int)edgeList[i].s.y==(int)ed.s.y and (int)edgeList[i].e.x==(int)ed.e.x and (int)edgeList[i].e.y==(int)ed.e.y )return i;
    }
}
*/





bool isIleagal(edge ed)
{
    printf("#############check for legalize\n");
    double angle1,angle2,totalAngle;
    if(!ed.a.validPoint)return false;
    angle1=findAngel(ed.a,ed.s,ed.e);
    if(ed.b.validPoint==false)return false;
    angle2=findAngel(ed.b,ed.s,ed.e);
    totalAngle=angle1+angle2;
    printf("total angle =%lf\n",totalAngle);
    if(totalAngle<=180.0)return false;
    else return true;

}



void LegalizeEdge(point pr,edge ed)
{
    //if(ed.a==P_1 or ed.a==P_2)return;
    //if(ed.b==P_1 or ed.b==P_2)return;
    //if(ed.s==P_1 or ed.s==P_2)return;
    //if(ed.e==P_1 or ed.e==P_2)return;

    printf("calling legalize for  point id=%d %d %d \n",pr.point_id,ed.s.point_id,ed.e.point_id);
    if(pr.point_id==ed.s.point_id or pr.point_id==ed.e.point_id)return;
    if(!ed.b.validPoint)
    {
        printf("by default legal because b is not valid----\n");
        return;
    }
    if(!ed.a.validPoint)
    {
        printf("by default legal because a is not valid----\n");
        return;
    }

    if( pr==ed.a)//(int)pr.x==(int)ed.a.x and (int)pr.y==(int)ed.a.y
    {
        printf("PR matched with A\n");

        if(isIleagal(ed))
        {
            printf("--------------------A Not Legal\n");
            edge newedge;
            newedge.s=ed.a;
            newedge.e=ed.b;
            newedge.a=ed.s;
            newedge.b=ed.e;
            newedge.edge_id=total_edge_count;

            int _a,_b,_c,_d;
            //_a=findOtheredge(ed.a,ed.s);
            _a=allEdgeId[ed.a.point_id][ed.s.point_id];
            //_b=findOtheredge(ed.a,ed.e);
            _b=allEdgeId[ed.a.point_id][ed.e.point_id];
            //_c=findOtheredge(ed.b,ed.s);
            _c=allEdgeId[ed.b.point_id][ed.s.point_id];

            //_d=findOtheredge(ed.b,ed.e);
            _d=allEdgeId[ed.b.point_id][ed.e.point_id];

            if(edgeList[_a].b==ed.e)
            {
                printf("checking----\n");
                edgeList[_a].b=ed.b;
            }
            else edgeList[_a].a=ed.b;
            if(edgeList[_b].b==ed.s)
            {
                printf("checking----\n");
                edgeList[_b].b=ed.b;
            }
            else
            {
                printf("checking----\n");
                edgeList[_b].a=ed.b;
            }


            if(edgeList[_c].b==ed.e)
            {
                printf("checking----\n");
                edgeList[_c].b=ed.a;
            }
            else
            {
                printf("checking----\n");
                edgeList[_c].a=ed.a;
            }
            if(edgeList[_d].b==ed.s)
            {
                printf("checking----\n");
                edgeList[_d].b=ed.a;
            }
            else
            {
                printf("checking----\n");
                edgeList[_d].a=ed.a;
            }

            //edgeList[_c].a=ed.a;
            //edgeList[_d].a=ed.a;

            edgeList[allEdgeId[ed.s.point_id][ed.e.point_id]].edge_validity=false;
            allEdgeId[ed.s.point_id][ed.e.point_id]=-1;
            allEdgeId[ed.e.point_id][ed.s.point_id]=-1;


            //edgeList[allEdgeId[ed.e.point_id][ed.s.point_id]].edge_validity=false;

            //edgeList.push_back(newedge);
            allEdgeId[newedge.s.point_id][newedge.e.point_id]=newedge.edge_id;
            allEdgeId[newedge.e.point_id][newedge.s.point_id]=newedge.edge_id;

            edgeList[total_edge_count]=newedge;
            total_edge_count++;

            int x1,y1,x2,y2;
            x1=newedge.a.point_id;
            y1=newedge.e.point_id;
            x2=newedge.b.point_id;
            y2=newedge.e.point_id;

            LegalizeEdge(pr,edgeList[allEdgeId[x1][y1]]);
            LegalizeEdge(pr,edgeList[allEdgeId[x2][y2]]);
        }
        else
        {
            printf("-----------------A Legal \n");
            return;
        }

    }
    else if(pr==ed.b) //(int)pr.x==(int)ed.b.x and (int)pr.y==(int)ed.b.y
    {
        printf("PR matched with B\n");

        if(isIleagal(ed))
        {
            printf("--------------------B Not Legal\n");
            edge newedge;
            newedge.s=ed.b;
            newedge.e=ed.a;
            newedge.a=ed.s;
            newedge.b=ed.e;
            newedge.edge_id=total_edge_count;

            int _a,_b,_c,_d;
            //_a=findOtheredge(ed.a,ed.s);
            //_b=findOtheredge(ed.a,ed.e);
            //_c=findOtheredge(ed.b,ed.s);
            //_d=findOtheredge(ed.b,ed.e);

            //_a=findOtheredge(ed.a,ed.s);
            _a=allEdgeId[ed.a.point_id][ed.s.point_id];
            //_b=findOtheredge(ed.a,ed.e);
            _b=allEdgeId[ed.a.point_id][ed.e.point_id];
            //_c=findOtheredge(ed.b,ed.s);
            _c=allEdgeId[ed.b.point_id][ed.s.point_id];

            //_d=findOtheredge(ed.b,ed.e);
            _d=allEdgeId[ed.b.point_id][ed.e.point_id];

            if(edgeList[_a].b==ed.e)
            {
                //printf("checking----\n");
                edgeList[_a].b=ed.b;
            }
            else edgeList[_a].a=ed.b;
            if(edgeList[_b].b==ed.s)
            {
                //printf("checking----\n");
                edgeList[_b].b=ed.b;
            }
            else edgeList[_b].a=ed.b;


            if(edgeList[_c].b==ed.e)
            {
                //printf("checking----\n");
                edgeList[_c].b=ed.a;
            }
            else edgeList[_c].a=ed.a;
            if(edgeList[_d].b==ed.s)
            {
                //printf("checking----\n");
                edgeList[_d].b=ed.a;
            }
            else edgeList[_d].a=ed.a;

            //edgeList[_a].b=ed.b;
            //edgeList[_b].b=ed.b;

            //edgeList[_c].a=ed.a;
            //edgeList[_d].a=ed.a;

            //edgeList[allEdgeId[ed.s.point_id][ed.e.point_id]].edge_validity=false;
            //edgeList[allEdgeId[ed.e.point_id][ed.s.point_id]].edge_validity=false;
            //edgeList.push_back(newedge);

            edgeList[allEdgeId[ed.s.point_id][ed.e.point_id]].edge_validity=false;
            allEdgeId[ed.s.point_id][ed.e.point_id]=-1;
            allEdgeId[ed.e.point_id][ed.s.point_id]=-1;

            allEdgeId[newedge.s.point_id][newedge.e.point_id]=newedge.edge_id;
            allEdgeId[newedge.e.point_id][newedge.s.point_id]=newedge.edge_id;

            edgeList[total_edge_count]=newedge;
            total_edge_count++;

            int x1,y1,x2,y2;
            x1=newedge.a.point_id;
            y1=newedge.e.point_id;
            x2=newedge.b.point_id;
            y2=newedge.e.point_id;

            LegalizeEdge(pr,edgeList[allEdgeId[x1][y1]]);
            LegalizeEdge(pr,edgeList[allEdgeId[x2][y2]]);

            //LegalizeEdge(pr,edgeList[allEdgeId[newedge.a.point_id][newedge.e.point_id]]);
            //LegalizeEdge(pr,edgeList[allEdgeId[newedge.b.point_id][newedge.e.point_id]]);
        }
        else printf("-----------------B Legal\n");
        return;
    }
    else
    {
        printf("vulllllll----------\n");
        return;
    }
}

int main(int argc, char **argv)
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    //double dist=sqrt((topmostRightmostPoint.x-rightMostPoint.x)*(topmostRightmostPoint.x-rightMostPoint.x)+(topmostRightmostPoint.y-rightMostPoint.y)*(topmostRightmostPoint.y-rightMostPoint.y));
    //double xx=(INF*(rightMostPoint.x+10)-(INF-dist)*topmostRightmostPoint.x)/dist;
    //double yy=(INF*rightMostPoint.y-(INF-dist)*topmostRightmostPoint.y)/dist;

    srand (time(NULL));

    //cout<<" inf="<<INF<<endl;

    allInputPoints.clear();
    allValidPoints.clear();
    printf("Enter number of points=");
    scanf("%d",&number_of_points);
    double x,y;



    topmostRightmostPoint.x=-INF;
    topmostRightmostPoint.y=-INF;

    rightMostPoint.x=-INF;
    rightMostPoint.y=-INF;
    point testPoint;
    for(int i=0; i<number_of_points; i++)
    {
        cin>>x>>y;

        //x=-50+rand()%100;
        //y=-50+rand()%100;


        testPoint.x=x;
        testPoint.y=y;
        testPoint.point_id=i;
        allInputPoints.push_back(testPoint);
    }
    for(int i=0; i<number_of_points; i++)
    {

        testPoint=allInputPoints[i];


        if(testPoint.y>topmostRightmostPoint.y)
        {
            topmostRightmostPoint.x=testPoint.x;
            topmostRightmostPoint.y=testPoint.y;
            topmostRightmostPoint.point_id=testPoint.point_id;

        }
        else if((int)testPoint.y==(int)topmostRightmostPoint.y)
        {
            if(testPoint.x>topmostRightmostPoint.x)
            {
                topmostRightmostPoint.x=testPoint.x;
                topmostRightmostPoint.y=testPoint.y;
                topmostRightmostPoint.point_id=testPoint.point_id;
            }
        }

    }

    point _left,_right;
    double minAngle=INF;

    point l,r;
    l.x=topmostRightmostPoint.x-10;
    l.y=topmostRightmostPoint.y;

    r.x=topmostRightmostPoint.x+10;
    r.y=topmostRightmostPoint.y;
    for(int i=0; i<allInputPoints.size(); i++)
    {
        if(topmostRightmostPoint.point_id==allInputPoints[i].point_id)continue;
        double foundAngle=findAngel(topmostRightmostPoint,l,allInputPoints[i]);
        if(foundAngle<minAngle)
        {
            minAngle=foundAngle;
            _left=allInputPoints[i];
        }
    }
    //printf("min angle for leff=%lf\n",minAngle);
    minAngle=INF;
    for(int i=0; i<allInputPoints.size(); i++)
    {
        if(topmostRightmostPoint.point_id==allInputPoints[i].point_id)continue;
        double foundAngle=findAngel(topmostRightmostPoint,allInputPoints[i],r);
        if(foundAngle<minAngle)
        {
            minAngle=foundAngle;
            _right=allInputPoints[i];
        }
    }

    //printf("min angle for right=%lf\n",minAngle);
    double dist=sqrt((topmostRightmostPoint.x-(_left.x-2))*(topmostRightmostPoint.x-(_left.x-2))+(topmostRightmostPoint.y-(_left.y+2))*(topmostRightmostPoint.y-(_left.y+2)));
    double xx=(INF*(_left.x-2)-(INF-dist)*topmostRightmostPoint.x)/dist;
    double yy=(INF*(_left.y+2)-(INF-dist)*topmostRightmostPoint.y)/dist;

    P_1.x=xx;
    P_1.y=yy;

    if((int)_right.x<=(int)topmostRightmostPoint.x)
    {
        P_2.x=topmostRightmostPoint.x+5;
        P_2.y=-INF;
    }
    else
    {
        dist=sqrt((topmostRightmostPoint.x-(_right.x+2))*(topmostRightmostPoint.x-(_right.x+2))+(topmostRightmostPoint.y-(_right.y+2))*(topmostRightmostPoint.y-(_right.y+2)));
        xx=(INF*(_right.x+2)-(INF-dist)*topmostRightmostPoint.x)/dist;
        yy=(INF*(_right.y+2)-(INF-dist)*topmostRightmostPoint.y)/dist;

        P_2.x=xx;
        P_2.y=yy;
    }

    int p_id=3;
    for(int i=0; i<allInputPoints.size(); i++)
    {
        if(allInputPoints[i].point_id==topmostRightmostPoint.point_id)continue;

        else
        {
            allInputPoints[i].point_id=p_id;
            allPoints[p_id]=allInputPoints[i];
            p_id++;
        }
    }

    P_1.point_id=0;
    P_2.point_id=1;
    topmostRightmostPoint.point_id=2;

    allPoints[0]=P_1;
    allPoints[1]=P_2;
    allPoints[2]=topmostRightmostPoint;

    for(int i=0; i<p_id; i++)
    {
        printf("%d %.0lf %.2lf\n",allPoints[i].point_id,allPoints[i].x,allPoints[i].y);
    }







    findAngel(topmostRightmostPoint,P_1,P_2);

    edge firstEdge;
    firstEdge.s=topmostRightmostPoint;
    firstEdge.e=P_1;
    firstEdge.a=P_2;
    firstEdge.b.validPoint=false;
    firstEdge.edge_id=0;

    //edgeList.push_back(firstEdge);
    allEdgeId[firstEdge.e.point_id][firstEdge.s.point_id]=firstEdge.edge_id;
    allEdgeId[firstEdge.s.point_id][firstEdge.e.point_id]=firstEdge.edge_id;

    edgeList[0]=firstEdge;




    edge secEdge;
    secEdge.s=topmostRightmostPoint;
    secEdge.e=P_2;
    secEdge.a=P_1;
    secEdge.b.validPoint=false;
    secEdge.edge_id=1;

    //edgeList.push_back(secEdge);

    allEdgeId[secEdge.s.point_id][secEdge.e.point_id]=secEdge.edge_id;
    allEdgeId[secEdge.e.point_id][secEdge.s.point_id]=secEdge.edge_id;

    edgeList[1]=secEdge;


    edge thirEdge;
    thirEdge.s=P_1;
    thirEdge.e=P_2;
    thirEdge.a=topmostRightmostPoint;
    thirEdge.b.validPoint=false;
    thirEdge.edge_id=2;

    //edgeList.push_back(thirEdge);

    allEdgeId[thirEdge.s.point_id][thirEdge.e.point_id]=thirEdge.edge_id;
    allEdgeId[thirEdge.e.point_id][thirEdge.s.point_id]=thirEdge.edge_id;

    edgeList[2]=thirEdge;

    total_edge_count=3;



    printf("size=%d\n",p_id);
    for(int i=3; i<p_id; i++) // main loop
    {
        point nowPoint;
        nowPoint=allPoints[i];
        printf("for point =%d------\n",i);
        //printf("valid edge count=%d\n",validEdgeCount());
        for(int j=0; j<total_edge_count ; j++)
        {
            if(edgeList[j].edge_validity==false)continue;
            printf("valid edge id=%d \n",edgeList[j].edge_id);
            if(1==isInside(nowPoint,edgeList[j].s,edgeList[j].e,edgeList[j].a))
            {
                printf("point in line\n");



                edge newEdge1;
                newEdge1.s=nowPoint;
                newEdge1.e=edgeList[j].a;
                newEdge1.a=edgeList[j].e;
                newEdge1.b=edgeList[j].s;
                newEdge1.edge_id=total_edge_count;

                allEdgeId[newEdge1.s.point_id][newEdge1.e.point_id]=newEdge1.edge_id;
                allEdgeId[newEdge1.e.point_id][newEdge1.s.point_id]=newEdge1.edge_id;

                edgeList[total_edge_count]=newEdge1;

                total_edge_count++;

                edge newEdge2;
                newEdge2.s=nowPoint;
                newEdge2.e=edgeList[j].b;
                newEdge2.a=edgeList[j].s;
                newEdge2.b=edgeList[j].e;
                newEdge2.edge_id=total_edge_count;

                allEdgeId[newEdge2.s.point_id][newEdge2.e.point_id]=newEdge2.edge_id;
                allEdgeId[newEdge2.e.point_id][newEdge2.s.point_id]=newEdge2.edge_id;

                edgeList[total_edge_count]=newEdge2;

                total_edge_count++;

                edge newEdge3;
                newEdge3.s=nowPoint;
                newEdge3.e=edgeList[j].s;
                newEdge3.a=edgeList[j].a;
                newEdge3.b=edgeList[j].b;
                newEdge3.edge_id=total_edge_count;

                allEdgeId[newEdge3.s.point_id][newEdge3.e.point_id]=newEdge3.edge_id;
                allEdgeId[newEdge3.e.point_id][newEdge3.s.point_id]=newEdge3.edge_id;

                edgeList[total_edge_count]=newEdge3;

                total_edge_count++;


                edge newEdge4;
                newEdge4.s=nowPoint;
                newEdge4.e=edgeList[j].e;
                newEdge4.a=edgeList[j].a;
                newEdge4.b=edgeList[j].b;
                newEdge4.edge_id=total_edge_count;

                allEdgeId[newEdge4.s.point_id][newEdge4.e.point_id]=newEdge4.edge_id;
                allEdgeId[newEdge4.e.point_id][newEdge4.s.point_id]=newEdge4.edge_id;

                edgeList[total_edge_count]=newEdge4;

                total_edge_count++;



                point prevA=edgeList[j].a;
                printf("found edge ids %d %d %d\n",edgeList[j].a.point_id,edgeList[j].s.point_id,edgeList[j].e.point_id);
                int s_id,e_id,a_id,b_id;
                s_id=edgeList[j].s.point_id;
                e_id=edgeList[j].e.point_id;
                a_id=edgeList[j].a.point_id;
                b_id=edgeList[j].b.point_id;


                edgeList[j].edge_validity=false;


                //int p=findOtheredge(edgeList[j].s,prevA);
                //printf("found edge ids %d %d %d\n",edgeList[p].a.point_id,edgeList[p].s.point_id,edgeList[p].e.point_id);
                if(edgeList[allEdgeId[s_id][a_id]].a==allPoints[e_id])
                {
                    edgeList[allEdgeId[s_id][a_id]].a=nowPoint; //problem
                }
                else edgeList[allEdgeId[s_id][a_id]].b=nowPoint;
                //int q=findOtheredge(edgeList[j].e,prevA);
                if(edgeList[allEdgeId[e_id][a_id]].a==allPoints[s_id])
                {
                    edgeList[allEdgeId[e_id][a_id]].a=nowPoint;
                }
                else edgeList[allEdgeId[e_id][a_id]].b=nowPoint;



                if(edgeList[allEdgeId[s_id][b_id]].b==allPoints[e_id])
                {
                    edgeList[allEdgeId[s_id][b_id]].b=nowPoint; //problem
                }
                else edgeList[allEdgeId[s_id][b_id]].a=nowPoint;
                //int q=findOtheredge(edgeList[j].e,prevA);
                if(edgeList[allEdgeId[e_id][b_id]].b==allPoints[s_id])
                {
                    edgeList[allEdgeId[e_id][b_id]].b=nowPoint;
                }
                else edgeList[allEdgeId[e_id][b_id]].a=nowPoint;



                 //problem

                //LegalizeEdge(nowPoint,edgeList[j]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,edgeList[allEdgeId[s_id][a_id]]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,edgeList[allEdgeId[e_id][a_id]]);
                printf("-------------------------------------\n");

                LegalizeEdge(nowPoint,edgeList[allEdgeId[s_id][b_id]]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,edgeList[allEdgeId[e_id][b_id]]);
                printf("-------------------------------------\n");
                printf("breaked\n");
                break;





                printf("breaked\n");
                break;
            }
            else if(2==isInside(nowPoint,edgeList[j].s,edgeList[j].e,edgeList[j].a))
            {
                printf("---in A side of %d %d %d----\n",edgeList[j].s.point_id,edgeList[j].e.point_id,edgeList[j].a.point_id);
                printf("the point in the triange\n");
                edge newEdge1;
                newEdge1.s=nowPoint;
                newEdge1.e=edgeList[j].s;
                newEdge1.a=edgeList[j].e;
                newEdge1.b=edgeList[j].a;
                newEdge1.edge_id=total_edge_count;

                allEdgeId[newEdge1.s.point_id][newEdge1.e.point_id]=newEdge1.edge_id;
                allEdgeId[newEdge1.e.point_id][newEdge1.s.point_id]=newEdge1.edge_id;

                edgeList[total_edge_count]=newEdge1;

                total_edge_count++;

                edge newEdge2;
                newEdge2.s=nowPoint;
                newEdge2.e=edgeList[j].e;
                newEdge2.a=edgeList[j].s;
                newEdge2.b=edgeList[j].a;
                newEdge2.edge_id=total_edge_count;

                allEdgeId[newEdge2.s.point_id][newEdge2.e.point_id]=newEdge2.edge_id;
                allEdgeId[newEdge2.e.point_id][newEdge2.s.point_id]=newEdge2.edge_id;

                edgeList[total_edge_count]=newEdge2;

                total_edge_count++;

                edge newEdge3;
                newEdge3.s=nowPoint;
                newEdge3.e=edgeList[j].a;
                newEdge3.a=edgeList[j].s;
                newEdge3.b=edgeList[j].e;
                newEdge3.edge_id=total_edge_count;

                allEdgeId[newEdge3.s.point_id][newEdge3.e.point_id]=newEdge3.edge_id;
                allEdgeId[newEdge3.e.point_id][newEdge3.s.point_id]=newEdge3.edge_id;

                edgeList[total_edge_count]=newEdge3;

                total_edge_count++;



                point prevA=edgeList[j].a;
                printf("found edge ids %d %d %d\n",edgeList[j].a.point_id,edgeList[j].s.point_id,edgeList[j].e.point_id);
                int s_id,e_id,a_id;
                s_id=edgeList[j].s.point_id;
                e_id=edgeList[j].e.point_id;
                a_id=edgeList[j].a.point_id;
                edgeList[j].a=nowPoint;
                //int p=findOtheredge(edgeList[j].s,prevA);
                //printf("found edge ids %d %d %d\n",edgeList[p].a.point_id,edgeList[p].s.point_id,edgeList[p].e.point_id);
                if(edgeList[allEdgeId[s_id][a_id]].a==allPoints[e_id])
                {
                    edgeList[allEdgeId[s_id][a_id]].a=nowPoint; //problem
                }
                else edgeList[allEdgeId[s_id][a_id]].b=nowPoint;
                //int q=findOtheredge(edgeList[j].e,prevA);
                if(edgeList[allEdgeId[e_id][a_id]].a==allPoints[s_id])
                {
                    edgeList[allEdgeId[e_id][a_id]].a=nowPoint;
                }
                else edgeList[allEdgeId[e_id][a_id]].b=nowPoint;
                 //problem

                LegalizeEdge(nowPoint,edgeList[j]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,edgeList[allEdgeId[s_id][a_id]]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,edgeList[allEdgeId[e_id][a_id]]);
                printf("-------------------------------------\n");
                printf("breaked\n");
                break;
            }
            else if(edgeList[j].b.validPoint && 2==isInside(nowPoint,edgeList[j].s,edgeList[j].e,edgeList[j].b))
            {



                printf("---in B side----\n");
                printf("the point in the triange\n");
                edge newEdge1;
                newEdge1.s=nowPoint;
                newEdge1.e=edgeList[j].s;
                newEdge1.a=edgeList[j].e;
                newEdge1.b=edgeList[j].b;
                newEdge1.edge_id=total_edge_count;

                allEdgeId[newEdge1.s.point_id][newEdge1.e.point_id]=newEdge1.edge_id;
                allEdgeId[newEdge1.e.point_id][newEdge1.s.point_id]=newEdge1.edge_id;

                edgeList[total_edge_count]=newEdge1;

                total_edge_count++;

                edge newEdge2;
                newEdge2.s=nowPoint;
                newEdge2.e=edgeList[j].e;
                newEdge2.a=edgeList[j].s;
                newEdge2.b=edgeList[j].b;

                newEdge2.edge_id=total_edge_count;

                allEdgeId[newEdge2.s.point_id][newEdge2.e.point_id]=newEdge2.edge_id;
                allEdgeId[newEdge2.e.point_id][newEdge2.s.point_id]=newEdge2.edge_id;

                edgeList[total_edge_count]=newEdge2;

                total_edge_count++;

                edge newEdge3;
                newEdge3.s=nowPoint;
                newEdge3.e=edgeList[j].b;
                newEdge3.a=edgeList[j].s;
                newEdge3.b=edgeList[j].e;
                newEdge3.edge_id=total_edge_count;

                allEdgeId[newEdge3.s.point_id][newEdge3.e.point_id]=newEdge3.edge_id;
                allEdgeId[newEdge3.e.point_id][newEdge3.s.point_id]=newEdge3.edge_id;

                edgeList[total_edge_count]=newEdge3;

                total_edge_count++;




                point prevA=edgeList[j].b;
                printf("found edge ids %d %d %d\n",edgeList[j].a.point_id,edgeList[j].s.point_id,edgeList[j].e.point_id);
                int s_id,e_id,b_id;
                s_id=edgeList[j].s.point_id;
                e_id=edgeList[j].e.point_id;
                b_id=edgeList[j].b.point_id;

                edgeList[j].b=nowPoint;
                //int p=findOtheredge(edgeList[j].s,prevA);
                //printf("found edge ids %d %d %d\n",edgeList[p].a.point_id,edgeList[].s.point_id,edgeList[p].e.point_id);
                //edgeList[allEdgeId[s_id][b_id]].b=nowPoint; //problem
                //int q=findOtheredge(edgeList[j].e,prevA);
                //edgeList[allEdgeId[e_id][b_id]].b=nowPoint; //problem


                if(edgeList[allEdgeId[s_id][b_id]].b==allPoints[e_id])
                {
                    edgeList[allEdgeId[s_id][b_id]].b=nowPoint; //problem
                }
                else edgeList[allEdgeId[s_id][b_id]].a=nowPoint;
                //int q=findOtheredge(edgeList[j].e,prevA);
                if(edgeList[allEdgeId[e_id][b_id]].b==allPoints[s_id])
                {
                    edgeList[allEdgeId[e_id][b_id]].b=nowPoint;
                }
                else edgeList[allEdgeId[e_id][b_id]].a=nowPoint;




                LegalizeEdge(nowPoint,edgeList[j]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,edgeList[allEdgeId[s_id][b_id]]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,edgeList[allEdgeId[e_id][b_id]]);
                printf("-------------------------------------\n");

                break;


            }

            else
            {
                printf("point is not in triangle and not in line\n");
            }
        }
    }
























    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL





    return 0;
}
