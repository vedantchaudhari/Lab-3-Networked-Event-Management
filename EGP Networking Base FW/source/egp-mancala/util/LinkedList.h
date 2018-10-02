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

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct node {

		// Define player data that needs to be tracked by the server e.g. username string

		struct node* next;
	} Node;

	typedef struct list {
		Node* head;
	} List;

	List* emptylist();

	void addNode(char username[16], int USER_ID, List * list);
	void removeNode(char username[16], int USER_ID, List * list);
	void display(List * list);
	void reverse(List * list);
	void destroy(List * list);

	int listLength(List * list);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !_LINKEDLIST_H
