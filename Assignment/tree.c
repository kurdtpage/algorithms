#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

/**
 * Implementation for a tree ADT that can be either a BST or RBT
 * by specifying which type by the static tree_type variable
 * @author Jacques Jamieson, Mark Baker, Shaun Henderson
 */

/*Macros used for checking the color of a node and setting the correct colour */
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

static tree_t tree_type;

struct tree_node {
    char *key;
    rbt_colour colour;
    tree left;
    tree right;
    int frequency;
};

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
  if(t->key != NULL) {
    fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
            t->key, t->key, t->frequency,
            (RBT == tree_type && RED == t->colour) ? "red":"black");
  }
  if(t->left != NULL) {
    tree_output_dot_aux(t->left, out);
    fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
  }
  if(t->right != NULL) {
    tree_output_dot_aux(t->right, out);
    fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
  }
}

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
  fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
  tree_output_dot_aux(t, out);
  fprintf(out, "}\n");
}

/**
 * Traverses the tree until a NULL node is found then return 0 if it is NULL
 * and return 1 otherwise. This is repeated for left and right
 *
 * @param t the tree to traverse.
 */
int tree_depth(tree t) {
  int height;
  int heightL = 0;
  int heightR = 0;
  if(t == NULL){
    return 0;
  }
  height = 1;
  if(t->left == NULL && t->right == NULL){
    height = 0;
  }
  if( t->left != NULL){
    heightL = tree_depth(t->left);
  }
  if(t->right != NULL) {
    heightR = tree_depth(t->right);
  }
  if(heightL>heightR){
    return heightL + height;
  }
  return heightR + height;
}

/**
 * In place left rotation of tree/subtree when fixing RBT after inserting a node
 *
 * @param r the tree/subtree to left rotate.
 */
static tree left_rotate(tree r) {
    tree temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

/**
 * In place right rotation of tree/subtree when fixing RBT after inserting a node
 *
 * @param r the tree/subtree to left rotate.
 */
static tree right_rotate(tree r) {
    tree temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

/**
 * Tree fixes the RBT after inserting a new node. It checks for repeating RED
 * nodes in both left and right tree/subtrees and either left rotates or right
 * to and changes the colors in order to fix the coloring
 *
 * @param r the tree/subtree to fix.
 */
static tree rbt_fix(tree r) {
    if(IS_RED(r->left)){
        if(IS_RED(r->left->left)){
            if(IS_RED(r->right)){
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            }else if(IS_BLACK(r->right)){
                r=right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        } else if (IS_RED(r->left->right)) {
            if(IS_RED(r->right)){
                r->colour=RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            }else if(IS_BLACK(r->right)){
                r->left = left_rotate(r->left);
                r = right_rotate(r);
                r->colour = BLACK;
                r->right->colour = RED;
            }
        }
    } else if(IS_RED(r->right)) {
        if (IS_RED(r->right->left)) {
            if (IS_RED(r->left)) {
                r->colour = RED;
                r->left->colour = BLACK;
                r->right->colour = BLACK;
            } else if (IS_BLACK(r->left)) {
                r->right = right_rotate(r->right);
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        }else if (IS_RED(r->right->right)) {
            if (IS_RED(r->left)){
                r->colour = RED;
                r->left->colour= BLACK;
                r->right->colour = BLACK;
            }
            else if (IS_BLACK(r->right)) {
                r = left_rotate(r);
                r->colour = BLACK;
                r->left->colour = RED;
            }
        }
    }
    return r;
}

/**
 * Inserts a key into the tree/subtree. Works for both BST and RBT
 *
 * @param b the tree/subtree to insert key into.
 */
tree tree_insert(tree b, char *str) {
    if(b == NULL){
      b = tree_new(tree_type);
    }
    if (b->key == NULL) {
        b->key = emalloc((strlen(str) + 1) * sizeof  str[0]);
        strcpy(b->key, str);
        return b;
    }
    if(strcmp(str, b->key) == 0) {
        b->frequency++;
    }
    else if(strcmp(str, b->key) < 0) {
        b->left = tree_insert(b->left, str);
    }
    else if(strcmp(str, b->key) > 0) {
        b->right = tree_insert(b->right, str);
    }
    if(tree_type == RBT){
        b = rbt_fix(b);
    }
    return b;
}

/**
 * Traverse tree in inorder and apply the function to print out the frequency
 * and the key
 * @param f is a function that takes in two paramaters int and char
 * @param b the tree/subtree to traverse.
 */
void tree_inorder(tree b, void f(int i, char *str)) {
    if(NULL == b){ /*Base case to stop recursion*/
        return;
    }
    tree_inorder(b->left, f);  /*inorder traverse left subtree*/
    f(b->frequency ,b->key);                 /*apply the function to the key*/
    /*
    if (tree_type == RBT && IS_RED(b)) {
        f("=> RED \n");
    } else if (tree_type == RBT && IS_BLACK(b)) {
        f("=> BLACK \n");
    }*/
    tree_inorder(b->right, f); /*inorder traverse right subtree*/
}

/**
 * Search the tree for a key. If key is found then return 1 or if not found
 * then return 0
 * @param str the key to look for
 * @param b the tree/subtree to search.
 */
int tree_search(tree b, char *str) {
    /*if key tree is null return 0*/
    if (NULL == b) {
        return 0;
    }
    if (strcmp(b->key, str) == 0) {
        return 1;
    }
    if(strcmp(str, b->key) < 0) {
        return tree_search(b->left, str);
    }
    if(strcmp(str, b->key) > 0) {
        return tree_search(b->right, str);
    }
    return 0;
}

/**
 * Traverse the tree in preorder and apply a function to print out frequency
 * and print out the key
 *
 * @param f is a function that takes in a int and char*
 * @param b the tree/subtree to traverse.
 */
void tree_preorder(tree b, void f(int i, char *str)) {
    if (NULL == b) {
        return;
    }
    f(b->frequency, b->key);
    /*if (tree_type == RBT && IS_RED(b)) {
        f("=> RED \n");
    } else if (tree_type == RBT && IS_BLACK(b)) {
        f("=> BLACK \n");
    }*/
    tree_preorder(b->left, f);
    tree_preorder(b->right, f);
}

/**
 * Traverse tree in postorder to free memory of every node and return NULL when
 * finished freeing
 *
 * @param t the tree/subtree to free memory.
 */
tree tree_free(tree t){
  if (t->key != NULL) {
    free(t->key);
    t->key = NULL;
  }
  if (t->left != NULL) {
    t->left = tree_free(t->left);
  }
  if (t->right != NULL) {
    t->right = tree_free(t->right);
  }
  if (t->key == NULL && t->left == NULL && t->right == NULL) {
    free(t);
    t = NULL;
  }
  return NULL;
}

/**
 * Creates a new tree and sets the key, left,right to NULL and sets type
 * of tree provided by input parameter and returns it. By default color is
 * set to RED.
 *
 * @param t the type tree/subtree to create.
 */
tree tree_new(tree_t type) {
    tree t = emalloc(sizeof(struct tree_node));
    t->key = NULL;
    t->left = NULL;
    t->right = NULL;
    tree_type = type;
    t->colour = RED;
    t->frequency = 0;
    return t;
}
