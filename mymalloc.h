#ifndef MYMALLOC_H_
#define MYMALLOC_H_

#define KiB 1024
#define MiB (1024 * KiB)

/**
 * @brief Initializer, guaranteed to be called before any memory request
 */
void my_malloc_init();

/**
 * @brief  Allocate a block of memory of size size.
 * @param  [in] size   the requested size of the block.
 * @retval the pointer to the block or a negative value
 *         if the request cannot be fulfilled. 
 */
void *my_malloc(size_t size);

/**
 * @brief Free a previously allocated block so that it
 *        becomes available again. 
 *        If possible, coalesc the block with adjacent free 
 *        blocks.
 * @param [in] ptr   the pointer to the block. 
 */
void my_free(void *ptr);

/**
 * @brief Dump a graphical representation of the state of the 
 *        mymalloc heap to the stream.
 * @param [in] stream   the stream to write to. 
 */ 
void my_dump_mem(FILE *stream);

/** 
 * @brief  Translate an absolute pointer address to the relative
 *         address (in MiB) within the mymalloc heap.
 * @param  [in] ptr   the address to translate.
 * @retval The translated address in MiB. 
 */
uint64_t my_address(void *ptr);

#endif // MYMALLOC_H_
