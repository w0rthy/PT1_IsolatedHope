/*
	Planar Tech 1 2D Engine
	By: Ethan "w0rthy" Pattie
	edpattie@gmail.com
*/
#include "precmp.h"

#include "pt_main.h"
#include "pt_util.h"
#include "pt_textures.h"
#include "pt_net.h"
#include "pt_keyboard.h"
#include "pt_pipe.h"

#include <ctime>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "SOIL.lib")
#pragma comment(lib, "freeglut.lib")

//DEBUG

//FPS CALC VARIABLE INIT
int frames = 0;
int lastFPSSample = 0;
double lastframe = 0.0;

//EXTERNAL VARIABLE INIT
int TICKRATE = 100;
long ticks = 0;
long lastTicks = 0;
int fps = 0;
double FRAMETIME = 0.0;

//FPS LIMITER
bool MAXFPSENABLED = true;
int MAXFPS = 500;
float MAXFPSTHRESH = 0.1f;
int MAXFPSCURDELAY = 0;

//WINDOW VARS INIT
int Width = 640;
int Height = 640;
int DEVWIDTH = 640;
int DEVHEIGHT = 640;

inline double CurTime(){
	return glutGet(GLUT_ELAPSED_TIME)/1000.0;
}

void calcFPS(){
	frames++;
	
	int time = glutGet(GLUT_ELAPSED_TIME);
	int elapsed = time - lastFPSSample;

	if(elapsed>1000){
		fps = (int)(frames / (elapsed/1000.0f));
		lastFPSSample = time;
		frames = 0;

		//FRAME LIMITER
		if(MAXFPSENABLED){
			if(fps > MAXFPS+(int)((float)MAXFPS*MAXFPSTHRESH)){
				MAXFPSCURDELAY++;
			}else if(fps > MAXFPS-(int)((float)MAXFPS*MAXFPSTHRESH));
			else{
				MAXFPSCURDELAY = max(MAXFPSCURDELAY-1,0);
			}
		}
	}

}

void mainLoop(){
	glClear(GL_COLOR_BUFFER_BIT);

	FRAMETIME = ElapsedTime(lastframe);
	lastframe = CurTime();
	//DRAW
	DrawPipeState();
	//END DRAW

	if(MAXFPSENABLED && MAXFPSCURDELAY > 0)
		SleepEx(MAXFPSCURDELAY,false);

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height){
	Width = width;
	Height = height;


	//ticks = getTicks();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,width,height);
	glOrtho(0, width, height, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
	SetKeyDown(key);
	KeyPipeImpulse(key,true,x,y);
	impulseRandomSeed(21);
}

void keyboardUp(unsigned char key, int x, int y){
	SetKeyUp(key);
	KeyPipeImpulse(key,false,x,y);
	impulseRandomSeed(17);
}

void passiveMotion(int x, int y){
	mousex = x;
	mousey = y;
	MouseMotionPipeImpulse(x,y,false);
	impulseRandomSeed(5);
}

void motion(int x, int y){
	mousex = x;
	mousey = y;
	MouseMotionPipeImpulse(x,y,true);
	impulseRandomSeed(3);
}

//State: 0 = down 1 = up
//0 = LMB 1 = MMB 2 = RMB
void mouse(int button, int state, int x, int y){
	MouseButtonPipeImpulse(button,state==0,x,y);
	impulseRandomSeed(13);
}

//wheel = useless
//Direction: 1 = up -1 = down
void mouseWheel(int wheel, int direction, int x, int y){
	MouseWheelPipeImpulse(direction==1,x,y);
	impulseRandomSeed(11);
}

void idle(){
	calcFPS();
	glutPostRedisplay();
}

int main(int argc, char** argv){
	//FreeConsole();

	//GL and GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(Width,Height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("PlanarTech1 Engine");
	
	//GLUT METHOD HOOKING
	glutDisplayFunc(mainLoop);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mouseWheel);

	//BACKGROUND COLOR
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	//2D REINFORCING
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_BITS);
	glDisable(GL_DEPTH);
	glDisable(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_COMPONENT);
	glDisable(GL_DEPTH_SCALE);
	glDisable(GL_DEPTH_BIAS);
	glDisable(GL_LIGHTING);
	glDisable(GL_3D);
	glDisable(GL_3D_COLOR);

	//ALPHA TRANSPARENCY
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//ANTI-ALIASING
	glEnable(GL_FOG);
	glHint(GL_FOG_HINT,GL_FASTEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_FASTEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT,GL_FASTEST);

	//SYSTEMS INIT
	InitTextureSystem();
	InitNetworkLib();
	InitPipeline();

	INITIALIZEGAME();

	glutMainLoop();

	return 0;
}

void EXITPROGRAM(){
	glutExit();
}