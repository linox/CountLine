void CodeCountError(char *program, char *arg) {
	if (strcmp(arg, "RUN_INIT") == 0) {
		system("cls");
		printf("\n%s: Nome/caminho do arquivo não informado.\n\n", program);
	} else {
		if (strcmp(arg, "FILE_ERROR") == 0) {
			system("cls");
			printf("\n%s: Arquivo não encontrado.\n\n", program);
		} else {
			system("cls");
			printf("\n%s: [%s] não é um argumento válido.\n\n", program, arg);
		}
	}
	
	exit(0);
}
