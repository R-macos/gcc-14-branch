#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

#ifndef PROG
#error "PROG must be defined"
#endif
#ifndef ARCH
#error "ARCH must be defined"
#endif

int main(int argc, char **argv) {
#ifdef AS_IS
  argv[argc] = 0;
  return execve("/usr/bin/" PROG, argv, environ);
#else
  char **na = (char**) calloc(sizeof(char*), argc + 4), **nb = na;
  int i = 1, has_arch = 0;
  while (i < argc) {
    if (!strcmp(argv[i], "-arch")) {
      has_arch = 1;
      if (i + 1 < argc && strcmp(argv[i + 1], ARCH))
	fprintf(stderr, "WARNING: attempt to call %s with arch %s!\n", argv[0], argv[i + 1]);
      break;
    }
#if 0
    else if (!strncmp(argv[i], "-mmacos-version-", 16)) {
      /* Apple has renamed -mmacosx-version-.. options to -mmacos-version-.. but
	 gfortran doesn't know that so we map them all to the original */
      char *x = (char*) malloc(strlen(argv[i] + 2));
      if (!x) { fprintf(stderr, "ERROR: out of memory!\n"); return 1; }
      strcpy(x, "-mmacosx-version-");
      strcpy(x + 17, argv[i] + 16);
      argv[i] = x;
    }
#endif
    i++;
  }
  i = 1;
  *(na++) = "/usr/bin/" PROG;
  if (!has_arch) {
    *(na++) = "-arch";
    *(na++) = ARCH;
  }
  while (i < argc) {
    /* fprintf(stderr, "'%s' ", argv[i]); */
    *(na++) = argv[i++];
  }
  fprintf(stderr, "\n");
  return execve("/usr/bin/" PROG, nb, environ);
#endif
}
