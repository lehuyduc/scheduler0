#include <iostream>
#include <pthread.h>
#include <queue>
#include <deque>
#include <utils.h>
#include <functions.h>
using namespace std;


int pid;
bool stopped;
FuncPointer myFunction;
pthread_t hwThread, cpuTthread;
vector<int> childs;

void childReceiveStop()

void schedule(int n, FuncPointer fp[]) {
    int i,j;

    for (i=0; i<n; i++) {
        pid = fork();
        if (pid==0) {
            myFunction = fp[i];
            return;
        }
        else {
            childs.push_back(pid);
            kill(pid, SIGSTOP);
        }
    }
}

void rr(vector<int> pids, int timeSlice) {
    int i, j, id, n;
    deque<int> q;

    n = pids.size();
    for (i=0; i<n; i++) q.push_back(pids[i]);

    while (!q.empty()) {
        id = q.front(); q.pop_front();
        kill(id, SIGCONT);
        msleep(timeSlice);
        kill(id, SIGSTOP);
    }
}

int main()
{
    FuncPointer fps[3];
    fps[0] = &func1;
    fps[1] = &func2;
    fps[2] = &func3;

    schedule(3, fps);

    if (pid==0) {
        myFunction();
    }
    else {
        rr(childs, 1000);
    }

    return 0;
}


