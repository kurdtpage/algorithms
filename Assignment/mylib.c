#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"


/*
  Allocate memory for a given size and returns a voided untyped pointer to it
*/
void *emalloc(size_t s) {
  void *result = malloc(s);
  if(NULL == result){
    fprintf(stderr, "Failled to malloc some memory bro\n");
    exit(EXIT_FAILURE);
  }
  return result;
}

/*
  Re-allocate memory for a given pointer and return the voided untyped pointer
*/
void *erealloc(void *p, size_t s){
  void *result = realloc(p, s);
  if(NULL == result){
    fprintf(stderr, "Failled to increase memory allocation bro\n");
  }
  return result;
}

int getword(char *s, int limit, FILE *stream){
  int c;
  char *w = s;
  assert(limit > 0 && s != NULL && stream != NULL);

  /*skip to the start of the word*/
  while (!isalnum(c = getc(stream)) && EOF != c)
    ;
  if(EOF == c) {
    return EOF;
  } else if (--limit > 0) { /*reduce limit by 1 to allow for \0*/
    *w++ = tolower(c);
  }

  while (--limit > 0) {
    if (isalnum(c = getc(stream))) {
      *w++ = tolower(c);
    } else if ('\'' == c) {
      limit++;
    } else {
      break;
    }
  }

  *w = '\0';
  return w - s;
}
