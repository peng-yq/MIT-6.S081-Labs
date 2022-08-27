#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
   int p_c[2], c_p[2];
   pipe(p_c);
   pipe(c_p);
   char buff = 'p';
   if(fork() > 0){ //parent
        close(p_c[0]);
        close(c_p[1]);
        write(p_c[1], &buff, sizeof(char));
        read(c_p[0], &buff, sizeof(char));
        printf("%d: received pong\n", getpid());
        close(p_c[1]);
        close(p_c[0]);
        exit(0);
   }else{ //child
        close(p_c[1]);
        close(c_p[0]);
        read(p_c[0], &buff, sizeof(char));
        printf("%d: received ping\n", getpid());
        write(c_p[1], &buff, sizeof(char));
        close(p_c[0]);
        close(c_p[1]);
        exit(0);
   }
}