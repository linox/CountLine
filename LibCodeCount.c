#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void CodeCount(char *file[], int mode) {
	//Guardará o número de Linhas.
	int lines = 0;
	
	//Guardará o número de Linhas Vazias.
	int emptyLines = 0;
	
	//Guardará o número de Linhas de comentário simples (//).
	int commentLines = 0;
	
	//Guardará o número de Linhas de comentário de Multiplas Linha [/*].
	int commentMultiLines = 0;
	
	//Guardará o número de caracteres que virão antes dos comentários.
	int countChar = 0;
	
	//Guardará o número de barras para  contar comentário simples(// = 2barras).
	int bar = 0;
	
	//Guardará o valor que o caracter representa na tabela ASCII. É ele que irá percorrer todo o arquivo.
	int ch = NULL;
	
	//Guardará o valor do caractere anterior (previous).
	int prev = NULL;
	
	//Guardará o valor do próximo caracter a ser buscado.
	int next = NULL;
	
	//Guardará o percentual de comentários.
	float percentComment = 0.0;

	//Determina se há valor(value) na linha corrente.	
	bool value = false;
	
	//isNotComment(Não é comentário) Determina se a linha corrente é comentário.
	bool isNotComment = false;
	
	//Quando é encontrado [/*] os comentários de Múltiplas linhas começam a ser computados até ser encontrado o seu final[*/].
	bool multiLines = false;
	
	//Determina se a linha corrente é commentário de linha Simples.
	bool commentOneLine = false;

	FILE *pFile;

	if (pFile = fopen(file[1], "r")) {
		do {
			ch = fgetc(pFile);
			//Quando não há nada no arquivo ou a linha está completamente vazia, existe o caracter "ÿ" no final.
			if (ch != '\n') {
			  if (ch == 'ÿ')
				 lines++;
			  
			//Valor [value] é passado para True, porque não é uma quebra de linha, ou seja, há algum valor nesta linha.
			value = true;

			if (ch == '/') {
				prev = ch;					
				if ((!isNotComment) && (!multiLines)) {
					bar++;
					if (bar >= 2)
						commentOneLine=true;
				}
				//Quando o número de barras chegar a 2, ele passa a ser comentário de linha simples, por isso, commentOneLine recebe true.
				//As barras só serão computadas quando a variável[Não é comentário] for falsa, e quando não for comentário de múltiplas linhas.
			} else {
				/*
				Se ch (a variável que está 'varrendo' todo o texto) não for igual 
				a \t ou [espaço], então ela tem outro valor[A-Z||0-9||Sí­mbolos] 
				então o [IsNotComment(Não é comentário)] se torna verdadeiro porque deixa de ser comentário
				*/
				isNotComment = ((ch != '\t') && (ch != ' ')) ? true : false;

				//Se multiLines for verdadeiro então começa a busca pelo seu final[*/]
				if (multiLines) {
					if (ch != '*') {
						prev = NULL;
						next = NULL;
					} else {
						next = ch;
					}
				} else {
					//Condição colocada apenas para mudar o valor de prev quando a letra que está sendo lida for dentre [A-Z||a-z].
					if (ch != '*')
						prev = NULL;	
					}
				}

				if (countChar >= 5)
					isNotComment = true;	
				
				/* 
				Se a soma das letras anteriores aos comentários for igual ou
				maior do que 5, não é comentário.
				Exemplo: 
					PRINTF [6 Letras]
					printf("blá blá blá"); //ESTE COMENTÁRIO NÃO SERÁ COMPUTADO.
					printf("// ESTE AQUI TAMBÉM NÃO");
				*/
				
				prev = (bar >= 2) ? NULL : prev; 

				/*
				A linha de cima é necessária para que um comentário Simples, 
				não seja contado como comentário de Múltipla linha.
				Exemplo: " // /*blá blá blá..." 
				*/
				if(((((prev == '/') && (ch == '*')) && (!multiLines)) || (((next == '*') && (ch == '/')) && (multiLines))) && (!commentOneLine)) {
					/*
					Para entrar neste IF: CommentOneLine(Comentário de uma linha) tem que ser false e...
					Prev tem que ser / e ch tem que ser * [/*]
					MultiLines tem que ser false.
					Se for isso ele entra e coloca o multilines em TRUE.

										ou
			
					MultiLines tem que ser TRUE
					Next tem que ser * e ch tem que ser / [* /]
			
					O IF que 'Liga' o Multiline é o mesmo que 'Desliga-o'
					*/
					
					multiLines = (!multiLines) ? true : false;
			
					if (multiLines)
						commentMultiLines++;				

					bar = 0;
				}
			} else {
				//Os comandos abaixo só serão executados quando for uma nova linha.[\n]
				
				lines++;
				
				if (multiLines) {
					/*
					Quando for um comentário de Múltiplas linhas, isNotComment recebe TRUE para
					que numa ocorrência, como a seguinte, ele não conte como comentário Simples. Para 
					ser comentário Simples isNotComment deve ser FALSE.
				
					Exemplo: " /* blá blá // blá blá ... "
					*/
					isNotComment = true;
					bar = 0;
					commentMultiLines++;
					
					if (!value)
						commentMultiLines--;
					
				} else {
					//Se não for comentário de Múltiplas Linhas isNotComment recebe FALSE normalmente.
					isNotComment = false;
				}
						
				countChar = 0;
			
				//Se o primeiro caracter da linha for [\n] então a linha é vazia.
				if (!value)
					emptyLines++;

				//value é setada FALSE pois a próxima linha pode não conter valor.
				value = false;

				//Contagem de comentários Simples.
				if ((commentOneLine) && (!isNotComment)) {
					commentLines++;
					bar = 0;
					commentOneLine=false;
				}
			}

			//Sempre executará os comandos abaixo. Pois estão fora do IF ELSE.
			//Quando é encontrado alguma letra antes do comentário o contador incrementa +1.
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
