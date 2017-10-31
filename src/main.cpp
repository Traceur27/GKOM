#include <GL/gl.h>
#include <GL/glut.h>

#include "PacMan.h"

#define TICKS_PER_SECOND 30

const int TIMER_MILLISECONDS = 1000 / TICKS_PER_SECOND;

GLfloat rotatex = -20.0;
GLfloat rotatey = 0.0;

GLdouble left = -21.0;
GLdouble right = 21.0;
GLdouble bottom = -21.0;
GLdouble top = 21.0;
GLdouble near1 = 1.0;
GLdouble far1 = 41.0;

// Lighting parameters
GLfloat lm_ambient[] = { 0.6, 0.6, 0.6, 1.0 };

PacMan * pacman = new PacMan();
Board * board = new Board();
Ghost * ghost1 = new Ghost();
Ghost * ghost2 = new Ghost();

GLfloat scale = 1.0;
int previousTime;
int currentTime;
int elapsedTime;


//Calling display with constant frame rate
void processAnimationTimer(int value) 
{
	//Setup timer
	glutTimerFunc(TIMER_MILLISECONDS, processAnimationTimer, 0);
	previousTime = currentTime;

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - previousTime;

	//Redraw scene
	glutPostRedisplay();
}


void Display()
{
	previousTime = currentTime;

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - previousTime;

	//Fill in the whole scene
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//Clear depth and color buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Pick modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Move coordinate system to the center
	glTranslatef(0, 0, -21);

	//Rotate the object - use arrow keys
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);
	
	//Scaling the object - "+" and "-"
	glScalef(scale, scale, scale);

	//Changing ambient lightning of the scene - "i" and "k"
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

	board->update();
	ghost1->update();
	ghost2->update();
	pacman->update();
	pacman->drawGUI();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	// Rendering will be processed on the whole window
	glViewport(0, 0, width, height);

	// Pick projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	if (width < height && width > 0)
		glOrtho(left, right, bottom * height / width, top * height / width, near1, far1);
	else
		if (width >= height && height > 0)
			glOrtho(left * width / height, right * width / height, bottom, top, near1, far1);

	Display();
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
		scale += 0.1;
	else if (key == '-' && scale > 0.1)
		scale -= 0.1;
	else if (key == 'a')
		pacman->setDirection(WEST);
	else if (key == 'd')
		pacman->setDirection(EAST);
	else if(key == 'w')
		pacman->setDirection(NORTH);
	else if(key == 's')
		pacman->setDirection(SOUTH);
	else if (key == 'm')
	{
		if (glIsEnabled(GL_FOG))
		{
			glDisable(GL_FOG);
		}
		else
		{
			glEnable(GL_FOG);
			glFogf(GL_FOG_DENSITY, 0.05);
		}
	}
	else if (key == 'i')
	{
		lm_ambient[0] += 0.1;
		lm_ambient[1] += 0.1;
		lm_ambient[2] += 0.1;
		if (lm_ambient[0] > 1)
		{
			lm_ambient[0] = 1;
			lm_ambient[1] = 1;
			lm_ambient[2] = 1;
		}
	}
	else if (key == 'k')
	{
		lm_ambient[0] -= 0.1;
		lm_ambient[1] -= 0.1;
		lm_ambient[2] -= 0.1;
		if (lm_ambient[0] < 0)
		{
			lm_ambient[0] = 0;
			lm_ambient[1] = 0;
			lm_ambient[2] = 0;
		}
	}
}


void KeyboardUp(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'd' || key == 'w' || key == 's')
		pacman->setDirection(NONE);
}


void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}
}


void init()
{
	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 }; 

	board->init();
	pacman->setBoard(board);
	ghost1->setRoute1();
	ghost2->setRoute2();
	pacman->setGhost(ghost1);
	pacman->setGhost(ghost2);
	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int main(int argc, char** argv)
{
   glutInit( &argc, argv );

   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

   glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) - 600)/2, (glutGet(GLUT_SCREEN_HEIGHT) - 600 )/2 );
   glutInitWindowSize( 600, 600 );

   glutCreateWindow( "Pac-Man" );

   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);

   //Add keyboard handling
   glutKeyboardFunc(Keyboard);
   glutKeyboardUpFunc(KeyboardUp);
   glutSpecialFunc(SpecialKeys);

   init();

   glutTimerFunc(TIMER_MILLISECONDS, processAnimationTimer, 0);
   //Time elapsed since calling glutInit
   currentTime = glutGet(GLUT_ELAPSED_TIME);

   glutMainLoop();

   return 0;
}
