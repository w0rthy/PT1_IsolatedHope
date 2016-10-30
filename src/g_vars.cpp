#include "g_vars.h"
#include <map>

using namespace std;

map<char*, double> variables;

void setVar(char* var, double val){
	variables[var] = val;
}

double getVar(char* var){
	return variables[var];
}

void addVar(char* var, double amt){
	variables[var] = variables[var] + amt;
}

void delVar(char* var){
	variables.erase(var);
}

void clearVars(){
	variables.clear();
}