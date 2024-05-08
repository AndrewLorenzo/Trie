#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 512

struct trie {
    char desc[501];
    bool isWord; 
    trie* children[SIZE];
};

trie* createNode() {
    trie *node = (trie*)malloc(sizeof(trie));
    node->isWord = false;
    memset(node->children, 0, sizeof(node->children));
    return node;
}

trie *root = createNode(); //declare root
int count=1; //global variable for counting
bool Active = false; //global variable for checking if there's any word in dictionary

void insert(trie *root, char word[], char desc[]){
	trie *curr = root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'A';
        if (curr->children[index] == NULL) {
            curr->children[index] = createNode(); //createnode for each word char
        }
        curr = curr->children[index];
    }
    curr->isWord = true; // mark valid word
    strcpy(curr->desc,desc); // assign word description
}

int getSpace(char s[]) {
	int len = strlen(s); //get string lenght
	int count = 0; //space counter
	for(int i = 0; i < len; i++){
		if(s[i] == ' '){ //if meet space character
			count++; //counter++
		}
	}
	return count; //return space character counter
}

char *searching(trie* root, char word[]) {
    trie* curr = root;
    for (int i = 0; i < strlen(word); i++) { //iterate through whole word's characters
        int index = word[i] - 'A';
        if (curr->children[index] == NULL) {
            return NULL; //a character was not found in the trie, indicating the word not existing
        }
        curr = curr->children[index];
    }
    if(curr != NULL && curr->isWord) return curr->desc; //if curr isnt null meaning this is an existing node + we ended on the word we were searching for
    
    return NULL;
}

void menu1() {
	char word[500], desc[500];
	bool isSpace;
	do {
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", word);
		getchar();
		isSpace = false;
		for(int i = 0; i < strlen(word); i++) {
			if(word[i] == ' ') {
				isSpace = true;
				break;
			}
		}
	}
	while (strlen(word) < 1 || strlen(word) > 200 || isSpace);
	
	do {
		printf("Input a new slang word description [Must be more than 2 words]: ");
		scanf("%[^\n]", desc); 
		getchar();
	}
	while(getSpace(desc)<=1);
	if (searching(root, word)) puts("Successfully updated a slang word.");
	else puts("Successfully released new slang word");
	insert(root,word,desc);
	Active = true;
	system("pause");
}

void menu2() {
	char search[202];
	bool isSpace;
	do{
		printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", search); 
		getchar();
		isSpace = false;
		for(int i = 0; i < strlen(search); i++) {
			if(search[i] == ' ') {
				isSpace = true;
				break;
			}
		}
	}while(strlen(search) < 1 || isSpace);
	
	char *desc = searching(root,search);
	if(desc) {
		printf("Slang word : %s\n", search);
		printf("Description : %s\n",desc);
	}
	else {
		printf("There is no word '%s' in the dictionary.\n", search);
	}
	system("pause");
}

void view(trie* curr, char temp[], int end) {
    if (curr->isWord) {
        temp[end] = '\0';
        printf("%d. %s\n", count++, temp);
    }
    for (int i = 0; i < SIZE; i++) {
        if (curr->children[i]) {
            temp[end] = 'A' + i;
            view(curr->children[i], temp, end+1);
        }
    }
}

void viewPrefix(trie* root, char pre[]) {
    trie* curr = root;
    char temp[500]={'\0'};
    strcpy(temp,pre); 
    for (int i = 0; i < strlen(pre); i++) { // travel to prefix last character node
        int index = pre[i] - 'A';
        if (!curr->children[index]) { //if we reach a end, means no word with that prefix exists
        	printf("There is no prefix '%s' in the dictionary\n", pre);
            return;
        }
        curr = curr->children[index];
    }
    printf("Words starts with \"%s\":\n", pre);
    view(curr, temp, strlen(pre)); //view user searched prefix
}

void menu3() {
	char pre[500];
	printf("Input a prefix to be searched: ");
	scanf("%[^\n]", pre);
	getchar();
	count=1;
	viewPrefix(root,pre);
	system("pause");
}

void menu4() {
	char def[100]={'\0'}; //default prefix, (to view all word, default prefix = '\0');
	if (Active) {
		printf("List of all slang words in the dictionary:\n");
		count=1;
		view(root,def,0); //default is no prefix and start from 0th index
	}
	else puts("There is no slang word yet in the dictionary.");
	system("pause");
}

int main () {
	int c; //declare integer c for menu choice
	do {
		system("cls");
		// print all the menu available
		puts("BOOGLE");
		puts("1. Release a new slang word");
		puts("2. Search a slang word");
		puts("3. View all slang words starting with a certain prefix word");
		puts("4. View all slang words");
		puts("5. Exit");
		printf("Input : ");
		scanf("%d", &c); //take menu choice from user
		getchar();
		// if choose 1, go to menu1
		if (c==1) menu1();
		
		// if choose 2, go to menu2
		else if (c==2) menu2();
		
		// if choose 3, go to menu3
		else if (c==3) menu3();
		
		// if choose 4, go to menu4
		else if (c==4) menu4();
		
		// if choose other than that, display error message
		else if (c!=5) {
			printf("Error choice!!!\n"); 
			system("pause");
		}
	}
	// if choosing 5, the loop doesn't run
	while (c!=5);
	
	// exit message
	puts("Thank you... Have a nice day :)");
}
