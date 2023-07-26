#include "stdio.h"
#include "string.h"
#define MAX_SIZE 30
// 变量用小写+下划线，函数用大写加下划线

// 定义栈
typedef struct
{
	char expression[MAX_SIZE];
	int top;
} caculation;

// 初始化栈
int Init_Stack(caculation *caculation)
{
	caculation->top = -1;
	return 1;
}

// 进栈
int Push_Stack(caculation *caculation, char inputed_expression)
{
	if (caculation->top == MAX_SIZE - 1)
	{
		printf("栈满，不能输入！");
		return 0;
	}

	caculation->top++;
	caculation->expression[caculation->top] = inputed_expression;
	return 1;
}

// 出栈
int Pop_Stack(caculation *caculation, char *pop_elem)
{
	if (caculation->top == -1)
	{
		printf("栈已为空！");
		return 0;
	}

	*pop_elem = caculation->expression[caculation->top];
	caculation->top--;
	return 1;
}

// 中缀转后缀
int Change_To_Suffix(char *inputed_array, caculation *caculation, char *store_array)
{
	int i = 0;
	int j = 0;
	int flag;
	char pop_elem;

	for (; inputed_array[i] != '\0'; i++)
	{
		switch (inputed_array[i])
		{
			case '(':
				Push_Stack(caculation, inputed_array[i]);
				flag = 0;
				break;

			case ')': /*不可能一开始就是右括号，所以不用判断栈空*/
				while (caculation->expression[caculation->top] != '(')
				{
					Pop_Stack(caculation, &pop_elem);
					store_array[j] = pop_elem;
					j++;
					store_array[j] = ' ';
					j++;
					flag = 0;
				}

				Pop_Stack(caculation, &pop_elem);
				break;

			case '*':
				while (caculation->expression[caculation->top] != '(' && caculation->expression[caculation->top] - inputed_array[i] != 3 && caculation->expression[caculation->top] - inputed_array[i] != 1 && caculation->top != -1)
				{
					Pop_Stack(caculation, &pop_elem);
					store_array[j] = pop_elem;
					j++;
					store_array[j] = ' ';
					j++;
				}

				Push_Stack(caculation, inputed_array[i]);
				flag = 0;
				break;

			case '/':
				while (caculation->expression[caculation->top] != '(' && inputed_array[i] - caculation->expression[caculation->top] != 4 && inputed_array[i] - caculation->expression[caculation->top] != 2 && caculation->top != -1)
				{
					Pop_Stack(caculation, &pop_elem);
					store_array[j] = pop_elem;
					j++;
					store_array[j] = ' ';
					j++;
				}

				Push_Stack(caculation, inputed_array[i]);
				flag = 0;
				break;

			case '+':
			case '-':
				while (caculation->expression[caculation->top] != '(')
				{
					if (caculation->top != -1)
					{
						Pop_Stack(caculation, &pop_elem);
						store_array[j] = pop_elem;
						j++;
						store_array[j] = ' ';
						j++;
					}
					else
						break;
				}

				Push_Stack(caculation, inputed_array[i]);
				flag = 0;
				break;

			default: //这里解决不止一位数的数字被拆分的问题
				if (flag == 1)
				{
					j--;
					store_array[j] = inputed_array[i];
				}
				else
					store_array[j] = inputed_array[i];

				j++;
				store_array[j] = ' ';
				j++;
				flag = 1;
				break;
		}
	}

	while (caculation->top != -1) //数字全部输出，把剩下的元素出栈
	{
		Pop_Stack(caculation, &pop_elem);
		store_array[j] = pop_elem;
		j++;
		store_array[j] = ' ';
		j++;
	}
	store_array[j] = '\0';

	return 1;
}

// 定义纯数字栈
typedef struct
{
	double number[MAX_SIZE];
	int top;
} number_stack;

// 初始化数字栈
int Init_Num_Stack(number_stack *number_stack)
{
	number_stack->top = -1;
	return 1;
}

