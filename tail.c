#include <stdio.h>
#include <stdlib.h>

struct cbuf{
char** buffer; 
int writeIndex;
int readIndex;
int bufferSize;
};

typedef struct LINE { char c[2048]; };

/*
int cbuf_get (int * value) 
{
  if (readIndex == writeIndex)
  {
     // buffer is empty
     return 0;
  }

  *value = buffer[readIndex];
  readIndex = (readIndex + 1) % N;
  return 1;
}
*/
char** cbuf_create(int n){
    char** buffer = malloc(sizeof(char*)*n);
    return buffer;
}

void cbuf_put (struct cbuf cbuffer, char* line) 
{
    cbuffer.buffer[cbuffer.writeIndex] = malloc(sizeof(char));
}

int main ()
{
    struct cbuf cbuffer;
    cbuffer.writeIndex = 0;
    cbuffer.readIndex = 0;
    cbuffer.buffer = cbuf_create(2);
    for(int i=0; i<2; i++){
        cbuffer.buffer[i] = 'a';
        printf("%c\n", cbuffer.buffer[i]);
    }
    int value = 1001;
    /*while (put (value ++));
    while (get (& value))
        printf ("read %d\n", value);*/
    return 0;
}