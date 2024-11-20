#include <stdint.h>
#include <unistd.h>

int main(){
	uint32_t counts[3] = {1,2,3};
	write(STDOUT_FILENO,counts,sizeof(uint32_t)*3);
}
