#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include "tree.h"
#include "mylib.h"

/**
 * A helper function that is used to print the info of a tree/subtrees freqeuncy
 * and its key
 * @param word is a char* to the key of the tree
 * @param freq the tree/subtree freqeuncy.
 */
static void print_info(int freq, char *word){
  printf("%-4d %s\n", freq, word);
}

/**
 * Prints help message for using this program to an I/O stream
 *
 * @param file is a pointer to I/O stream.
 */
static void print_help(FILE *file) {
   fprintf(file,"\n\n");
   fprintf(file," -c [filename] file to check spelling of words in using words read\n");
   fprintf(file,"    from stdin as dictionary. Prints timing info, unknown word\n");
   fprintf(file,"    count to stderr. When -c option is given -d -o are ignored\n");
   fprintf(file," -d Print depth of tree to stdout\n");
   fprintf(file,"    (defualt is linear)\n");
   fprintf(file," -f write dot output to file name instead of default if -o is also\n");
   fprintf(file,"    given.\n");
   fprintf(file," -o Ouput a representation of the tree in dot form to the file\n");
   fprintf(file,"    tree-view.dot\n");
   fprintf(file," -r Make tree an RBT instead of BST\n");
   fprintf(file," -h Displays help message describing program usage.\n");
}
/**
 * Main entry point for using hash table. Words are read in from
 * stdin and read into the hash table, they are then printed out
 * with there freqeuencies to stdout. Uses getopt library for
 * parsing arguments.
 * -c [filename] file to check spelling of words in using words read
 *    from stdin as dictionary. Prints timing info, unknown word
 *    count to stderr. When -c option is given -d -o are ignored
 * -d Print depth of tree to stdout
 *    (defualt is linear)
 * -f write dot output to file name instead of default if -o is also
 *    given.
 * -o Ouput a representation of the tree in dot form to the file
 *    tree-view.dot
 * -r Make tree an RBT instead of BST
 * -h Displays help message describing program usage.
 *
 * @param argc Total number of arguments used with program
 * @param argv Array of command line arguments
 */

int main(int argc, char **argv) {
  int option_c = 0;
  int option_d = 0;
  int option_o = 0;
  tree_t tree_type= BST;
  int words_and_freq = 1;
  const char *optstring = "c:df:orh";
  char file_name[256];
  char dot_file_name[256];
  int count_unknown_words=0;
  char option;
  clock_t clock_start;
  double time_search = 0;
  double clock_time_fill = 0;
  FILE *file;
  tree t;
  char word[256];

  while ((option = getopt(argc, argv, optstring)) != EOF) {
    switch (option) {
      case 'c':
        strcpy(file_name, optarg);
        option_c = 1;
        words_and_freq = 0;
        option_d = 0;
        option_o = 0;
        break;
      case 'd':
        option_d = 1;
        break;
      case 'f':
        strcpy(dot_file_name, optarg);
        /*option_f = 1;*/
        break;
      case 'o':
        option_o = 1;
        strcpy(dot_file_name, "tree-view.dot");
        break;
      case 'r':
        /*option_r = 1;*/
        tree_type = RBT;
        break;
      case 'h':
        fprintf(stderr, "Usage: %s [OPTION]... <STDIN>\n\n", argv[0]);
        print_help(stderr);
        exit(EXIT_FAILURE);
      default:
        fprintf(stderr, "Usage: %s [OPTION]... <STDIN>\n\n", argv[0]);
        print_help(stderr);
        exit(EXIT_FAILURE);
    }
  }
  t = tree_new(tree_type);

  while (getword(word, sizeof word, stdin) != EOF) {
    clock_start = clock();
    t = tree_insert(t, word);
    clock_time_fill += (clock() - clock_start) / (double) CLOCKS_PER_SEC;
  }

  if (option_c == 1) {
      file = fopen(file_name, "r"); /*read words from stdin in*/
      while (getword(word, sizeof word, file) != EOF) {
          clock_start = clock();
          if (tree_search(t, word) == 0) {
              fprintf(stderr, "%s\n", word);
              count_unknown_words++;
          }
          time_search += (clock() - clock_start) / (double) CLOCKS_PER_SEC;
      }
      printf("Fill time     : %f\n", clock_time_fill);
      printf("Search time   : %f\n", time_search);
      printf("Unknown words = %d\n", count_unknown_words);

      fclose(file);
    }

  if (option_d) {
    fprintf(stdout, "%d\n", tree_depth(t));
  }

  if (option_o) {
    printf("Creating dot file ");
    file = fopen(dot_file_name, "w");
    tree_output_dot(t, file);
    fclose(file);
  }

  if (words_and_freq) {
    tree_preorder(t, print_info);
  }
  tree_free(t);
  return EXIT_SUCCESS;
}
