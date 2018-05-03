#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "mymalloc.h"

static void *mem;

typedef int bool;
#define true 1
#define false 0

struct block
{
   int size;
   bool isFree; // boolean
   struct block *adj; // blocks it touches
};

struct block *root;

void my_malloc_init(size_t size)
{
   mem = malloc(size);
   root = mem;
   *root = (struct block) {size, true, NULL};
}

void *my_malloc(size_t size)
{
   struct block *find = root;
   while((find->size < size || !find->isFree) && (find->adj != NULL)) 
   {
      find = find->adj;
   }
   
   if (!find->isFree || find->size < size) // means it is at the end and isn't at an allocatable block 
   {
      return NULL;
   } 
   else if (find->size == size)
   {
      find->isFree = 0;
      return (void*)(find);
   }
   
   struct block *open = (struct block*)((char*)find + size);
   *open = (struct block) {(find->size) - size, true, find->adj}; 
   *find = (struct block) {size, false, open}; 
   return (void*)(find);
}

void my_free(void *ptr)
{
   struct block *bl = ptr;
   bl->isFree = 1;
   
   struct block *tmp;
   tmp = root;
   while(tmp->adj != NULL) {
      if (tmp->isFree && tmp->adj->isFree) {
         tmp->size += (tmp->adj->size);
         tmp->adj = tmp->adj->adj;
      } else {
         tmp = tmp->adj;
      }
      
   }
}

static void draw_box(FILE *stream, int size, int empty, int last)
{
   int i;
   int pad = size / 2;

   fprintf(stream, "+---------------------+\n");

   if (!empty) fprintf(stream, "%c[%d;%dm", 0x1B, 7, 37);

   for (i=0; i<pad; i++)
   {
      fprintf(stream, "|                     |\n");
   }

   fprintf(stream, "|         %2d          |\n", size);

   for (i++; i<size; i++)
   {
      fprintf(stream, "|                     |\n");   
   }

   if (!empty) fprintf(stream, "%c[%dm", 0x1B, 0);

   if (last) fprintf(stream, "+---------------------+\n");
}

void my_dump_mem(FILE *stream)
{
   struct block *tmp;
   tmp = root;
   while(tmp->adj != NULL) {
      draw_box(stream, (int)(tmp->size/MiB), tmp->isFree, 0);
      tmp = tmp->adj;      
   }
   draw_box(stream, tmp->size / MiB, tmp->isFree, 1);
}

uint64_t my_address(void *ptr)
{
   return ((((uint64_t) ptr) - ((uint64_t) mem)) / MiB);
}
