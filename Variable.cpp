#include "Variable.h"


// Setter method for Variable name
void Variable::setName(string n){
	name = n;
}

void Variable::inc_const(int num){
	constant += num;
}

void Variable::setSolved( bool state ){
	solved = state;
}

