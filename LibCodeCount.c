#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void CodeCount(char *file[], int mode) {
	//Guardar� o n�mero de Linhas.
	int lines = 0;
	
	//Guardar� o n�mero de Linhas Vazias.
	int emptyLines = 0;
	
	//Guardar� o n�mero de Linhas de coment�rio simples (//).
	int commentLines = 0;
	
	//Guardar� o n�mero de Linhas de coment�rio de Multiplas Linha [/*].
	int commentMultiLines = 0;
	
	//Guardar� o n�mero de caracteres que vir�o antes dos coment�rios.
	int countChar = 0;
	
	//Guardar� o n�mero de barras para  contar coment�rio simples(// = 2barras).
	int bar = 0;
	
	//Guardar� o valor que o caracter representa na tabela ASCII. � ele que ir� percorrer todo o arquivo.
	int ch = NULL;
	
	//Guardar� o valor do caractere anterior (previous).
	int prev = NULL;
	
	//Guardar� o valor do pr�ximo caracter a ser buscado.
	int next = NULL;
	
	//Guardar� o percentual de coment�rios.
	float percentComment = 0.0;

	//Determina se h� valor(value) na linha corrente.	
	bool value = false;
	
	//isNotComment(N�o � coment�rio) Determina se a linha corrente � coment�rio.
	bool isNotComment = false;
	
	//Quando � encontrado [/*] os coment�rios de M�ltiplas linhas come�am a ser computados at� ser encontrado o seu final[*/].
	bool multiLines = false;
	
	//Determina se a linha corrente � comment�rio de linha Simples.
	bool commentOneLine = false;

	FILE *pFile;

	if (pFile = fopen(file[1], "r")) {
		do {
			ch = fgetc(pFile);
			//Quando n�o h� nada no arquivo ou a linha est� completamente vazia, existe o caracter "�" no final.
			if (ch != '\n') {
			  if (ch == '�')
				 lines++;
			  
			//Valor [value] � passado para True, porque n�o � uma quebra de linha, ou seja, h� algum valor nesta linha.
			value = true;

			if (ch == '/') {
				prev = ch;					
				if ((!isNotComment) && (!multiLines)) {
					bar++;
					if (bar >= 2)
						commentOneLine=true;
				}
				//Quando o n�mero de barras chegar a 2, ele passa a ser coment�rio de linha simples, por isso, commentOneLine recebe true.
				//As barras s� ser�o computadas quando a vari�vel[N�o � coment�rio] for falsa, e quando n�o for coment�rio de m�ltiplas linhas.
			} else {
				/*
				Se ch (a vari�vel que est� 'varrendo' todo o texto) n�o for igual 
				a \t ou [espa�o], ent�o ela tem outro valor[A-Z||0-9||S�mbolos] 
				ent�o o [IsNotComment(N�o � coment�rio)] se torna verdadeiro porque deixa de ser coment�rio
				*/
				isNotComment = ((ch != '\t') && (ch != ' ')) ? true : false;

				//Se multiLines for verdadeiro ent�o come�a a busca pelo seu final[*/]
				if (multiLines) {
					if (ch != '*') {
						prev = NULL;
						next = NULL;
					} else {
						next = ch;
					}
				} else {
					//Condi��o colocada apenas para mudar o valor de prev quando a letra que est� sendo lida for dentre [A-Z||a-z].
					if (ch != '*')
						prev = NULL;	
					}
				}

				if (countChar >= 5)
					isNotComment = true;	
				
				/* 
				Se a soma das letras anteriores aos coment�rios for igual ou
				maior do que 5, n�o � coment�rio.
				Exemplo: 
					PRINTF [6 Letras]
					printf("bl� bl� bl�"); //ESTE COMENT�RIO N�O SER� COMPUTADO.
					printf("// ESTE AQUI TAMB�M N�O");
				*/
				
				prev = (bar >= 2) ? NULL : prev; 

				/*
				A linha de cima � necess�ria para que um coment�rio Simples, 
				n�o seja contado como coment�rio de M�ltipla linha.
				Exemplo: " // /*bl� bl� bl�..." 
				*/
				if(((((prev == '/') && (ch == '*')) && (!multiLines)) || (((next == '*') && (ch == '/')) && (multiLines))) && (!commentOneLine)) {
					/*
					Para entrar neste IF: CommentOneLine(Coment�rio de uma linha) tem que ser false e...
					Prev tem que ser / e ch tem que ser * [/*]
					MultiLines tem que ser false.
					Se for isso ele entra e coloca o multilines em TRUE.

										ou
			
					MultiLines tem que ser TRUE
					Next tem que ser * e ch tem que ser / [* /]
			
					O IF que 'Liga' o Multiline � o mesmo que 'Desliga-o'
					*/
					
					multiLines = (!multiLines) ? true : false;
			
					if (multiLines)
						commentMultiLines++;				

					bar = 0;
				}
			} else {
				//Os comandos abaixo s� ser�o executados quando for uma nova linha.[\n]
				
				lines++;
				
				if (multiLines) {
					/*
					Quando for um coment�rio de M�ltiplas linhas, isNotComment recebe TRUE para
					que numa ocorr�ncia, como a seguinte, ele n�o conte como coment�rio Simples. Para 
					ser coment�rio Simples isNotComment deve ser FALSE.
				
					Exemplo: " /* bl� bl� // bl� bl� ... "
					*/
					isNotComment = true;
					bar = 0;
					commentMultiLines++;
					
					if (!value)
						commentMultiLines--;
					
				} else {
					//Se n�o for coment�rio de M�ltiplas Linhas isNotComment recebe FALSE normalmente.
					isNotComment = false;
				}
						
				countChar = 0;
			
				//Se o primeiro caracter da linha for [\n] ent�o a linha � vazia.
				if (!value)
					emptyLines++;

				//value � setada FALSE pois a pr�xima linha pode n�o conter valor.
				value = false;

				//Contagem de coment�rios Simples.
				if ((commentOneLine) && (!isNotComment)) {
					commentLines++;
					bar = 0;
					commentOneLine=false;
				}
			}

			//Sempre executar� os comandos abaixo. Pois est�o fora do IF ELSE.
			//Quando � encontrado alguma letra antes do coment�rio o contador incrementa +1.
			if (isNotComment == true)
				countChar++;			
			
		} while (ch != EOF);
  	
	  	fclose(pFile);
    
		if ((lines-emptyLines) == 0) {
			percentComment = 0;
		} else {
			percentComment = ((commentLines + commentMultiLines) * 100.0) / (lines - emptyLines);
		}
	  	
	  	CodeCountOutput(file, &lines, &emptyLines, &commentLines, &commentMultiLines, &percentComment, &mode);	  	
	} else {
		CodeCountError(file[0], "FILE_ERROR");
	}
}
