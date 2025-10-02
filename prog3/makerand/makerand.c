#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <num_bytes>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    long num_bytes = strtol(argv[2], NULL, 10);

    if (num_bytes <= 0) {
        fprintf(stderr, "Error: num_bytes must be > 0\n");
        return 1;
    }

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (long i = 0; i < num_bytes; i++) {
        uint8_t byte = rand() % 256;
        fwrite(&byte, 1, 1, fp);
    }

    fclose(fp);

    printf("Wrote %ld random bytes to %s\n", num_bytes, filename);
    return 0;
}

