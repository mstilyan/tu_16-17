#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define N 1000

void inpFromFile(FILE* fr, char lineWithMinSymbols[], int* numOfIfElse, int* brackets);
void outpInFile(FILE* fw, char lineWithMinSymbols[], int* numOfIfElse, int* brackets);
void outpInConsole(char lineWithMinSymbols[], int* numOfIfElse, int* brackets);
void inpFromConsole(char lineWithMinSymbols[], int* numOfIfElse, int* brackets);

int main()
{
  FILE *readf;
  FILE *writef;
  int choice;
  int numOfIfElse = 0;
  int countOfBracketsAfterIf = 0;
  char lineWithMinSymbols[N] = {0};

  printf("\t choose from menu \n");
  printf("1: input - *.c file / output - *.txt file \n");
  printf("2: input - *.c file / output - console \n");
  printf("3: input - console / output - *.txt file \n");
  printf("4: input/output - console \n");
  printf("5: EXIT\n");

  do {
    scanf("%d", &choice);
    switch (choice)
    {
      case 1:
        inpFromFile(readf, lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        outpInFile(writef, lineWithMinSymbols, &numOfIfElse,&countOfBracketsAfterIf);
        break;
      case 2:
        inpFromFile(readf, lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        outpInConsole(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        break;
      case 3:
        inpFromConsole(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        outpInFile(writef, lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        break;
      case 4:
      inpFromConsole(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
      outpInConsole(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        break;
    }

    if(choice < 1 || choice > 5)
      printf("Invalid input! Please try again.\n");
  } while(choice < 1 || choice > 5);

  return 0;
}

void inpFromFile(FILE* fr, char lineWithMinSymbols[], int* numOfIfElse, int* brackets)
{
  char *pointElse = NULL;
  char *pointIf = NULL;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  bool searchNextLine = false;
  int numMinSymbls = 0;
  char *nameOfFile = (char*) malloc(100);
  int posOfBrack = 0;

  printf("Input the name of your *.c file\n");
  scanf("%s", nameOfFile);

  fr = fopen(nameOfFile, "r");
  if (fr == NULL)
  {
    printf("Unable to open or allocate your file \n");
    return;
  }

  while ((read = getline(&line, &len, fr)) != -1)
  {
    if (searchNextLine && *(line + posOfBrack) == '{')
    {
      (*brackets)++;
      searchNextLine = false;
    }

    if ((pointIf = strstr(line, "if (")) != NULL || (pointIf = strstr(line, "if(")) != NULL)
    {
      posOfBrack = 0;
      searchNextLine = true;
      (*numOfIfElse)++;

      for (;posOfBrack < strlen(line); posOfBrack++)
        if ( (line + posOfBrack) == pointIf)
          break;

      if (strchr(pointIf,'{') != NULL)
      {
        (*brackets)++;
        searchNextLine = false;
      }
    }
    else if ((pointElse = strstr(line, "else (")) != NULL || (pointElse = strstr(line, "else(")) != NULL)
      (*numOfIfElse)++;
    if (*(line + 0) != '\n' && read < numMinSymbls)
    {
      numMinSymbls = read;
      for (int i = 0; i <= strlen(line); i++)
        lineWithMinSymbols[i] = *(line + i);
    }
  }

  fclose(fr);
  free(pointElse);
  free(pointIf);
  free(line);
  free(nameOfFile);
  return;
}

void outpInFile(FILE* fw, char lineWithMinSymbols[], int* numOfIfElse, int* brackets)
{
  fw = fopen("result.txt", "w");
  if (fw == NULL)
    printf("Unable to open/find file result.txt");

  fprintf(fw, "Number of 'if/if else' operators found is: %d\n", *numOfIfElse);
  fprintf(fw, "Shortest line found:\n%s", lineWithMinSymbols);
  fprintf(fw, "Number of brackets found after 'if' operators is: %d\n", *brackets);

  fclose(fw);
  return;
}

void outpInConsole(char lineWithMinSymbols[], int* numOfIfElse, int* brackets)
{
  printf("\nNumber of 'if/if else' operators found is: %d\n", *numOfIfElse);
  printf("Shortest line found:\n%s", lineWithMinSymbols);
  printf("Number of brackets found after 'if' operators is: %d\n", *brackets);

  return;
}

void inpFromConsole(char lineWithMinSymbols[], int* numOfIfElse, int* brackets)
{
  char *pointElse = NULL;
  char *pointIf = NULL;
  bool searchNextLine = false;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int numMinSymbls = N;
  char* lastLine;
  int posOfBrack = 0;

  printf("Input the content of your *.c file in the console below.\n");
  printf("Use ':x' in a newline to cancel input.\n");

  while ((read = getline(&line, &len, stdin)) != -1)
  {
    if( *(line + 0) == ':' && *(line + 1) == 'x' )
      break;

    if (searchNextLine && *(line + posOfBrack) == '{')
    {
      (*brackets)++;
      searchNextLine = false;
    }

    if ((pointIf = strstr(line, "if (")) != NULL || (pointIf = strstr(line, "if(")) != NULL)
    {
      posOfBrack = 0;
      searchNextLine = true;
      (*numOfIfElse)++;

      for (;posOfBrack < strlen(line); posOfBrack++)
        if ( (line + posOfBrack) == pointIf)
          break;

      if (strchr(pointIf,'{') != NULL)
      {
        (*brackets)++;
        searchNextLine = false;
      }
    }
    else if ((pointElse = strstr(line, "else (")) != NULL || (pointElse = strstr(line, "else(")) != NULL)
      (*numOfIfElse)++;

    if (*(line + 0) != '\n' && read < numMinSymbls)
    {
      numMinSymbls = read;
      for (int i = 0; i <= strlen(line); i++)
        lineWithMinSymbols[i] = *(line + i);
    }
  }

  free(pointIf);
  free(pointElse);
  free(line);
  return;
}
