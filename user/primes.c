#include "kernel/types.h"
#include "user/user.h"

void pipline(int rfd){
    
}

int main(int argc, char* argv[]){
    int p[2];
    pipe(p);

    if(fork() > 0){ 
        close(p[0]);
        for(int i=2; i<=35; i++){
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait((int *) 0); //wait for child
        exit(0);
    } else{
        close(p[1]);
        pipline(p[0]);
        exit(0);
    }
}