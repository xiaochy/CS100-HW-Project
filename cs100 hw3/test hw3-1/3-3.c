#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>
enum JumpType {
    T, S, Lo, F, Lz, A
};

static double scoreTable[4][6] = { {0.4, 0.4, 0.5, 0.5, 0.6, 1.1},
                                   {1.3, 1.3, 1.7, 1.8, 2.1, 3.3},
                                   {4.2, 4.3, 4.9, 5.3, 5.9, 8.0},
                                   {9.5, 9.7, 10.5, 11.0, 11.5, 12.5} };

double Score(int rotations, enum JumpType type) {
    if (rotations < 1 || rotations > 4) {
        return -1;
    }
    return scoreTable[rotations - 1][type];
}
int max_2(int a, int b) {
    int max=a;
    if (b >= max) {
        max = b;
    }
    return max;
    
}
int min_2(int a, int b) {
    int min = a;
    if (b <= min) {
        min = b;
    }
    return min;
}

float value(int a, int b, char* str) {
    int i;
    int rotation;
    int type;
    float middle=0;
    int percent_70 = 0;

    for (i = a; i <= b; i++) {
        if (str[i] == '1') {
            rotation = 1;
        }
        else if (str[i] == '2') {
            rotation = 2;
        }
        else if (str[i] == '3') {
            rotation = 3;
        }
        else if (str[i] == '4') {
            rotation = 4;
        }
        else if (str[i] == 'T') {
            type = 0;
        }
        else if (str[i] == 'S') {
            type = 1;
        }
        else if (str[i] == 'F') {
            type = 3;
        }
        else if (str[i] == 'A') {
            type = 5;
        }
        else if (str[i] == 'L') {
            if (str[i + 1] == 'o') {
                type = 2;
            }
            else if (str[i + 1] == 'z') {
                type = 4;
            }
        }
        else if (str[i] == 'q' || str[i] == '!') {
            middle += 0;
        }
        else if (str[i] == 'e') {
            percent_70 = 1;
        }
        else if (str[i] == '<') {
            if (str[i + 1] == '<') {
                rotation -= 1;
            }
            else if(str[i-1]!='<'){//xiugaile
                percent_70 += 1;
            }
        }

    }
    if (rotation == 0) {
        middle += 0;
    }
    else {
        middle += Score(rotation, type);
        for (i = 0; i < percent_70; i++) {
            middle *= 0.7;
        }
    }
    return middle;
}




