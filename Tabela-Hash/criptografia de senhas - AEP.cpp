#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef struct tipoUsuario
{
	char login[40];
	char numeroSus[40];
	char sal[20];
	char hash[40];
}TUsuario;


typedef struct tipoUsuarioLogin
{
	char login[40];
	char senha[20];
}TUsuarioLogin;


typedef struct tipoElemento
{
	char caracter;
	struct tipoElemento *proximo;
}TElemento;


typedef struct tipoLista
{
	TElemento *inicio;
	TElemento *fim;
}TLista;


TLista tabelaHashing[10];
TUsuario usuario;

void inicializar ()
{
	int i;
	for (i= 0; i < 10; i++)
	{
		tabelaHashing[i].inicio = NULL;
		tabelaHashing[i].fim = NULL;
	}
}

int hash (int valor)
{
	return valor % 10;
}

void cadastrar()
{
	printf("\n Informe o login: ");
	fflush(stdin);
	gets(usuario.login);
	
	strcpy(usuario.sal, "SQ#)46FlC&bq");
	
	char senhaCadastro[40];
	
	printf("\n Informe a senha:");
	fflush(stdin);
	gets(senhaCadastro);
	
	strcat(senhaCadastro, usuario.sal);
	
	printf("\n Informe o numero do cartao SUS: ");
	fflush(stdin);
	gets(usuario.numeroSus);
	
	
	
	int i, indice;
	
	for (i = 0; i < strlen(senhaCadastro); i++)
	{
		TElemento *novoCaracter;
		novoCaracter = new TElemento;
		
		novoCaracter->caracter = senhaCadastro[i];
		novoCaracter->proximo = NULL;
		
		indice = hash(senhaCadastro[i]);
		
		if (tabelaHashing[indice].inicio == NULL)
		{
			tabelaHashing[indice].inicio = novoCaracter;
			tabelaHashing[indice].fim = novoCaracter;
		}
		else
		{
			tabelaHashing[indice].fim->proximo = novoCaracter;
			tabelaHashing[indice].fim = novoCaracter;
		}
	}
	
	int j = 0;
	
	for (i = 0; i < 10; i++)
	{
		TElemento *aux;
		aux = tabelaHashing[i].inicio; 
		while (aux != NULL)
		{
			usuario.hash[j] = aux->caracter;
			j++;
			aux = aux->proximo;
		}
	}
	usuario.hash[j] = '\0';
}


void apresentar()
{
	int i;
	
	for(i = 0; i<10; i++) 
	{
		TElemento *aux;
		aux = tabelaHashing[i].inicio;
		if (aux != NULL)
		{
			printf("\n Indice: %d - ", i);
			while (aux != NULL) 
			{
				printf("%c | ", aux->caracter);
				aux = aux->proximo;
			}
		}
		else
		{
			printf("\n Indice: %d  - / ", i);
		}
	}
	printf("\n Senha criptografada: %s", usuario.hash);	
}

void validarSenha(TUsuarioLogin usuarioLogin)
{
	strcat(usuarioLogin.senha, "SQ#)46FlC&bq");
	
	inicializar();
	int i, indice;
	
	for (i = 0; i < strlen(usuarioLogin.senha); i++)
	{
		TElemento *novoCaracter;
		novoCaracter = new TElemento;
		
		novoCaracter->caracter = usuarioLogin.senha[i];
		novoCaracter->proximo = NULL;
		
		indice = hash(usuarioLogin.senha[i]);
		
		if (tabelaHashing[indice].inicio == NULL)
		{
			tabelaHashing[indice].inicio = novoCaracter;
			tabelaHashing[indice].fim = novoCaracter;
		}
		else
		{
			tabelaHashing[indice].fim->proximo = novoCaracter;
			tabelaHashing[indice].fim = novoCaracter;
		}
	}

	int j = 0;
	
	char hashLogin[40];
	
	for (i = 0; i < 10; i++)
	{
		TElemento *aux;
		aux = tabelaHashing[i].inicio;
		while (aux != NULL)
		{
			hashLogin[j] = aux->caracter;
			j++;
			aux = aux->proximo;
		}
	}
	hashLogin[j] = '\0';

	if (strcmp(hashLogin, usuario.hash) == 0)
	{
		printf("\n USUARIO AUTENTICADO COM SUCESSO");
	}
	else
	{
		printf("\n SENHA INVALIDA TENTE NOVAMENTE");
	}	
	getch();	
}

void fazerLogin()
{
	TUsuarioLogin usuarioLogin;
	
	printf("\n Informe o login: ");
	fflush(stdin);
	gets(usuarioLogin.login);
		
	printf("\n Informe senha: ");
	fflush(stdin);
	gets(usuarioLogin.senha);
	
	validarSenha(usuarioLogin);
}

void apresentarDados()
{
	printf("\n Usuario: %s", usuario.login);
	printf("\n Numero do cartao SUS: %s", usuario.numeroSus);	
}


int main(void)
{
	int opcao;
	
	do
	{
		printf("\n\n 1 - Cadastrar usuario");
		printf("\n 2 - Logar no sistema");
		printf("\n 3 - Hash com senha criptografada");
		printf("\n 4 - Dados do usuario");
		printf("\n 0 - Sair");
		printf("\n Escolha uma opcao: ");
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1: cadastrar(); break;
			case 2: fazerLogin(); break;
			case 3: apresentar(); break;
			case 4: apresentarDados();break;
		}
	} while (opcao != 0);
}
