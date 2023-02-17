#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void error_exit(char* msg, int ex) {
    perror(msg);
    exit(ex);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        error_exit("Usage: 1 argumento bro\n", 1);
    }

    int n = atoi(argv[1]);

    int vec_nums[1048576+1];
    srand(getpid());
    for (int i = 0; i < n; ++i) {
        int num = rand() % 1048576;
        if (vec_nums[num] != 1) {
            write(57, &num, sizeof(num));
            vec_nums[num] == 1;
        }
        else {
            int found = 0;
            while (!found && vec_nums[num] == 1) {
                num = rand() % 1048576;
                if (vec_nums[num] != 1) {
                    vec_nums[num] = 1;
                    found = 1;
                }
            }
        }

    }
}
