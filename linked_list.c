#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;

typedef struct Node{
	element data;
	struct Node *next;
}Node;

void insert_node(Node **phead , Node *p, Node *new_node); //노드 삽입
void remove_node(Node **phead, Node *p, Node *removed);  //노드 삭제
void display(Node * head); //리스트 조회
Node * search(Node *head, int item); //해당 아이템이 있는 주소 찾기
Node * concat(Node *head1, Node *head2); //리스트 연결
void error(char *message);  //오류 메시지 발생
Node * create_node(element data, Node *next); //노드 생성

int main()
{
	Node * list1 = NULL, * list2 = NULL;
	Node * p;

	insert_node(&list1, NULL, create_node("짱",NULL));
	insert_node(&list1, NULL, create_node("JEONGHUN",NULL));
	insert_node(&list1, NULL, create_node("LEE",NULL));
	display(list1);

	remove_node(&list1, search(list1,"JEONGHUN"), search(list1,"짱"));
	display(list1);

	insert_node(&list2, NULL, create_node("바보",NULL));
	
	concat(list1,list2);
	display(list1);
}

void insert_node(Node ** phead , Node *p, Node *new_node)
{
	if(*phead == NULL) //공백리스트
	{
		new_node -> next = NULL;
		*phead = new_node;
	}
	else if( p == NULL) //p가 NULL이면 첫 번째 노드로 삽입 선행노드 없으면 걍 첫번쨰 넣겠다는거임
	{
		new_node -> next = *phead;
		*phead = new_node;
	}
	else{
		new_node -> next = p -> next;
		p -> next = new_node;
	}
}

void remove_node(Node **phead, Node *p, Node *removed)
{
	if( p == NULL)
	{
		*phead = (*phead) -> next;
	}
	else
	{
		p -> next = removed -> next;
	}
	free(removed);
}

void display(Node * head)
{
	//지역변수인데 p안마들고 head써도 되지 않을까?
	while(head != NULL)
	{
		printf("%s->", head->data);
		head = head -> next;
	}
	printf("\n");
}

Node * search(Node *head, element item)
{
	while( head != NULL)
	{
		if( head -> data == item)
			return head;
		head = head -> next;
	}
	return NULL;
}

Node * concat(Node *head1, Node *head2)
{
	Node * p;

	if(head1 == NULL) return head2;
	else if(head2 == NULL) return head1;
	else 
	{
		p = head1;
		while(p -> next != NULL)  p = p -> next;
		p -> next = head2;
		return head1;
	}
}

void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}

Node * create_node(element data, Node *next)
{
	Node * new_node;
	new_node = (Node *)malloc(sizeof(Node));
	if(new_node == NULL) error("메모리 할당 에러");
	new_node -> data = data;
	new_node -> next = next;
	return new_node;
}