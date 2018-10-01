// Certificate of Authenticity
//
// EGP-405-01 Networking for Online Games
// Project 1
// 8-27-2018
//
// Vedant Chaudhari, 1532077
//
// We certify that this work is entirely our own.The assessor of this project may reproduce this project 
// and provide copies to other academic staff, and/or communicate a copy of this project to a plagiarism 
// - checking service, which may retain a copy of the project on its database.

// Inspired by https://github.com/skorks/c-linked-list/blob/master/linkedlist.h

#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* createNode(char username[16], int USER_ID);

Node * createnode(char username[16], int USER_ID) {
	Node * newNode = malloc(sizeof(Node));
	strcpy(newNode->username, username);
	newNode->USER_ID = USER_ID;
	newNode->next = NULL;
	return newNode;
}

List * emptylist() {
	List * list = malloc(sizeof(List));
	list->head = NULL;
	return list;
}

void display(List * list) {
	Node * current = list->head;
	if (list->head == NULL)
		return;
	while (current->next != NULL) {
		printf("%s,", current->username);
		current = current->next;
	}
	printf("%s\n", current->username);
}

void addNode(char username[16], int USER_ID, List * list) {
	Node * current = NULL;
	if (list->head == NULL) {
		list->head = createnode(username, USER_ID);
	}
	else {
		current = list->head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = createnode(username, USER_ID);
	}
}

void removeNode(char username[16], int USER_ID, List * list) {
	Node * current = list->head;
	Node * previous = current;
	while (current != NULL) {
		if (current->username == username) {
			previous->next = current->next;
			if (current == list->head)
				list->head = current->next;
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

void reverse(List * list) {
	Node * reversed = NULL;
	Node * current = list->head;
	Node * temp = NULL;
	while (current != NULL) {
		temp = current;
		current = current->next;
		temp->next = reversed;
		reversed = temp;
	}
	list->head = reversed;
}

void destroy(List * list) {
	Node * current = list->head;
	Node * next = current;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	free(list);
}

int listLength(List * list) {
	Node * current = list->head;
	int iter = 0;

	if (list->head == NULL)
		return iter;

	while (current->next != NULL) {
		iter += 1;
		current = current->next;
	}

	iter += 1;	// Left over +1 index

	return iter;
}