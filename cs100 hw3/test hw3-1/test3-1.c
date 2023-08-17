/*#include <stdio.h>
#include <string.h>
#include <math.h>
#include<ctype.h>
#include<stdlib.h>
int main(void)
{
	char str[20000] = { 0 };
	int m;  //语句的条数
	int i;
	int j;
	int count_str = 0;
	
	int len = 0;
	//输入的字符串的长度
	//给输入的命令用字符串数组存起来
	
	char ch;
	while ((ch = getchar()) != '\n') {
		str[count_str] = ch;
		len += 1;
		count_str += 1;
	}
	str[len] = '\0';               //这里循环用scanf要在%前面加空格 否则无法清理缓存用不了
	

	
	scanf_s("%d", &m);
	getchar();
	for (i = 0; i < m; i++) {
		char command[20000] = { 0 };
		int len_c = 0;
		int count_command = 0;
		int k = 2;
		                                               
		
		while ((ch=getchar() )!= '\n' && ch != EOF) {
			command[count_command] = ch;
			len_c += 1;
			count_command += 1;
		}
		command[len_c] = '\0';
		if (command[0] == '0') {
			for (j = 2; j < len_c; j++) {
				if (command[k] == ' ') {
					break;
				}
				else if (command[k] != ' ') {
					k += 1;                                  //这边是把char当成int乘起来了
				}
			}
			int num_1 = 0;
			int c;
			int a;

			for (j = 2; j < k; j++) {
				c = command[j] - '0';
				num_1 += c * pow(10, k - j - 1);       
			}
		


			int b = k + 1;

			for (j = k + 1; j < len_c; j++) {
				if (command[b] == ' ') {
					break;
				}
				else if (command[b] != ' ') {
					b++;
				}

			}
			//printf("%d\n", b);
			int num_2 = 0;
			for (j = k + 1; j < b; j++) {
				a = command[j] - '0';
				num_2 += a * pow(10, b - j - 1);
			}
			//printf("%d\n", num_2);

			//这里接下去写把字母都跳出来换成大写，在判断的程序
			char range[10000] = { 0 };
			for (j = 0; j < num_2 - num_1 + 1; j++) {
				range[j] = str[num_1 + j];
			}
			range[num_2 - num_1+1] = '\0';

			char alpha[10000] = { 0 };
			int count = 0;
			for (j = 0; j < num_2 - num_1 + 1; j++) {
				if (isalpha(range[j]) != 0) {
					alpha[count] = range[j];
					count += 1;
				}
			}
			alpha[count] = '\0';

			for (j = 0; j < count + 1; j++) {
				alpha[j] = toupper(alpha[j]);//
			}
			int number = 0;
			if (count % 2 == 0) {
				if (count != 0) {
					for (j = 0; j <= (count - 2) / 2; j++) {
						if (alpha[j] == alpha[count - 1 - j]) {
							number += 1;
						}
					}
				}
				else if (count == 0) {
					number = 0;
				}
				if (number == count / 2) {
					printf("Yes\n");
				}
				else {
					printf("No\n");
				}
				
			}

			else if (count % 2 != 0) {
				if (count != 1) {
					for (j = 0; j <= (count - 3) / 2; j++) {
						if (alpha[j] == alpha[count - 1 - j]) {
							number += 1;
						}
					}
				}
				else if (count == 1) {
					number = 0;
				}
				if (number == (count - 1) / 2) {
					printf("Yes\n");
				}
				else {
					printf("No\n");
				}

				for (j = num_1; j <= num_2; j++) {
					printf("%c", str[j]);
				}
				putchar('\n');
			}
		}

		else if (command[0] == '1') {
			int p = 2;

			while (command[p] != ' ') {
				p++;
			}
			int num_3 = 0;
			int d;
			for (j = 2; j < p; j++) {
				d = command[j] - '0';
				num_3 += d * pow(10, p - j - 1);
			}
			//printf("%d\n", num_3);
			//putchar('a');
			char x;
			x = command[p + 1];
			str[num_3] = x;
		}

		else if (command[0] == '2') {    //这里出问题了
			int q;
			for (q = 0; q < len_c-1; q++) {
				str[len + q] = command[2 + q];

			}
			len += len_c - 2;


		}
	

	}

	return 0;
}*/












/*for (j = 0; j < count_char; j++) {
			printf("%c", str[j]);
		}
		putchar('\n');*/

/*#include<stdio.h>
int main(void)
{

		char a[10] = { 0 };
		int i;
		a[0] = '1';
		a[1] = '2';
		a[2] = '3';
		a[3] = '\n';
		for (i = 0; i < 10; i++) {
			printf("%c", a[i]);
		}

	
}


#include<stdio.h>
int main(void)
{
	char str[10] = ;
	int i;
	for (i = 0; i < 10; i++) {
		printf("%c",str[i]);
	}
}*/




