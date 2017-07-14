#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include <windows.h>
#include <glut.h>

#include<vector>

#define pi (2*acos(0.0))

using namespace std;

double cameraHeight;
double cameraAngle;

int drawaxes;



struct point
{
    double x,y;
};

vector<point*> *FinalQuickHull=new vector<point*>();
vector<point*> *setOfPoints=new vector<point*>();







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

void drawQuickHull()
{
    glColor3f(255,0,0);
    for(int i=0;i<FinalQuickHull->size()-1;i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(FinalQuickHull->at(i)->x,FinalQuickHull->at(i)->y,0);
            glVertex3f(FinalQuickHull->at(i+1)->x,FinalQuickHull->at(i+1)->y,0);
        }
        glEnd();
    }
}

void drawAllPoints()
{
    for(int i=0;i<setOfPoints->size();i++)
    {
        glPushMatrix();
        {
            glTranslatef(setOfPoints->at(i)->x,setOfPoints->at(i)->y,0);
            drawCircle(1,20);

        }
        glPopMatrix();


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
    //drawGrid();



    drawAllPoints();
    glColor3f(0,255,0);
    drawQuickHull();





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

int checkleftORRight(point* a,point* b,point* c)
{
    point* vector_ab=new point();
    vector_ab->x=b->x-a->x;
    vector_ab->y=b->y-a->y;

    point* vector_ac=new point();

    vector_ac->x=c->x-a->x;
    vector_ac->y=c->y-a->y;

    double turn=vector_ac->x*vector_ab->y-vector_ab->x*vector_ac->y;
    if(turn>0)return 1;
    if(turn<0)return -1;
    if(turn==0)return 0;
}

double area_of_triangel(point* a, point* b,point*c)
{
    double area=a->x*b->y+b->x*c->y+c->x*a->y-(a->y*b->x+b->y*c->x+c->y*a->x);
    if(area<0)area=area*-1;
    return area;
}

void QuickHull(point* a, point* b,vector<point*> *S)
{
    if(S->size()==0)return;
    point* c=new point();
    double maxarea=0;
    for(int i=0;i<S->size();i++)
    {
        if(area_of_triangel(a,b,S->at(i))>maxarea)
        {
            maxarea=area_of_triangel(a,b,S->at(i));
            c->x=S->at(i)->x;
            c->y=S->at(i)->y;
        }
    }

    vector<point*> *A=new vector<point*>();
    vector<point*> *B=new vector<point*>();
    for(int i=0;i<S->size();i++)
    {
        //printf("%.2lf %.2lf ",setOfPoints->at(i)->x,setOfPoints->at(i)->y);
        double testturnOfac=checkleftORRight(a,c,S->at(i));
        double testturnOfcb=checkleftORRight(c,b,S->at(i));
        if(testturnOfac==1)
        {
            A->push_back(S->at(i));
            //printf("right\n");
        }

        if(testturnOfcb==1)
        {
            B->push_back(S->at(i));
        }
    }

    QuickHull(a,c,A);
    printf("%.2lf  %.2lf\n",c->x,c->y);
    FinalQuickHull->push_back(c);
    QuickHull(c,b,B);



}

int main(int argc, char **argv)
{
    srand (time(NULL));

    //freopen("input.txt", "r", stdin);


    int fromFileOrRandomInput=0;
    int n;



    point* leftmostandtopmostpoint=new point();
    leftmostandtopmostpoint->x=100000;
    leftmostandtopmostpoint->y=-100000;


    point* RightMostandDownMost=new point();
    RightMostandDownMost->x=-100000;
    RightMostandDownMost->y=1000000;

    scanf("%d",&n);

    for(int s=0;s<n;s++)
    {
        int q,w;
        double xx,yy;
        q=rand()%100-50;
        w=rand()%100-50;

        point* p=new point();

        if(fromFileOrRandomInput==0)
        {
            p->x=q;
            p->y=w;
        }
        else if(fromFileOrRandomInput==1)
        {
            scanf("%lf %lf",&xx,&yy);
            p->x=xx;
            p->y=yy;
        }

        setOfPoints->push_back(p);

        if(p->x<=leftmostandtopmostpoint->x)
        {

            if(p->x==leftmostandtopmostpoint->x and p->y>leftmostandtopmostpoint->y)
            {
                leftmostandtopmostpoint->x=p->x;
                leftmostandtopmostpoint->y=p->y;
            }
            else if(p->x<leftmostandtopmostpoint->x)
            {
                leftmostandtopmostpoint->x=p->x;
                leftmostandtopmostpoint->y=p->y;
            }

        }

        if(p->x>=RightMostandDownMost->x)
        {

            if(p->x==RightMostandDownMost->x and p->y<RightMostandDownMost->y)
            {
                RightMostandDownMost->x=p->x;
                RightMostandDownMost->y=p->y;
            }
            else if(p->x>RightMostandDownMost->x)
            {
                RightMostandDownMost->x=p->x;
                RightMostandDownMost->y=p->y;
            }

        }

    }

    printf("left most point=%.2lf %.2lf rightmost=%.2lf %.2lf\n",leftmostandtopmostpoint->x,leftmostandtopmostpoint->y,RightMostandDownMost->x,RightMostandDownMost->y);


    vector<point*> *A=new vector<point*>();
    vector<point*> *B=new vector<point*>();
    for(int i=0;i<setOfPoints->size();i++)
    {
        //printf("%.2lf %.2lf ",setOfPoints->at(i)->x,setOfPoints->at(i)->y);
        double testturn=checkleftORRight(RightMostandDownMost,leftmostandtopmostpoint,setOfPoints->at(i));
        if(testturn==1)
        {
            A->push_back(setOfPoints->at(i));
            //printf("right\n");
        }

        else if(testturn==-1)
        {
            B->push_back(setOfPoints->at(i));
            //printf("left\n");
        }
        else if(testturn==0)
        {
            //printf("coliner\n");
        }
    }
    FinalQuickHull->push_back(RightMostandDownMost);
    printf("%.2lf  %.2lf\n",RightMostandDownMost->x,RightMostandDownMost->y);
    QuickHull(RightMostandDownMost,leftmostandtopmostpoint,A);
    FinalQuickHull->push_back(leftmostandtopmostpoint);
    printf("%.2lf  %.2lf\n",leftmostandtopmostpoint->x,leftmostandtopmostpoint->y);
    printf("---------------\n");
    QuickHull(leftmostandtopmostpoint,RightMostandDownMost,B);
    printf("%.2lf  %.2lf\n",RightMostandDownMost->x,RightMostandDownMost->y);
    FinalQuickHull->push_back(RightMostandDownMost);
    double totalLengthOfConvexHull=0;
    for(int i=0;i<FinalQuickHull->size()-1;i++)
    {

            totalLengthOfConvexHull=totalLengthOfConvexHull+sqrt((FinalQuickHull->at(i+1)->x-FinalQuickHull->at(i)->x)*(FinalQuickHull->at(i+1)->x-FinalQuickHull->at(i)->x)+(FinalQuickHull->at(i)->y-FinalQuickHull->at(i+1)->y)*(FinalQuickHull->at(i)->y-FinalQuickHull->at(i+1)->y));

    }
    printf("%.2lf\n",totalLengthOfConvexHull);













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
