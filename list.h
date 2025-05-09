typedef struct node {
  int value;
  struct node *next;
} node;
typedef struct {
  node *first;
} head;

head *create_list();
int count(head *p);
void add_to_start(head *p, int v);
void add_to_end(head *h, int v);
int add_by_index(head *h, int index, int v);
int remove_node(head *h, int index);
int find_node(head *h, int index, node *out);
void clean_memory(head *h);
#define INDEX_IS_OUT_OF_RANGE -1
