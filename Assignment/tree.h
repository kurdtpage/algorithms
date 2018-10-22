#ifndef TREE_H_
#define TREE_H_

/**
 * Header file for a tree ADT that can be either a BST or RBT
 * by specifying which type
 * @author Jacques Jamieson, Mark Baker, Shaun Henderson
 */
#include <stdio.h>
typedef struct tree_node *tree;
typedef enum {RED, BLACK} rbt_colour;
typedef enum tree_e { BST, RBT } tree_t;

extern tree   tree_free(tree t);
extern void   tree_inorder(tree t, void f(int i, char *str));
extern tree   tree_insert(tree t, char *str);
extern tree   tree_new(tree_t t);
extern void   tree_preorder(tree t, void f(int i, char *str));
extern int    tree_search(tree t, char *str);
extern int    tree_depth(tree t);
extern void   tree_output_dot(tree t, FILE *out);
#endif
