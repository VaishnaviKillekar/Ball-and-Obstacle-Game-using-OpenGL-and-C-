// Save the Ball
// Author: Vaishnavi Killekar
// Date: April 2018

#include <stdio.h>
#include <gl/glut.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

GLfloat rotation = 90.0;
float pos1X = -1, pos1Y = 0, pos1Z = 0, pos2X = +1, pos2Y = 0, pos2Z = 0, posBallx=-0.9, posBally=0.0, posBallz=0.1;
float ob1x=0.2, ob1y=0.6, ob2x=-0.4, ob2y=0.3, ob3x=-0.5, ob3y=-0.7, ob4x=0.6, ob4y=-0.1;
int flag=0, ob_flag=0, ob_flag1=0, ob_flag2=0, ob_flag3=0;
void *currentfont;
int dis_flag_start=0, dis_flag_inst=0, dis_game_end=0, win=0, stop=0;

void start()
{
    // Start line
    glPushMatrix();
    glTranslatef(pos1X, pos1Y, pos1Z);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.05, -1);
    glVertex2f(-0.05, 1);
    glVertex2f(0.05, 1);
    glVertex2f(0.05, -1);
    glEnd();
    glPopMatrix();
}

void finish()
{
    //Finish line
    glPushMatrix();
    glTranslatef(pos2X, pos2Y, pos2Z);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.05, 1);
    glVertex2f(0.05, -1);
    glVertex2f(-0.05, -1);
    glVertex2f(-0.05, 1);
    glEnd();
    glPopMatrix();
}

class button
{
	int x1,y1,x2,y2;
	int state;
	char str[10];

    public:
            button()
            {

            }
            button(int x11,int y11,int x22,int y22,char *str1)
            {
                x1=x11;
                y1=y11;
                x2=x22;
                y2=y22;
                state=1;
                strcpy(str,str1);
            }
	void draw();
	void togglestate();
	int insidebutton(int x, int y);
};

void setFont(void *font)
{
	currentfont=font;
}

void drawstring(float x,float y,char *string)
{
    char *c;
	glRasterPos2f(x,y);

	for(c=string;*c!='\0';c++)
	{	glColor3f(1.0,1.0,1.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void button::draw()
{
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(1.0,1.0,1.0);
	drawstring(x1+10,y1+10,str);

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x1,y1);
	glVertex2f(x2,y1);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glEnd();
	if(state==0)
	{
        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glEnd();
	}
	else if(state==1)
	{
		glColor3f(0,0,0);
		glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x1,y2);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glEnd();
	}
}

void button::togglestate(void)
{
	state=(state==1)?0:1;
}

int button::insidebutton(int x,int y)
{
	if(x>x1&&x<x2&&y>y1&&y<y2)
		return 1;
	else return 0;
}


button startGame(250, 400, 400, 450, "Start Game");
button instructions(250, 360, 400, 410, "Instructions");
button exitGame(250, 320, 400, 370, "Exit Game");
button backBtn(250, 140, 400, 190, "BACK");
button playAgain(250, 360, 400, 190, "PLAY AGAIN");
button quit(250, 320, 400, 150, "QUIT");

void text(char *menu, int x, int y)
{
    int len;
    len = strlen(menu);

    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D( 0, 600, 0, 600 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

    glLoadIdentity();

    glRasterPos2i(x, y);


    for ( int i = 0; i < len; ++i )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menu[i]);
    }

    glPopMatrix();

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
}


