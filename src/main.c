#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	nodeSystemAddPipe("First",NODE_IN,NODE_INT_8,1);
	nodeSystemAddPipe("Second",NODE_OUT,NODE_DOUBLE,1);

	nodeSystemInit();

	nodeSystemBegine();


	while(!nodeSystemIsActive()){

	}
}
