#include <stdio.h>
#include "main.h"

void proper_division(int a) {
    int i = 0;
    while (i < a) {
        printf("%d", a / i);
        i++;
    }
}

void find_test(enum testage a) {
    switch (a) {
        case test1:
        case test2:
        case test3:
        case test4:
        case test5:
            printf("All case are found");
    }
}


void copy_data(void) {
    char a[31];
    char b[31];

    memcpy(a, b, NAME_LEN);

}


int main(void) {
    int a;
    int b;
        int c;

        printf("a = %d, b = %d, c = %d\n", a, b, c);


        c=34;
        while (c < 100) {
            printf("c = %d\n", c);
            a++;
        }
        find_test(0);
        proper_division(12);

        char d[10];
a[9] = 0;
a[10] = 0;
        return (0);
}
