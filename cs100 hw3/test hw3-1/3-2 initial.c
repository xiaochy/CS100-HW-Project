/*#include<stdio.h>
int main(void)
{
	int line;
	int count_control = 0;
	int count_end_curly = 0;
	int i, j,k;
	char ch;
	scanf_s("%d", &line);
	getchar();
	for (i = 0; i < line; i++) {
		char str[100] = { 0 };
		int count_char = 0;
		while ((ch = getchar()) != '\n' && ch != EOF) {
			str[count_char] = ch;
			count_char += 1;
		}
		str[count_char] = '\0';

		int count_semicolon = 0;
		int semi_idx[100] = { 0 };
		semi_idx[0] = 0;
		for (i = 0; i < 100; i++) {
			if (str[i] == ';' || str[i] == ' ') {
				semi_idx[count_semicolon+2] = i;
				count_semicolon += 1;
			}
		}

		for (i = 0; i < count_semicolon; i++) {
			int p = 0;
			int len_divide = 0;
			char* str_divide;
			for (j = semi_idx[i] + 1; j <= semi_idx[i + 1]; j++) {
				int count_blank = 0;
				if (str[j] == ' ') {
					count_blank += 1;
				}
				for (k = semi_idx[i] + 1 + count_blank; k <= semi_idx[i + 1]; k++) {
					len_divide += 1;
				}
				str_divide= (char)malloc(len_divide * sizeof(char));

			}
		}


	}
	free(str_divide);
	return 0;
}
*/
/*char* a;
int n;
a = (char)malloc(n * sizeof(char));
free(a); //事先不知道数组大小的情况下，可以用malloc*/














/*#include<stdio.h>
int main(void)
{
	int A = 0;
	int B = 0;
	int count_char = 0;
	int count_control = 0;
	char str[100] = { 0 };
	int num;
	int i, j, k, p;
	char ch;
	scanf_s("%d", &num);
	getchar();
	for (p = 0; p < num; p++) {
		while ((ch = getchar()) != '\n') {
			if (A == 0 && ch == ' ') {
				continue;
			}
			if (ch != ' ') {
				A = 1;
			}
			if (A == 1) {
				str[count_char] = ch;
				count_char += 1;
				printf("%c\n", str[count_char]);
			}
			if (A == 1 && ch == '}') {
				str[0] = ch;
				str[1] = '\n';
			}
			if ((A == 1 && ch == ';') || (A == 1 && ch == '{')) {
				A = 0;
				str[count_char] = '\n';
				//str[count_char + 1] = '\n';
			}

		}

		for (i = 0; i < count_char; i++) {
			if (str[i] == ')') {
				for (j = i + 1; j < 100; j++) {
					str[j] = ' ';
				}
				str[i + 2] = '{';
				str[i + 3] = '\n';
			}
			else if (str[0] == 'e' && str[5] != 'i') {
				for (k = 4; k < 100; k++) {
					str[k] = ' ';
				}
				str[5] = '{';
				str[6] = '\n';
			}

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

		
		for (i = 0; i < 100; i++) {
			printf("%c", str[i]);
		}
		//putchar('\n');
		for (i = 0; i < 100; i++) {
			str[i] = '0';
		}
	}
	return 0;
}*/


/*

#include<stdio.h>
#define NUMBER 150
int main(void)
{
	int A = 0; //这里是判断字符是否在要打印出来的语句中，如果在：A=1；如果不在：A=0；
	int B = 0; //这里是判断该句语句是否是单独一个} 如果是：B=1；如果不是：B=0；
	int C = 0;//这里是判断遇到一个;要不要截断语句  如果前面"（的数量"=")的数量"，此时要截断：C=1； 如果前面"（的数量"！=")的数量"，说明不要截断：C=0
	int D = 0;//这里是判断该语句是否为control flow 如果是：D=1； 如果不是：D=0；
	int E = 0;//这里是判断
	int F = 0;//这里是判断遇到一个{要不要截断语句  如果前面"（的数量"=")的数量"，此时要截断：F=1； 如果前面"（的数量"！=")的数量"，说明不要截断：F=0
	int count_char = 0;
	int count_control = 0;
	int count_brace = 0;
	int open_brace_1 = 0;
	int close_brace_1 = 0;
	int open_brace_2 = 0;
	int close_brace_2 = 0;
	char str[NUMBER] = { 0 };   //这里数组大小先改成20做调试用
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

			if (str[0] == '}') {
				E = 0;
			}
			else {
				E = 1;
			}

			if (ch == ';') {
				open_brace_2 = 0;
				close_brace_2 = 0;
				if (str[0] == 'f' && str[1] == 'o' && str[2] == 'r') {
					C = 0;
				}
				else {
					for (i = 0; i < count_char; i++) {
						if (str[i] == '(') {
							open_brace_2 += 1;
						}
						if (str[i] == ')') {
							close_brace_2 += 1;
						}
					}
					if (open_brace_2 == close_brace_2) {
						C = 1;
					}
					else {
						C = 0;
					}

				}
			}
			if (ch == '{') {
				open_brace_1 = 0;
				close_brace_1 = 0;
				for (i = 0; i < count_char; i++) {
					if (str[i] == '(') {
						open_brace_1 += 1;
					}
					if (str[i] == ')') {
						close_brace_1 += 1;
					}
				}
				if (open_brace_1 == close_brace_1) {
					F = 1;
				}
				else {
					F = 0;
				}
			}



			if ((A == 1 && C == 1) || (A == 1 && ch == '{' && D == 1 && F == 1) || (A == 1 && ch == '}' && E == 0)) {//包括了普通以;结尾的语句；刚输入的字符是{ 或者} 的语句。现在第一种不用改动，第三种不用改动，只用改动第二种；即第二种如果前面是普通语句，则需要继续读直到读到分号；如果是循环语句，则停止
				A = 0;
				str[count_char] = '\n';				                                             //这里有问题是导致 if(ch=='}'){无法正确输出的原因
				for (i = 0; i < count_char; i++) {
					if (str[i] == ')' && str[i + 1] != ';') {//这里有问题，应该是最后一个圆括号后面才能改
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
		



	}
	return 0;
}*/