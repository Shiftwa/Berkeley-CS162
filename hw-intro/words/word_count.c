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

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utililties */

char *new_string(char *str)
{
  return strcpy((char *)malloc(strlen(str) + 1), str);
}

void init_words(WordCount **wclist)
{
  /* Initialize word count.  */
  printf("%s", "敷之前");
  // printf("%d",(*(*wclist)).count);

  (*wclist)->word = NULL;
  (*wclist)->count = 0;
  (*wclist)->next = NULL;
}

size_t len_words(WordCount *wchead)
{
  size_t len = 0;
  while (wchead->next != NULL)
  {
    len++;
    wchead = wchead->next;
  }

  return len;
}

WordCount *find_word(WordCount *wchead, char *word)
{
  /* Return count for word, if it exists */
  WordCount *wc = malloc(sizeof(WordCount));
  //写法1:
  wc = wchead;
  do
  { 
    if (strcmp(word, wc->word) == 0)
    {
      return wc;
    }

    wc = wc->next;

  } while (wc != NULL);  
  //写法2:
  //  for (wc = wchead; wc->next!=NULL; wc = wc->next)
  // {
  //    if(strcmp(word,wc->word)==0){
  //     return wc;
  //    }
  // }
  return NULL;
}

void add_word(WordCount **wclist, char *word2)
{
  /* If word is present in word_counts list, increment the count, otw insert with count 1. */

  WordCount *a = (WordCount *)malloc(sizeof(WordCount));
  WordCount *b = (WordCount *)malloc(sizeof(WordCount));
  WordCount *c = (WordCount *)malloc(sizeof(WordCount));
  (b->count) = 1;
  (b->next) = (WordCount *)malloc(sizeof(WordCount));
  char *str = malloc(sizeof(char) * 50);
  strcpy(str, word2);
  (b->word) = str;

  //如果链表为空，则插入第一个节点
  if ((*wclist)->word == NULL)
  {

    *wclist = b;
    //  printf("%p\n",b);
    // printf("%p\n",(*wclist));
    printf("%s\n", ((*wclist)->word));
  }
  else
  {
    if ((c = find_word(*wclist, word2)) != NULL)
    {
      (c->count)++;
    }
    else
    {
      a = *wclist;
      while (((a->next)->count) != 0)
      {
        a = a->next;
      }

      a->next = b;
    }
  }
}

void fprint_words(WordCount *wchead, FILE *ofile)
{
  /* print word counts to a file */
  WordCount *wc;

  for (wc = wchead; wc->next != NULL; wc = wc->next)
  {
    //  printf("%p\n",(wchead));
    //  printf("%s",wchead->word);
    //  printf("%i%s\n", wc->count, wc->word);

    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}
