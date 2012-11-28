void CodeCountOutput(char *file[], int *lines, int *emptyLines, int *commentLines, int *commentMultiLines, float *percentComment, int *mode) {
	system("cls");
	
	char *report="Codecount_report.txt";
	if (*mode == 2 || *mode == 0) {
		printf("#####################################################\n");
	  	printf("##                 Code Count - 2010               ##\n");
	  	printf("##                 Version Ultimate                ##\n");
	  	printf("#####################################################");
		printf("\n\n\tArquivo processado: %s", file[1]);
	  	printf("\n\n\tNúmero de linhas:\t\t%d", *lines);
	  	printf("\n\tNúmero de linhas vazias:\t%d", (*emptyLines<1)?0:*emptyLines);
	} else {
		printf("Arquivo \"%s\" gerado em:\n", report);
		system("pwd");
	}
  	
  	switch (*mode) {
  		case 2: 
  			/* Foi passado o parâmetro (-c) ou (-comment) */
	  		printf("\n\tNúmero de comentários (//):\t%d", (*commentLines<1)?0:*commentLines);
	  		printf("\n\tNúmero de comentários (/*):\t%d", (*commentMultiLines<1)?0:*commentMultiLines);
			printf("\n\tPercentual de comentários:\t%.2f%%", (*percentComment<0.1)?0.0:*percentComment);
	  		break;
	  	case 3:
	  		/* Foi passado o parâmetro (-s) ou (-silent) */
	  		StartReport(file[1], lines, emptyLines, commentLines, commentMultiLines, percentComment, mode, report);
	  		break;
	  	case 1:
	  		/* Foi passado o parâmetro (-c) ou (-comment) e (-s) ou (-silent) */
	  		StartReport(file[1], lines, emptyLines, commentLines, commentMultiLines, percentComment, mode, report);
  	}
  	
  	printf("\n\n");
}
