#include <iostream>
#include <stdio.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>


// THRESHOLD=n => bytes of the bmp file are only modified from the n+1-th byte onward.
// THRESHOLD exists so that crucial bytes related to filetype, etc, are not modified.
#define THRESHOLD 10000

using namespace std;

// defines the transformation of pixels. could be made more general.
unsigned char transform(unsigned char byte, unsigned char* list, int len) {
  cout << "Begin transform" << endl;
  for (int i = 0; i < len; i++) {
    if (byte <= list[i]) return list[i];
  }
  return 255; // should not be reached.
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout 
      << "Usage: ./interpret [Filename] [Outfilename]" << endl 
      << "Enter integers in ascending order into STDIN to define the discrete coloring of the target image." << endl;
    return 0;
  }

  int list_ctr = 0;
  unsigned char list[256];
  while(!cin.fail() || list_ctr >= 256) {
    cin >> list[list_ctr++];
  }
  list[list_ctr++] = 255; //rounds pixels up.

  unsigned char byte;
  int from = open(argv[1], O_RDONLY);
  int to = open(argv[2], O_RDWR|O_CREAT, 0666);

  int ctr = 1;
  int t = read(from, &byte, 1);
  // works while pixels are left to be read
  // assumes t=0 => termination, rather than error.
  while (t != 0) {
    char write_byte = (ctr > THRESHOLD) ? transform(byte,(unsigned char*)list,list_ctr) : byte;
    write(to, &write_byte, 1);
    t = read(from,&byte, 1);
    ctr ++;
  }
  close(from);
  close(to);
  return 0;
}
