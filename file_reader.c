#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    
    fd = open(myfifo, O_RDONLY);
    
    write(STDOUT_FILENO,"Status:\n",sizeof("Status:\n"));
    
    for(int i=0;i<10;i++)
    {
	read(fd, buf, MAX_BUF);
	printf("%s\n",buf);
    }
    
    close(fd);

    return 0;
}
