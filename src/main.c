// Charybdis

#include <stdio.h>
#include <stdbool.h>

void map(int day) {
    int progress = day*4;
    printf("Map of Progress:\n");
    for (int i = 0; i <= 16; i++) {
        if (i <= progress) {
            printf("[X]");
        } else {
            printf("[ ]");
        }
    }
    printf("\n__________________\n");
}

void combat_encounter(int *day, int *hp, int *supplies) {
    printf("You encounter a monster of the Aegean Sea, it has damaged your ship\n");
    *hp = *hp - (*day * 10);

}

void goto_port(int *day, int *hp, int *supplies) {
    printf("You go to port, and gain fresh supplies for the journey ahead!\n");
    *supplies = *supplies + (*day *10);
    bool at_port = true;
    while (at_port) {
        printf("H for health\nS for Supplies\nG to go forth\n");
        char port_input;
        scanf(" %c", &port_input);
        printf("__________________\n");
        if (port_input == 'h') {
            printf("Health is %d\n", *hp);
            printf("__________________\n");
        } else if (port_input == 's') {
            printf("Supplies is %d\n", *supplies);
        } else if (port_input == 'g') {
            printf("You choose to leave the port for the next leg of your journey\n");
            at_port = false;
        } else {
            printf("not a valid input, try again: \n");
        }
    }
}

void repair_ship(int *hp, int *supplies) {
    *hp = *hp + *supplies;
    *supplies = 0;
}

void ending(int hp) {}

int main() {
    // Initialize Variables
    bool running = true;
    int day = 1;
    int hp = 100;
    int supplies = 0;
    


    printf("Welcome to Charybdis:\n");
    // Main gameplay loop
    while (running) {
        printf("M for map\nD for Day Count\nP to go to the nearest port\nG to go forth across the sea\nQ to quit\n");
        char input;
        scanf(" %c", &input);
        printf("__________________\n");
        switch (input) {
            case 'q' | 'Q':
                running = false;
                break;
            case 'd' | 'D':
                printf("Current Day is %d\n__________________\n", day);
                break;
            case 'm' | 'M':
                map(day);
                break;
            case 'g' | 'G':
                if (day == 4) {
                    combat_encounter(&day, &hp, &supplies);
                    day ++;
                    break;
                } else {
                    ending(hp);
                    running = false;
                    break;
                }
            case 'p' | 'P':
                printf("You chose to go to the port\n");
                goto_port(&day, &hp, &supplies);
                combat_encounter(&day, &hp, &supplies);
                day ++;
                break;
            case 'r' | 'R':
                repair_ship(&hp, &supplies);
                break;
            default:
                printf("not a valid input, try again: \n");
                break;
        }
    }
    return 0;
}