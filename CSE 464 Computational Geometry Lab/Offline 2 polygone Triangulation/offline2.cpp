#include<bits/stdc++.h>
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

using namespace std;

double cameraHeight;
double cameraAngle;
int drawaxes;



struct point
{
    int point_id;
    double x,y;
    int PointType;
};

bool operator <(const point& a, const point& b)
{
    if(a.y!=b.y)
    {
        return  (a.y>b.y);
    }
    else if(a.y==b.y)
    {
        return a.x<b.x;
    }

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

vector<point>allPoints,allPointsSorted;
vector<edge>allEdge,newDrawEgdes;
int number_of_points;
double sweep_line_pos_y;

int helper[10000];




set<edge>BST_edges;

bool operator <(const edge& a, const edge& b)
{
    //printf("compairing for ids %d %d\n",a.edge_id,b.edge_id);
    /*
    point vector_a;
    vector_a.x=a.pb.x-a.pa.x;
    vector_a.y=a.pb.y-a.pa.y;

    point vector_b;
    vector_b.x=b.pb.x-b.pa.x;
    vector_b.y=b.pb.y-b.pa.y;


    double turn=vector_a.x*vector_b.y-vector_b.x*vector_a.y;
    if(turn>0)return false;
    if(turn<0)return true;
    if(turn==0)return false;
        */


    /*
    if(a.edge_id==b.edge_id)return false;
    double x;
    //if((a.pa.y-a.pb.y)==0)return false;
    x=(b.pa.y-a.pa.y)*(a.pa.x-a.pb.x)/(a.pa.y-a.pb.y)+a.pa.x;
    printf("x=%.2lf own=%.2lf\n",x,b.pa.x);
    if(x<b.pa.x)return true;
    else if(x>=b.pa.x)return false;
    else return false;
        */


    //if(a.pa.x<b.pa.x and a.pb.x<b.pb.x)return true;
    //else return false;

    //printf("current pos of sweep line=%.2lf\n",sweep_line_pos_y);
    double current_pos_a_x;
    double current_pos_b_x;
    if((a.pa.y-a.pb.y)!=0)
    {
        current_pos_a_x=(sweep_line_pos_y-a.pa.y)*(a.pa.x-a.pb.x)/(a.pa.y-a.pb.y)+a.pa.x;
    }
    else
    {
        current_pos_a_x=a.pa.x;
    }

    if((b.pa.y-b.pb.y)!=0)
    {
        current_pos_b_x=(sweep_line_pos_y-b.pa.y)*(b.pa.x-b.pb.x)/(b.pa.y-b.pb.y)+b.pa.x;
    }
    else
    {
        current_pos_b_x=b.pa.x;
    }


    //printf("a=%.2lf b=%.2lf\n",current_pos_a_x,current_pos_b_x);

    return current_pos_a_x<current_pos_b_x;

}



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
    for(int i=0; i<number_of_points; i++)
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

void handelStartVertex(point vertex)
{
    //printf("Handeling Start Vertex id=%d %.2lf %.2lf\n",vertex.point_id,vertex.x,vertex.y);
    BST_edges.insert(allEdge[vertex.point_id]);
    helper[allEdge[vertex.point_id].edge_id]=vertex.point_id;


}
void handelEndVertex(point vertex)
{
    //printf("Handeling END Vertex id=%d %.2lf %.2lf\n",vertex.point_id,vertex.x,vertex.y);
    int vertex_id=vertex.point_id;
    int preEdge_id=(vertex_id-1+number_of_points)%number_of_points;
    int helper_prev_Vertex_id=helper[preEdge_id];

    if(allPoints[helper_prev_Vertex_id].PointType==mergeV)
    {
        edge drawEdge;
        drawEdge.pa=vertex;
        drawEdge.pb=allPoints[helper_prev_Vertex_id];
        newDrawEgdes.push_back(drawEdge);
    }

    BST_edges.erase(BST_edges.find(allEdge[preEdge_id]));

}
void handelSplitVertex(point vertex)
{
    //printf("Handeling Split Vertex id=%d %.2lf %.2lf\n",vertex.point_id,vertex.x,vertex.y);
    set<edge>::iterator testit;
    testit=BST_edges.upper_bound(allEdge[vertex.point_id]);
    testit--;
    edge addEdge=(*testit);
    int helper_vertex_id=helper[addEdge.edge_id];

    edge drawEdge;
    drawEdge.pa=vertex;
    drawEdge.pb=allPoints[helper_vertex_id];
    newDrawEgdes.push_back(drawEdge);

    helper[addEdge.edge_id]=vertex.point_id;

    BST_edges.insert(allEdge[vertex.point_id]);
    helper[vertex.point_id]=vertex.point_id;

}
void handelMergeVertex(point vertex)
{
    //printf("Handeling merge Vertex id=%d %.2lf %.2lf\n",vertex.point_id,vertex.x,vertex.y);
    int vertex_id=vertex.point_id;
    int preEdge_id=(vertex_id-1+number_of_points)%number_of_points;
    int helper_prev_Vertex_id=helper[preEdge_id];

    if(allPoints[helper_prev_Vertex_id].PointType==mergeV)
    {
        edge drawPrevEdge;
        drawPrevEdge.pa=vertex;
        drawPrevEdge.pb=allPoints[helper_prev_Vertex_id];
        newDrawEgdes.push_back(drawPrevEdge);
    }

    BST_edges.erase(BST_edges.find(allEdge[preEdge_id]));

    set<edge>::iterator testit;
    testit=BST_edges.upper_bound(allEdge[vertex.point_id]);
    testit--;
    edge addEdge=(*testit);

    int helper_Vertex_id=helper[addEdge.edge_id];

    if(allPoints[helper_Vertex_id].PointType==mergeV)
    {
        edge drawEdge;
        drawEdge.pa=vertex;
        drawEdge.pb=allPoints[helper_Vertex_id];
        newDrawEgdes.push_back(drawEdge);

    }
    helper[addEdge.edge_id]=vertex.point_id;


}
void handelRegularVertex(point vertex)
{
    //printf("Handeling regular Vertex for id=%d %.2lf %.2lf\n",vertex.point_id,vertex.x,vertex.y);
    int prevPos=(vertex.point_id-1+number_of_points)%number_of_points;
    int nextPos=(vertex.point_id+1)%number_of_points;

    if(allPoints[prevPos].y>vertex.y)
    {
        //printf("this is left side point\n");
        int vertex_id=vertex.point_id;
        int preEdge_id=(vertex_id-1+number_of_points)%number_of_points;
        int helper_prev_Vertex_id=helper[preEdge_id];

        //printf("helper id %did=%d %.2lf %.2lf\n",helper_prev_Vertex_id,allPoints[helper_prev_Vertex_id].x,allPoints[helper_prev_Vertex_id].y);

        if(allPoints[helper_prev_Vertex_id].PointType==mergeV)
        {
            edge drawEdge;
            drawEdge.pa=vertex;
            drawEdge.pb=allPoints[helper_prev_Vertex_id];
            newDrawEgdes.push_back(drawEdge);
        }

        BST_edges.erase(BST_edges.find(allEdge[preEdge_id]));

        BST_edges.insert(allEdge[vertex.point_id]);
        helper[allEdge[vertex.point_id].edge_id]=vertex.point_id;


    }
    else
    {
        set<edge>::iterator testit;
        testit=BST_edges.upper_bound(allEdge[vertex.point_id]);
        testit--;
        edge addEdge=(*testit);

        int helper_Vertex_id=helper[addEdge.edge_id];

        if(allPoints[helper_Vertex_id].PointType==mergeV)
        {
            edge drawEdge;
            drawEdge.pa=vertex;
            drawEdge.pb=allPoints[helper_Vertex_id];
            newDrawEgdes.push_back(drawEdge);

        }
        helper[addEdge.edge_id]=vertex.point_id;

    }


}


void makeMonotone()
{
    for(int i=0; i<allPointsSorted.size(); i++)
    {
        sweep_line_pos_y=allPointsSorted[i].y;
        set<edge>::iterator it;
        for(it=BST_edges.begin(); it!=BST_edges.end(); ++it)
        {
            //printf("edge id=%d ax=%.2lf ay=%.2lf bx=%.2lf by=%.2lf\n",(*it).edge_id,(*it).pa.x,(*it).pa.y,(*it).pb.x,(*it).pb.y);
        }
        if(allPointsSorted[i].PointType==startV)
        {
            handelStartVertex(allPointsSorted[i]);
        }
        else if(allPointsSorted[i].PointType==endV)
        {
            handelEndVertex(allPointsSorted[i]);
        }
        else if(allPointsSorted[i].PointType==splitV)
        {
            handelSplitVertex(allPointsSorted[i]);
        }
        else if(allPointsSorted[i].PointType==mergeV)
        {
            handelMergeVertex(allPointsSorted[i]);
        }
        else if(allPointsSorted[i].PointType==regularV)
        {
            handelRegularVertex(allPointsSorted[i]);
        }

        //BST_edges.insert(allEdge[allPointsSorted[i].point_id]);
    }



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

void drawAllLines()
{
    glColor3f(255,0,0);
    for(int i=0; i<allPoints.size(); i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(allPoints[i].x,allPoints[i].y,0);
            glVertex3f(allPoints[(i+1)%number_of_points].x,allPoints[(i+1)%number_of_points].y,0);
        }
        glEnd();
    }
    glColor3f(0,255,0);
    for(int i=0; i<newDrawEgdes.size(); i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(newDrawEgdes[i].pa.x,newDrawEgdes[i].pa.y,0);
            glVertex3f(newDrawEgdes[i].pb.x,newDrawEgdes[i].pb.y,0);
        }
        glEnd();
    }
}

