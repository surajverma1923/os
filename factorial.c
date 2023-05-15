#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int factorial(int n){
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int sum_digits(int n){
    int sum = 0;
    while (n > 0){
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int pid = fork();

    if (pid == 0){
        int fact = factorial(num);
        printf("Factorial of %d is %d\n", num, fact);
    }
    else{
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)){
            int sum = sum_digits(num);
            printf("Sum of digits of %d is %d\n", num, sum);
        }
    }
    return 0;
}