/*#include<stdio.h>
int main(void)
{
	int A=0;
	int B=0;
	int C = 0;
	char a;
	int count_char = 0;
	int count_control = 0;
	char str[100] = {0};   //这里数组大小先改成20做调试用
	int num;
	int i, j, k,p;
	char ch;
	scanf("%d", &num);
	getchar();
	for (p = 0; p < num; p++) {
		while ((ch = getchar()) != '\n' && ch !=EOF) {
			if (A == 0 && ch == ' ') {
				continue;
			}
			if (ch != ' ') {
				A = 1;
			}
			if (A == 1) {
				str[count_char] = ch;
				count_char += 1;
			}
			if (ch == ';') {
				if (str[0] == 'f' && str[1] == 'o' && str[2] == 'r') {
					C = 0;
				}
				else {
					C = 1;
				}
			}

			if ((A == 1 && C==1) || (A == 1 && ch == '{') || (A == 1 && ch == '}')) {
				A = 0;
				str[count_char] = '\n';				
				for (i = 0; i < count_char; i++) {
					if (str[i] == ')' && str[i + 1] != ';') {
						for (j = i + 1; j < 100; j++) {
							str[j] = ' ';
						}
						str[i + 2] = '{';
						str[i + 3] = '\n';
					}
				}

				if (str[0] == 'e' && str[5] != 'i') {
					for (k = 4; k < 100; k++) {
						str[k] = ' ';
					}
					str[5] = '{';
					str[6] = '\n';
				}
				if (A == 0 && ch == '}') {
					count_control -= 1;
				}

				for (i = 0; i < 4 * count_control; i++) {
					putchar(' ');
				}

				if ((str[0] == 'i' && str[1] == 'f') || str[0] == 'e' || str[0] == 'f' || str[0] == 'w') {
					count_control += 1;
				}
				else if (B == 1 && str[0] != '}') {
					count_control += 0;
				}
				else if (B == 1 && str[0] == '}') {
					count_control -= 1;
				}
				else {
					count_control += 0;
				}

				if (str[0] == '}') {
					B = 1;
				}
				else {
					B = 0;
				}

				for (j = 0; j < 100; j++) {
					a = str[j];
					if (str[j] == '\n') {
						for (i = 0; i <= j; i++) {
							printf("%c", str[i]);
						}
						break;						
					}
					
				}
				
				for (i = 0; i < 100; i++) {
					str[i] = '0';
				}
				count_char = 0;
				C = 0;
			}
	}
		for (i = 0; i < 100; i++) {
			str[i] = '0';
		}
		count_char = 0;
		C = 0;

	
		
}
	return 0;
}
*/



//40分的3-2答案
/*#include<stdio.h>
int main(void)
{
	int A = 0;
	int B = 0;
	int C = 0;
	char a;
	int count_char = 0;
	int count_control = 0;
	int count_brace = 0;
	char str[100] = { 0 };   //这里数组大小先改成20做调试用
	int num;
	int i, j, k, p;
	char ch;
	scanf("%d", &num);
	getchar();
	for (p = 0; p < num; p++) {
		while ((ch = getchar()) != '\n' && ch != EOF) {
			if (A == 0 && ch == ' ') {
				continue;
			}
			if (ch != ' ') {
				A = 1;
			}
			if (A == 1) {
				str[count_char] = ch;
				count_char += 1;
			}
			if (ch == ';') {
				if (str[0] == 'f' && str[1] == 'o' && str[2] == 'r') {
					C = 0;
				}
				else {
					C = 1;
				}
			}

			if ((A == 1 && C == 1) || (A == 1 && ch == '{') || (A == 1 && ch == '}')) {
				A = 0;
				str[count_char] = '\n';
				for (i = 0; i < count_char; i++) {
					if (str[i] == ')' && str[i + 1] != ';') {//这里有问题，应该是最后一个圆括号后面才能改
						count_brace = 0;
						for (k = i + 1; k < 100; k++) {
							if (str[k] != ')') {
								count_brace += 1;
							}
						}
						if (count_brace == 99 - i) {
							for (j = i + 1; j < 100; j++) {
								str[j] = ' ';
							}
							str[i + 2] = '{';
							str[i + 3] = '\n';
						}
						else {
							;
						}
					}

				}

				if (str[0] == 'e' && str[5] != 'i') {
					for (k = 4; k < 100; k++) {
						str[k] = ' ';
					}
					str[5] = '{';
					str[6] = '\n';
				}
				if (A == 0 && ch == '}') {
					count_control -= 1;
				}

				for (i = 0; i < 4 * count_control; i++) {
					putchar(' ');
				}

				if ((str[0] == 'i' && str[1] == 'f') || str[0] == 'e' || str[0] == 'f' || str[0] == 'w') {
					count_control += 1;
				}
				else if (B == 1 && str[0] != '}') {
					count_control += 0;
				}
				else if (B == 1 && str[0] == '}') {
					count_control -= 1;
				}
				else {
					count_control += 0;
				}

				if (str[0] == '}') {
					B = 1;
				}
				else {
					B = 0;
				}

				for (j = 0; j < 100; j++) {
					a = str[j];
					if (str[j] == '\n') {
						for (i = 0; i <= j; i++) {
							printf("%c", str[i]);
						}
						break;
					}

				}

				for (i = 0; i < 100; i++) {
					str[i] = '0';
				}
				count_char = 0;
				C = 0;
			}
		}
		for (i = 0; i < 100; i++) {
			str[i] = '0';
		}
		count_char = 0;
		C = 0;



	}
	return 0;
}*/


