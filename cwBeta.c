#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define N 1000

void inpFromFile(char lineWithMinSymbols[], int* numOfIfElse, int* brackets);
void outpInFile(char lineWithMinSymbols[], int* numOfIfElse, int* brackets);
void outpInConsole(char lineWithMinSymbols[], int* numOfIfElse, int* brackets);
void inpFromConsole(char lineWithMinSymbols[], int* numOfIfElse, int* brackets);

int main()
{
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
        inpFromFile(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        outpInFile(lineWithMinSymbols, &numOfIfElse,&countOfBracketsAfterIf);
        break;
      case 2:
        inpFromFile(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        outpInConsole(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        break;
      case 3:
        inpFromConsole(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
        outpInFile(lineWithMinSymbols, &numOfIfElse, &countOfBracketsAfterIf);
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

void inpFromFile(char lineWithMinSymbols[], int* numOfIfElse, int* brackets)
{
  FILE *readf;
  char *pointIf = NULL;
  char line[N];
  bool searchNextLine = false;
  char *nameOfFile = (char*) malloc(100);
  int posOfBrack = 0;
  int lenghtOfShoretestLine = N;

  printf("Input the name of your *.c file\n");
  scanf("%s", nameOfFile);

  readf = fopen(nameOfFile, "r");
  if (readf == NULL)
  {
    printf("Unable to open or allocate your file \n");
    return;
  }

  while (fgets(line, sizeof(line), readf) != NULL)
  {
    if (searchNextLine && line[posOfBrack] == '{')
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
    else if (strstr(line, "else") != NULL)
      (*numOfIfElse)++;
    if (*line != '\n' && lenghtOfShoretestLine > strlen(line))
    {
       lenghtOfShoretestLine = strlen(line);
       strcpy(lineWithMinSymbols, line);
    }
  }

  fclose(readf);
  free(pointIf);
  free(nameOfFile);
  return;
}

void outpInFile(char lineWithMinSymbols[], int* numOfIfElse, int* brackets)
{
  FILE *writef;
  char *nameOfFile = (char*) malloc(100);

  printf("Input the name of your *.txt file for the results\n");
  scanf("%s", nameOfFile);

  writef = fopen(nameOfFile, "w");
  if (writef == NULL)
    printf("Unable to open/find file result.txt");

  fprintf(writef, "Number of 'if/if else' operators found is: %d\n", *numOfIfElse);
  fprintf(writef, "Shortest line found:\n%s", lineWithMinSymbols);
  fprintf(writef, "Number of brackets found after 'if' operators is: %d\n", *brackets);

  fclose(writef);
  free(nameOfFile);
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
  char *pointIf = NULL;
  bool searchNextLine = false;
  char line[N];
  int posOfBrack = 0;
  int lenghtOfShoretestLine = N;

  printf("Input the content of your *.c file in the console below.\n");
  printf("Use ':x' in a newline to cancel input.\n");

  while (1){
    fgets(line, sizeof(line), stdin);
    if( *(line + 0) == ':' && *(line + 1) == 'x' )
      break;

    if (searchNextLine && line[posOfBrack] == '{')
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
    else if (strstr(line, "else") != NULL)
      (*numOfIfElse)++;

    if (*line != '\n' &&  strlen(line) < lenghtOfShoretestLine)
    {
      lenghtOfShoretestLine = strlen(line);
      strcpy(lineWithMinSymbols, line);
    }
  }

  free(pointIf);
  return;
}
