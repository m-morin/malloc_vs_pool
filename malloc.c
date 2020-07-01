#include <stdlib.h>
#include <stdio.h>
#define NUM_NODES 10000000

typedef struct Node {
  int val;
  struct Node *next;
} Node;

int main() {
  Node *head = malloc(sizeof(Node));
  *head = (Node){0, NULL};
  Node *tail = head;

  for(int i = 1; i < NUM_NODES-1; i++) {
    tail->next = malloc(sizeof(Node));
    *tail->next = (Node){i,NULL};
    tail = tail->next;
  }

  // Remove any nodes that are a multiple of 3 or 5
  for(Node *n = head; n->next != NULL; n = n->next) {
    if(n->next->val % 3 == 0 || n->next->val % 5 == 0) {
      Node *del = n->next;
      n->next = n->next->next;
      free(del);
    }
  }

  // After any node that is a multiple of 7, insert a 4
  for(Node *n = head; n->next != NULL; n = n->next) {
    if(n->next->val % 7 == 0) {
      Node *old_next = n->next->next;
      n->next = malloc(sizeof(Node));
      *n->next = (Node){4, old_next};
    }
  }

  long int sum = 0;
  for(Node *n = head; n != NULL; n = n->next) {
    sum += n->val;
  }
  printf("%ld\n", sum);

  for(Node *n = head; n != NULL;) {
    Node *next = n->next;
    free(n);
    n = next;
  }
}
