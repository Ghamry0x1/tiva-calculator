#include "parser_module.h"

char n1[16] = "", n2[16] = "", op = 'a';
int i = 0;
bool Opchanged = false;

void append(char* s, char c)
{
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}

int strToInt(char a[]) {
	int c, sign = 0, offset;
	int n;

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
void parser(char x[]) {
	for (int i = 0; x[i] != '\0'; i++) {
		if (!isdigit(x[i]) && i == 0) // the first number is negative (or postive (ex:+90)----- also handled )
			append(n1, x[i]);
		else if (isdigit(x[i]) && op == 'a') // still adding to the first string (number) because there is no op yet (op == 'a')
			append(n1, x[i]);
		else if (!isdigit(x[i]) && op == 'a') // first string (number) finished and received an operand 
			op = x[i];
		else if (!isdigit(x[i]) && op != 'a') // second string (number) is negative (ex : 90 + -10)
			append(n2, x[i]);
		else if (isdigit(x[i]) && op != 'a') // still adding to the second string (number) because there is op (op != 'a')
			append(n2, x[i]);
	}

	int n;
	switch (op) {
	case '+':
		n = strToInt(n1) + strToInt(n2);
		break;
	case '-':
		n = strToInt(n1) - strToInt(n2);
		break;
	case '*':
		n = strToInt(n1) * strToInt(n2);
		break;
	default:
		n =  strToInt(n1) / strToInt(n2);

	}
	char num[16];
	_itoa(n, num, 10);
	
    LCD_command(0xC0);

    for(int i;num[i]!='\0';i++)
        LCD_data(num[i]);

}
