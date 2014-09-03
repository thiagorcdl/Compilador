#define TKLEN 64

int in(char *item, char **lista){
	len = sizeof(lista)/sizeof(lista[0]);
	for (i=0; i < len; i++)
		if (!strcmp(item,lista[i]))
			return 1;
	return 0;
}

void lexico(){
	char token[TKLEN], prox, palavra[TKLEN];
	do prox = proximo();
	while (prox == ' ' || prox == '\n' || prox == '\t');
	if (in(prox,simbolos) ){
		strcpy(palavra,prox);
		prox = proximo();
		switch(palavra){
			case ':': if(proximo == '='){
					strcat(palavra,prox);
					prox = proximo();
				}
			case '.': if(proximo == '.'){
					strcat(palavra,prox);
					prox = proximo();
				}
			default : 
		}
		simbolo = codigo(palavra);
	} else if (in(prox,letras)){
		do {
			strcat(token,prox);
			prox = proximo();
		} while (in(prox,letras) || in(prox,digitos));
		if (in(token,keywords))
			simbolo = codigo(token);
		else
			simbolo = CODID; //codigo_de_identificador
	} else if (in(prox,digitos)){
		do {
			strcat(token,prox);
			prox = proximo();
		} while (in(prox,digitos));
		if (in(proximo,letras))
			erro(3);
		else 
			simbolo = CODNUM;
	}
	
}
