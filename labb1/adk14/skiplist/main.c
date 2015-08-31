/* This file contains a sample driver program to test out skiplists...
 * This code is pretty blah.  It isn't meant as much except something
 * to verify the skiplist implementation.
 *
 *    Dominic Giampaolo  (nick@maxine.wpi.edu)
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "skiplist.h"

/* Why does it seem that TRUE and FALSE are never defined anywhere? Doesn't 
 * it seem like they would be useful to have define in standard header 
 * files?
 */
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

SkipList makeskiplist(char **table, int num);
int	 print_item(char *item);
int	 find_item(char *item, char *key);
void     do_help(void);
char    *mystrdup(char *str);

int stringcompare(char *i, char *j)
{
  return strcmp(i, j);
}

void stringfree(char *s)
{
   free(s);
}


#define SAMPLE_SIZE 512      /* how many elements to test with */

void main(void)
{
  SkipList l = NULL;
  int i, start, end;
  int keep_going = TRUE;
  char **keys = NULL;
  char *v;
  char buff[256];

  printf("Creating items to put in SkipList...");
  fflush(stdout);

  keys = (char **)malloc(SAMPLE_SIZE * sizeof(char **));
  if (keys == NULL)
    exit(50);

  l = makeskiplist(keys, SAMPLE_SIZE);
  if (l == NULL)
    exit(30);

  do_help();   /* print an initial help message */

  while(!feof(stdin) && keep_going == TRUE)
   {
     printf("Enter your command :");   fflush(stdout);

     if (fgets(buff, 256, stdin) == NULL)
       continue;
     buff[strlen(buff)-1] = '\0';   /* chop off the trailing newline */

     if (isupper(*buff))
       *buff = tolower(*buff);

     switch(*buff)
      {
	case 'a' : v = (char *)mystrdup(buff+2);
		   if (v == NULL)
		     break;
		   i = InsertSL(l, v);
		   if (i == FALSE)
		     printf("Element <%s> not added properly\n", v);
		   else if (i == DUPLICATE_ITEM)
		     printf("Tried to add a duplicate item <%s>\n", v);
		   break;

	case 'f' : DoForSL(l, find_item, buff+2);
		   break;

	case 'd' : if (DeleteSL(l, buff+2) != FALSE)
		     printf("Element deleted properly\n");
		   else
		     printf("Element <%s> not found...\n", buff+2);
		   break;

	case 'p' : DoForSL(l, print_item, NULL);
		   break;

	case 's' : if ((v = (char *)SearchSL(l, buff+2)))
		     printf("Found element with value : %s.\n", v);
		   else
		     printf("Element <%s> not found.\n", buff+2);
		   break;

	case 'q' :
        case 'x' : keep_going = FALSE;
	           break;

	case '?' : do_help();
		   break;

	default  : printf("Unknown command : <%s>\n", buff);
		   break;
      }
   }

  printf("Searching for element %s.\n", keys[1]);

  if ((v = (char *)SearchSL(l, keys[1])))
    printf("Found element with value : %s.\n", v);
  else
    printf("Element NOT found, instead found : %s.\n", v);


  printf("Deleting elements 0 - %d. ", SAMPLE_SIZE);
  fflush(stdout);
  start = time(NULL);

  for(i=0; i < SAMPLE_SIZE; i++)
   {
    if (DeleteSL(l, keys[i]) == FALSE)
      printf("BUG : element %d (%s) not removed properly.\n", i, keys[i]);
   }

  end = time(NULL);
  printf("Took %d seconds.\n", end - start);

  printf("Attempting to delete last element in list (SHOULDN'T WORK)...\n");
  if (DeleteSL(l, keys[SAMPLE_SIZE - 1]) == FALSE)
    printf("Great, things are working fine.\n");


  printf("\nFreeing list...\n");
  FreeSL(l);
  printf("List freed.\n");

  free(keys);
  exit(0);
}



/* Used to print out the elements of the list.  Up above we call DoForSL() 
 * with a pointer to this function and DoForSL() calls this routine 
 * with a pointer to the element in the list, and we do what we want 
 * with it (in this case that is printing).
 */
int print_item(char *item)
{
  printf("%s\n", item);

  return TRUE;
}


/* This is used when doing a sequential search of the list using the
 * list iterator DoForSL()
 */
int find_item(char *item, char *key)
{
  if (strcmp(key, item) == 0)
    { 
      printf("Found item (%s == %s)\n", key, item); 
      return FALSE; 
    }
  return TRUE;
}


void do_help(void)
{
  printf("Your command can be one of :\n");
  printf("\ta <string> : add <string> to skiplist\n");
  printf("\td <string> : delete <string> from skiplist\n");
  printf("\tf <string> : sequential (slow) search for <string> in skiplist\n");
  printf("\tp          : print ENTIRE skiplist (could be long)\n");
  printf("\ts <string> : search for <string> in skiplist\n");
  printf("\tq          : quit program\n");
  printf("\tx          : quit program\n");
  printf("\t?          : this help\n");
}


SkipList makeskiplist(char **keys, int num)
{
  int i,k, size;
  int  start, end;
  SkipList l;

  srand(time(NULL) | 0x01);    /* seed with an odd number */

  /* now go through and make some random ASCII strings */
  for(i=0; i < num; i++)
   {
     size    = (rand() % 24) + 8;
     keys[i] = (char *)malloc(size + 1);
     if (keys[i] == NULL)
       { printf("couldn't build a string...\n"); exit(50); }

     for(k=0; k < size-1; k++)
       keys[i][k] = (rand() % 26) + 'a';

     keys[i][k] = '\0';
   }
  printf("...done.\n");


  /*
   * If you wanted to allow duplicates in the list, you'd do it like this : 
   *     l = NewSL(stringcompare, stringfree, ALLOW_DUPLICATES); 
   */
 
  l = NewSL(stringcompare, stringfree, NO_DUPLICATES);
  if (l == NULL)
    { printf("Error adding creating list.\n"); return NULL; }

  printf("Skiplist created.  Adding elements...");
  fflush(stdout);

  start = time(NULL);
  for(k=0; k < num; k++)
    {
      i = InsertSL(l, keys[k]);
      if (i == DUPLICATE_ITEM)
	printf("Error, item already in list.\n");
      else if (i == FALSE)
	{ FreeSL(l); printf("Error adding element.\n"); return NULL; };
    }
  end = time(NULL);

  printf("done.  Added %d elements in %d seconds.\n", num, end - start);

  return l;
}


/* unfortunately strdup() isn't in every library, so I have to include
 * it here.  Sigh, when will the world really be ANSI....
 */
char *mystrdup(char *str)
{
  int len;
  char *ptr;

  len = strlen(str) + 1;

  ptr = (char *)malloc(len);
  if (ptr)
    strcpy(ptr, str);

  return ptr;
}
