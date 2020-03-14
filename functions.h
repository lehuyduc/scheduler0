#pragma once

typedef void (*FuncPointer)(void*);

void func1() {
    for (int i=1;i<=1000000000;i++) printf("F1\n");
}

void func2() {
    for (int i=1;i<=1000000000;i++) printf("F1\n");
}

void func3() {
    for (int i=1;i<=1000000000;i++) printf("F1\n");
}
