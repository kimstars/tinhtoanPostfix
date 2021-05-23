//chuyen doi bieu thuwc dang infix->postfix va tinh gia tri bieu thuc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct node
{
	char data;
	struct node *next;
};
typedef struct node Node;
//khoi tao node
Node *initNode(char val)
{
	Node *temp = (Node *)malloc(sizeof(Node));
	if (temp == NULL)
	{
		printf("khong khoi tao duoc");
	}
	temp->data = val;
	temp->next = NULL;
	return temp;
}
struct stack
{
	Node *top;
};
typedef struct stack Stack;

void initStack(Stack s)
{
	s.top = NULL;
}
int isEmpty(Stack s)
{
	if (s.top == NULL)
	{
		return 0;
	}
	else
		return 1;
}
void push(Stack *s, char val)
{
	Node *temp = initNode(val);
	if (isEmpty(*s))
	{
		printf("\npush %c\n", temp->data);
		s->top = temp;
	}
	else
	{
		temp->next = s->top;
		s->top = temp;
	}
}
char pop(Stack *s)
{
	int val;
	if (isEmpty(*s))
	{
		printf("\nkhong lay duoc phan tu tu stack");
		return;
	}
	val = s->top->data;
	s->top = s->top->next;
	printf("pop\n");
	return val;
}

char peek(Stack s)
{
	char val;
	if (!isEmpty(s))
	{
		printf(" Khong co gia tri cua phan tu dau.");
		return;
	}
	else
	{
		val = s.top->data;
		printf("peek ok %c\n", val);
		return val;
	}
}
bool isNumber(char val)
{
	return (val >= '0' && val <= '9');
}
bool isOperator(char y)
{
	return (y == '+' || y == '-' || y == '*' || y == '/');
}
int Pri(char val)
{
	if (val == '+' || val == '-')
	{
		return 1;
	}
	if (val == '*' || val == '/')
	{
		return 2;
	}
	return 0;
}
int tinh(int a, int b, char c)
{
	if (c == '+')
	{
		return a + b;
	}
	if (c == '-')
	{
		return a - b;
	}
	if (c == '*')
	{
		return a * b;
	}
	if (c == '/')
	{
		return a / b;
	}
}

char *InfixtoPostfix(char *infix)
{
	char *postfix = (char*)calloc(strlen(infix) * 2, sizeof(char));
	Stack s;
	initStack(s);
	char y;
	int i, j = -1;
	for (i = 0; infix[i]; i++)
	{
		if(isNumber(infix[i])){
			while(isNumber(infix[i])){
				postfix[++j] = infix[i++];
			}
			printf("%s", postfix);
			postfix[++j] = 32;
        }
		if (infix[i] == '(') {
			push(&s, infix[i]);
		}
		if (infix[i] == ')'){
			while(peek(s) != '('){
				postfix[++j] = pop(&s);
				postfix[++j] = 32;
			}
			pop(&s);
		}
		if (isOperator(infix[i])){
			while(!isEmpty(s) && Pri(infix[i]) <= Pri(peek(s))){
				postfix[++j] = 32;
				postfix[++j] = pop(&s);
				printf("while2");
			}
			push(&s,infix[i]);
			// printf("after push %c\n", peek(s));

			
		}

	}	
	printf("after for %c\n", peek(s));
	
	while(!isEmpty(s)){
		postfix[++j] = 32;
		printf("while3");
		postfix[++j] = pop(&s);
	}

	return postfix;
}
// int Calculate(char postfix[])
// {
// 	Stack s;
// 	initStack(s);
// 	int i;
// 	int a, b;
// 	int c;
// 	for (i = 0; i <= strlen(postfix); i++)
// 	{
// 		if (isNumber(postfix[i]))
// 		{
// 			push(&s, postfix[i]);
// 		}
// 		if (isOperator(postfix[i]))
// 		{
// 			a = pop(&s);
// 			b = pop(&s);
// 			push(&s, tinh(a, b, postfix[i]));
// 		}
// 	}
// 	c = peek(s);
// 	return c;
// }

int main()
{
	char infix[100];
	char *postfix;
	printf("\nNhap vap mot chuoi phep tinh: ");
	gets(infix);
	postfix = InfixtoPostfix(infix);
	printf("\nKet qua phep tinh la: %s", postfix);
	return 0;
}
