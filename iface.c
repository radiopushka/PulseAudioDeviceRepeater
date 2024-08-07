#include "alsa/alsa.h"
#include <stdlib.h>
#include <stdio.h>


void make_empty_buffer(short* input){
 int i;
  for(i = 0; i < 100; i++){
    input[i] = 0;
  }

}

int main(int argn, char* argv[]){
  if(argn < 3){
    printf("%s <input device> <output device> [sample rate]\n", argv[0]);
    return 0;
  }

  int samplerate = 48000;

  if(argv[3] != NULL){
    samplerate = atoi(argv[3]);
  }



  int status = setup_alsa(argv[1], argv[2], 100, samplerate);

  if( status < 0)
    return 0;

  short* input = malloc(sizeof(short) * (100));
  make_empty_buffer(input);
  int error = 0;
  char pull = 0;
  while( error != -1){
    sync_record();
    awrite(input);
    error = aread(input);
  }


  free(input);
  free_alsa();

  return 0;
}
