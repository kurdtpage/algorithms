#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void *emalloc(size_t s) {
    /* implementation of emalloc goes here */
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    /* implementation of erealloc goes here */
    void *result = realloc(p, s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}


struct bstnode {
    char *key;
    bst left;
    bst right;
};

bst bst_delete(bst b, char *str){
    if(b == NULL){
        /* do nothing */
        return b;
    }
    if(b->key == str){
        if(b->left == NULL && b->right == NULL){
            /* 0 children (leaf) */
            free(b->key);
            bst_free(b);
            /*b = NULL;*/
        }else{
            if(b->left != NULL && b->right != NULL){
                /* 2 children */
                
            }else{
                /* 1 child */
                if(b->left == NULL){
                    b = b->right;
                    bst_free(b->right);
                }else{
                    b = b->left;
                    bst_free(b->left);
                }
            }
        }
        return b;
    }
    if(str < b->key){
        b->left = bst_insert(b->left, str);
        return b;
    }
    if(str > b->key){
        b->right = bst_insert(b->right, str);
        return b;
    }
    return b;
}

void print_bst(char *str){
    printf("%s", str);
}

void bst_inorder(bst b, void f(char *str)){
    if(b == NULL) return; /* stopping case */
    /* inorder traverse the left subtree */
    bst_inorder(b->left, f);
    /* apply f to b->key */
    f(b->key);
    /* inorder traverse the right subtree */
    bst_inorder(b->right, f);
}

bst bst_new(){
    bst bst = emalloc(sizeof *bst);
    bst->key = NULL;
    bst->left = NULL;
    bst->right = NULL;
    return bst;
}

bst bst_insert(bst b, char *str){
    if(b == NULL){
        b = bst_new();
        /*b->left = NULL;
        b->right = NULL;*/
     }
    if (b->key == NULL) {
        b->key = emalloc((strlen(str) + 1) * sizeof str[0]);
        strcpy(b->key, str);
        return b;
    }
    
    if(strcmp(str, b->key) == 0){
        /* do nothing */
        return b;
    }
    if(strcmp(str, b->key) < 0) {
        b->left = bst_insert(b->left, str);
    }
    if(strcmp(str, b->key) > 0) {
        b->right = bst_insert(b->right, str);
    }
    
    return b;
}

void bst_preorder(bst b, void f(char *str)){
    if(b == NULL) return; /* stopping case */
    /* apply f to b->key */
    f(b->key);
    /* preorder traverse the left subtree */
    bst_preorder(b->left, f);
    /* preorder traverse the right subtree */
    bst_preorder(b->right, f);
}

int bst_search(bst b, char *str){
    if(b == NULL){
        return 0;
    }
    if(b->key == str){
        return 1;
    }
    if(str < b->key){
        return bst_search(b->left, str);
    }
    if(str > b->key){
        return bst_search(b->right, str);
    }
    return 0;
}

bst bst_free(bst b){
    free(b);
    return b;
}

int main(void){
    
    bst b = bst_new();
    
    bst_insert(b, "m");
    bst_insert(b, "a");
    bst_insert(b, "z");
    bst_insert(b, "f");
    bst_insert(b, "e");
    bst_insert(b, "n");
    
    bst_inorder(b, print_bst);
    bst_free(b);
    
    return EXIT_SUCCESS;
}
