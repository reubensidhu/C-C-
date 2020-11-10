#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"
#include <pthread.h>

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;


void* ServeClient(char *client){

	// TODO: Open the client command file and read commands line by line

	// TODO: match and execute commands

	// TODO: Handle command: "insertNode <some unsigned int value>"
	// print: "[ClientName]insertNode <SomeNumber>\n"
	// e.g. "[client1_commands]insertNode 1\n"
	

	// TODO: Handle command: "deleteNode <some unsigned int value>"
	// print: "[ClientName]deleteNode <SomeNumber>\n"
	// e.g. "[client1_commands]deleteNode 1\n"

	// TODO: Handle command: "countNodes"
	// print: "[ClientName]countNodes = <SomeNumber>\n"
	// e.g. "[client1_commands]countNodes 1\n"


	// TODO: Handle command: "sumSubtree"
	// print: "[ClientName]sumSubtree = <SomeNumber>\n"
	// e.g. "[client1_commands]sumSubtree 1\n"

	char oneLine[500];
		int line = 0;
		FILE *fp0;
		fp0 = fopen(client,"r");
		if(fp0 == NULL){
			printf("Cannot open files\n");
			return (NULL);
			}

		Node *root=NULL;
			while(fgets(oneLine, 500, fp0)){
				/*char function[20];
				sscanf(oneLine, "%s", function);
				(function == "insertNode"); */ 
				if  (oneLine[0] == 'i') {
					int i;
					sscanf(oneLine,"%d",&i);
					pthread_rwlock_wrlock(&lock);
					root = insertNode(root, i);
					printf("[%s]%s\n", client, oneLine);
					pthread_rwlock_unlock(&lock);
				}
				else if (oneLine[0] == 'd') {
					int i;
					sscanf(oneLine,"%d",&i);
					pthread_rwlock_wrlock(&lock);
					root = deleteNode(root, i);
					printf("[%s]%s\n", client, oneLine);
					pthread_rwlock_unlock(&lock);
				}
				else if (oneLine[0] == 'c') {
					pthread_rwlock_rdlock(&lock);
					int n = countNodes(root);
					printf("[%s]%s %d\n", client, oneLine, n);
					pthread_rwlock_unlock(&lock);
				}
				else { //if (oneLine[0] == 's') {
					pthread_rwlock_rdlock(&lock);
					int n = sumSubtree(root);
					printf("[%s]%s %d\n", client, oneLine, n);
					pthread_rwlock_unlock(&lock);
				}
				line = line + 1; 
			}
		fclose(fp0);
		//return 0;


	return NULL;
}

/*int main (void) {
	ServeClient("client1_commands");
	return 0;
}*/