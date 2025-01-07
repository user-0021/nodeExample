#include <nodeSystem.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int8_t constData[3] = {23,12,0};

	int first  = nodeSystemAddPipe("First",NODE_PIPE_CONST,NODE_UNIT_INT8,3,constData);
	int second = nodeSystemAddPipe("Second",NODE_PIPE_OUT,NODE_UNIT_DOUBLE,2,NULL);
	int third  = nodeSystemAddPipe("A",NODE_PIPE_OUT,NODE_UNIT_INT8,1,NULL);
	int forth  = nodeSystemAddPipe("C",NODE_PIPE_IN,NODE_UNIT_INT8,1,NULL);

	nodeSystemInit();

	nodeSystemBegine();

	nodeSystemDebugLog("SystemBegin");

	int8_t rdata[3] = {};
	char msg[2048];

	while(!nodeSystemLoop()){
		// uint8_t wdata = 0;
		// int ret = nodeSystemRead(first,rdata);
		// if(ret == 1){
		// 	wdata = rdata[0] + 1;
		// }

		// nodeSystemWrite(third,&wdata);
		// sprintf(msg,"Count %d",(int)rdata[0]);
		// nodeSystemDebugLog(msg);
		sleep(3);
	}
}
