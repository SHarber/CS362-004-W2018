/********************************************************************************/
/* Author: Sarah Harber     													*/
/* Class:  CS 362 - Software Engineering II 									*/
/* Assignment: Random Testing Quiz 2											*/
/********************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*** Function: inputChar - Returns random letter or symbol in the set ***********/
char inputChar()
{
	return "[({ ax})]"[random() % 9]; // Return ASCII Char In set
}

char *inputString()
{
	// Declare Char Array to Hold set
	static char my_string[5];

	// Declare int for the for loop
	int i;	

	// For each element of the string of 5 Characters
	for(i = 0; i < 6; i++)
	{
		// Assign a random letter between e, r, s, and t
		my_string[i] = "erst"[rand() %4];

		// If i = 5
		if(i==5)
			my_string[i] = '\0'; // Assign a Null Character
	}
	return my_string; // Return the String
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
