/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#include "matrix.h"
#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>
#include <cmath>
#include "adjL.h"
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <Enemies.h>

#include <wall.h>
#include <math.h>
#include <cstdlib>

/* GLUT callback Handlers */

using namespace std;
//WALL RUN-IN
bool wallCheck(Player *p, int direc,matrix<bool> grid){
            int a = p->getPlayerLoc().x;
            int b = p->getPlayerLoc().y;
            float dif = 0;
            float holder = 0;
            float var = 0;
    switch(direc){
        case GLUT_KEY_UP:
            if((a)>=0 && b+1<15){ //Checks the bounds to make sure still in maze
            if(grid.getVal(a,b+1)){ //checks the boolean grid to see if there  is a wall ahead
                var = p->getPlayerLocForC("up").y;//assigns the float-type coordinate ***offset can be adjusted***
                holder = b;                         //assigns the y value as a float
                dif = holder - var;            //this is the value of distance between player and wall
                cout << "dif value: "<<dif<< endl;
                if (abs(dif) <.1) return true; //If close enough to wall STOP
               }
            }
        case GLUT_KEY_DOWN:
            if ((b-1)<15 && (b-1)>=0){
                if(grid.getVal(a,b-1)){
                    var = p->getPlayerLocForC("down").y;
                    holder = b;
                    dif = var - holder;
                    cout << "dif value: "<<dif<< endl;
                    if (dif <.2) return true;
                }
            }
        case GLUT_KEY_LEFT:
            if ((a-1)<15 && (a-1)>=0){
                if (grid.getVal(a-1,b)){
                    var = p->getPlayerLocForC("left").x;
                    holder = a;
                    dif = var - holder;
                    cout << "dif value: "<<dif<< endl;
                    if (dif <.01) return true;
                }
            }
        case GLUT_KEY_RIGHT:
            if ((a+1)<15 && (a+1)>=0)
                if(grid.getVal(a+1,b)){
                    var = p->getPlayerLocForC("right").x;
                    holder = a;
                    dif = holder - var;
                    cout << "dif value: "<<dif<< endl;
                    if (dif <.01) return true;
                }
        }

}




//WALL RUN-IN

//Maze Graph
Maze *M = new Maze(15);                         // Set Maze grid size
Player *P = new Player();                       // create player
//MATRIX FOR WALL CHECK
matrix<bool> wallGrid(15);
wall W[110];
//wall W2[100];                                    // wall with number of bricks
Enemies E[10];                                  // create number of enemies

Timer *T0 = new Timer();                        // animation timer

float wWidth, wHeight;                          // display window width and Height
float xPos,yPos;                                // Viewpoar mapping


void display(void);                             // Main Display : this runs in a loop

void resize(int width, int height)              // resizing case on the window
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void init()
{
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();                                        // set timer to 0

    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    M->loadBackgroundImage("images/bak.jpg");           // Load maze background image
    M->loadChestImage("images/chest.png");              // load chest image
    M->placeChest(3,3);                                 // place chest in a grid

    M->loadSetOfArrowsImage("images/arrwset.png");      // load set of arrows image
    M->placeStArrws(5,3);                               // place set of arrows

    P->initPlayer(M->getGridSize(),6,"images/p.png");//10   // initialize player pass grid size,image and number of frames
    P->loadArrowImage("images/arr.png");                // Load arrow image
    P->placePlayer(0,1);                                // Place player


    //load maze
int x = 0, y = 0, i = 0;
fstream maz ("mz1.txt");

while (maz&&i<110){
        cout << "file open\n";
    maz >> x >> y;
    i++;

    W[i].wallInit(M->getGridSize(),"images/wall.png");
    W[i].placeWall(x,y);

    wallGrid.insert(x,y,true);
    //cout << "inserting: " <<"("<< x <<","<< y <<")" <<"index at: " <<i<<endl;
//if (maz.eof()) break;
}



    for(int i=0; i<10;i++)
    {
        E[i].initEnm(M->getGridSize(),4,"images/e.png"); //Load enemy image
        E[i].placeEnemy(float(rand()%(M->getGridSize())),float(rand()%(M->getGridSize())));
        //place enemies random x,y
    }
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();
        glPopMatrix();


        for(int i=0; i<110/*M->getGridSize()*/;i++)
        {
           W[i].drawWall();
        }

        glPushMatrix();
            M->drawGrid();
        glPopMatrix();

        glPushMatrix();
            P->drawplayer();
        glPopMatrix();

        for(int i=0; i<10;i++)
        {
        E[i].drawEnemy();
        }

        glPushMatrix();
            P->drawArrow();
        glPopMatrix();

         glPushMatrix();
           M->drawChest();
        glPopMatrix();

        glPushMatrix();
           M->drawArrows();
        glPopMatrix();

    glutSwapBuffers();
}




void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
          // if(!M->liveSetOfArrws)      // if setof arrows were picked by player
             P->shootArrow();
        break;
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}


 void GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    xPos =posX ;
    yPos =posY ;
}

 void idle(void)
{

    //Your Code here

    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
            }
            break;


      case GLUT_RIGHT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
            }
            break;
    }
     glutPostRedisplay();
};

void Specialkeys(int key, int x, int y)
{

    // Your Code here
    switch(key)
    {
    case GLUT_KEY_UP:
         cout<< P->getPlayerLoc().x<<"     "<<P->getPlayerLoc().y<<endl;
         if (!wallCheck(P,GLUT_KEY_UP,wallGrid)){
            P->movePlayer("up");
         E[0].moveEnemy("up");
         E[1].moveEnemy("left");
         E[2].moveEnemy("up");
         }
    break;

    case GLUT_KEY_DOWN:
         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         if(!wallCheck(P,GLUT_KEY_DOWN,wallGrid)) {
         P->movePlayer("down");
         E[0].moveEnemy("down");
         E[1].moveEnemy("down");
         E[2].moveEnemy("down");
         }
    break;

    case GLUT_KEY_LEFT:
         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         if (!wallCheck(P,GLUT_KEY_LEFT,wallGrid)){
         P->movePlayer("left");
         //wallCheck(P,W);
         E[0].moveEnemy("left");
         E[1].moveEnemy("left");
         E[2].moveEnemy("left");
         }

    break;

    case GLUT_KEY_RIGHT:
         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         if (!wallCheck(P,GLUT_KEY_RIGHT,wallGrid)){
            P->movePlayer("right");
         //wallCheck(P,W);
         E[0].moveEnemy("right");
         E[1].moveEnemy("right");
         E[2].moveEnemy("right");
         }

    break;

   }
  glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init();

   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

   return EXIT_SUCCESS;
}
