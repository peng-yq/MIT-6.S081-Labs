#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
   // 创建两个管道
   int p_c[2], c_p[2];
   pipe(p_c);
   pipe(c_p);
   // 一字节数据
   char buff = 'p';
   int pid = fork();
   if(pid > 0){ // 父进程
        // 关闭不需要的管道端，即父进程的读端和子进程的写端
        close(p_c[0]);
        close(c_p[1]);
        // 父进程写入一字节的数据
        write(p_c[1], &buff, sizeof(char));
        // 父进程读入一字节的数据
        read(c_p[0], &buff, sizeof(char));
        printf("%d: received pong\n", getpid());
        // 关掉使用完毕的管道
        close(p_c[1]);
        close(p_c[0]);
        exit(0);
   }else if(pid == 0){ // 子进程
        // 关闭不需要的管道端，即父进程的写端和子进程的读端
        close(p_c[1]);
        close(c_p[0]);
        // 子进程读入一字节的数据
        read(p_c[0], &buff, sizeof(char));
        printf("%d: received ping\n", getpid());
        // 子进程写入一字节的数据
        write(c_p[1], &buff, sizeof(char));
        // 关闭使用完毕的管道
        close(p_c[0]);
        close(c_p[1]);
        exit(0);
   }else{
     close(p_c[0]);
     close(p_c[1]);
     close(c_p[0]);
     close(c_p[1]);
     exit(1);
   }
}