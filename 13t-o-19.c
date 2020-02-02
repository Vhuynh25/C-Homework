#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#define MAXLINE 1000

char wordbuf[50];
int words[50]; // array of word length of the index
int length;

void copy(char to[], char from[]);
void copyNoTrailing(char to[], char from[]);

void addword() {
	words[length] += 1;
}

// Exercise 1-13
void lengthsHist() {
	printf("---- Exercise 1-13 histogram of word lengths ----\n");
	int c;
	memset(words, 0, sizeof words); //the entire words array in 0
	while ((c = getchar()) != EOF) {
		if (isalpha(c) == 0 && c != '-' && c != ''') {
			addword();
			length = 0;
		}
		else {
			length++;
		}
	}
	for (int i = 1; i <= 50; ++i) {
		printf("%3d: ", i);
		for (int j = 0; j < words[i]; ++j) {
			printf("*");
			if (j % 5 == 4) { printf("|"); }
		}
		printf("\n");
	}

}

// Exercise 1-14
void charHist() {
	printf("---- Exercise 1-14 histogram of chars ----\n");
	int characters[127];
	int c;
	memset(characters, 0, sizeof(characters)); // set array characters to 0

	c = getchar();
	int length = 0;
	do { // use c as index for array character
		characters[c] += 1;
	} while ((c = getchar()) != EOF);

	for (length = 32; length <= 127; ++length) { // ignore first 31 characters of ASCII
		putchar(length);
		putchar(':');
		for (int j = 0; j < characters[length]; ++j) {
			printf("*");
			if (j % 5 == 4) { printf("|"); }
		}
		printf("\n");
	}

}

float convertFtoC(float f) {
	float c = (5.0 / 9.0)*(f - 32);
	return c;
}

float convertCtoF(float C) {
	float F = (9.0 / 5.0)*(C + 32);
	return F;
}
float convertCtoK(float c) { return c - 273; }

float convertFtoK(float f) { return convertCtoK(convertFtoC(f)); }

float convertKtoC(float k) { return k + 273; }


void printLongestLine() { //Exercise 1-16
	printf("---- Exercise 1-16 print only the longest line ----\n");
	int len, max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while ((len = getlinex(line, MAXLINE)) > 0) {
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) { printf("%s\n%d\n", longest, max); }
	return;
}

void print80plus() { //Exercise 1-17
	printf("---- Exercise 1-17 print only 80 plus lines ----\n");
	int len, cutOff;
	char line[MAXLINE];
	char longest[MAXLINE];

	cutOff = 80;
	while ((len = getlinex(line, MAXLINE)) > 0) { // while getting line, if line length = 80 or greater, printf that line
		if (len >= cutOff) {
			copy(longest, line);
			printf("%s\n", longest);
		}
	}
	return;
}


void removeBlanks() {// Exercise 1-18
	printf("---- Exercise 1-18 Remove trailing blanks and empty lines ----\n");
	int len, cutOff;
	char line[MAXLINE];

	while ((len = getlineNoTrailing(line, MAXLINE)) > 0) {
		if (len > 0) {
			printf("%s\n", line);
		}
	}
	return;
}

int getlinex(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void copy(char to[], char from[]) {
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}

int getlineNoTrailing(char s[], int lim) {
	int c, i, j;
	j = 0;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
		if (c == '\t' || c == ' ') { j++; } // whitespace start counting
		else { j = 0; }
	}
	if (c == '\n' && j != 0) { // if there is whitespace at the end move i accordingly
		i = i - j;
		if (i != 0){ 
		s[i] = c;
		++i;
		}
	}
	s[i] = '\0';
	return i;
}

// Exercise 1-19
int getAll(char s[], int lim) { // modified getline to keep going until EOF
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
void reverse(char norm[]) {
	int c = strlen(norm) - 1;
	int d = 0;
	char to[MAXLINE];
	for (; c >= 0; --c) {
		to[d++] = norm[c];
	}
	to[d] = 0;
	printf("%s\n", to);
}

void readReverse() {
	printf("---- Exercise 1-19 reverse the entire input ----\n");
	int len;
	char line[MAXLINE];

	getAll(line, MAXLINE);

	reverse(line);
	return;
}

int main(int argc, const char* argv[]) {

	lengthsHist();
	charHist();
	printLongestLine();
	print80plus();
	removeBlanks();
	readReverse();

	return 0;
}
