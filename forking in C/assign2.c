#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main(int argc, char *argv[])
{
	void handler(int signum);
	//Taking the number of children as a terminal input
	int numberOfChildren = atoi(argv[1]);
	//Takes the name of the file that holds the data from the terminal
	char* fileName = argv[2];
	//Pointer to an object for reading from the file
	FILE *myFile;
	int* arr;
	//Instead of creating a vector class (overhead)
	//I assume the number of lines wont exceed 100*number of children
	arr = malloc(100 * numberOfChildren);
	myFile = fopen(fileName, "r");
	int numberOfLines = 0;
	while ((fscanf(myFile, "%d", &arr[numberOfLines])) != EOF) //scanf and check EOF
		numberOfLines++;
	fclose(myFile);

	//I need a case handler for numberOfLines == 0 OR number of children is 0
	//TOOOOOOOOOOOOOOOOOOOODOOOOOOOOOOOOOOOOOOOOOOOOOO

	//numberoflines is now updated with its true value
	//Pointers for children
	int *pids; //For pids
	pids = malloc(numberOfChildren);

	int **part = malloc(numberOfChildren); //For portions (double array) array of arrays
	//Creating an empty array for each child to have its values
	int div = numberOfLines / numberOfChildren;
	for (int i = 0; i < numberOfChildren; i++)
		part[i] = malloc(div+1);

	//This loop to handle if number of lines is less than number of children
	for (int i = 0; i < numberOfChildren; i++)
		part[i][0] = 0;
	//Filling the array of arrays with the data needed
	int k = 0;
	int i = 0;
	for (i; i < numberOfLines; i++)
	{
		int mod = i%numberOfChildren;
		part[mod][k] = arr[i];
		if ((i + 1) % numberOfChildren == 0)
			k++;
	}
	//Let's assign size for each child
	int* size_per_each = malloc(numberOfChildren);
	if (div == 0)
	{
		//Case 1
		//I do know now that each children will be responsible for exactly one line, and the last (subtraction) wont have any
		int i = 0;
		for (i; i < numberOfLines; i++)
			size_per_each[i] = 1;
		for (i; i < numberOfChildren; i++)
			size_per_each[i] = 0;
	}
	else {
		//Case 2
		//if mod == 0 //no remaindes
		//else
		int mod = numberOfLines % numberOfChildren;
		if (mod == 0)
		{
			int l = 0;
			for (int i = 0; i < numberOfLines; i++)
			{
				size_per_each[l] = arr[i];
				l++;
				if (l == numberOfChildren)
					l = 0; //To wrap around
			}
		}
		else {
			for (int i = 0; i < numberOfChildren; i++)
			{
				size_per_each[i] = div;
			}
			for (int i = 0; i < mod; i++)
				size_per_each[i] = size_per_each[i] + 1;
		}
	}

	//Now to the main CODE
	for (int i = 0; i<numberOfChildren; i++)
	{
		int pidi = fork();
		if (pidi == -1)
			perror("error in forking first child ");
		else if (pidi == 0) {

			// sum and print the values from the file
			int sum = 0;
			for (int k = 0; k < size_per_each[i]; k++) {
				sum += part[i][k];
			}
			printf("%d\n", sum);

			while (1) {} //Infinite loop so as the child wont become a Zombie
		}
		else {
			signal(SIGCHLD, handler);
			sleep(10); //Ten seconds to test if any of the children would become a zombie

			for (int ki = 0; ki<numberOfChildren; ki++)
			{
				kill(pidi, SIGKILL);
				sleep(1);
			}
			//I can print the total summation here
			printf("\n Good Bye World ! \n\n");
		}
	}
}

void handler(int signum)
{

	int pid, stat_loc;

	pid = wait(&stat_loc);
	if (!(stat_loc & 0x00FF))
		printf("\nA child with pid %d terminated with exit code %d\n", pid, stat_loc >> 8);


}
