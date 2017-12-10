#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "gen.h"
#include "c_buffer.h"

int main()
{
	int fd = shm_open("memory", O_CREAT | O_RDWR, S_IRWXU );
	if( fd < 0 )
	{
		perror("open");
		return 1;
	}

	int res;
	res = ftruncate( fd, sizeof(struct cyclic_buf) );
	if( res < 0 )
	{
		perror("Can't truncate file");
		return res;
	}
	
	struct cyclic_buf* mem = mmap( NULL, sizeof(struct cyclic_buf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return 1;
	}
	
    mem->pos = 0;
    uint32_t seed = 0;
    while(1)
    {
		generate((void*)mem->array[mem->pos], seed);
		printf("Generate: array[%d] - seed: %d\n", mem->pos,seed);
		mem->pos++;
		mem->pos %= _BLOCK_COUNT;
		seed++;
    }

	return 0;
}