void ball()
{
    if(posBallx>=0.9)
    {
        dis_game_end=1;
        win=1;
        dis_flag_inst=0;
        dis_flag_start=0;
        stop=1;
    }
    else if(posBallx<=-0.9)
        posBallx=-0.9;
    else if(posBally>=1)
        posBally=0.9;
    else if(posBally<=-1)
        posBally=-0.9;
    else if(sqrt(pow(posBallx-ob1x, 2)+pow(posBally-ob1y, 2))-0.25 <= 0)
    {
        win=0;
        stop=1;
        dis_game_end=1;
        dis_flag_inst=0;
        dis_flag_start=0;
    }
    else if(sqrt(pow(posBallx-ob2x, 2)+pow(posBally-ob2y, 2))-0.25 <= 0)
    {
        win=0;
        stop=1;
        dis_game_end=1;
        dis_flag_inst=0;
        dis_flag_start=0;
    }
    else if(sqrt(pow(posBallx-ob3x, 2)+pow(posBally-ob3y, 2))-0.25 <= 0)
    {
        win=0;
        stop=1;
        dis_game_end=1;
        dis_flag_inst=0;
        dis_flag_start=0;
    }
    else if(sqrt(pow(posBallx-ob4x, 2)+pow(posBally-ob4y, 2))-0.25 <= 0)
    {
        win=0;
        stop=1;
        dis_game_end=1;
        dis_flag_inst=0;
        dis_flag_start=0;
    }

    glPushMatrix();
    glTranslatef(posBallx, posBally, posBallz);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.05, 100, 10);
    glPopMatrix();
}

void obstacles()
{
    glPushMatrix();
    glTranslatef(ob1x, ob1y, 0.0);
    glColor3f(0.5, 1.0, 0.8);
    glutSolidSphere(0.2, 100, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ob2x, ob2y, 0.0);
    glColor3f(1.0, 0.5, 0.5);
    glutSolidSphere(0.2, 100, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ob3x, ob3y, 0.0);
    glColor3f(0.5, 1.0, 0.5);
    glutSolidSphere(0.2, 100, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ob4x, ob4y, 0.0);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.2, 100, 10);
    glPopMatrix();
}

void display()
{
	glClearColor(0,0,0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(dis_flag_start==0 && dis_flag_inst==0 && dis_game_end==0)
    {
        text("SAVE THE BALL", 235, 520);
        startGame.draw();
        instructions.draw();
        exitGame.draw();
        text("Start Game", 260, 410);
        text("Instructions", 260, 370);
        text("Exit Game", 260, 330);
    }
    if(dis_flag_inst==1 && dis_flag_start==0 && dis_game_end==0)
    {
        text("INSTRUCTIONS:", 235, 520);
        text("1. The ball needs to be taken from the Start line to the Finish line.", 50, 460);
        text("2. All the obstacles must be avoided by the ball or you lose.", 50, 420);
        text("3. To make the game interesting the controls have been reversed: ", 50, 380);
        text(" - Top Arrow key -> Ball moves Down", 70, 340);
        text(" - Down Arrow key -> Ball moves Up", 70, 300);
        text(" - Left Arrow key -> Ball moves Right", 70, 260);
        text(" - Right Arrow key -> Ball moves Left", 70, 220);
        backBtn.draw();
        text("BACK", 260, 150);
    }

    if(dis_flag_start==1 && dis_flag_inst==0 && dis_game_end==0)
    {
        glLoadIdentity();
        ball();                 // Draws ball
        text("SAVE THE BALL", 250, 570);
        start();                // Draws start line
        text("START", 19, 5);
        finish();               //Draws finish line
        text("FINISH", 505, 5);
        obstacles();            // Draws obstacles
    }

    if(dis_game_end==1 && dis_flag_start==0 && dis_flag_inst==0)
    {
        if(win==1)
        {
            text("You WIN! :)", 235, 400);
            //playAgain.draw();
            //text("Play Again", 260, 360);
            quit.draw();
            text("Quit", 260, 320);
        }
        else
        {
            text("You LOSE! :(", 235, 400);
            //playAgain.draw();
            //text("Play Again", 260, 360);
            quit.draw();
            text("Quit", 260, 320);
        }
    }

    glFlush();
    glutSwapBuffers();
    //glutPostRedisplay();
}


void reshape(int width, int heigth)
{
    /* window ro reshape when made it bigger or smaller*/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //clip the windows so its shortest side is 2.0
    if (width < heigth)
    {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)heigth / (GLfloat)width, 2.0 * (GLfloat)heigth / (GLfloat)width, 2.0, 2.0);
    }
    else{
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)width / (GLfloat)heigth, 2.0 * (GLfloat)width / (GLfloat)heigth,2.0 , 2.0);
    }
    // set viewport to use the entire new window
    glViewport(0, 0, width, heigth);
}


void init()
{
    // set clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // set fill color to white
    glColor3f(1.0, 1.0, 1.0);

    //set up standard orthogonal view with clipping
    //box as cube of side 2 centered at origin
    //This is the default view and these statements could be removed
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

}

