#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct bag* build_bag(struct bag *current_bag, char **inputs, long unsigned int);

void print_bags(struct bag *);

void print_bag(struct bag*);

void reset_bag(struct bag *bag);

void build_bags_tree(struct bag* current, char **inputs, long unsigned int inputs_size);

long unsigned int qty(struct bag *current_bag);

struct bag{
  int qty;
  char *color;
  struct bag **contains;
  int contains_size;
};
