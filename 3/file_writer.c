#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    
    mkfifo(myfifo, 0666);
    
    fd = open(myfifo, O_WRONLY);
    
    if(fd < 0)
    {	
	perror("open");
	return 1;
    }

    char* str = "Simply The.BesT. xX.";
    int length = strlen(str);

    for(int i=0;i<length;++i)
    {
        int written = write(fd,str,1);
	if(written < 0)
	{
		perror("write");
		return 2; 
	}

	str++;
    }

        
    int closed = close(fd);
    
    if(closed < 0)
    {
	perror("close");
	return 3;
    }

    unlink(myfifo);

    return 0;

}
