/*
	Planar Tech 1 Rendering Pipeline
*/

#include "pt_main.h"
#include "pt_pipe.h"

PipeState* states[MAX_STATES];
PipeInput* inputs[MAX_STATES];
char curstate = 0;

//preps pipe state values
void InitPipeline(){
	for(int i = 0; i < MAX_STATES; i++){
		states[i] = nullptr;
		inputs[i] = nullptr;
	}
}

//Changes active pipe
void ChangeState(char state){
	if(states[state] == nullptr)
		return;

	states[curstate]->stopfunc();
	curstate = state;
	states[curstate]->initfunc();
}

//Registers a new pipe state for use with ChangeState
void RegisterState(PipeState* state, PipeInput* input, char index){
	if(states[index] != nullptr)
		delete states[index];
	if(inputs[index] != nullptr)
		delete inputs[index];

	states[index] = state;
	inputs[index] = input;
}
void RegisterState(PipeState* state, char index){
	RegisterState(state,nullptr,index);
}

//ENGINE CALL REDIRECTIONS
void DrawPipeState(){
	states[curstate]->drawfunc();
}

void KeyPipeImpulse(char key, bool down, int x, int y){
	if(inputs[curstate] == nullptr || inputs[curstate]->keyfunc == nullptr)
		return;
	inputs[curstate]->keyfunc(key,down,x,y);
}

void MouseMotionPipeImpulse(int x, int y, bool drag){
	if(inputs[curstate] == nullptr || inputs[curstate]->mmovefunc == nullptr)
		return;
	inputs[curstate]->mmovefunc(x,y,drag);
}

void MouseButtonPipeImpulse(int button, bool down, int x, int y){
	if(inputs[curstate] == nullptr || inputs[curstate]->mbtnfunc == nullptr)
		return;
	inputs[curstate]->mbtnfunc(button,down,x,y);
}

void MouseWheelPipeImpulse(bool fwd, int x, int y){
	if(inputs[curstate] == nullptr || inputs[curstate]->mwhlfunc == nullptr)
		return;
	inputs[curstate]->mwhlfunc(fwd,x,y);
}