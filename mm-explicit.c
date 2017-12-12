/*
 * mm-explicit.c - an empty malloc package
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 *
 * @id : 201402436 
 * @name : 조정진
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#define DEBUG
#ifdef DEBUG
# define dbg_printf(...) printf(__VA_ARGS__)
#else
# define dbg_printf(...)
#endif


/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

#define HDRSIZE 4
#define FTRSIZE 4
#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1<<12)
#define OVERHEAD 8

#define MAX(x,y) ((x)>(y) ? (x) : (y))
#define MIN(x,y) ((x)<(y) ? (x) : (y))

#define PACK(size, alloc) ((unsigned) ((size) | (alloc)))

#define GET(p) (*(unsigned *)(p))
#define PUT(p,val) (*(unsigned *)(p) = (unsigned)(val))
#define GET8(p) (*(unsigned long *)(p))
#define PUT8(p,val) (*(unsigned long *)(p) = (unsigned long)(val))

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE((char*)(bp) - DSIZE))

#define NEXT_FREEP(bp) ((char *)(bp))
#define PREV_FREEP(bp) ((char *)(bp) + WSIZE)

#define NEXT_FREE_BLKP(bp) ((char *)GET8((char *)(bp)))
#define PREV_FREE_BLKP(bp) ((char *)GET8((char *)(bp) + WSIZE))

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define SIZE_PTR(p) ((size_t*)(((char*)(p)) - SIZE_T_SIZE))

#define MIN_BLKSIZE 24

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(p) (((size_t)(p) + (ALIGNMENT-1)) & ~0x7)

static char *heap_listp = 0;
static char *heap_start = 0;
static char *epilogue = 0;

static void #extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void delete_freenode(void *bp);
static void insert_freenode(void *bp);
/*
 * Initialize: return -1 on error, 0 on success.
 */
int mm_init(void) {
	if((heap_listp = mem_sbrk(DSIZE + 4 * HDRSIZE)) == NULL)
	return -1;

	heap_start = heap_listp;

	PUT(heap_listp, NULL);
	PUT(heap_listp + WSIZE, NULL);
	PUT(heap_listp + DSIZE, 0);
	PUT(heap_listp + DSIZE + HDRSIZE, PACK(OVERHEAD,1));
	PUT(heap_listp + DSIZE + HDRSIZE + FTRSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp + DSIZE + 2 * HDRSIZE + FTRSIZE, PACK(0,1));

	heap_listp += DSIZE + DSIZE;

	epilogue = heap_listp + HDRSIZE;

	if(extend_heap(CHUNKSIZE/WSIZE) == NULL)
		return -1;

	return 0;
}

/*
 * malloc
 */
void *malloc (size_t size) {
	char *bp;
	unsigned asize;
	unsigned extendsize;

	if(size<=0)
		return NULL;

	asize = MAX(ALIGN(size + SIZE_T_SIZE), MIN_BLKSIZE);

	return NULL;
}

/*
 * free
 */
void free (void *ptr) {
    if(!ptr) return;
}

/*
 * realloc - you may want to look at mm-naive.c
 */
void *realloc(void *oldptr, size_t size) {
    return NULL;
}

/*
 * calloc - you may want to look at mm-naive.c
 * This function is not tested by mdriver, but it is
 * needed to run the traces.
 */
void *calloc (size_t nmemb, size_t size) {
    return NULL;
}


/*
 * Return whether the pointer is in the heap.
 * May be useful for debugging.
 */
static int in_heap(const void *p) {
    return p < mem_heap_hi() && p >= mem_heap_lo();
}

/*
 * Return whether the pointer is aligned.
 * May be useful for debugging.
 */
static int aligned(const void *p) {
    return (size_t)ALIGN(p) == (size_t)p;
}

/*
 * mm_checkheap
 */
void mm_checkheap(int verbose) {
}
