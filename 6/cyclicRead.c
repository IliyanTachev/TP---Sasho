#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "gen.h"
#include "gen.c"
#include "cyclicBuf.h"


int main()
{
	int memFd = shm_open( "simple_memory", O_RDONLY, 0 );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	struct buffer* memory = mmap( NULL, sizeof(struct buffer), PROT_READ, MAP_SHARED, memFd, 0 );
	if( memory == NULL )
	{
		perror("Can't mmap");
		return 1;
	}
    
    uint64_t position = memory->position;
    uint64_t seed;
    uint64_t genuineseed;
	printf("starting at %ld\n", position);
    int i=0;

    while(1)
	{
       		 while(memory -> position != position)
		 {
	       		 seed = verify((void *)memory->array[position %=COUNT]);
	        	 if(seed==-1)
			 {
		        	printf("Error in verify\n");
	        	 }

	        	 if(memory->position >= position + COUNT )
			 {
	            		printf("Overload");
	            		return 1;
	        	 }

	        	 if(i==0)
			 {
            			genuineseed=seed;
                		i = 1;
	        	 }
			 else if(genuineseed + 1 == seed)
			 {
	            		printf("Error in seed");
	        	 }
			 else
			 {
           			genuineseed++;
	        	 }

            		 printf("Veryfy array[%ld] - seed:%d\n",position %=COUNT,seed);
            		 position ++;
        	}
    	}  
	return 0;
}
