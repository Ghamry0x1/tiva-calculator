#include "parser_module.h"

char n1[16] = "", n2[16] = "", op = 'a';
int i = 0;
bool Opchanged = false;

void append(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
}

double strToInt(char a[]) {
    int c, sign = 0, offset;
    double n;

    if (a[0] == '-') {  // Handle negative integers
        sign = -1;
    }

    if (sign == -1) {  // Set starting position to convert (starts from index 1 if the number starts with negative sign)
        offset = 1;
    }
    else {
        offset = 0;
    }

    n = 0;

    for (c = offset; a[c] != '\0'; c++) {
        n = n * 10 + a[c] - '0';
    }

    if (sign == -1) {
        n = n*-1;
    }

    return n;
}

char* parser(char c[]) {
    //char c;
    //scanf_s("%c", &c); // 10--10
    while (c != '=') {
        if (isdigit(c) || i == 0 || Opchanged) {
            if (op == 'a') {
                append(n1, c); // add the char to the first string (number)

            }
            else {
                append(n2, c); // add the char to the second string (number)
            }
        }
        else if(!Opchanged){
            op = c;
            Opchanged = true;
        }
        i++;
        //scanf_s("%c", &c);
    }

    int x;
    switch (op) {
    case '+':
        x = strToInt(n1) + strToInt(n2);
        break;
    case '-':
        x = strToInt(n1) - strToInt(n2);
        break;
    case '*':
        x = strToInt(n1) * strToInt(n2);
        break;
    //default:
    //  x =  (double)(strToInt(n1) / strToInt(n2));

    }
    char num[16];
    _itoa(x, num, 10);
    //printf("%s", num);
    //printf("\n");
}
