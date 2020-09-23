#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoPaciente
{
	int cartaoSUS;
	char nome[35];
	char dataNasc[15];
	
}TPaciente;

typedef struct tipoNo
{
	TPaciente paciente;
	struct tipoNo *esq, *dir;
}TNo;

TNo* inserir (TNo *raiz, TPaciente *paciente)
{
	if (raiz == NULL)
	{
		
		
		raiz = new TNo;
		raiz->paciente.cartaoSUS = paciente->cartaoSUS;
		strcpy(raiz->paciente.nome , paciente->nome);
		strcpy(raiz->paciente.dataNasc, paciente->dataNasc);
		raiz->esq = NULL;
		raiz->dir = NULL;
	}
	else
	{
		if (paciente->cartaoSUS < raiz->paciente.cartaoSUS)
		{
			raiz->esq = inserir (raiz->esq, paciente);
		}
		else
		{
			raiz->dir = inserir (raiz->dir, paciente);
		}		
	}
	return raiz;
	
	
}

void lerDados(TPaciente *paciente)
{	
	fflush(stdin);
	printf ("\n Informe numero cartaoSUS do paciente: ");
	scanf ("%d", &paciente->cartaoSUS);
	fflush(stdin);
	printf ("\n Informe nome do paciente: ");
	gets ( paciente->nome);
	fflush(stdin);
	printf ("\n Informe data de nascimento do paciente (DD/MM/AAAA): ");
	gets (paciente->dataNasc);
}

void preOrdem(TNo *raiz)
{	
	if (raiz != NULL)
	{		
		
		printf ("\n Numero Cartao SUS: %d ", raiz->paciente.cartaoSUS);
		printf ("\n Nome Paciente: %s ",raiz->paciente.nome);
		printf ("\n Data Nascimento: %s\n",  raiz->paciente.dataNasc);
		preOrdem (raiz->esq);
		preOrdem (raiz->dir);
	}
}

void emOrdem(TNo *raiz)
{
	if (raiz != NULL)
	{		
		emOrdem (raiz->esq);
		printf ("\n Numero Cartao SUS: %d ", raiz->paciente.cartaoSUS);
		printf ("\n Nome Paciente: %s ",raiz->paciente.nome);
		printf ("\n Data Nascimento: %s\n",  raiz->paciente.dataNasc);
		emOrdem (raiz->dir);
	}
}

void posOrdem(TNo *raiz)
{
	if (raiz != NULL)
	{		
		posOrdem (raiz->esq);		
		posOrdem (raiz->dir);
		printf ("\n Numero Cartao SUS: %d ", raiz->paciente.cartaoSUS);
		printf ("\n Nome Paciente: %s ",raiz->paciente.nome);
		printf ("\n Data Nascimento: %s\n",  raiz->paciente.dataNasc);
	}
}

int consultar (TNo *auxRaiz, int auxcartaoSUS)
{
	if (auxRaiz == NULL)
	{
		return 0;
	}
	else
	{
		if (auxRaiz->paciente.cartaoSUS == auxcartaoSUS)
		{
			return 1;
		}
		else
		{
			if (auxcartaoSUS < auxRaiz->paciente.cartaoSUS)
			{
				return consultar (auxRaiz->esq, auxcartaoSUS);
			}
			else
			{
				return consultar (auxRaiz->dir, auxcartaoSUS);
			}
		}
	}
}

int sobeMaiorDireita (TNo *aux)
{
	while (aux->dir != NULL) 
	{
		aux = aux->dir;
	}
	return (aux->paciente.cartaoSUS);   
}

TNo* remover (TNo *raiz, int auxcartaoSUS) 
{
	if (raiz == NULL) 
	{
		printf("\n Cartao SUS nao encontrado!\n");
	}
	else  
	{
		if (auxcartaoSUS < raiz->paciente.cartaoSUS)  
		{
			raiz->esq = remover (raiz->esq, auxcartaoSUS);
		}
		else
		{
			if (auxcartaoSUS > raiz->paciente.cartaoSUS) 
			{
				raiz->dir = remover (raiz->dir, auxcartaoSUS);
			}
			else 
			{				
				{
					if (raiz->dir == NULL) 
					{
						TNo *aux;
						aux = raiz;
						raiz = raiz->esq;
						free(aux);
					}
					else  
					{
						if (raiz->esq == NULL) 
						{
							TNo *aux;
							aux = raiz;
							raiz = raiz->dir;
							free(aux);
						}
						else
						{
							raiz->paciente.cartaoSUS = sobeMaiorDireita (raiz->esq);  
							raiz->esq = remover (raiz->esq, raiz->paciente.cartaoSUS); 
						}
					}
				}
			}
		}
	}
	return raiz;  
}

int main()
{
	TNo *raiz;
	raiz = NULL;
	
	TPaciente paciente;
	
	int opcao;
	
	do
	{
		printf ("\n --------------- M E N U ---------------");
		printf ("\n ");
		printf ("\n  1 - Inserir dados paciente na arvore");
		printf ("\n  2 - Apresentar pre-ordem");
		printf ("\n  3 - Apresentar em-ordem");
		printf ("\n  4 - Apresentar pos-ordem");
		printf ("\n  5 - Consultar Cartao SUS");
		printf ("\n  6 - Excluir Cartao SUS da arvore");
		printf ("\n  0 - Sair");
		printf ("\n ");
		printf ("\n ---------------------------------------");	
		printf ("\n Escolha uma opcao: ");		
		scanf ("%d",&opcao);		
		printf ("\n\n ");
		
		switch (opcao)
		{
			case 1:
			{
				lerDados (&paciente);
				raiz = inserir (raiz, &paciente); break;
			}
			case 2: preOrdem (raiz); break;
			case 3: emOrdem (raiz); break;
			case 4: posOrdem (raiz); break;
			case 5:
			{
				int auxcartaoSUS, encontrou;
				printf ("\n Informe cartao SUS a ser consultado: ");
				scanf ("%d", &auxcartaoSUS);
				encontrou = consultar (raiz, auxcartaoSUS);
				if (encontrou == 1)
				{
					printf ("\n Cartao SUS encontrado!\n");
				}
				else
				{
					printf ("\n Cartao SUS nao encontrado!\n");
				}
				getch();
				break;
			}
			case 6:
			{
				int auxcartaoSUS;
				printf("\n Informe Cartao SUS para ser excluido: ");
				scanf("%d", &auxcartaoSUS);
				raiz = remover (raiz, auxcartaoSUS);
			}
		}
	}while (opcao != 0);	
}



