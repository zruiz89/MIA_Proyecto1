#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXIT "exit"
#define MKDISK "mkdisk"

static int areEquals(char *string1, char *string2) {
    return ((strlen(string1) == strlen(string2)) && (strcmp(string1, string2) == 0));
}

static void toLowerCase(char *string) {
    for(int i = 0; string[i]; i++){
        string[i] = tolower(string[i]);
    }
}

static void readCommand(char *command) {
        puts("Processing command...");
        toLowerCase(command);
        printf("Your command: %s\n", command);

}

int main() {
    char command[301];
    while (1) {
        //scanf("%300s", command);
        fgets(command, sizeof(command), stdin);
        readCommand(command);
    }

    return 0;
}