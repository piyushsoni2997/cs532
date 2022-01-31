#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// cs532

struct keywords{
    char *keyword;
    int count;
}*table;

int i;
// initializing the structure 
void init_table(int argc,struct keywords *table, char *argv[])
{
    for(i=1; i<argc;i++)
    {
        table[i-1].keyword = argv[i];
        table[i-1].count = 0;
    }
}

void word_count(int argc,struct keywords *table, char *str)
{
//    Tokenizing the text and creating a dynamic array 
   const char s[2] = " ";
   char *token;
   token = strtok(str, s);
   while( token != NULL ) {
    for(i=0;i<argc-1;i++)
    {
        // Comparing keywords and updating keyword count 
        if(strcmp(token,table[i].keyword) == 0)
        {
            table[i].count++;
        }
    }
      token = strtok(NULL, s);
   }
}
// Display the keyword/count table 
void display_count(int argc, struct keywords *table)
{
    printf("Word Count:\n");
    for(i=0;i<argc-1;i++)
    {
        printf("%s : %d \n",table[i].keyword,table[i].count);
    }
}

int main(int argc, char *argv[])
{  
    // Creating a dynamic table (array of structs) based on the command-line arguments
    table = malloc(argc * sizeof(struct keywords));
    init_table(argc,table,argv);
    char *line=NULL;
	size_t maxlen=0;
	ssize_t n;
    // Reading text from standard input 
	while ( (n = getline(&line, &maxlen, stdin)) > 0) {
        word_count(argc,table,line);
	}
    display_count(argc,table);
    free(line);
    return 0;
}

/*
1. run gcc hw1.c to compile
2. run ./a.out <'text file' <arguments> to execute the code
*/