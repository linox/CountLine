void CodeCountError(char *program, char *arg) {
	if (strcmp(arg, "RUN_INIT") == 0) {
		system("cls");
		printf("\n%s: Nome/caminho do arquivo n�o informado.\n\n", program);
	} else {
		if (strcmp(arg, "FILE_ERROR") == 0) {
			system("cls");
			printf("\n%s: Arquivo n�o encontrado.\n\n", program);
		} else {
			system("cls");
			printf("\n%s: [%s] n�o � um argumento v�lido.\n\n", program, arg);
		}
	}
	
	exit(0);
}
