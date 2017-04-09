#include <stdio.h>
#include <string.h>
#include <inttypes.h>

// for int32_t, uint32_t, int64_t, uint64_t
#define __STDC_FORMAT_MACROS
 
int main(int argc,char *argv[])
{

  signed char data_sc = 128;
  unsigned char data_usc = 128;
  printf("data=%hhd\n", data_sc);
  printf("data=%hhu\n", data_usc);

  int data_int = 1;
  short int data_short_int = 1;
  unsigned short int data_unsigned_short_int = 1;
  unsigned int data_unsigned_int = 1;
  long int data_long_int = 1;
  long long int data_long_long_int = 1;
  unsigned long int data_unsigned_long_int = 1;
  unsigned long long int data_unsigned_long_long_int = 1;
  printf("data=%d\n",   data_int);
  printf("data=%hd\n",  data_short_int);
  printf("data=%hu\n",  data_unsigned_short_int);
  printf("data=%u\n",   data_unsigned_int);
  printf("data=%ld\n",  data_long_int);
  printf("data=%lld\n", data_long_long_int);
  printf("data=%lu\n",  data_unsigned_long_int);
  printf("data=%llu\n", data_unsigned_long_long_int);
 
  int8_t   data8_t   = 1;
  int32_t  data32_t  = 1;
  uint32_t datau32_t = 1;
  int64_t  data64_t  = 1;
  uint64_t datau64_t = 1;
  printf("data=%" PRIi8 "\n",data8_t);
  printf("data=%" PRId32 "\n",data32_t);
  printf("data=%" PRIu32 "\n",datau32_t);
  printf("data=%" PRId64 "\n",data64_t);
  printf("data=%" PRIu64 "\n",datau64_t);
  return 0;
}