void drawAllPoints()
{
    for(int i=0; i<allPoints.size(); i++)
    {
        glPushMatrix();
        {
            glTranslatef(allPoints[i].x,allPoints[i].y,0);
            drawCircle(.1,20);

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

    //drawAxes();
    //drawGrid();


    glScalef(5,5,5);
    drawAllPoints();
    glColor3f(0,255,0);
    drawAllLines();





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



int main(int argc, char **argv)
{
    //freopen("input11.txt", "r", stdin);
    //freopen("output11.txt", "w", stdout);
    //printf("Enter number of points=");
    scanf("%d",&number_of_points);
    //printf("mod=%d",(-1+number_of_points)%number_of_points);
    for(int i=0; i<number_of_points; i++)
    {
        double x_cordi,y_cordi;
        cin>>x_cordi>>y_cordi;
        point testPoint;
        testPoint.x=x_cordi;
        testPoint.y=y_cordi;
        testPoint.point_id=i;

        allPoints.push_back(testPoint);


    }
    for(int i=0; i<allPoints.size(); i++)  // for making all edges
    {
        edge testEdge;
        testEdge.edge_id=allPoints[i].point_id;
        testEdge.pa=allPoints[i];
        testEdge.pb=allPoints[(i+1)%number_of_points];

        allEdge.push_back(testEdge);


    }

    for(int i=0; i<allPoints.size(); i++) // initization of helper
    {
        helper[allPoints[i].point_id]=allPoints[i].point_id;
    }

    pointsTypeFinding();

    for(int i=0; i<allPoints.size(); i++)
    {
        allPointsSorted.push_back(allPoints[i]);
    }

    sort(allPointsSorted.begin(),allPointsSorted.begin()+number_of_points);

    for(int i=0; i<number_of_points; i++)
    {
        printf("x=%.2lf y=%.2lf ",allPointsSorted[i].x,allPointsSorted[i].y);
        int type=allPointsSorted[i].PointType;
        if(type==1)printf("Start\n");
        else if(type==2)printf("end\n");
        else if(type==3)printf("split\n");
        else if(type==4)printf("merge\n");
        else if(type==5)printf("regular\n");
    }
    makeMonotone();

    printf("\nDiagonals:\n");
    for(int i=0; i<newDrawEgdes.size(); i++)
    {

            printf("%.2lf %.2lf\n",newDrawEgdes[i].pa.x,newDrawEgdes[i].pa.y);
            printf("%.2lf %.2lf\n",newDrawEgdes[i].pb.x,newDrawEgdes[i].pb.y);

            printf("\n");

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
