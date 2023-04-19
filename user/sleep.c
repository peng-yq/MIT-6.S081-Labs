#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    // 判断参数
    if(argc < 2){
        fprintf(2, "Usage: sleep <time>\n");
        exit(1);
    }
    // 使用atoi()函数将string转换为数字，并调用sleep syscall
    sleep(atoi(argv[1]));
    exit(0);
}