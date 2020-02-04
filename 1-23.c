#include <fileopen.h>

int main(int argc, const char* argv[]) {
	if (openFiles(argc, argv) != true) { return 1; }

	FILE* fin = fopen(argv[1], "r");
	FILE* fout = fopen(argv[2], "w");
	int state;
	int t = atoi(argv[3]);

	char c, temp;
	state = 0;
	while ((c = fgetc(fin)) != EOF) {
		if (state == 3) {
			if (c == '\'') { state = 0; }
			fputc(c, fout);
		}
		else if (state == 4) {
			if (c == '\"') { state = 0; }
			fputc(c, fout);
		}
		else if (state == 0 ) {
			if (c == '\'') { state = 3; }
			if (c == '\"') { state = 4; }

		}
		else if (c == '\\') {
			temp = c;
			if (c = fgetc(fin) == '\\') { state = 2; }
			else if (c = fgetc(fin) == '\*') { state = 1; }
			else { fputc(c, fout); }
		}
		else if (state == 1) {
			if (c == '*' && (c = fgetc(fin)) == '\\') {
				state = 0;
			}
		}
		else if (state == 2) {
			if (c == '\n') {
				fputc(c, fout);
				state = 0;
			}
		}
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
