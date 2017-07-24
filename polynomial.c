//다항식 처리 프로그램 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYS 100
#define BUFFER_LENGTH 100

typedef struct Term 
{
	int coef;              //계수
	int expo;              //지수
	struct Term * next;
}Term;

typedef struct ploynomial
{
	char name;              //다항식 이름 ex: f, g
	Term *first;            //첫 번째 항의 주소
	int size;               //항 개수
} Polynomial;

Polynomial *polys[MAX_POLYS]; //여러개의 다항식을 저장하는 포인터 배열
int n = 0;                    //저장된 다항식의 개수

int eval_poly(Polynomial * poly, int x); //다항식의 값을 계산하는 함수
int eval(Term * term, int x); //항 하나를 계산하는 함수
int read_line(char str[], int n);

void add_term(int c, int e, Polynomial * poly); //poly가 가리키는 다항식에 항 추가하는(c,e) 함수
void print_poly(Polynomial *p); //다항식 입력받으면 출력하는 함수
void print_term(Term *pTerm); //항을 출력해주는 함수
void process_command(); //사용자에게 입력받은 명령문 처리하는 함수
void handle_print(char name);
void handle_calc(char name, char *x_str);
void handle_definition(char *expression);

char* erase_blanks(char *expression); //공백 제거 

Term *create_term_instance();                       //항생성  
Polynomial *create_polynomial_instance(char name);  //다항식생성 생성할 때 이름정하게




int main()
{
}

Term *create_term_instance()
{
	Term *t = (Term *)malloc(sizeof(Term));
	t -> coef = 0;
	t -> expo = 0;
	t -> next = NULL;
	return t;
}

Polynomial *create_polynomial_instance(char name)
{
	Polynomial *ptr_poly = (Polynomial *)malloc(sizeof(Polynomial));
	ptr_poly -> name = name;
	ptr_poly -> size = 0;
	ptr_poly -> first = NULL;
	return ptr_poly;
}

void add_term(int c, int e, Polynomial* poly)
{
	Term * p = poly -> first, *q = NULL;
	
	if(c == 0)
		return;

	while(p != NULL && p -> expo > e)
	{
		p = q;
		p = p -> next;
	}
	
	if(p != NULL && p -> expo == e) //동일 차수 항이 존재하는 경우
	{
		p -> coef += c;             //계수더해줌
		if (p -> coef == 0)         //더했더니 계수가 0일때
		{
			if (q == NULL) poly -> first = p -> next; //q가 NULL이면 첫번째 노드 삭제
			else q -> next = p -> next;
			poly -> size--;
			free(p);
		}
		return;
	}

	//동일 차수 항이 존재하지 않는 경우
	Term * term = create_term_instance();
	term -> coef = c;
	term -> expo = e;

	if(q == NULL) //맨 앞 삽입
	{
		term -> next = poly -> first;
		poly -> first = term;
	}
	else          //그 외
	{
		term -> next = q -> next;
		q -> next = term;
	}
	poly -> size++;
}

int eval_poly(Polynomial * poly, int x)
{
	int result = 0;
	Term * t = poly -> first; 
	
	while(t != NULL)
	{
		result += eval(t, x);
		t = t -> next;
	}

	return result;
}

int eval(Term * term, int x)
{
	int i;
	int result = term -> coef;
	
	for(i = 0; i < term -> expo; i++)
	{
		result *= x;
	}

	return result;
}

void print_poly(Polynomial *p)
{
	printf("%c = ", p -> name);
	Term * t = p -> first;
	
	while(t != NULL)
	{
		print_term(t);
		t -> expo > 0 ? printf("+") : printf("-");
		t = t -> next;
	}
}

void print_term(Term *pTerm)
{
	pTerm -> coef > 1 ? 
	printf("%dx^%d", pTerm ->coef, pTerm -> expo):
	printf("%dx", pTerm -> coef);
}

int read_line(char str[], int n)
{
	int ch, i = 0;
	while ((ch = getchar()) != '\n')
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';

	return i;
}

void process_command()
{
	char command_line[BUFFER_LENGTH];
	char copied[BUFFER_LENGTH];
	char *command, *arg1, *arg2;

	while(1) 
	{
		printf("$ ");
		if (read_line(command_line, BUFFER_LENGTH) <= 0)
			continue;
		strcpy(copied, command_line);
		command = strtok(command_line, " ");
		if(strcmp(command, "print") == 0)
		{
			arg1 = strtok(NULL, " ");
			if(arg1 == NULL) 
			{
				printf("Invalid argument.\n");
				continue;
			}
			handle_print(arg1[0]);
		}
		else if (strcmp(command, "calc") == 0)
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) 
			{
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) 
			{
				printf("Invalid arguments. \n");
				continue;
			}
			handle_calc(arg1[0], arg2);
		}
		else if(strcmp(command, "exit") == 0)
			break;
		else
		{
			handle_definition(copied);
		}
	}
}

void handle_print(char name)
{
	int i = 0;

	for(i = 0; i < n; i++)
	{
		if(polys[i] -> name == name) break;
		else
		{
			printf("해당 이름의 함수는 없습니다.\n");
			return;
		}
	}

	print_poly(polys[i]);
}
void handle_calc(char name, char *x_str)
{
	int i = 0, x = atoi(x_str);

	for(i = 0; i < n; i++)
	{
		if(polys[i] -> name == name) break;
		else
		{
			printf("해당 이름의 함수는 없습니다.\n");
			return;
		}
	}

	eval_poly(polys[i], x);
}

void handle_definition(char *expression)
{
	expression = erase_blanks(expression);
	char *f_name = strtok(expression, "=");
	char *exp_body = strtok(NULL, "=");

	if (f_name == NULL || strlen(f_name) != 1)
	{
		printf("Unsupported command.");
		return;
	}

	
	if (exp_body == NULL || strlen(exp_body) <= 0)
	{
		printf("Invalid expression format.--");
		return;
	}
	else
	{
		Polynomial *pol = create_by_parse_polynomial(f_name[0], exp_body);
	}
}

char* erase_blanks(char *expression)
{
	char *p = (char *)malloc(sizeof(char) * 50);
	char str[50];
	int i = 0, j = 0;

	for(i = 0; i < strlen(expression); i++)
	{
		if(expression[i] != ' ')
		{
			p[j] = expression[i];
			j++;
		}
	}
	p[j] = '\0';

	return p;
	free(p);
}