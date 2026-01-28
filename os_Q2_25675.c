#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>
int main(){
    int fd=open("output.txt",O_CREAT | O_WRONLY | O_APPEND,0777);
    if (fd<0){
        perror("file open failed");
        exit(1);
    }
pid_t pid = fork();
if(pid==0){
 char c1[]="This line is written by the child process\n";
 write(fd,c1,strlen(c1));
 close(fd);
}
else{
    wait(NULL);
    char c2[]="this line is written by the parent process";
    write(fd,c2,strlen(c2));
    close(fd);
}
return 0;
}
