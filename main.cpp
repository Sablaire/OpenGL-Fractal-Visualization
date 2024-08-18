
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib,"glaux.lib")
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <iostream>
#include <complex>
#include "gl/glut.h"
const  int W = 512;
const  int H = 512;
GLubyte data[W][H][3] = {0};
using namespace std; 
float color[255];
float minCoordFract=-2.0;  
float maxCoordFract=2.0;
float EscapeAreaRadius=2.0; 
int MaxIterNumber = 20;  
int IterCounter = 0;  
double PixelSize=( maxCoordFract - minCoordFract)/ W; 
void Init(void) { 
 for (int help = 0; help < 255; help++) color[help] = 0.0;
 glClearColor (0.0, 0.0, 0.0, 0.0);
    for( int y = 0; y < W; y++ ) {
        for( int x = 0; x < H; x++ ) {
			double Xnew=minCoordFract+PixelSize*x;
			double Ynew=minCoordFract+PixelSize*y;
			complex<double> c(Xnew,Ynew); 
			complex<double> z(0, 0); 
			IterCounter = 0; 
			loop1:
			z = z * z + c;
			IterCounter++;
			if(abs(z*z)<EscapeAreaRadius && IterCounter<MaxIterNumber){ goto loop1;	}
			else {
			if(IterCounter<MaxIterNumber/10.5) {
				data[y][x][0] = 125; 
				data[y][x][1] = 125; 
				data[y][x][2] = 125; 	}
			else if (IterCounter<MaxIterNumber/9.5) {
				data[y][x][0] = 255; 
				data[y][x][1] = 0; 
				data[y][x][2] = 0;  }
			else if (IterCounter<MaxIterNumber/6.5) {
				data[y][x][0] = 255; 
				data[y][x][1] = 0; 
				data[y][x][2] = 255;	}
			else if (IterCounter<MaxIterNumber/2) {
				data[y][x][0] = 255; 
				data[y][x][1] = 255; 
				data[y][x][2] = 0; }
			else if (IterCounter<MaxIterNumber)  {
				data[y][x][0] = 0; 
				data[y][x][1] = 255; 
				data[y][x][2] = 255;	}
			else	{
				data[y][x][0] = 0; 
				data[y][x][1] = 0; 
				data[y][x][2] = 0; }	}
        }
    }
	 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	 glPixelStorei(GL_UNPACK_ROW_LENGTH, W); 
	 glPixelStorei(GL_UNPACK_SKIP_ROWS, 0); 
	 glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0); 
}
 void Reshape(int w, int h)  {
	 glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluOrtho2D(-w/2., w/2., -h/2., h/2.);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity(); }
 
 void Draw(void)  {
	 glClear(GL_COLOR_BUFFER_BIT);
	 glRasterPos2i(-256, -256);
	 glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, data);
	 glutSwapBuffers();  }
 
 int main(int argc, char** argv)  {
	 glutInit(&argc, argv);
	 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	 glutInitWindowSize(512, 512);
	 glutInitWindowPosition(100, 100);
	 glutCreateWindow("Sem 14");
	 Init();
	 glutDisplayFunc(Draw);
	 glutReshapeFunc(Reshape);
	 glutMainLoop();
	 return 0;  }
