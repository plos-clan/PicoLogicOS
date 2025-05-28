#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct highlight_rule {
} highlight_rule_t;

void highlight(const char *text, size_t len) {}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    perror("fopen");
    return 1;
  }
  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(filesize + 1);
  if (!buffer) {
    perror("malloc");
    fclose(file);
    return 1;
  }

  size_t read_size = fread(buffer, 1, filesize, file);
  if (read_size != filesize) {
    fprintf(stderr, "Error reading file\n");
    free(buffer);
    fclose(file);
    return 1;
  }
  buffer[filesize] = '\0';

  highlight(buffer, filesize);

  free(buffer);
  fclose(file);
  return 0;
}