float move_unit = 0.1f;
void keyboardown(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:   posBally-=move_unit;
                            break;

        case GLUT_KEY_DOWN: posBally+=move_unit;
                            break;

        case GLUT_KEY_LEFT: posBallx+=move_unit;
                            break;

        case GLUT_KEY_RIGHT: posBallx-=move_unit;
                             break;
    }
    glutPostRedisplay();
}

void update(int value)
{

    if(posBallx>-0.95 && stop==0)
    {
       posBallx -= 0.003f;
    }

    if(!ob_flag)
    {
        if(sqrt(pow(posBallx-ob1x, 2)+pow(posBally-ob1y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
        ob1y-=0.01f;
        if(ob1y<-0.2)
            ob_flag=1;
    }
    else
    {
        if(sqrt(pow(posBallx-ob1x, 2)+pow(posBally-ob1y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
        ob1y+=0.01f;
        if(ob1y>0.7)
            ob_flag=0;
    }

    if(!ob_flag1)
    {
        if(sqrt(pow(posBallx-ob2x, 2)+pow(posBally-ob2y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
        ob2x-=0.01f;
        if(ob2x<-0.7)
            ob_flag1=1;
    }
    else
    {
        if(sqrt(pow(posBallx-ob2x, 2)+pow(posBally-ob2y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
        ob2x+=0.01f;
        if(ob2x>-0.3)
            ob_flag1=0;
    }

    if(!ob_flag2)
    {
        if(sqrt(pow(posBallx-ob3x, 2)+pow(posBally-ob3y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
       ob3x-=0.05f;
       if(ob3x<-0.7)
            ob_flag2=1;
    }
    else
    {
        if(sqrt(pow(posBallx-ob3x, 2)+pow(posBally-ob3y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
        ob3x+=0.05f;
        if(ob3x>0.7)
            ob_flag2=0;
    }

    if(!ob_flag3)
    {
        if(sqrt(pow(posBallx-ob4x, 2)+pow(posBally-ob4y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
        ob4y+=0.01f;
        if(ob4y>0.7)
            ob_flag3=1;
    }
    else
    {
        if(sqrt(pow(posBallx-ob4x, 2)+pow(posBally-ob4y, 2))-0.25 <= 0)
        {
            win=0;
            dis_game_end=1;
            dis_flag_inst=0;
            dis_flag_start=0;
        }
        ob4y-=0.01f;
        if(ob4y<-0.2)
            ob_flag3=0;
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(15, update, 0);
}

void mouse(int btn, int state, int x, int y)
{
	y=600-y;

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
        if(startGame.insidebutton(x,y))
        {
            dis_flag_start=1;
            dis_flag_inst=0;
            dis_game_end=0;
        }
        if(instructions.insidebutton(x,y))
        {
            dis_flag_inst=1;
            dis_flag_start=0;
            dis_game_end=0;
        }
        if(backBtn.insidebutton(x,y))
        {
            dis_flag_start=0;
            dis_flag_inst=0;
            dis_game_end=0;
        }
        if(exitGame.insidebutton(x,y))
        {
            exit(0);
        }
        if(playAgain.insidebutton(x,y))
        {
            dis_game_end=0;
            win=0;
            stop=0;
            dis_flag_inst=0;
            dis_flag_start=1;
            posBallx=-0.9;
            posBally=0.0;
        }
        if(quit.insidebutton(x,y))
        {
            exit(0);
        }
	}
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if(startGame.insidebutton(x,y))
        {
            startGame.togglestate();
        }
		if(instructions.insidebutton(x,y))
        {
            instructions.togglestate();
        }
		if(backBtn.insidebutton(x,y))
        {
            backBtn.togglestate();
        }
		if(exitGame.insidebutton(x,y))
        {
            exitGame.togglestate();
        }
        if(playAgain.insidebutton(x,y))
        {
            playAgain.togglestate();
        }
        if(quit.insidebutton(x,y))
        {
            quit.togglestate();
        }
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Save the Ball");
    glutDisplayFunc(display);
    init();
    glutSpecialFunc(keyboardown);
    glutTimerFunc(25, update, 0);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}
