#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    
    mkfifo(myfifo, 0666);
    
    fd = open(myfifo, O_WRONLY);
    
    for(int i=0;i<10;++i)
    {
        write(fd, "Simply The.BesT. xX." , sizeof("Simply The.BesT. xX.")+1);
    }

        
    close(fd);

    unlink(myfifo);

    return 0;

}
