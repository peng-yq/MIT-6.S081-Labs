#include "kernel/types.h"
#include "user/user.h"

void pipline(int rfd){
    int p, n;
    // 数据读取完毕，关闭文件描述符，并退出程序
    if(read(rfd, &p, sizeof(int)) == 0){
        close(rfd);
        exit(0);
    };
    // 打印第一个数
    printf("prime %d\n", p);
    // 创建连接下一个进程的管道
    int ppl[2];
    pipe(ppl);
    if(fork() == 0){ // 子进程
        close(ppl[1]);
        pipline(ppl[0]); // 继续递归调用
    } else{// 父进程
        close(ppl[0]);
        for(;;){
            // 上个进程输入的数据读完即结束循环
            if(read(rfd, &n, sizeof(int)) == 0){
                close(rfd);
                break;
            }
            // 过滤非质数
            if(n % p != 0){
                write(ppl[1], &n, sizeof(int));
            }
        }
        close(ppl[1]);
        wait((int *)0);
        exit(0);
    }
}

int main(int argc, char* argv[]){
    // 创建一个管道
    int p[2];
    pipe(p);

    if(fork() > 0){  // 主进程
        // 关闭管道的读端
        close(p[0]);
        // 向第一个进程写入2-35，一次写入一个数
        for(int i = 2; i <= 35; i++){
            write(p[1], &i, sizeof(int));
        }
        // 关闭写完数据的写端
        close(p[1]);
        wait((int *) 0); // 等待子进程完成
        exit(0);
    } else{ // 子进程
        // 关闭写端 
        close(p[1]);
        pipline(p[0]);
        exit(0);
    }
}