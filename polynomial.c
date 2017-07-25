//다항식 처리 프로그램 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly); //하나의 항 추가

void add_term(int c, int e, Polynomial * poly); //poly가 가리키는 다항식에 항 추가하는(c,e) 함수
void print_poly(Polynomial *p); //다항식 입력받으면 출력하는 함수
void print_term(Term *pTerm); //항을 출력해주는 함수
void process_command(); //사용자에게 입력받은 명령문 처리하는 함수
void handle_print(char name);
void handle_calc(char name, char *x_str);
void handle_definition(char *expression);
void insert_polynomial(Polynomial *ptr_poly);  //받은 배열에 다항식 저장
void destroy_polynomial(Polynomial *ptr_poly); //삭제

char* erase_blanks(char *expression); //공백 제거 

Term *create_term_instance();                       //항생성  
Polynomial *create_polynomial_instance(char name);  //다항식생성 및 초기화
Polynomial *create_by_parse_polynomial(char name, char* body); //문자열에서 받은 다항식 생성
Polynomial *create_by_add_two_polynomias(char name, char f, char g); //두개의 다항식 하나로 합치는 함수


int main()
{
	process_command();
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
	Term * p = NULL , *q = NULL;
	Term * term = create_term_instance();

	p = poly -> first;

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
	Term * t = create_term_instance();

	printf("%c = ", p -> name);
	t =	p -> first;
	
	while(t != NULL)
	{
		t -> coef > 0 ? printf("+") : printf(" ");
		print_term(t);	
		t = t -> next;
	}
}

void print_term(Term *pTerm)
{
	int sign_coef = 1, abs_num;

	if(pTerm -> coef >= 0)
	{
		abs_num = pTerm -> coef;
	}
	else
	{
		abs_num = pTerm -> coef * -1;
		sign_coef = -1;
	}


	if(abs_num > 1 && pTerm -> expo > 1)
		printf("%dx^%d", pTerm ->coef * sign_coef, pTerm -> expo);
	else if(abs_num == 1 && pTerm -> expo > 1)
		printf("x^%d", pTerm ->coef * sign_coef, pTerm -> expo);
	else if(abs_num > 1 && pTerm -> expo == 1)
		printf("%dx" , pTerm -> coef * sign_coef);
	else if(abs_num == 1 && pTerm -> expo == 1)
		printf("x", pTerm -> coef * sign_coef);
	else if(pTerm -> expo == 0)
		printf("%d", pTerm -> coef * sign_coef);

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
		if(polys[i] -> name == name) 
			break;
		else
		{
			printf("해당 이름의 함수는 없습니다.\n");
			return;
		}
	}

	printf("결과 : %d\n",eval_poly(polys[i], x));
}

void handle_definition(char *expression)
{	
	char *f_name = NULL;
	char *exp_body = NULL;

	expression = erase_blanks(expression);

	f_name = strtok(expression, "=");
	exp_body = strtok(NULL, "=");

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

	if (exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x')
	{
		char *former = strtok(exp_body, "+");
		char *later = strtok(NULL, "+");
		Polynomial *pol = create_by_add_two_polynomias(f_name[0], former[0], later[0]);

		if(former == NULL || strlen(former) != 1)
		{
			printf("Invalid expression format.");
			return;
		}

		if(later == NULL || strlen(later) != 1) 
		{
			printf("Invalid expression format.");
			return;
		}

		if(pol == NULL)
		{
			printf("Invalid expression format.");
			return;
		}

		insert_polynomial(pol);
	}
	else
	{
		Polynomial *pol = create_by_parse_polynomial(f_name[0], exp_body);
		if(pol == NULL)
		{
			printf("Invalid expression format.");
			return;
		}
		insert_polynomial(pol);
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

Polynomial *create_by_parse_polynomial(char name, char* body)
{
	Polynomial *ptr_poly = create_polynomial_instance(name);
	int i = 0, begin_term = 0, result;
	
	while (i < strlen(body))
	{
		if(body[i] == '+' || body[i] == '-') 
			i++;
		
		while(i < strlen(body) && body[i] != '+' && body[i] != '-') 
			i++;
		
		result = parse_and_add_term(body, begin_term, i, ptr_poly);
		
		if(result == 0) 
		{
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}

int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly)
{
	int i = begin;
	int sign_coef = 1, coef = 0, expo = 1;

	if (expr[i] == '+') 
		i++;
	else if (expr[i] == '-')
	{
		sign_coef = -1;
		i++;
	}
	while(i < end && expr[i] >= '0' && expr[i] <= '9')
	{
		coef = coef*10 + (int)(expr[i] - '0');
		i++;
	}
	if (coef == 0)
		coef = sign_coef;
	else
		coef *= sign_coef;

	if(i >= end)
	{
		add_term(coef, 0, p_poly);
		return 1;
	}
	if(expr[i] != 'x')
		return 0;
	i++;
	
	if(i >= end)
	{
		add_term(coef, 1, p_poly);
		return 1;
	}

	if(expr[i] != '^')
		return 0;
	i++;

	expo = 0;
	while (i < end && expr[i] >= '0' && expr[i] <= '9')
	{
		expo = expo * 10 + (int)(expr[i] - '0');
		i++;
	}

	add_term(coef, expo, p_poly);
	return 1;
}

void insert_polynomial(Polynomial *ptr_poly)
{
	int i;

	for(i = 0; i < n; i++)
	{
		if(polys[i] -> name == ptr_poly -> name)
		{
			destroy_polynomial(polys[i]);
			polys[i] = ptr_poly;
			return;
		}
	}
	polys[n++] = ptr_poly;
}

void destroy_polynomial(Polynomial *ptr_poly)
{
	Term *t = ptr_poly -> first, *tmp;

	if(ptr_poly == NULL)
		return;
	while(t != NULL)
	{
		tmp = t;
		t = t-> next;
		free(tmp);
	}
	free(ptr_poly);
}

Polynomial *create_by_add_two_polynomias(char name, char f, char g)
{
	int i = 0;
	//새로운 다항식만들고
	Polynomial *ptr_poly = create_polynomial_instance(name);
	Term *tmp = NULL;

	while(polys[i] -> name != f)
	{
		i++;
	}

	tmp = polys[i] -> first;
	i = 0;

	while(tmp != NULL)
	{
		add_term(tmp -> coef, tmp -> expo, ptr_poly);
		tmp = tmp -> next;
	}

	while(polys[i] -> name != g)
	{
		i++;
	}

	while(tmp != NULL)
	{
		add_term(tmp -> coef, tmp -> expo, ptr_poly);
		tmp = tmp -> next;
	}

	return ptr_poly;

}