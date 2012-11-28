int optionsHandler(int argc, char *argv[]) {
	/*
	* Verifica quais parâmetros foram passados e retorna o código
	* correspondente a cada processo que deverá ser executado.
	* =======================================================================
	* Integer	comment		(0) Parâmetro desligado. (1) Parâmetro ligado
	* Integer	silent 		(0) Parâmetro desligado. (1) Parâmetro ligado
	* Integer	selected	Posição do parâmetro corrente no FOR.
	*/
	
	int comment=0, silent=0, selected;
	
	for (selected=2; selected<argc; selected++) {
		if (argv[selected][1] == 'h') {
			ShowHelp();
		}
		
		if (argv[selected][1] == 'c') {
			comment = 1;
		} else {
			if (argv[selected][1] == 's') {
				silent = 1;
			}
		}
	}
	
	return getOptionHandler(&comment, &silent, argv);
}

int getOptionHandler(int *comment, int *silent, char *argv[]) {
	if (*comment == 1 && *silent == 1) {
		// Conta as linhas de comentário e grava em arquivo.
		return 1;
	} else {
		if (*comment == 1) {
			// Conta as linhas de comentário.
			return 2;
		} else {
			if (*silent == 1) {
				// Grava em arquivo.
				return 3;
			} else {
				// Modo padrão.
				return 4;
			}
		}
	}	
}
