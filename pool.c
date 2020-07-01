#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#define NUM_NODES 10000000

typedef struct Node {
  int val;
  struct Node *next;
} Node;

typedef struct PoolObject {
  struct PoolObject *next;
  char mem[];
} PoolObject;

typedef struct {
  size_t num_objects;       // Number of objects in pool
  size_t object_size;       // Size of PoolObject
  size_t mem_size;          // Size of mem in bytes
  PoolObject *highest;      // Address of highest allocated object
  PoolObject *head;         // Free list head
  char *mem_end;            // Pointer to the byte after last valid byte
  char mem[];               // The pool memory
} Pool;

// Initialize a pool for allocating n objects of size s
Pool *pool_create(size_t n, size_t s) {
  size_t object_size = sizeof(PoolObject) + s;
  size_t mem_size = object_size * n;

  Pool *p = malloc(sizeof(Pool) + mem_size);
  *p = (Pool) {
    .num_objects = n,
    .object_size = object_size,
    .mem_size = mem_size,
    .highest = NULL,
    .head = NULL,
    .mem_end = p->mem + mem_size,
  };

  // Allocate then free an object to seed the free list
  PoolObject *po = (PoolObject *)p->mem;
  p->highest = po;
  po->next = NULL;
  p->head = po;

  return p;
}

// Free memory for entire pool
void pool_destroy(Pool *p) {
  free(p);
}

// Allocate an object from the pool
void *pool_alloc(Pool *p) {
  PoolObject *po = NULL;

  if(p->head != NULL) {
    // Allocate an object from the free list
    po = p->head;
    p->head = p->head->next;
  } else if((char *)(p->highest) + p->object_size < p->mem_end) {
    // Allocate an object from the end of the block
    p->highest = (PoolObject *)((char *)p->highest + p->object_size);
    po = p->highest;
  } else {
    // Out of memory
    return NULL;
  }

  po->next = NULL;
  return po->mem;
}

// Free an object from the pool
void pool_free(Pool *p, void *o) {
  PoolObject *po = (PoolObject*)((char *)o - offsetof(PoolObject,mem));
  po->next = p->head;
  p->head = po;
}



int main() {
  Pool *p = pool_create(NUM_NODES, sizeof(Node));

  Node *head = pool_alloc(p);
  *head = (Node){0, NULL};
  Node *tail = head;

  for(int i = 1; i < NUM_NODES-1; i++) {
    tail->next = pool_alloc(p);
    *tail->next = (Node){i,NULL};
    tail = tail->next;
  }

  // Remove any nodes that are a multiple of 3 or 5
  for(Node *n = head; n->next != NULL; n = n->next) {
    if(n->next->val % 3 == 0 || n->next->val % 5 == 0) {
      Node *del = n->next;
      n->next = n->next->next;
      pool_free(p, del);
    }
  }

  // After any node that is a multiple of 7, insert a 4
  for(Node *n = head; n->next != NULL; n = n->next) {
    if(n->next->val % 7 == 0) {
      Node *old_next = n->next->next;
      n->next = pool_alloc(p);
      *n->next = (Node){4, old_next};
    }
  }

  long int sum = 0;
  for(Node *n = head; n != NULL; n = n->next) {
    sum += n->val;
  }
  printf("%ld\n", sum);

  pool_destroy(p);
}
