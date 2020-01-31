#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#define MAXLINE 1000

char wordbuf[50];
int words[50];
int length;

void copy(char to[], char from[]);
void copyNoTrailing(char to[], char from[]);

void addword() {
	words[length] += 1;
}

// Exercise 1-13
void lengthsHist() {
	int c;
	memset(words, 0, sizeof words);
	while ((c = getchar()) != EOF) {
		if (isalpha(c) == 0 && c != '-') {
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
	int characters[127];
	int c;
	memset(characters, 0, sizeof(characters));

	c = getchar();
	int length = 0;
	do {
		characters[c] += 1;
	} while ((c = getchar()) != EOF);

	for (length = 32; length <= 127; ++length) {
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
	int len, cutOff;
	char line[MAXLINE];
	char longest[MAXLINE];

	cutOff = 80;
	while ((len = getlinex(line, MAXLINE)) > 0) {
		if (len > cutOff) {
			copy(longest, line);
			printf("%s\n", longest);
		}
	}
	return;
}


void removeBlanks() {// Exercise 1-18
	int len, cutOff;
	char line[MAXLINE];
	char trueLine[MAXLINE];

	while ((len = getlinex(line, MAXLINE)) > 0) {
		if (len > 0) {
			copyNoTrailing(trueLine, line);
			//printf("%s\n", trueLine);
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


void copyNoTrailing(char to[], char from[]) {
	int i, j, k, state;
	char buf[MAXLINE];
	//memset(buf, '\0', sizeof buf);

	state = j = k = i = 0;
	while (from[i] != '\0') {
		if (from[i] == ' ' || from[i] == '\t') {
			state = 1;
			buf[k++] = from[i];
			//buf[k] = '\0';
		}
		else if (state == 1) {
			state = 0;
			strcpy_s(to + j,MAXLINE, buf);
			j = j + k;
			k = 0;
			to[j++] = from[i];
			to[j] = '\0';
		}
		else {
			to[j++] = from[i];
			to[j] = '\0';
		}
		++i;
	}
	printf("%s", to);
}

// Exercise 1-19

void reverse(char norm[], char to[]) {
	int c = strlen(norm) - 1;
	int d = 0;
	for (; c >= 0; --c) {
		to[d++] = norm[c];
	}
	to[d] = 0;
	printf("%s\n", to);
}

void readReverse() {
	int len;
	char line[MAXLINE];
	char d[MAXLINE];

	while ((len = getlinex(line, MAXLINE)) > 0) {
		if (len > 0) {
			reverse(line, d);
		}
	}
	return;
}

int main(int argc, const char* argv[]) {

	//lengthsHist();
	//charHist();
	//printLongestLine();
	//print80plus();
	//removeBlanks();
	//readReverse();

	return 0;
}