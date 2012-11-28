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
	* Verifica se existem parâmetros repetidos e com a mesma quantidade de caracteres.
	* Exemplo: -c e -c, ou -comment e -commnent.
	* Se existir, apaga os repetidos e deixa apenas um.
	* ============================================================================================
	* Integer	selected	Posição do parâmetro corrente no FOR.
	* Integer	compare		Posição do parâmetro que deve ser comparado com o da posição selected.
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
	* Valida os parâmetros.
	* Se encontrar algum parâmetro inválido chama a função CodeCountError(),
	* passando como parâmetro o nome do programa e o parâmetro inválido para
	* que seja exibida uma mensagem de erro informando o usuário.
	* ======================================================================
	* Integer	selected	Posição do parâmetro corrente no FOR.
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
	* Verifica se existem parâmetros com os caracteres da posição 1 iguais.
	* Exemplo: -h e -help, ou -c e -comment.
	* Se existir, apaga os repetidos e deixa apenas um.
	* ===========================================================================================
	* Integer	selected	Posição do parâmetro corrente no FOR.
	* Integer	compare		Posição do parâmetro que deve ser comparado com o da posição selected.
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
