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
		return 1;
	}
	else
		return 0;
}
void push(Stack *s, char val)
{
	Node *temp;
	temp = initNode(val);
	if (isEmpty(*s))
	{
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
	return val;
}

char peek(Stack s)
{
	char val;
	if (isEmpty(s))
	{
		printf(" Khong co gia tri cua phan tu dau.");
		return;
	}
	else
	{
		val = s.top->data;
		// printf("peek ok %c\n", val);
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
		return b - a;
	}
	if (c == '*')
	{
		return a * b;
	}
	if (c == '/')
	{
		return b / a;
	}
}

char* PostFix(char* infix){   
    Stack k;
	initStack(k);
	char *res = (char*)calloc(strlen(infix)*2,sizeof(char));
    int i,j;
    for (i = 0, j = -1; infix[i] ; ++i){
        if(isNumber(infix[i])){
			while(isNumber(infix[i])){
				res[++j] = infix[i++];
			}
			res[++j] = 32;
        }
		if (infix[i] == '(') {
			push(&k, infix[i]);
		}
		if (infix[i] == ')'){
			while(peek(k) != '('){
				res[++j] = pop(&k);
				res[++j] = 32;
			}
			pop(&infix);
		}
		if (isOperator(infix[i])){
			while(!isEmpty(k) && 
					Pri(infix[i]) <= Pri(peek(k))){
				res[++j] = 32;
				res[++j] = pop(&k);
			}
			push(&k,infix[i]);
		}
    }
	while(!isEmpty(k)){
		// printf("while3\n");
		res[++j] = 32;
		res[++j] = pop(&k);
	}
	// printf("\n postfix %s", res);
	return res;
}

int Calculate(char *postfix)
{
	Stack s;
	initStack(s);
	int i;
	int a, b;
	int c = 0;
	for (i = 0; i <= strlen(postfix); i++)
	{
		if (isNumber(postfix[i]))
		{
			while(isNumber(postfix[i])){
				c = c * 10 + postfix[i++] - '0';
				// printf("\npush 1\n");
			}
			push(&s, c);
			c = 0;
		}
		if (!isEmpty(s) && isOperator(postfix[i]))
		{
			a = pop(&s);
			b = pop(&s);
			push(&s, tinh(a, b, postfix[i]));
		}
	}
	c = peek(s);
	return c;
}



int main(){
    char input[100];
	gets(input);
	printf("\n ket qua %d",Calculate(PostFix(input)));
	return 0;

}