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

struct point
{
    double x,y;
    int point_id;
    bool validPoint=true;

};




struct edge
{
    point s,e,a,b;
    int edge_id;
    bool edge_validity=true;
};


point allPoints[100];

point P_1,P_2;

point topmostRightmostPoint,rightMostPoint;


vector<edge>AllEdge;


vector<point> allValidPoints,allInputPoints;




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
    for(int i=0; i<AllEdge.size(); i++)
    {
        //if(AllEdge[i].s.x==P_1.x or AllEdge[i].s.x==P_2.x or AllEdge[i].e.x==P_1.x or AllEdge[i].e.x==P_2.x)continue;
        if(AllEdge[i].edge_validity==false)continue;
        glBegin(GL_LINES);
        {
            glVertex3f(AllEdge[i].s.x,AllEdge[i].s.y,0);
            glVertex3f(AllEdge[i].e.x,AllEdge[i].e.y,0);
        }
        glEnd();
    }
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







float area(point pt, point s,point e)
{
    return abs((pt.x*(s.y-e.y) + s.x*(e.y-pt.y)+ e.x*(pt.y-s.y))/2.0);
}


float sign (point p1, point p2, point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (point pt, point v1, point v2, point v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

bool PointInLine(point pt, point s,point e)
{
    printf("point in line check########\n");
    float A=area(pt,s,e);
    cout<<"area="<<A<<endl;

    if((int)A==0)
    {
        double maxX=max(s.x,e.x);
        double minX=min(s.x,e.x);


        double maxy=max(s.y,e.y);
        double miny=min(s.y,e.y);

        if(pt.x<=maxX and pt.y>=minX and pt.y<=maxy and pt.y>=miny) return true;
        else return false;
    }
    else return false;

}

int findOtheredge(point ss,point ee)
{

    for(int i=0; i<AllEdge.size(); i++)
    {
        if(AllEdge[i].edge_validity==false)continue;
        if((int)AllEdge[i].s.x==(int)ss.x and (int)AllEdge[i].s.y==(int)ss.y and (int)AllEdge[i].e.x==(int)ee.x and (int)AllEdge[i].e.y==(int)ee.y or (int)AllEdge[i].e.x==(int)ss.x and (int)AllEdge[i].e.y==(int)ss.y and (int)AllEdge[i].s.x==(int)ee.x and (int)AllEdge[i].s.y==(int)ee.y)
        {
            return i;
            break;
        }
    }
}

int findAnedge(edge ed)
{
   for(int i=0; i<AllEdge.size(); i++)
    {
    if((int)AllEdge[i].s.x==(int)ed.s.x and (int)AllEdge[i].s.y==(int)ed.s.y and (int)AllEdge[i].e.x==(int)ed.e.x and (int)AllEdge[i].e.y==(int)ed.e.y )return i;
    }
}

double P_dist(point p1,point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double findAngel(point center,point left,point rig)
{
    //printf("point ids=%d %d %d\n",center.point_id,left.point_id,rig.point_id);
    double angle= acos((P_dist(center,left)*P_dist(center,left)+P_dist(center,rig)*P_dist(center,rig)-P_dist(left,rig)*P_dist(left,rig))/(2*P_dist(center,left)*P_dist(center,rig)))*180.0/pi;
    cout<<"angle="<<angle<<endl;
    return angle;
}

bool isIleagal(edge ed)
{
    double angle1,angle2,totalAngle;
    angle1=findAngel(ed.a,ed.s,ed.e);
    if(!ed.b.validPoint)return false;
    angle2=findAngel(ed.b,ed.s,ed.e);
    totalAngle=angle1+angle2;
    printf("total angle =%lf\n",totalAngle);
    if(totalAngle>180.0)return true;
    else return false;

}

void LegalizeEdge(point pr,edge ed)
{
    printf("legalized point id=%d %d %d \n",ed.a.point_id,ed.s.point_id,ed.e.point_id);
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
    if(pr.x==ed.a.x and pr.y==ed.a.y)
    {

        if(isIleagal(ed))
        {
            printf("--------------------illigal\n");
            edge newedge;
            newedge.s=ed.a;
            newedge.e=ed.b;
            newedge.a=ed.s;
            newedge.b=ed.e;

            int _a,_b,_c,_d;
            _a=findOtheredge(ed.a,ed.s);
            _b=findOtheredge(ed.a,ed.e);
            _c=findOtheredge(ed.b,ed.s);
            _d=findOtheredge(ed.b,ed.e);

            if(AllEdge[_a].b.x==ed.e.x)
            {
                printf("checking----\n");
                AllEdge[_a].b=ed.b;
            }
            else AllEdge[_a].a=ed.b;
            if(AllEdge[_b].b.x==ed.s.x)
            {
                printf("checking----\n");
                AllEdge[_b].b=ed.b;
            }
            else AllEdge[_b].a=ed.b;


            if(AllEdge[_c].b.x==ed.e.x)
            {
                printf("checking----\n");
                AllEdge[_c].b=ed.a;
            }
            else AllEdge[_c].a=ed.a;
            if(AllEdge[_d].b.x==ed.s.x)
            {
                printf("checking----\n");
                AllEdge[_d].b=ed.a;
            }
            else AllEdge[_d].a=ed.a;

            //AllEdge[_c].a=ed.a;
            //AllEdge[_d].a=ed.a;

            AllEdge[findAnedge(ed)].edge_validity=false;
            AllEdge.push_back(newedge);

            LegalizeEdge(pr,AllEdge[findOtheredge(ed.s,ed.b)]);
            LegalizeEdge(pr,AllEdge[findOtheredge(ed.e,ed.b)]);
        }
        else printf("-----------------not illigal\n");
        return;

    }
    else if(pr.x==ed.b.x and pr.y==ed.b.y)
    {

        if(isIleagal(ed))
        {
            printf("--------------------illigal\n");
            edge newedge;
            newedge.s=ed.b;
            newedge.e=ed.a;
            newedge.a=ed.s;
            newedge.b=ed.e;

            int _a,_b,_c,_d;
            _a=findOtheredge(ed.a,ed.s);
            _b=findOtheredge(ed.a,ed.e);
            _c=findOtheredge(ed.b,ed.s);
            _d=findOtheredge(ed.b,ed.e);
            if(AllEdge[_a].b.x==ed.e.x)
            {
                printf("checking----\n");
                AllEdge[_a].b=ed.b;
            }
            else AllEdge[_a].a=ed.b;
            if(AllEdge[_b].b.x==ed.s.x)
            {
                printf("checking----\n");
                AllEdge[_b].b=ed.b;
            }
            else AllEdge[_b].a=ed.b;


            if(AllEdge[_c].b.x==ed.e.x)
            {
                printf("checking----\n");
                AllEdge[_c].b=ed.a;
            }
            else AllEdge[_c].a=ed.a;
            if(AllEdge[_d].b.x==ed.s.x)
            {
                printf("checking----\n");
                AllEdge[_d].b=ed.a;
            }
            else AllEdge[_d].a=ed.a;

            //AllEdge[_a].b=ed.b;
            //AllEdge[_b].b=ed.b;

            //AllEdge[_c].a=ed.a;
            //AllEdge[_d].a=ed.a;

            AllEdge[findAnedge(ed)].edge_validity=false;
            AllEdge.push_back(newedge);
            LegalizeEdge(pr,AllEdge[findOtheredge(ed.s,ed.a)]);
            LegalizeEdge(pr,AllEdge[findOtheredge(ed.e,ed.a)]);
        }
        else printf("-----------------not illigal\n");
        return;
    }
    else
    {
        printf("vulllllll----------\n");
    }
}

int main(int argc, char **argv)
{
    //freopen("input.txt", "r", stdin);
    //freopen("output11.txt", "w", stdout);

    //double dist=sqrt((topmostRightmostPoint.x-rightMostPoint.x)*(topmostRightmostPoint.x-rightMostPoint.x)+(topmostRightmostPoint.y-rightMostPoint.y)*(topmostRightmostPoint.y-rightMostPoint.y));
    //double xx=(INF*(rightMostPoint.x+10)-(INF-dist)*topmostRightmostPoint.x)/dist;
    //double yy=(INF*rightMostPoint.y-(INF-dist)*topmostRightmostPoint.y)/dist;

    srand (time(NULL));

    cout<<" inf="<<INF<<endl;

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
        //cin>>x>>y;

        x=-50+rand()%100;
        y=-50+rand()%100;


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
    for(int i=0;i<allInputPoints.size();i++)
    {
        if(topmostRightmostPoint.point_id==allInputPoints[i].point_id)continue;
        double foundAngle=findAngel(topmostRightmostPoint,l,allInputPoints[i]);
        if(foundAngle<minAngle)
            {
                minAngle=foundAngle;
                _left=allInputPoints[i];
            }
    }
    printf("min angle for leff=%lf\n",minAngle);
    minAngle=INF;
    for(int i=0;i<allInputPoints.size();i++)
    {
        if(topmostRightmostPoint.point_id==allInputPoints[i].point_id)continue;
        double foundAngle=findAngel(topmostRightmostPoint,allInputPoints[i],r);
        if(foundAngle<minAngle)
        {
                minAngle=foundAngle;
                _right=allInputPoints[i];
        }
    }

    printf("min angle for right=%lf\n",minAngle);
    double dist=sqrt((topmostRightmostPoint.x-(_left.x-5))*(topmostRightmostPoint.x-(_left.x-5))+(topmostRightmostPoint.y-(_left.y+10))*(topmostRightmostPoint.y-(_left.y+10)));
    double xx=(INF*(_left.x-5)-(INF-dist)*topmostRightmostPoint.x)/dist;
    double yy=(INF*(_left.y+10)-(INF-dist)*topmostRightmostPoint.y)/dist;

    P_1.x=xx;
    P_1.y=yy;

    if((int)_right.x<=(int)topmostRightmostPoint.x)
    {
        P_2.x=topmostRightmostPoint.x+10;
        P_2.y=-INF;
    }
    else
    {
        dist=sqrt((topmostRightmostPoint.x-(_right.x+5))*(topmostRightmostPoint.x-(_right.x+5))+(topmostRightmostPoint.y-(_right.y+10))*(topmostRightmostPoint.y-(_right.y+10)));
        xx=(INF*(_right.x+5)-(INF-dist)*topmostRightmostPoint.x)/dist;
        yy=(INF*(_right.y+10)-(INF-dist)*topmostRightmostPoint.y)/dist;

        P_2.x=xx;
        P_2.y=yy;
    }


    allValidPoints.push_back(P_1);
    allValidPoints.push_back(P_2);
    allValidPoints.push_back(topmostRightmostPoint);

    findAngel(topmostRightmostPoint,P_1,P_2);

    edge firstEdge;
    firstEdge.s=topmostRightmostPoint;
    firstEdge.e=P_1;
    firstEdge.a=P_2;
    firstEdge.b.validPoint=false;
    //firstEdge.edge_id=0;

    AllEdge.push_back(firstEdge);

    edge secEdge;
    secEdge.s=topmostRightmostPoint;
    secEdge.e=P_2;
    secEdge.a=P_1;
    secEdge.b.validPoint=false;
    //secEdge.edge_id=1;

    AllEdge.push_back(secEdge);


    edge thirEdge;
    thirEdge.s=P_1;
    thirEdge.e=P_2;
    thirEdge.a=topmostRightmostPoint;
    thirEdge.b.validPoint=false;
    //thirEdge.edge_id=2;

    AllEdge.push_back(thirEdge);


    for(int i=0; i<allInputPoints.size(); i++)
    {
        if(allInputPoints[i].point_id==topmostRightmostPoint.point_id)continue;
        allValidPoints.push_back(allInputPoints[i]);
    }

    printf("size=%d\n",allValidPoints.size());
    for(int i=3; i<allValidPoints.size(); i++) // main loop
    {
        point nowPoint;
        nowPoint=allValidPoints[i];
        printf("for point =%d------\n",i);
        for(int j=0; j<AllEdge.size() ; j++)
        {
            if(AllEdge[j].edge_validity==false)continue;

            if(PointInTriangle(nowPoint,AllEdge[j].s,AllEdge[j].e,AllEdge[j].a))
            {
                printf("---in A side----\n");
                printf("the point in the triange\n");
                edge newEdge1;
                newEdge1.s=nowPoint;
                newEdge1.e=AllEdge[j].s;
                newEdge1.a=AllEdge[j].e;
                newEdge1.b=AllEdge[j].a;
                //newEdge1.edge_id=i;

                edge newEdge2;
                newEdge2.s=nowPoint;
                newEdge2.e=AllEdge[j].e;
                newEdge2.a=AllEdge[j].s;
                newEdge2.b=AllEdge[j].a;

                edge newEdge3;
                newEdge3.s=nowPoint;
                newEdge3.e=AllEdge[j].a;
                newEdge3.a=AllEdge[j].s;
                newEdge3.b=AllEdge[j].e;

                AllEdge.push_back(newEdge1);
                AllEdge.push_back(newEdge2);
                AllEdge.push_back(newEdge3);
                point prevA=AllEdge[j].a;
                printf("found edge ids %d %d %d\n",AllEdge[j].a.point_id,AllEdge[j].s.point_id,AllEdge[j].e.point_id);
                AllEdge[j].a=nowPoint;
                int p=findOtheredge(AllEdge[j].s,prevA);
                printf("found edge ids %d %d %d\n",AllEdge[p].a.point_id,AllEdge[p].s.point_id,AllEdge[p].e.point_id);
                AllEdge[p].a=nowPoint;
                int q=findOtheredge(AllEdge[j].e,prevA);
                AllEdge[q].a=nowPoint;

                LegalizeEdge(nowPoint,AllEdge[j]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,AllEdge[p]);
                printf("-------------------------------------\n");
                LegalizeEdge(nowPoint,AllEdge[q]);
                printf("-------------------------------------\n");

                break;
            }
            else if(AllEdge[j].b.validPoint)
            {


                if(PointInTriangle(nowPoint,AllEdge[j].s,AllEdge[j].e,AllEdge[j].b))
                {
                    printf("---in B side----\n");
                    printf("the point in the triange\n");
                    edge newEdge1;
                    newEdge1.s=nowPoint;
                    newEdge1.e=AllEdge[j].s;
                    newEdge1.a=AllEdge[j].e;
                    newEdge1.b=AllEdge[j].b;
                    //newEdge1.edge_id=i;

                    edge newEdge2;
                    newEdge2.s=nowPoint;
                    newEdge2.e=AllEdge[j].e;
                    newEdge2.a=AllEdge[j].s;
                    newEdge2.b=AllEdge[j].b;

                    edge newEdge3;
                    newEdge3.s=nowPoint;
                    newEdge3.e=AllEdge[j].b;
                    newEdge3.a=AllEdge[j].s;
                    newEdge3.b=AllEdge[j].e;

                    AllEdge.push_back(newEdge1);
                    AllEdge.push_back(newEdge2);
                    AllEdge.push_back(newEdge3);

                    point prevB=AllEdge[j].b;
                    AllEdge[j].b=nowPoint;
                    int p=findOtheredge(AllEdge[j].s,prevB);
                    AllEdge[p].b=nowPoint;
                    int q=findOtheredge(AllEdge[j].e,prevB);
                    AllEdge[q].b=nowPoint;

                    LegalizeEdge(nowPoint,AllEdge[j]);
                    printf("-------------------------------------\n");
                    LegalizeEdge(nowPoint,AllEdge[p]);
                    printf("-------------------------------------\n");
                    LegalizeEdge(nowPoint,AllEdge[q]);
                    printf("-------------------------------------\n");

                    break;
                }
                break;

            }
            if(PointInLine(nowPoint,AllEdge[j].s,AllEdge[j].e))
            {
                printf("point in line\n");
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

