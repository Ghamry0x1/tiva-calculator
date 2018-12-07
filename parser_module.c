#include "parser_module.h"

char n1[16] = "", n2[16] = "", op = 'a';
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

void reverse(char s[]) {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str);

    return str;
}

void parser(char x[]) {
    int i;
	for (i = 0; x[i] != '\0'; i++) {
		if (!isdigit(x[i]) && i == 0) // the first number is negative (or positive (ex:+90)----- also handled )
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
	itoa(n, num, 10);
	
    LCD_command(0xC0);

    for(i = 0; num[i]!='\0'; i++)
        LCD_data(num[i]);

    Globals_reset();
}

void Globals_reset(void) {
    memset(n1, 0, 255);
    memset(n2, 0, 255);
    op = 'a';
    Opchanged = false;
}
