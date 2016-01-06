#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include "PacMan.h"
#include "Board.h"
#include <iostream>
#include "Ghost.h"


GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

//const GLdouble left = -10.0;
//const GLdouble right = 10.0;
//const GLdouble bottom = -10.0;
//const GLdouble top = 10.0;
//const GLdouble near1 = 1.0;
//const GLdouble far1 = 5.0;

GLdouble left = -21.0;
GLdouble right = 21.0;
GLdouble bottom = -21.0;
GLdouble top = 21.0;
GLdouble near1 = 1.0;
GLdouble far1 = 41.0;

GLfloat lm_ambient[] = { 0.2, 0.2, 0.2, 1.0 };//0.2 0.2 0.2

GLfloat scale = 1.0;
PacMan * pacman = new PacMan();
Board * board = new Board();
Ghost * ghost1 = new Ghost();
Ghost * ghost2 = new Ghost();


void Display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//Clear the color buffer and z buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW); //- potrzebne przy rysowaniu primitywuw
	glLoadIdentity();
	// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
	//glTranslatef(0, 0, -(far1 + near1) / 2);

	//std::cout << "x: " << rotatex << "y: " << rotatey << "scale: " << scale << std::endl;

	glTranslatef(0, 0, -21);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	//glRotatef(-6, 1.0, 0, 0);
	
	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);
	//glScalef(0.5, 0.5, 0.5);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

	board->update();
	ghost1->update();
	ghost2->update();
	pacman->update();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();


	if (width < height && width > 0)
		glFrustum(left, right, bottom * height / width, top * height / width, near1, far1);
	else

		// szerokoœæ okna wiêksza lub równa wysokoœci okna
		if (width >= height && height > 0)
			glOrtho(left * width / height, right * width / height, bottom, top, near1, far1);

	//glMatrixMode(GL_MODELVIEW);
	Display();
}


void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
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

	// odrysowanie okna
	//Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
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
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

		// kursor w górê
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

		// kursor w dó³
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	// odrysowanie okna
	//Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void init()
{
	GLfloat light_position[] = { 0.0, 0.0, 20.0, 1.0 }; 

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
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
	glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv)
{
   glutInit( &argc, argv );

   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

   //Draw the window in the middle of the screen
   glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH) - 600)/2, (glutGet(GLUT_SCREEN_HEIGHT) - 600 )/2 );
   glutInitWindowSize( 600, 600 );

   glutCreateWindow( "Pac-Man" );

   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutIdleFunc(Display);

   // do³¹czenie funkcji obs³ugi klawiatury
   glutKeyboardFunc(Keyboard);
   glutKeyboardUpFunc(KeyboardUp);
   // do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
   glutSpecialFunc(SpecialKeys);

   init();



   glutMainLoop();

   return 0;
}


/*
Oswietlenie:
- glEnable GL_LIGHTING, GL_LIGHT0 i bufor g³êbokoœci
- glLightfv( GL_LIGHT0, GL_POSITION, light_position ); lightPosition 4 wartosci
- zmiana parametrow swiatla przy uzycie GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR
- ustawienie modelu oswietlenia glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient ); mozliwe ze tez GL_LIGHT_MODEL_COLOR_CONTROL - do tekstur
- ustawienie materialow glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
- trzeba zdefiniowacwektory normalne void glNormal3fv( const GLfloat * v )




*/