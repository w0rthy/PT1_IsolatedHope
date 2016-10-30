#pragma once

#define MAX_STATES 10

struct PipeState {
	void (*initfunc)();
	void (*stopfunc)();
	void (*drawfunc)();

	PipeState(void(*init)(),void(*stop)(),void(*draw)()){
		initfunc = init;
		stopfunc = stop;
		drawfunc = draw;
	}
};

struct PipeInput {
	void (*keyfunc)(char,bool,int,int);
	void (*mmovefunc)(int,int,bool);
	void (*mbtnfunc)(int,bool,int,int);
	void (*mwhlfunc)(bool,int,int);

	PipeInput(void(*key)(char,bool,int,int),void(*mmove)(int,int,bool),void(*mbtn)(int,bool,int,int),void(*mwhl)(bool,int,int)){
		keyfunc = key;
		mmovefunc = mmove;
		mbtnfunc = mbtn;
		mwhlfunc = mwhl;
	}
};

void InitPipeline();

void ChangeState(char state);

void RegisterState(PipeState* state, PipeInput* input, char index);
void RegisterState(PipeState* state, char index);


void DrawPipeState();
void KeyPipeImpulse(char key, bool down, int x, int y);
void MouseMotionPipeImpulse(int x, int y, bool drag);
void MouseButtonPipeImpulse(int button, bool down, int x, int y);
void MouseWheelPipeImpulse(bool fwd, int x, int y);