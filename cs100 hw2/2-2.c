/*#include <stdio.h>

int length(int x) {
    int count = 0;
    do {
        x /= 10;
        count++;
    } while (x != 0);
    return count;
}

int max_num(int a, int b, int c) {
    int max = a;
    if (b > max && b > c) {
        max = b;
    }
    else if (c > max && c > b) {
        max = c;
    }
    else {
        max = a;
    }
    return max;
}

void blank(int i) {
    int j;
    for (j = 1; j <= i; j++) {
        putchar(' ');
    }
}

void line(int i) {
    int j;
    for (j = 1; j <= i; j++) {
        putchar('-');
    }
}


void add(int a, int b){
    int l_a = 0;
    int l_b = 0;
    int l_sum=0;
    int l_max=0;
    int l_line=0;
    int c = a + b;
    l_a = length(a);
    l_b = length(b);
    l_sum = length(c);
    if (l_a > l_b) {
        l_max = max_num(l_a, l_b, l_sum);
    }
    else if (l_a < l_b) {
        l_max = max_num(l_a, l_b, l_sum) + 1;
    }

    l_line = l_max + 2;

    blank(l_line - l_a);
    printf("%d\n", a);


    putchar('+');
    blank(l_line - l_b - 1);
    printf("%d\n", b);


    line(l_line);
    putchar('\n');

    blank(l_line - l_sum);
    printf("%d\n", c);




}

void subtract(int a, int b){
    // YOUR CODE HERE
}

void multiply(int a, int b){
    // YOUR CODE HERE
}

int main(){
    int a, b;
    char op;
    scanf_s("%d %c %d", &a, &op, &b);
    switch (op) {
        case '+':
            add(a, b);
            break;
        case '-':
            subtract(a, b);
            break;
        case 'x':
            multiply(a, b);
            break;
        default:
            printf("Sample input: 12 + 34");
    }
    return 0;
}*/