// 入数字栈
int Push_Num(number_stack *number_stack, double num)
{
	if (number_stack->top == MAX_SIZE - 1)
	{
		printf("数字栈已满！");
		return 0;
	}

	number_stack->top++;
	number_stack->number[number_stack->top] = num;
	return 1;
}

// 出数字栈
int Pop_Num(number_stack *number_stack, double *pop_num)
{
	if (number_stack->top == -1)
	{
		printf("数字栈为空！");
		return 0;
	}

	*pop_num = number_stack->number[number_stack->top];
	number_stack->top--;
	return 1;
}

// 获得数字栈长度
int Get_Numarr_Length(char *num_str) // 存疑
{
	int i = 0;
	while (num_str[i] != '\0')
	{
		i++;
	}

	return i;
}

// 将数组中的数字字符串转化为数字
int Change_To_Num(char *num_str, int numarr_length)
{
	int i = numarr_length - 1;
	int j = numarr_length - 1;
	double number = 0;
	int ten = 1;
	for (; i >= 0; i--) //乘以10是因为有多位数
	{
		for (; j > 0; j--)
		{
			if (num_str[i] == '.')
			{
				num_str = (float)num_str;
				printf("%f", num_str);
				return num_str;
			}
		}
		number += (double)((num_str[i] - '0') * ten);
		ten *= 10;
	}
	return number;
}

// 计算用的函数
int Caculate(number_stack *number_stack, char *suffix_expression)
{
	double top_num;
	double under_top_num;
	int i;
	int j = 0;
	double result;
	char num_str[MAX_SIZE];
	int len;
	double changed_num;
	for (i = 0; suffix_expression[i] != '\0'; i++)
	{
		switch (suffix_expression[i])
		{
			case ' ':
				break;

			case '+':
				Pop_Num(number_stack, &top_num);
				Pop_Num(number_stack, &under_top_num); //用地址是为了直接改变变量的值
				Push_Num(number_stack, under_top_num + top_num);
				break;

			case '-':
				Pop_Num(number_stack, &top_num);
				Pop_Num(number_stack, &under_top_num); //用地址是为了直接改变变量的值
				Push_Num(number_stack, under_top_num - top_num);
				break;

			case '*':
				Pop_Num(number_stack, &top_num);
				Pop_Num(number_stack, &under_top_num); //用地址是为了直接改变变量的值
				Push_Num(number_stack, under_top_num * top_num);
				break;

			case '/':
				Pop_Num(number_stack, &top_num);
				Pop_Num(number_stack, &under_top_num); //用地址是为了直接改变变量的值
				Push_Num(number_stack, (double)under_top_num / (double)top_num);
				break;

			default:
				while (suffix_expression[i] != '\0' && suffix_expression[i] != ' ') // 取出数字
				{
					num_str[j] = suffix_expression[i];
					i++;
					j++;
				}

				num_str[j] = '\0';
				len = Get_Numarr_Length(num_str);
				printf("%d\n", len);
				changed_num = Change_To_Num(num_str, len);
//				printf("%lf\n", changed_num);
				Push_Num(number_stack, changed_num);
				j = 0;
		}
	}
	result = number_stack->number[number_stack->top];
	int k;

	number_stack->top = -1;
	return result;
}

int main()
{
	int j = 1000;
	while (j != 0)
	{
		caculation caculation_stack;
		Init_Stack(&caculation_stack);

		char input_expression[MAX_SIZE] /* = "19+(5-1)*6/3" */;
		char store_expression[MAX_SIZE];

		scanf("%s", input_expression);

		int i;
		int flag = 0;
		for (i = 0; i < strlen(input_expression); i++)
		{
			if (isalpha(input_expression[i]))
			{
				printf("请输入数字！");
				flag = 1;
				break;
			}
		}

		if (flag == 1) continue;

		Change_To_Suffix(input_expression, &caculation_stack, store_expression);

		number_stack num_stack;
		Init_Num_Stack(&num_stack);

		double cal_result = Caculate(&num_stack, store_expression);
		printf("=%.0lf\n", cal_result);
		j--;
	}

	return 0;
}
