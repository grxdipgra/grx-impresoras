#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

int main(int argc, char **argv)
{
  if(argc < 3)
  {
    fprintf(stderr, "Usage: %s input output\n", argv[0]);
    return 1;
  }

  // Open input & output files
  FILE *input = fopen(argv[1], "rb");
  if(input == NULL)
  {
    fprintf(stderr, "fopen: %s: %s\n", argv[1], strerror(errno));
    return 1;
  }

  gzFile output = gzopen(argv[2], "wb");
  if(output == NULL)
  {
    fprintf(stderr, "gzopen: %s: %s\n", argv[2], strerror(errno));
    fclose(input);
    return 1;
  }

  // Read in data from the input file, and compress & write it to the
  // output file
  char buffer[8192];
  int N;
  while((N = fread(buffer, 1, sizeof(buffer), input)) > 0)
  {
    gzwrite(output, buffer, N);
  }

  fclose(input);
  gzclose(output);

  return 0;
}