//50分的答案
/*
#include<stdio.h>
#define NUMBER 150
int main(void)
{
	int A = 0;
	int B = 0;
	int C = 0;
	int D = 0;
	int E = 0;
	char a;
	int count_char = 0;
	int count_control = 0;
	int count_brace = 0;
	char str[NUMBER] = { 0 };  
	int num;
	int i, j, k, p;
	char ch;
	scanf_s("%d", &num);
	getchar();
	for (p = 0; p < num; p++) {
		while ((ch = getchar()) != '\n' && ch != EOF) {
			if (A == 0 && ch == ' ') {
				continue;
			}
			if (ch != ' ') {
				A = 1;
			}

			if ((str[0] == 'i' && str[1] == 'f') || str[0] == 'e' || (str[0] == 'f' && str[1] == 'o' && str[2] == 'r') || str[0] == 'w') {
				D = 1;
			}
			else {
				D = 0;
			}


			if (A == 1) {
				if (ch == '{' && D == 0) {
					str[count_char] = ch;
					count_char += 1;
				}
				else {
					str[count_char] = ch;
					count_char += 1;
				}
			}

			if (str[0] != '}') {
				E = 1;
			}
			else {
				E = 0;
			}

			if (ch == ';') {
				if (str[0] == 'f' && str[1] == 'o' && str[2] == 'r') {
					C = 0;
				}
				else {
					C = 1;
				}
			}



			if ((A == 1 && C == 1) || (A == 1 && ch == '{' && D == 1) || (A == 1 && ch == '}' && E == 0)) {
				str[count_char] = '\n';
				for (i = 0; i < count_char; i++) {
					if (str[i] == ')' && str[i + 1] != ';') {
						count_brace = 0;
						for (k = i + 1; k < NUMBER; k++) {
							if (str[k] != ')') {
								count_brace += 1;
							}
						}
						if (count_brace == NUMBER - 1 - i) {
							for (j = i + 1; j < NUMBER; j++) {
								str[j] = ' ';
							}
							str[i + 2] = '{';
							str[i + 3] = '\n';
						}
						else {
							;
						}
					}

				}

				if (str[0] == 'e' && str[5] != 'i') {
					for (k = 4; k < NUMBER; k++) {
						str[k] = ' ';
					}
					str[5] = '{';
					str[6] = '\n';
				}
				if (A == 0 && ch == '}') {
					count_control -= 1;
				}

				for (i = 0; i < 4 * count_control; i++) {
					putchar(' ');
				}

				if ((str[0] == 'i' && str[1] == 'f') || (str[0] == 'e' && str[1] == 'l' && str[2] == 's' && str[3] == 'e') || (str[0] == 'f' && str[1] == 'o' && str[2] == 'r') || (str[0] == 'w' && str[1] == 'h' && str[2] == 'i' && str[3] == 'l' && str[4] == 'e')) {
					count_control += 1;
				}
				else if (B == 1 && str[0] != '}') {
					count_control += 0;
				}
				else if (B == 1 && str[0] == '}') {
					count_control -= 1;
				}
				else {
					count_control += 0;
				}

				if (str[0] == '}') {
					B = 1;
				}
				else {
					B = 0;
				}

				for (j = 0; j < NUMBER; j++) {
					a = str[j];
					if (str[j] == '\n') {
						for (i = 0; i <= j; i++) {
							printf("%c", str[i]);
						}
						break;
					}

				}

				for (i = 0; i < NUMBER; i++) {
					str[i] = '0';
				}
				count_char = 0;
				C = 0;
			}
		}
		for (i = 0; i < NUMBER; i++) {
			str[i] = '0';
		}
		count_char = 0;
		C = 0;



	}
	return 0;
}*/