int count_loop(int a, int b, char* str) {
    int is_valid = 1;
    int i, j, k, p;

    if (str[a] != '1' && str[a] != '2' && str[a] != '3' && str[a] != '4') {
        is_valid = 0;

    }
    else {
        for (j = a + 1; j <= b; j++) {
            if (isdigit(str[j]) != 0) {
                is_valid = 0;
            }
        }
        if (str[a + 1] == 'T' || str[a + 1] == 'S' || str[a + 1] == 'F' || str[a + 1] == 'A') {
            for (k = a + 2; k <= b; k++) {
                if (str[k] == 'T' || str[k] == 'S' || str[k] == 'F' || str[k] == 'A' || str[k] == 'L' || str[k] == 'o' || str[k] == 'z') {
                    is_valid = 0;
                    break;
                }

            }
                int count_q = 0;
                int count_min = 0;
                int count_e = 0;
                int count_exclaim = 0;
                int q_idx = b;
                int min_idx = b;
                int e_idx = 0;
                int exclaim_idx = 0;
                if (str[a + 1] == 'T' || str[a + 1] == 'S' || str[a + 1] == 'A') {
                    for (p = a + 2; p <= b; p++) {
                        if (str[p] == 'q') {
                            count_q += 1;
                            q_idx = p;
                        }
                        if (str[p] == '<') {
                            count_min += 1;
                            min_idx = p;
                        }
                        if (str[p] == '!' || str[p] == 'e') {
                            is_valid = 0;
                        }
                        if (count_q >= 2 || count_min >= 3) {
                            is_valid = 0;
                        }
                        if (count_q >= 1 && count_min >= 1) {
                            is_valid = 0;
                        }
                    }
                }

                else if (str[a + 1] == 'F') {
                    for (p = a + 2; p <= b; p++) {
                        if (str[p] == '!') {
                            count_exclaim += 1;
                            exclaim_idx = p;
                        }
                        if (str[p] == 'e') {
                            count_e += 1;
                            e_idx = p;
                        }
                        if (str[p] == 'q') {
                            count_q += 1;
                            q_idx = p;
                        }
                        if (str[p] == '<') {
                            count_min += 1;
                            min_idx = p;
                        }
                        if (count_q >= 2 || count_min >= 3) {
                            is_valid = 0;
                        }
                        if (count_q >= 1 && count_min >= 1) {
                            is_valid = 0;
                        }
                        if (count_exclaim >= 1 && count_e >= 1) {
                            is_valid = 0;
                        }
                        if (count_exclaim >= 2 || count_e >= 2) {
                            is_valid = 0;
                        }
                        if (is_valid == 1) {
                            if ((count_q == 1 || count_min == 1) && (count_e == 1 || count_exclaim == 1)) {
                                if (max_2(exclaim_idx, e_idx) < min_2(q_idx, min_idx)) {
                                    is_valid = 1;
                                }
                                else {
                                    is_valid = 0;
                                }
                            }
                        }
                    }
                }
            

        }

        else if ((str[a + 1] == 'L' && str[a + 2] == 'o') || (str[a + 1] == 'L' && str[a + 2] == 'z')) {
            for (k = a + 3; k <= b; k++) {
                if (str[k] == 'T' || str[k] == 'S' || str[k] == 'F' || str[k] == 'A' || str[k] == 'L' || str[k] == 'o' || str[k] == 'z') {
                    is_valid = 0;
                    break;
                }
            }

            int count_q = 0;
            int count_min = 0;
            int count_e = 0;
            int count_exclaim = 0;
            int q_idx = b;
            int min_idx = b;
            int e_idx = 0;
            int exclaim_idx = 0;
            if (str[a + 1] == 'L' && str[a + 2] == 'o') {
                for (p = a + 3; p <= b; p++) {
                    if (str[p] == 'q') {
                        count_q += 1;
                        q_idx = p;
                    }
                    if (str[p] == '<') {
                        count_min += 1;
                        min_idx = p;
                    }
                    if (str[p] == '!' || str[p] == 'e') {
                        is_valid = 0;
                    }
                    if (count_q >= 2 || count_min >= 3) {
                        is_valid = 0;
                    }
                    if (count_q >= 1 && count_min >= 1) {
                        is_valid = 0;
                    }
                }
            }
            else if (str[a + 1] == 'L' && str[a + 2] == 'z') {
                for (p = a + 3; p <= b; p++) {
                    if (str[p] == '!') {
                        count_exclaim += 1;
                        exclaim_idx = p;
                    }
                    if (str[p] == 'e') {
                        count_e += 1;
                        e_idx = p;
                    }
                    if (str[p] == 'q') {
                        count_q += 1;
                        q_idx = p;
                    }
                    if (str[p] == '<') {
                        count_min += 1;
                        min_idx = p;
                    }
                    if (count_q >= 2 || count_min >= 3) {
                        is_valid = 0;
                    }
                    if (count_q >= 1 && count_min >= 1) {
                        is_valid = 0;
                    }
                    if (count_exclaim >= 1 && count_e >= 1) {
                        is_valid = 0;
                    }
                    if (count_exclaim >= 2 || count_e >= 2) {
                        is_valid = 0;
                    }
                    if (is_valid == 1) {
                        if ((count_q == 1 || count_min == 1||count_min==2) && (count_e == 1 || count_exclaim == 1)) {
                            if (max_2(exclaim_idx, e_idx) < min_2(q_idx, min_idx)) {
                                is_valid = 1;
                            }
                            else {
                                is_valid = 0;
                            }
                        }
                    }
                }
            }
           



        }
        else if (str[a + 1] == 'x') {
            is_valid = 0;
        }
        else {
        is_valid = 0;
}
       
    }
    return is_valid;
}


    
    
    int main(void){
        int i, j, k, p;
        int len;
        char str[100] = { 0 };
        char ch;

        for (j = 0; j < 3; j++) {
            int is_valid = 1;
            int count_char = 0;
            int plus[2] = { 0 };
            while ((ch = getchar()) != '\n' && ch != EOF) {
                str[count_char] = ch;
                count_char += 1;
            }
            str[count_char] = '\0';
            len = strlen(str);
            int count_plus = 0;

            for (i = 0; i < len; i++) {

                if (str[i] == '+') {
                    count_plus += 1;
                    if (count_plus == 1) {
                        plus[0] = i;
                    }
                    else if (count_plus == 2) {
                        plus[1] = i;
                    }
                }


                if (str[i] == 'x') {
                    if (i != len - 1) {
                        count_plus = -1;
                        is_valid = 0;
                        //break;
                    }
                }
                if (str[i] != 'T' && str[i] != 'S' && str[i] != 'L' && str[i] != 'o' && str[i] != 'F' && str[i] != 'z' &&
                    str[i] != 'A' && str[i] != 'q' && str[i] != '<' && str[i] != '!' && str[i] != 'e' && str[i] != 'x' && str[i] != '+' &&
                    str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4') {
                    count_plus = -1;
                    is_valid = 0;
                    //break;

                }

            }

            if (count_plus == 0 && is_valid == 1) {
                is_valid = count_loop(0, len - 1, str);
            }
            else if (count_plus == 1 && is_valid == 1) {
                int pre_right_1 = 0;//等于1的时候才能执行下一个循环
                is_valid = count_loop(0, plus[0] - 1, str);

                if (is_valid == 1) {
                    pre_right_1 = 1;
                }

                if (pre_right_1 == 1)
                    is_valid = count_loop(plus[0] + 1, len - 1, str);
            }


            else if (count_plus == 2 && is_valid == 1) {
                int pre_right_2 = 0;
                int pre_right_3 = 0;
                is_valid = count_loop(0, plus[0] - 1, str);
                if (is_valid == 1) {
                    pre_right_2 = 1;
                }

                if (pre_right_2 == 1) {
                    is_valid = count_loop(plus[0] + 1, plus[1] - 1, str);
                    if (is_valid == 1) {
                        pre_right_3 = 1;
                    }

                }
                if (pre_right_2 == 1 && pre_right_3 == 1) {
                    is_valid = count_loop(plus[1] + 1, len - 1, str);
                }
            }
            float base = 0;
            /*int rotation;
            int type;
            int no_influence = 0;
            int percent_70 = 0;*/
            if (is_valid == 1) {
                if (count_plus == 0) {
                    base += value(0, len - 1, str);
                }
                else if (count_plus == 1) {
                    base += value(0, plus[0] - 1, str);
                    base += value(plus[0] + 1, len - 1, str);
                }
                else if (count_plus == 2) {
                    base += value(0, plus[0] - 1, str);
                    base += value(plus[0] + 1, plus[1] - 1, str);
                    base += value(plus[1] + 1, len - 1, str);
                }
            }
            if (str[len - 1] == 'x') {
                base *= 1.1;
            }
            printf("%.2f\n", base);

        }
    }



