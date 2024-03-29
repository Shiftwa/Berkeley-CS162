/*

  Word Count using dedicated lists

*/

/*
Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <assert.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "word_count.h"
bool too_long;
/* Global data structure tracking the words encountered */
WordCount *word_counts = NULL;

/* The maximum length of each word in a file */
#define MAX_WORD_LEN 64

/*
 * 3.1.1 Total Word Count
 *
 * Returns the total amount of words found in infile.
 * Useful functions: fgetc(), isalpha().
 */
int num_words(FILE *infile)
{
  int num_words = 0;
  char ch;
  bool lastBlank = 0;
  if (infile == NULL)
  {
    printf("Could not oopen the file \n");
    return 1;
  }

  while ((ch = fgetc(infile)) != EOF)
  {
    if (!isalpha(ch))
    {
      lastBlank = 1;
    }
    else if (isalpha(ch) && lastBlank)
    {
      /* code */
      num_words++;
      lastBlank = 0;
    }
  }

  return num_words + 1;
}

/*
 * 3.1.2 Word Frequency Count
 *
 * Given infile, extracts and adds each word in the FILE to `wclist`.
 * Useful functions: fgetc(), isalpha(), tolower(), add_word().
 */

void count_words(WordCount **wclist, FILE *infile)
{
   int SPACE = ' ', CR = '\n', LF = '\r';
  bool is_word = false;
  int c, i = 0;
  char buffer[MAX_WORD_LEN];
  // c = fgetc(infile);
  do{
    c = fgetc(infile);
    // printf("%c\n",c);
    if(isalpha(c)!=0){
      is_word = true;
      buffer[i++] = tolower(c);
    }
    else {
      if(is_word){
        buffer[i] = '\0';
        i = 0;
        // printf("%s\n",buffer);
       add_word(wclist,  buffer);
        buffer[0] = '\0';  
        is_word = false;
       }
    }
    if(i > MAX_WORD_LEN){
        too_long = true;
      	printf("%s\n", "WORD LEN > MAX_WORD_LEN !");
      	break;
    }
  }while(c!=EOF); 
}



/*
 * Comparator to sort list by frequency.
 * Useful function: strcmp().
 */
static bool wordcount_less(const WordCount *wc1, const WordCount *wc2)
{
 return (wc1->count==wc2->count?strcmp(wc1->word,wc2->word)<0:wc1->count<wc2->count);
}

// In trying times, displays a helpful message.
static int display_help(void)
{
  printf("Flags:\n"
         "--count (-c): Count the total amount of words in the file, or STDIN if a file is not specified. This is default behavior if no flag is specified.\n"
         "--frequency (-f): Count the frequency of each word in the file, or STDIN if a file is not specified.\n"
         "--help (-h): Displays this help message.\n");
  return 0;
}

/*
 * Handle command line flags and arguments.
 */
int main(int argc, char *argv[])
{
  word_counts = ((WordCount *)malloc(sizeof(WordCount)));

  // Count Mode (default): outputs the total amount of words counted
  bool count_mode = true;
  int total_words = 0;

  // Freq Mode: outputs the frequency of each word
  bool freq_mode = false;

  FILE *infile = NULL;

  // Variables for command line argument parsing
  int i;
  static struct option long_options[] =
      {
          {"count", no_argument, 0, 'c'},
          {"frequency", no_argument, 0, 'f'},
          {"help", no_argument, 0, 'h'},
          {0, 0, 0, 0}
          };

  // Sets flags
  while ((i = getopt_long(argc, argv, "cfh", long_options, NULL)) != -1)
  {
    switch (i)
    {
    case 'c':
      count_mode = true;
      freq_mode = false;
      break;
    case 'f':
      count_mode = false;
      freq_mode = true;
      break;
    case 'h':
      return display_help();
    }
  }

  if (!count_mode && !freq_mode)
  {
    printf("Please specify a mode.\n");
    return display_help();
  }

  /* Create the empty data structure */
  init_words(&word_counts);

  if ((argc - optind) < 1)
  {
    // No input file specified, instead, read from STDIN instead.
    infile = stdin;
  }
  else
  {
    // At least one file specified. Useful functions: fopen(), fclose().
    // The first file can be found at argv[optind]. The last file can be
    // found at argv[argc-1].
    //  for(int i =0; i<argc-1; i++){
    infile = fopen(argv[argc - 1], "r");
    // printf(argc);
    //total_words = num_words(infile);
   // fclose(infile);
  }
  // }

  if (count_mode)
  {
    // printf("The total number of words is: %i\n", total_words);
    // count_words(&word_counts,infile);
    // printf("第一个字%d",word_counts->count);

    printf("The frequencies of each word are: \n");
    infile = fopen(argv[argc - 1], "r");
    count_words(&word_counts, infile);
    fprint_words(word_counts, stdout);
  }
  else
  {
    // wordcount_sort(&word_counts, wordcount_less);

    // printf("The frequencies of each word are: \n");
    // fprint_words(word_counts, stdout);
  }
  return 0;
}
