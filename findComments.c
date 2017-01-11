#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSymbolsInComment(char* str)
{
  int count = 0;
  int i = 0;

  while (str[i] != '\0')
  {
    if((str[i] != ' ') && (str[i] != '\t') && str[i] != '\n')
      count ++;
    i++;
  }
  return count;
}

int main()
{
  FILE *fr;
  int pos;
  int symbolsInAllcomments = 0;
  bool foundCommentWithStar = 0;
  char line[1000];
  char copy[1000];
  char *point;
  char *nameOfFile = (char*) malloc(100);

  printf("Input the name of your *.c file\n");
  scanf("%s", nameOfFile);

  fr = fopen(nameOfFile, "r");

  if (fr == NULL)
  {
    printf("Unable to open file \n");
    return 0;
  }

  while(fgets(line, sizeof(line), fr) != NULL)
  {
    if(strstr(line, "*/") == NULL && foundCommentWithStar)
    {
      symbolsInAllcomments += countSymbolsInComment(line);
      continue;
    }
    if ((point = strstr(line, "//")) != NULL  && !foundCommentWithStar)
    {
      strcpy(copy, point + 2);
      symbolsInAllcomments += countSymbolsInComment(copy);
    }
    else if((point = strstr(line, "/*")) != NULL && !foundCommentWithStar)
    {
      strcpy(copy, point + 2);
      symbolsInAllcomments += countSymbolsInComment(copy);
      foundCommentWithStar = 1;
    }

    if ((point = strstr(line, "*/")) != NULL && foundCommentWithStar)
    {
      for(pos = 0; pos < strlen(line); pos++)
      {
        if(&line[pos] == point)
          break;
        copy[pos] = line[pos];
      }
      copy[pos + 1] = '\0';
      symbolsInAllcomments += countSymbolsInComment(copy);
      foundCommentWithStar = 0;
    }
  }
  fclose(fr);
  printf("%d\n", symbolsInAllcomments);

  return 0;
}
