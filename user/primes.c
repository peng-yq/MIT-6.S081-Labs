#include "kernel/types.h"
#include "user/user.h"

void pipline(int rfd){
    int p, n;
    // get the first number from last progress  
    if(read(rfd, &p, sizeof(int)) == 0){
        close(rfd);
        exit(0);
    };
    printf("prime %d\n", p);
    // create a new pipe to commuicate with next progress
    int ppl[2];
    pipe(ppl);
    if(fork() == 0){// child
        close(ppl[1]);
        pipline(ppl[0]); //recursive call pipline()
    } else{// parent
        close(ppl[0]);
        for(;;){
            if(read(rfd, &n, sizeof(int)) == 0){
                close(rfd);
                break;
            }
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
    int p[2];
    pipe(p);

    if(fork() > 0){  //main progress 
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