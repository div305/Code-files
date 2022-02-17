#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <stdio.h>

void Print(char *text, char *extra) //function created
{
	printf(text, extra);
	exit(1);
}

int main(int argc, char *argv[]) //main function 
{
	FILE *possibilities; //wordlist file
	char *hash, salt[2], word[11]; // hashed password and salt input
	if(argc < 2) // condition if the specific details are not provided
	{
		Print("%s (possibilities file) (salt,password hash) \n", argv[0]);
	}
	strncpy(salt, argv[2], 2); //copies the salt from the input hashed password 
	salt[2] ='\0'; // the salt input is provided by variable
	printf("Salt: %s \n", salt); //prints the salt
	if((possibilities = fopen(argv[1], "r")) == 0) // if condition to check the file is found and able to open as Read-Only. If not, print the following message
	{ 
		Print("Program was not able to open the file %s \n", argv[1]);
	}
	while (fgets(word, 11, possibilities) != 0) //while condition to hash every value with crypt. If word not found just exits the loop
	{ 
		word[strlen(word)-1] = '\0'; //removes the extra bits
		hash = crypt(word,salt); // hashes the words in the file

		if(strcmp(hash, argv[2]) == 0) //if condition to compare the hash with the provided hash password. If matched, prints the following output. and if not just exits the loop and prints the FAILED output
		{ 
			printf("SUCCESS: The hash %s is from the wordlist and the ", argv[2]); 
			printf("plaintext string is %s \n", word);			
			fclose(possibilities); //closes the file
			exit(0); //exit the program
		}
	}
	printf("FAILED: Plaintext not found.\n"); //prints if no output is found

}
