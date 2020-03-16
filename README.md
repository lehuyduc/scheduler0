# scheduler0
Most basic cpp scheduler

I. Information:
SUMMARY: simulate a OS cpu scheduler. The program is a CPU core, each function is a process.

CONDITION:
- only 1 function is allowed to run at a time
- The program knows nothing about a function except for its input parameters.
- The functions (processes) don't need to handle interrupt/saving states (because that's the job of the OS/Process Control Block).

GOAL: There are N functions, the program must run these functions in "parallel".

II. Difficulties:
PROBLEM 1:
- At least TWO threads or processes are needed because we need to simulate hardware interrupt. 
- It is impossible to do this task using 1 thread unless the functions have some pre-defined ways to communicate
-> Use 2 threads or processes.

PROBLEM 2:
- A function is not a process. It does not have a PCB so it cannot save its current state
- Any code (except assembly) is not atomic. (i = a[n] * b[n] / 1234) is a lot of instructions.
  How to interrupt during the middle of a command, and go back there later?
- No PCB, not atomic, and no program counter -> the function cannot know which is the current command to save

-> Have to use built-in pause/continue signals such as SIGSTOP and SIGCONT

PROBLEM 3:
- Linux's fault:
The POSIX standard provides no mechanism by which a thread A can suspend the execution of another thread B, without cooperation from B. 
The only way to implement a suspend/restart mechanism is to have B check periodically some global variable for a suspend request and then suspend itself on a condition variable, 
which another thread can signal later to restart B.

-> We cannot use thread.

-> Use fork().

III. Ideas:
- We have a main process that acts as the hardware thread.
- For each function, we fork() and creates a process that will run only that function. That process will exit when the function is finished
- Immediately after creating, we stop it (basically put it in ready queue).

- Round robin:
+ Get a process id from queue
+ Send SIGCONT 
+ Let it run for timeSlice = 2ms
+ SEND SIGSTOP
+ If the process has not ended then push it back to the back of queue 
  (note, I abandoned this scheduler0 project for a better version, so it always push into queue).

IV. Results:
- A program that run 3 functions in parallel, even though only 1 function is allowed to run at a time.

V. Future works: https://github.com/lehuyduc/scheduler1
- Cross-platform simulator
- ZERO pthread or fork() or any kind of threading. It uses EXACTLY 1 THREAD as required
- Can simulate a process control block
- Functions (actually programs) that can be stopped and resumed any time
- All commands are atomic
- Can be ported to C (just longer code).

- Downside: 
+ Functions have to be written using assembly-like home-made language (compiler is already provided).
+ No documentation yet (finished 5 minutes ago).
+ Currently only int or string is available (no float, long long, double, ...). Can be added using char*
+ Limited number of instruction


 


