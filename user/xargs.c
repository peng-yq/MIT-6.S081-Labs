#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
    char *argv_array[MAXARG];
    int i;
    // 将xargs的所有参数装入argv_array数组中
    for(i = 0; i < argc; i++){
        argv_array[i] = argv[i];
    }
    // 用于接收父进程输出
    char buff[256];
    for( ; ;){
        int j = 0;
        // 接收一行输入，直到读完了或者出现换行符'\n'
        while(read(0, buff + j, sizeof(char)) != 0 && buff[j] != '\n'){
            j++;
        }
        // j=0表示read()返回0（进入for新循环后j被初始化为0，并且while循环中没有改变），即输入已全部读取完毕，跳出循环，结束父进程
        if(j == 0)
            break;
        buff[j] = 0;
        // 将父进程输出加入参数数组中
        argv_array[i] = buff;
        // 设置exec()结束
        argv_array[i+1] = 0;
        // 创建子进程，执行exec()调用
        if(fork() == 0){
            exec(argv_array[1], argv_array+1);
        } else{
            // 父进程等待子进程结束
            wait( (int *) 0);
        }
    }
    exit(0);
}