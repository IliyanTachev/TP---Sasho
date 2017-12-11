#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf;

    
    fd = open(myfifo, O_RDONLY);

    if(fd < 0)
    {
	perror("open");
    }  
  
    write(STDOUT_FILENO,"Message:\n",sizeof("Message:\n"));
    
    while(read(fd, &buf, 1) > 0)
    {
	int written = write(STDOUT_FILENO, &buf, 1);
	if(written < 0)
	{
		perror("write");
		return 1;
	}
    }
    
   int closed = close(fd);
   if(closed < 0)
   {	
	perror("close");
	return 2;
   }

    return 0;
}
