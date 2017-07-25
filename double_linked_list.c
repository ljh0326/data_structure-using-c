#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
	char *data;
	struct Node *next;
	struct Node *prev;
};

Node *head;
Node *tail;
int size = 0;

void add_after(Node *pre, char *item); //pre다음에 노드 삽입 예외처리 전부 함

int main()
{
}

void add_after(Node *pre, char *item)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node -> data = item;
	new_node -> prev = NULL;
	new_node -> next = NULL;

	if (pre == NULL && head == NULL) //노드가 하나도 없는 경우
	{
		head = new_node;
		tail = new_node;
	}
	else if(pre == NULL)  //적어도 하나의 노드는 존재하지만 맨앞에 삽입
	{
		new_node -> next = head;
		head -> prev = new_node;
		head = new_node;
	}
	else if( pre == tail) //맨 뒤에 노드를 추가하느 ㄴ경우
	{
		new_node -> prev = tail;
		tail -> next = new_node;
		tail = new_node;
	}
	else  //중간에 삽입하는 경우
	{
		new_node -> prev = pre;
		new_node -> next = pre -> next;
		new_node -> next -> prev = new_node;
		pre -> next = new_node;
	}
	size++;
}

//remove
//1. p가 유일한 노드인 경우
//2. p가 head인 경우
//3. p가 tail인 경우
//4. 그밖의 일반적인 경우

void add_ordered_list(char *item) //정렬리스트에 아이템 추가
{
	Node *p = tail;
	while (p != NULL && strcmp(item, p -> data) < 0)
		p = p -> prev;
	add_after(p, item);
}