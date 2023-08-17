/*#include<stdio.h>
int min_2(int a, int b)
{
	int min = a;
	if (b <= min) {
		min = b;
	}
	return min;
}
int max_2(int a, int b)
{
	int max = a;
	if (b >= max) {
		max = b;
	}
	return max;
}

void count_sanpai(int* solo, int* pair, int* joker, int* trio, int* bomb, int* a);
int san_pai(int* b);
void shunzi_3(int step, int* pai);
void shunzi_2(int step, int* pai);
void shunzi_1(int step, int* pai);
int ans = 17;

//int pai[15] = { 0 };//其中第一个空里不放东西，后面的下标就对应牌的数字
int chupai(int step, int* c) //传入的参数是pai
{
	int tmp;
	if (step >= ans) {
		return;
	}
	else {
		tmp = san_pai(c);
		ans = min_2(ans, step + tmp);
		//printf("%d", ans);
		shunzi_3(step, c);
		shunzi_1(step, c);
		shunzi_2(step, c);
		//可能需要注意一下顺序

	}
	return ans;
}
void shunzi_3(int step, int* pai)
{
	int len, end, start, j, k;
	for (start = 3; start <= 14; start++) {
		len = 0;
		while (pai[start + len] >= 3) {    //这里还要考虑1的情况
			len++;
		}
		for (int j = len; j >= 2; --j) {
			end = start + j - 1;
			for (int k = start; k <= end; k++) {
				pai[k] -= 3;
			}

			chupai(step + 1, pai);
			for (int k = start; k <= end; k++) {
				pai[k] += 3;
			}


		}
	}
	return;
}

void shunzi_2(int step, int* pai)
{
	int len, end, start, j, k;
	for (start = 3; start <= 14; start++) {
		len = 0;
		while (pai[start + len] >= 2) {    //这里还要考虑1的情况
			len++;
		}
		for (int j = len; j >= 3; --j) {
			end = start + j - 1;
			for (int k = start; k <= end; k++) {
				pai[k] -= 2;
			}
			chupai(step + 1, pai);
			for (int k = start; k <= end; k++) {
				pai[k] += 2;
			}


		}
	}
	return;
}


void shunzi_1(int step, int* pai)
{
	int len, end, start, j, k;
	for (start = 3; start <= 14; start++) {
		len = 0;
		while (pai[start + len] >= 1) {    //这里还要考虑1的情况
			len++;
		}
		for (int j = len; j >= 5; --j) {
			end = start + j - 1;
			for (int k = start; k <= end; k++) {
				pai[k] -= 1;
			}
			chupai(step + 1, pai);
			for (int k = start; k <= end; k++) {
				pai[k] += 1;
			}


		}
	}
	return;
}

int san_pai(int* b)//相当于传进去的数组是pai
{
	int i;
	int step = 0;
	int max_count;
	int solo = 0; int pair = 0; int joker = 0; int trio = 0; int bomb = 0;

	count_sanpai(&solo, &pair, &joker, &trio, &bomb, b);
	int res = solo + 2 * pair + joker;
	int res_1 = solo + pair + joker;
	int sp = solo + pair;
	max_count = b[1];
	for (i = 2; i <= 15; i++) {
		if (b[i] >= max_count) {
			max_count = b[i];
		}
	}
	if (max_count <= 1) {
		step = res_1;
	}
	if (max_count == 2) {
		if (joker != 0) {
			step = sp + 1;
		}
		else {
			step = sp;
		}
	}
	if (max_count == 3) {
		if (trio == 1) {
			if (res == 0) {
				step = 1;
			}
			else {
				if (solo != 0 || pair != 0) {
					if (joker == 0) {
						step = sp;
					}
					else {
						step = sp + 1;
					}
				}
				else if (solo == 0 && pair == 0) {
					if (joker == 2) {
						step = 2;
					}
					else {
						step = 1;
					}
				}
			}
		}
		else if (trio == 2) {
			if (sp >= 2) {
				if (joker == 0) {
					step = sp;
				}
				else {
					step = sp + 1;
				}
			}
			else if (sp <= 1) {
				if (sp == 0) {
					step = 2;
				}
				else if (sp == 1) {
					if (joker == 2) {
						step = 3;
					}
					else {
						step = 2;
					}
				}
			}
		}
		else if (trio == 3) {
			if (sp <= 2) {
				if (sp == 0) {
					if (joker == 0) {
						step = 2;
					}
					else {
						step = 3;
					}
				}
				else if (sp == 1) {
					step = 3;
				}
				else if (sp == 2) {
					if (joker == 2) {
						step = 4;
					}
					else {
						step = 3;
					}
				}
			}
			else if (sp >= 3) {
				if (joker == 0) {
					step = sp;
				}
				else {
					step = sp + 1;
				}
			}
		}
		else if (trio == 4) {
			if (sp <= 3) {
				if (sp == 2) {
					step = 4;
				}
				else if (sp == 1) {
					if (joker == 0) {
						step = 3;
					}
					else {
						step = 4;
					}
				}
				else if (sp == 0) {
					if (joker == 2) {
						step = 4;
					}
					else {
						step = 3;
					}
				}
				else if (sp == 3) {
					if (joker == 2) {
						step = 5;
					}
					else {
						step = 4;
					}
				}
			}
			else if (sp >= 4) {
				if (joker == 0) {
					step = sp;
				}
				else {
					step = sp + 1;
				}
			}
		}
		else if (trio == 5) {
			step = 4;
		}
	}
	if (bomb != 0 && trio == 0) {
		if (bomb == 1) {
			if (solo >= 2 || pair >= 2) {
				if (joker == 2) {
					step = sp;
				}
				else {
					step = res_1 - 1;
				}
			}
			else if ((solo == 1 && pair == 1) || (solo == 0 && pair == 1)) {
				if (joker == 2) {
					step = 3;
				}
				else {
					step = 2;
				}
			}
			else if (solo == 1 && pair == 0) {
				if (joker == 1) {
					step = 1;
				}
				else {
					step = 2;
				}
			}
			else if (solo == 1 && pair == 0) {
				if (joker == 0) {
					step = 1;
				}
				else {
					step = 2;
				}
			}
		}
		else if (bomb == 2) {
			if ((res >= 0 && res <= 2) || (res == 4)) {
				step = 2;
			}
			else if (res == 3) {
				if ((pair == 1 && solo == 1) || (pair == 1 && joker == 1)) {
					step = 2;
				}
				else {
					step = 3;
				}
			}
			else if (res == 5) {
				step = 3;
			}
			else if (res == 6) {
				if ((solo == 6) || (solo == 5 && joker == 1)) {
					step = 4;
				}
				else if ((solo == 2 && pair == 2) || (solo == 1 && joker == 1 && pair == 2)) {
					step = 2;
				}
				else {
					step = 3;
				}
			}
			else if (res == 7) {
				if ((solo == 7) || (solo == 6 && joker == 1)) {
					step = 5;
				}
				else if ((solo == 5 && pair == 1) || (solo == 5 && joker == 2) || (solo == 4 && joker == 1 && pair == 1) || (solo == 3 && joker == 2 && pair == 1)) {
					step = 4;
				}
				else {
					step = 3;
				}
			}
			else if (res == 8) {
				if (pair == 4) {
					step = 2;
				}
				else if ((solo == 8) || (solo == 7 && joker == 1)) {
					step = 6;
				}
				else if ((solo == 6 && joker == 2) || (solo == 6 && pair == 1) || (solo == 5 && joker == 1 && pair == 1)) {
					step = 5;
				}
				else if ((solo == 2 && pair == 3) || (solo == 2 && joker == 2 && pair == 2) || (solo == 1 && joker == 1 && pair == 3)) {
					step = 3;
				}
				else {
					step = 4;
				}
			}
			else if (res == 9) {
				if ((solo == 1 && pair == 4) || (joker == 1 && pair == 4)) {
					step = 3;
				}
				else if ((solo == 9) || (solo == 8 && joker == 1)) {
					step = 7;
				}
				else if ((solo == 7 && pair == 1) || (solo == 7 && joker == 2) || (solo == 6 && joker == 1 && pair == 1)) {
					step = 6;
				}
				else if ((solo == 5 && pair == 2) || (solo == 5 && joker == 2 && pair == 1) || (solo == 4 && pair == 2 && joker == 1)) {
					step = 5;
				}
				else {
					step = 4;
				}
			}

		}
		else if (bomb == 3) {
			if (res == 5) {
				if ((solo == 5) || (solo == 4 && joker == 1) || (solo == 3 && joker == 2)) {
					step = 4;
				}
				else {
					step = 3;
				}
			}
			else if (res == 4) {
				if (pair == 2) {
					step = 2;
				}
				else {
					step = 3;
				}
			}
			else {
				step = 3;
			}
		}
		else if (bomb == 4) {
			if (res == 0) {
				step = 2;
			}
			else {
				step = 3;
			}
		}
	}
	if (bomb != 0 && trio != 0) {
		if (bomb == 1) {
			if (trio == 1) {
				if (res == 0 || res == 1 || res == 3) {
					step = 2;
				}
				else if (res == 2) {
					if (joker == 2) {
						step = 3;
					}
					else {
						step = 2;
					}
				}
				else if (res == 4) {
					if ((solo == 2 && pair == 1) || (solo == 1 && joker == 1 && pair == 1) || (pair == 2)) {
						step = 2;
					}
					else {
						step = 3;
					}
				}
				else if (res == 5) {
					if ((solo == 5) || (solo == 4 && joker == 1)) {
						step = 4;
					}
					else if ((solo == 1 && pair == 2) || (joker == 1 && pair == 2)) {
						step = 2;
					}
					else {
						step = 3;
					}
				}
				else if (res == 6) {
					if (pair == 3) {
						step = 2;
					}
					else if ((solo == 6) || (solo == 5 && joker == 1)) {
						step = 5;
					}
					else if ((solo == 4 && joker == 2) || (solo == 4 && pair == 1) || (solo == 3 && joker == 1 && pair == 1)) {
						step = 4;
					}
					else {
						step = 3;
					}
				}
				else if (res == 7) {
					if ((solo == 7) || (solo == 6 && joker == 1)) {
						step = 6;
					}
					else if ((solo == 5 && pair == 1) || (solo == 5 && joker == 2) || (solo == 4 && joker == 1 && pair == 1)) {
						step = 5;
					}
					else if ((solo == 1 && pair == 3) || (solo == 1 && joker == 2 && pair == 2) || (pair == 3 && joker == 1)) {
						step = 3;
					}
					else {
						step = 4;
					}
				}
				else if (res == 8) {
					if ((solo == 8) || (solo == 7 && joker == 1)) {
						step = 7;
					}
					else if ((solo == 6 && joker == 2) || (solo == 6 && pair == 1) || (solo == 5 && joker == 1 && pair == 1)) {
						step = 6;
					}
					else if ((pair == 4) || (joker == 2 && pair == 3)) {
						step = 3;
					}
					else if ((solo == 2 && pair == 3) || (solo == 2 && joker == 2 && pair == 2) || (solo == 1 && joker == 1 && pair == 3)) {
						step = 4;
					}
					else {
						step = 5;
					}
				}
				else if (res == 9) {
					if ((solo == 9) || (solo == 8 && joker == 1)) {
						step = 8;
					}
					else if ((solo == 7 && pair == 1) || (solo == 7 && joker == 2) || (solo == 6 && joker == 1 && pair == 1)) {
						step = 7;
					}
					else if ((solo = 5 && pair == 2) || (solo == 5 && joker == 2 && pair == 1) || (solo == 4 && pair == 2 && joker == 1)) {
						step = 6;
					}
					else if ((solo == 3 && pair == 3) || (solo == 3 && pair == 2 && joker == 2) || (solo == 2 && pair == 3 && joker == 1)) {
						step = 5;
					}
					else {
						step = 4;
					}
				}
				else if (res == 10) {
					if ((solo == 10) || (solo == 9 && joker == 1)) {
						step = 9;
					}
					else if ((solo == 8 && pair == 1) || (solo == 8 && joker == 2) || (solo == 7 && joker == 1 && pair == 1)) {
						step = 8;
					}
					else if ((solo == 6 && pair == 2) || (solo == 6 && pair == 1 && joker == 2) || (solo == 5 && pair == 2 && joker == 1)) {
						step = 7;
					}
					else if ((solo == 4 && pair == 3) || (solo == 4 && pair == 2 && joker == 2) || (solo == 3 && joker == 1 && pair == 3)) {
						step = 6;
					}
					else if ((pair == 5) || (pair == 4 && joker == 2)) {
						step = 4;
					}
					else {
						step = 5;
					}
				}
			}
			else if (trio == 2) {
				if (res == 0 || res == 1) {
					step = 2;
				}
				else if (res == 2) {
					if (pair == 1) {
						step = 2;
					}
					else {
						step = 3;
					}
				}
				else if (res == 3 || res == 4) {
					step = 3;
				}
				else if (res == 5) {
					if ((solo == 5) || (solo == 4 && joker == 1) || (solo == 3 && joker == 2)) {
						step = 4;
					}
					else {
						step = 3;
					}
				}
				else if (res == 6) {
					if ((solo == 6) || (solo == 5 && joker == 1)) {
						step = 5;
					}
					else if ((solo == 4 && joker == 2) || (solo == 4 && pair == 1) || (solo == 3 && joker == 1 && pair == 1) || (solo == 2 && pair == 1 && joker == 2)) {
						step = 4;
					}
					else {
						step = 3;
					}
				}
				else if (res == 7) {
					if ((solo == 7) || (solo == 6 && joker == 1)) {
						step = 6;
					}
					else if ((solo == 5 && pair == 1) || (solo == 5 && joker == 2) || (solo == 4 && joker == 1 && pair == 1)) {
						step = 5;
					}
					else if ((solo == 1 && pair == 3) || (pair == 3 && joker == 1)) {
						step = 3;
					}
					else {
						step = 4;
					}
				}
			}
			else if (trio == 3) {
				if (res == 0 || res == 1 || res == 2) {
					step = 3;
				}
				else if (res == 3) {
					if ((solo == 1 && pair == 1) || (joker == 1 && pair == 1)) {
						step = 3;
					}
					else {
						step = 4;
					}
				}
				else if (res == 4) {
					if (pair == 2) {
						step = 3;
					}
					else {
						step = 4;
					}
				}
			}
			else if (trio == 4) {
				if (res == 0) {
					step = 3;
				}
				else if (res == 1) {
					step = 4;
				}
			}
		}
		else if (bomb == 2) {
			if (trio == 1) {
				if (res == 0) {
					step = 2;
				}
				else if (res == 1) {
					step = 3;
				}
				else if (res == 2) {
					if (pair == 1) {
						step = 2;
					}
					else {
						step = 3;
					}
				}
				else if (res == 3) {
					if ((solo == 1 && pair == 1) || (joker == 1 && pair == 1)) {
						step = 2;
					}
					else {
						step = 3;
					}
				}
				else if (res == 4 || res == 5) {
					step = 3;
				}
				else if (res == 6) {
					if ((solo == 6) || (solo == 5 && joker == 1) || (solo == 4 && joker == 2)) {
						step = 4;
					}
					else {
						step = 3;
					}
				}
			}
			else if (trio == 2) {
				if (res == 0) {
					step = 2;
				}
				else if (res == 1) {
					step = 3;
				}
				else if (res == 2) {
					if (joker == 2 || pair == 1) {
						step = 3;
					}
					else {
						step = 4;
					}
				}
				else if (res == 3) {
					if ((solo == 1 && pair == 1) || (joker == 1 && pair == 1) || (solo == 1 && joker == 2)) {
						step = 3;
					}
					else {
						step = 4;
					}
				}
			}
			else if (trio == 3) {
				step = 3;
			}
		}
		else if (bomb == 3 && trio == 1) {
			step = 3;
		}
	}

	return step;
}

void count_sanpai(int* solo, int* pair, int* joker, int* trio, int* bomb, int* a) //相当于传进去的数组是pai
{
	int i;
	for (i = 0; i <= 15; i++) {
		if ((a[i] == 1) && (i != 15)) {
			*solo += 1;
		}
		if ((a[i] == 2) && (i != 15)) {
			*pair += 1;
		}
		if (a[15] == 1) {
			*joker = 1;
		}
		if (a[15] == 2) {
			*joker = 2;
		}
		if (a[i] == 3) {
			*trio += 1;
		}
		if (a[i] == 4) {
			*bomb += 1;
		}
	}
}




int main(void)
{
	int round, card_number, i, number;
	int count = 0;
	int tmp_num[2] = { 0 };
	char ch;
	int is_inline = 0;
	int answer;

	int solo = 0; int pair = 0; int joker = 0;
	scanf_s("%d %d", &round, &card_number);
	getchar();

	for (i = 0; i < round; i++) {
		int pai[16] = { 0 };
		while ((ch = getchar()) && (ch != EOF)) {

			if (ch == ' ') {
				is_inline = 0;
				if (count == 2) {
					number = tmp_num[0] * 10 + tmp_num[1];
				}
				else if (count == 1) {
					number = tmp_num[0];
				}
				tmp_num[0] = 0; tmp_num[1] = 0; count = 0;
				if (number != 1 && number != 14) {
					pai[number] += 1;
				}
				else if (number == 1) {
					pai[14] += 1;
				}
				else if (number == 14) {
					pai[15] += 1;
				}
			}
			else if (ch == '\n') {
				is_inline = 0;
				if (count == 2) {
					number = tmp_num[0] * 10 + tmp_num[1];
				}
				else if (count == 1) {
					number = tmp_num[0];
				}
				tmp_num[0] = 0; tmp_num[1] = 0; count = 0;
				if (number != 1 && number != 14) {
					pai[number] += 1;
				}
				else if (number == 1) {
					pai[14] += 1;
				}
				else if (number == 14) {
					pai[15] += 1;
				}
				break;
			}
			else {
				if (is_inline == 0) {
					tmp_num[0] = ch - '0';
					count += 1;
				}
				else if (is_inline == 1) {
					tmp_num[1] = ch - '0';
					count += 1;
				}

				is_inline = 1;
			}
		}
		answer = chupai(0, pai);
		printf("%d\n", answer);
		ans = 17;
	}





}*/