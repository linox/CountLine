void ShowHelp() {
	system("cls");
	printf("#####################################################\n");
  	printf("##                 Code Count - HELP               ##\n");
  	printf("##                 Version Ultimate                ##\n");
  	printf("#####################################################");
	printf("\n\nExibe a quantidade de linhas de um ARQUIVO.\n");
	printf("Quantidade de linhas e quantidade de linhas vazias. (modo padrão)");
	printf("\n\nUso: ./codecount [ARQUIVO]... [OPÇÕES]...");
	printf("\n\nArgumentos opcionais:\n\n");
	printf("\t-c, -comment\t exibir quantidade de linhas comentadas.\n");
	printf("\t-h, -help\t exibir help.\n");
	printf("\t-s, -silent\t não exibir resultados na tela.\n");
	printf("\t\t\t Esta opção faz com que o resultado do processamento seja gravado em\n");
	printf("\t\t\t um arquivo chamado \"Codecount_report.txt\" que é gerado no mesmo\n"); 
	printf("\t\t\t diretório onde está localizado o programa CodeCount.\n");
	exit(0);
}
