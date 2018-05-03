#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "mymalloc.h"
#include <inttypes.h>
#include <assert.h>

int main() 
{
   my_malloc_init(12 * MiB);

   void *b1 = my_malloc(2 * MiB);
   assert(b1);
   
   void *b2 = my_malloc(2 * MiB);
   assert(b2);

   void *b3 = my_malloc(1 * MiB);
   assert(b3);

   void *b4 = my_malloc(2 * MiB);
   assert(b4);

   my_free(b2);

   void *b5 = my_malloc(1 * MiB);
   assert(b5);

   my_free(b1);

   void *b6 = my_malloc(1 * MiB);

   printf("HEAP (1)\n");
   my_dump_mem(stdout);

   printf("Address of p5 is %" PRIu64 "\n", my_address(b5));
   printf("Address of p6 is %" PRIu64 "\n", my_address(b6));

   my_free(b3);

   my_free(b5);
   my_free(b6);

   printf("HEAP (2)\n");
   my_dump_mem(stdout);

   return 0;
}
