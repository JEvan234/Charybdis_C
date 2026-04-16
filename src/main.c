// Charybdis

#include <stdio.h>
#include <stdbool.h>

void load_asset(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error, could not find file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    printf("\n");
}

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
        char port_input = getchar();
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

void dialogue(char dialogue[]) {
    printf("%s\n", dialogue);
    bool wait = true;
    char input;
    while (wait == true) {
        printf("Press enter/return to continue");
        input = getchar();
        if (input == '\n') {
            wait = false;
        } else {
            continue;
        }
    }
}

int start_menu() {
    load_asset("assets/CharybdisLogo.txt");
    int difficulty;
    printf("Enter a difficulty (0 = easy/1 = hard): ");
    scanf("%d", &difficulty);
    dialogue("You play as Theseus, eternally bound to your ship (The Ship of Theseus)");
    dialogue("In greek mythology, there is common debate whether or not the ship is the same after all of the parts have been replaced.");
    dialogue("With you know helming the ship, it is up to you to face the seas and find a solution to the paradox yourself!");

    return difficulty;
}

void ending(int hp) {
    load_asset("assets/TheEND.txt");
}

int main() {
    // Initialize Variables
    bool running = true;
    int day = 1;
    int hp = 100;
    int supplies = 0;

    // Start the game + exposition
    int difficulty = start_menu();
    
    // Main gameplay loop
    while (running) {
        printf("M for map\nD for Day Count\nP to go to the nearest port\nG to go forth across the sea\nQ to quit\n");
        newline_fix: false;
        char input = getchar();
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
                if (day <= 4) {
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
            case '\n':
                goto newline_fix;
            default:
                printf("not a valid input, try again: \n");
                printf("%d\n", input);
                break;
        }
    }
    return 0;
}