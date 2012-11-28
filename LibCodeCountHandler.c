int optionsHandler(int argc, char *argv[]) {
	/*
	* Verifica quais par�metros foram passados e retorna o c�digo
	* correspondente a cada processo que dever� ser executado.
	* =======================================================================
	* Integer	comment		(0) Par�metro desligado. (1) Par�metro ligado
	* Integer	silent 		(0) Par�metro desligado. (1) Par�metro ligado
	* Integer	selected	Posi��o do par�metro corrente no FOR.
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
		// Conta as linhas de coment�rio e grava em arquivo.
		return 1;
	} else {
		if (*comment == 1) {
			// Conta as linhas de coment�rio.
			return 2;
		} else {
			if (*silent == 1) {
				// Grava em arquivo.
				return 3;
			} else {
				// Modo padr�o.
				return 4;
			}
		}
	}	
}
