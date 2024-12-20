#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int first  = nodeSystemAddPipe("First",NODE_CONST,NODE_INT_8,3);
	int second = nodeSystemAddPipe("Second",NODE_OUT,NODE_DOUBLE,2);
	int third  = nodeSystemAddPipe("A",NODE_OUT,NODE_INT_8,1);
	int forth  = nodeSystemAddPipe("C",NODE_IN,NODE_INT_8,1);

	nodeSystemInit();

	nodeSystemBegine();

	nodeSystemDebugLog("SystemBegin");

	int8_t rdata[3] = {};
	char msg[2048];

	while(!nodeSystemLoop()){
		uint8_t wdata = 0;
		int ret = nodeSystemRead(first,rdata,0);
		if(ret == 1){
			wdata = rdata[0] + 1;
		}

		nodeSystemWrite(third,&wdata,0);
		sprintf(msg,"Count %d",(int)rdata[0]);
		nodeSystemDebugLog(msg);
		sleep(3);
	}
}
