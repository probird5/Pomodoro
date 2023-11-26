#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int remaining_time;

void display_timer(int seconds) {
    int minutes = seconds / 60;
    printf("%02d:%02d\r", minutes, seconds % 60);
    fflush(stdout); // Flush the output buffer to immediately display the timer
}

void timer_expired(int signo) {
    // Play around here and maybe can play a sound
    printf("Timer expired\n");
}

void start_timer(int seconds) {
    remaining_time = seconds;
    signal(SIGALRM, timer_expired);
    alarm(remaining_time);
}

void stop_timer() {
    alarm(0);
}

int main () {
    int work_duration, break_duration, pomodoro_count = 0;

    printf("Enter work duration (in minutes): ");
    scanf("%d", &work_duration);
    work_duration *= 60; // converts minutes to seconds

    printf("Enter break duration (in minutes): ");
    scanf("%d", &break_duration);
    break_duration *= 60; // coverts minutes to seconds

    while (1) { //Infinite loop for pomodoro cycle
        printf("Pomordoro #%d (Work)\n", pomodoro_count + 1);
        start_timer(work_duration);

        //Display dynamic countdown for the work phase
        while (remaining_time > 0) {
            printf("Work Timer: ");
            display_timer(remaining_time);
            sleep(1); // Sleep for 1 second 
            remaining_time--;
            printf("\r"); // this will overwrite the line instead of making a new one
        }

        stop_timer();

        printf("\nPomordo #%d (Break)\n", pomodoro_count + 1);
        start_timer(break_duration);

        //Display countdown for break phase
        while (remaining_time > 0) {
            printf("Break Timer: ");
            display_timer(remaining_time);
            sleep(1);
            remaining_time--;
            printf("\r");
        }
        stop_timer();
        pomodoro_count++;

         
    }

    return 0;
} 
