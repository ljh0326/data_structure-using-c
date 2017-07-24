#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	char *data;
	struct node *next;
}Node;

//typedef struct node Node;

int main()
{
	// 기본적인 테스트
	Node * head;
	Node * q;
	Node * p;

	head = (Node *)malloc(sizeof(Node));
	head -> data = "LEE";
	head -> next = NULL;

	q = (Node *)malloc(sizeof(Node));
	q -> data = "JEONG HUN";
	q -> next = NULL;

	head -> next = q;
	
	p = head;
	 //헤드포인터는 한상 첫 번째 노드의 주소를 가르키고 있어야 한다.
	while(p!=NULL)
	{
		printf("%s\t", p->data);
		p = p -> next;
	}

}

//strcpy는 문자열과 문자열 조합, 문자열 포인터와 문자열 조합을 할 수 없음