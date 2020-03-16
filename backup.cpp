/*
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int pid = 0;

// some very time-consuming function
void childLabor() {
    for (long long i=1;i<=10000000000;i++) {
       // printf("i'm printing\n");
        fflush(stdout);
    }
}

// stop the process who calls this
void stopYourself() {
    // TODO
}

void childReceiveStop() {
    signal(SIGTSTP, childReceiveStop);
    printf("I have important things to do first before stopping\n");
    fflush(stdout);
    // do important things

    printf("I stop myself now\n");
    fflush(stdout);
    stopYourself();
}

void childReceiveContinue() {
    signal(SIGCONT, childReceiveContinue);
}

/*
int main()
{
    pid = fork();
    if (pid==0) {
        signal(SIGTSTP, childReceiveStop);
        signal(SIGCONT, childReceiveContinue);
        stopYourself();     // wait until parent sends SIGCONT
        childLabor();
    }
    else {
        // start/stop child every 2 second
        kill(pid,SIGCONT);
        for (int i=1; i<=100; i++) {
            printf("sending signal stop\n");
            fflush(stdout);
            kill(pid, SIGTSTP);
            sleep(3);

            printf("sending signal start\n");
            kill(pid, SIGCONT);
            sleep(1);
        }
    }

    return 0;
}
*/
