#include <nodeSystem.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <nodeSystem.h>
#include <stdio.h>

typedef struct{
	int fd[2];
	char* pipeName;
	uint8_t type;
	uint8_t unit;
	uint16_t length;
} _node_pipe;

static uint8_t _nodeSystemIsActive = 0;

static uint16_t _pipe_count = 0;
static _node_pipe* _pipes = NULL;

static const uint32_t _node_init_head = 0x83DFC690;
static const uint32_t _node_init_eof  = 0x85CBADEF;
static const uint32_t _node_begin_head = 0x9067F3A2;
static const uint32_t _node_begin_eof  = 0x910AC8BB;

int nodeSystemInit(){
	//check system state
	if(_nodeSystemIsActive){
		return -3;
	}
	
	//set state
	_nodeSystemIsActive = 1;

	//send header
	write(STDOUT_FILENO,&_node_init_head,sizeof(_node_init_head));

	//send pipe count
	write(STDOUT_FILENO,&_pipe_count,sizeof(_pipe_count));

	//send pipe data
	uint16_t i;
	for(i = 0;i < _pipe_count;i++){
		write(STDOUT_FILENO,&_pipes[i].type,sizeof(_pipes[i].type));
		write(STDOUT_FILENO,&_pipes[i].unit,sizeof(_pipes[i].unit));
		write(STDOUT_FILENO,&_pipes[i].length,sizeof(_pipes[i].length));
		write(STDOUT_FILENO,_pipes[i].pipeName,strlen(_pipes[i].pipeName)+1);
	}
	
	//send eof
	write(STDOUT_FILENO,&_node_init_eof,sizeof(_node_init_eof));
}

int nodeSystemAddPipe(const char* const pipeName,NODE_PIPE_TYPE type,NODE_DATA_UNIT unit,uint16_t arrayLength){
	//check system state
	if(_nodeSystemIsActive){
		return -3;
	}

	//check pipe count
	if(_pipe_count == 0xFFFF){
		return -4;
	}
	
	//malloc piep struct
	_node_pipe pipe = {};
	
	//cpy data
	pipe.type = type;
	pipe.unit = unit;
	pipe.length = arrayLength;
	pipe.pipeName = malloc(strlen(pipeName)+1);
	if(!pipe.pipeName){
		return -1;
	}
	strcpy(pipe.pipeName,pipeName);

	//add pipe array
	_node_pipe* tmp = _pipes;
	_pipes = realloc(_pipes,sizeof(_node_pipe)*(_pipe_count+1));
	if(!_pipes){
		_pipes = tmp;
		free(pipe.pipeName);
		return -2;
	}
	_pipes[_pipe_count] = pipe;

	return _pipe_count++;
}

int nodeSystemBegine(){
	//check system state
	if(_nodeSystemIsActive != 1){
		return -3;
	}

	//set state
	uint8_t _nodeSystemIsActive = 2;

	//send header
	write(STDOUT_FILENO,&_node_begin_head,sizeof(_node_begin_head));

	//send pipe data
	uint16_t i;
	for(i = 0;i < _pipe_count;i++){
		switch(_pipes[i].type){
			case NODE_IN:{
				read(STDIN_FILENO,&_pipes[i].fd[0],sizeof(int));
				break;
			}case NODE_OUT:{
				read(STDIN_FILENO,&_pipes[i].fd[1],sizeof(int));
				break;
			}case NODE_IN_OUT:{
				read(STDIN_FILENO,_pipes[i].fd,sizeof(int) << 1);
				break;
			}
		}
	}
	
	//send eof
	write(STDOUT_FILENO,&_node_begin_eof,sizeof(_node_begin_eof));
}
