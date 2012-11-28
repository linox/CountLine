void ValidRunCmd(int argc, char *program[]) {
	//Verifica se foi informado nome/caminho do arquivo.
	if (argc < 2) {
		CodeCountError(program[0], "RUN_INIT");
	} else {
		if ((argc == 2) && (strcmp(program[1],"-h")==0 || strcmp(program[1],"-help")==0)) {
			ShowHelp();
		} else {
			if (argc > 2) {
				ValidArgs(argc, program);
			}
		}
	}
}

void ValidRepeatedArgs(int numArgs, char *args[]) {
	/*
	* Verifica se existem par�metros repetidos e com a mesma quantidade de caracteres.
	* Exemplo: -c e -c, ou -comment e -commnent.
	* Se existir, apaga os repetidos e deixa apenas um.
	* ============================================================================================
	* Integer	selected	Posi��o do par�metro corrente no FOR.
	* Integer	compare		Posi��o do par�metro que deve ser comparado com o da posi��o selected.
	*/
	
	int selected, compare=0;
	
	for (selected = 2; selected < numArgs; selected++) {
		for (compare = 2; compare < numArgs; compare++) {
			if ((selected != compare) && (strcmp(args[selected], args[compare]) == 0)) {
				strcpy(args[compare],"..");
			}
		}
	}
}

void ValidArgs(int argc, char *argv[]) {
	/*
	* Valida os par�metros.
	* Se encontrar algum par�metro inv�lido chama a fun��o CodeCountError(),
	* passando como par�metro o nome do programa e o par�metro inv�lido para
	* que seja exibida uma mensagem de erro informando o usu�rio.
	* ======================================================================
	* Integer	selected	Posi��o do par�metro corrente no FOR.
	*/
	
	int selected;
	
	for (selected = 2; selected < argc; selected++) {
		if (strlen(argv[selected]) <= 2) {
			if ((strcmp(argv[selected],"-c")!=0) && (strcmp(argv[selected],"-h")!=0) && (strcmp(argv[selected],"-s")!=0) && (strcmp(argv[selected],".."))!=0) {
				CodeCountError(argv[0], argv[selected]);
			}
		} else {
			if (strlen(argv[selected]) > 2) {
				if ((strcmp(argv[selected],"-comment")!=0) && (strcmp(argv[selected],"-help")!=0) && (strcmp(argv[selected],"-silent")!=0)) {
					CodeCountError(argv[0], argv[selected]);
				}
			} else {
				CodeCountError(argv[0], argv[selected]);
			}
		}
	}
}

void FixEqualsArgs(int argc, char *argv[]) {
	/*
	* Verifica se existem par�metros com os caracteres da posi��o 1 iguais.
	* Exemplo: -h e -help, ou -c e -comment.
	* Se existir, apaga os repetidos e deixa apenas um.
	* ===========================================================================================
	* Integer	selected	Posi��o do par�metro corrente no FOR.
	* Integer	compare		Posi��o do par�metro que deve ser comparado com o da posi��o selected.
	*/
	int selected, compare=0;
		
	for (selected = 2; selected < argc; selected++) {
		for (compare = 2; compare<argc; compare++) {
			if ((selected != compare) && (argv[selected][1] == argv[compare][1])) {
				strcpy(argv[compare]," ");
			}
		}
	}
}
