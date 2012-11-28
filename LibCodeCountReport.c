#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void StartReport(char Vfile[255], int *lines, int *emptyLines, int *commentLines, int *commentMultiLines, float *percentComment, int *mode, char *report) {
	FILE *pReport;
	char str[1000], num[10];
	int loop = 0;
	
	strcpy(str, "#####################################################\n");
	strcat(str, "##                 Code Count - 2010               ##\n");
	strcat(str, "##                 Version Ultimate                ##\n");
  	strcat(str, "#####################################################\n\n");
	strcat(str, "\tArquivo processado:\t");
	strcat(str, Vfile);
	strcat(str, "\n\n");
	strcat(str, "\tNúmero de linhas:\t\t\t");
	sprintf(num, "%d", *lines);
	strcat(str, num);
	strcat(str, "\n");
	strcat(str, "\tNúmero de linhas vazias:\t");
	sprintf(num, "%d", *emptyLines);
	strcat(str, num);
	
	if (*mode == 1) {
		strcat(str, "\n");
		strcat(str, "\tNúmero de comentários (//):\t");
		sprintf(num, "%d", *commentLines);
		strcat(str, num);
		strcat(str, "\n");
		strcat(str, "\tNúmero de comentários (/*):\t");
		sprintf(num, "%d", *commentMultiLines);
		strcat(str, num);
		strcat(str, "\n");
		strcat(str, "\tPercentual de comentários: \t");
		sprintf(num, "%.2f", *percentComment);
		strcat(str, num);
		strcat(str, "%");
	}
	
	// Cria o arquivo
	if (!(pReport = fopen(report, "w"))) {
		printf("\n\nErro ao criar arquivo!\n\n");
		exit(0);
	}
	
	// Grava no arquivo
	while (str[loop] != '\0') {
		putc(str[loop], pReport);
		loop++;
	}
}
