#include "LibCodeCount.h"
#include <stdbool.h>

main(int argc, char *argv[]) {
	ValidRunCmd(argc, argv);
	ValidRepeatedArgs(argc, argv);
	ValidArgs(argc, argv);
	FixEqualsArgs(argc, argv);

	switch (optionsHandler(argc, argv)) {
		case 1: CodeCount(argv, 1); break; //Comment e Silent (Conta também as linhas de comentário e grava em arquivo).
		case 2: CodeCount(argv, 2); break; //Comment (Conta também as linhas de comentário).
		case 3: CodeCount(argv, 3); break; //Silent (grava em arquivo com modo padrão).
		default: CodeCount(argv, 0);       //Modo padrão.
	}
}
