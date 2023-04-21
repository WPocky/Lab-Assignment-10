#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26

// defining a struct Trie
struct Trie {
    struct Trie* children[SIZE];
    int count;
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie* temp = *ppTrie;
    int len = strlen(word);
    for(int i = 0; i < len; i++) {
        int index = word[i] - 'a';

        if(temp->children[index] == NULL) {
            temp->children[index] = (struct Trie*)malloc(sizeof(struct Trie));

            for(int j = 0; j < SIZE; j++) {
                temp->children[index]->children[j] = NULL;
            }
            temp->children[index]->count = 0;
        }
        temp = temp->children[index];
    }
    temp->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie* temp = pTrie;
    int len = strlen(word);
    for(int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        
        if(temp->children[index] == NULL) {
            return 0;
        }
        temp = temp->children[index];
    }
    return temp->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if(pTrie == NULL)
        return NULL;
    
    for(int i = 0; i < SIZE; i++) {
        if(pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
    /* I am not sure what I'm supposed to do to the main fucntion since I don't have an input file
    but I created a Trie struct and read the number of words in the dictionary and added those words
    to the data struct, I also fixed a typo in the "deallocateTree" function call. When trying to run
    code, it returned errors at lines 84 and 86 for incorrect pointer types but since that is part of the
    given code, I am leaving it alone.*/

    struct Trie* trie = (struct Trie*)malloc(sizeof(struct Trie));

      //read the number of the words in the dictionary
      //assuming the first input from the user will be a number
      int wordCount;
      scanf("%d", &wordCount);
      // parse line  by line, and insert each word to the trie data structure
      // assuming no word will be larger than 50 characters
      char dictWord[50];
      for(int i = 0; i < wordCount; i++) {
        scanf("%s", dictWord);
        insert(&trie, dictWord);
      }

      char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
      for (int i=0;i<5;i++)
      {
          printf("\t%s : %d\n",pWords[i], numberOfOccurances(&trie, pWords[i]));
     }
    trie = deallocateTrie(&trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}