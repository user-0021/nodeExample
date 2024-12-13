#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int first  = nodeSystemAddPipe("First",NODE_IN,NODE_INT_8,1);
	int second = nodeSystemAddPipe("Second",NODE_OUT,NODE_DOUBLE,2);

	nodeSystemInit();

	nodeSystemBegine();

	nodeSystemDebugLog("SystemBegin");

	while(!nodeSystemIsActive()){

		nodeSystemDebugLog("Loop!");
		sleep(1);
	}
}
