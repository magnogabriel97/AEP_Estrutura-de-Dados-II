#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoPaciente
{
	int cartaoSUS;
	char nome[35];
	char dataNasc[10];
	
}TPaciente;

typedef struct tipoNo
{
	TPaciente paciente;
	struct tipoNo *esq, *dir;
}TNo;

void inserirNaoRecursivo (TNo *&raiz, TPaciente *paciente)
{
	TNo *novoNo;
	novoNo = new TNo;
	novoNo->paciente.cartaoSUS = paciente->cartaoSUS;
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	
	if (raiz == NULL)
	{
		raiz = novoNo;
	}
	else
	{
		TNo *aux;
		aux = raiz;
		int inseriu = 0;
		
		while (inseriu == 0)
		{
			if (novoNo->paciente.cartaoSUS < aux->paciente.cartaoSUS)
			{
				if (aux->esq == NULL)
				{
					aux->esq = novoNo;
					inseriu = 1;		
				}
				else
				{
					aux = aux->esq;
				}
			}
			else
			{
				if (aux->dir == NULL)
				{
					aux->dir = novoNo;
					inseriu = 1;
				}
				else
				{
					aux = aux->dir;
				}
			}
		}
	}	
}

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
		printf ("\n Numero Cartao SUS: %d \n Nome Paciente: %s \n Data Nascimento: %s\n", raiz->paciente.cartaoSUS, raiz->paciente.nome, raiz->paciente.dataNasc);
		emOrdem (raiz->dir);
	}
}

void posOrdem(TNo *raiz)
{
	if (raiz != NULL)
	{		
		posOrdem (raiz->esq);		
		posOrdem (raiz->dir);
		printf ("\n Numero Cartao SUS: %d \n Nome Paciente: %s \n Data Nascimento: %s\n", raiz->paciente.cartaoSUS, raiz->paciente.nome, raiz->paciente.dataNasc);

	}
}

void apresentarMenorcartaoSUS(TNo *raiz)
{
	TNo *aux;
	aux = raiz;
    while (aux->esq != NULL)
    {
        aux = aux->esq;
    }
    printf ("\n O Menor Cartao SUS e: %d", aux->paciente.cartaoSUS);
}

void apresentarMaiorcartaoSUS(TNo *raiz)
{
	TNo *aux;
	aux = raiz;
    while (aux->dir != NULL)
    {
        aux = aux->dir;
    }
    printf("\n O Maior Cartao SUS e: %d", aux->paciente.cartaoSUS);
}

int consultarNaoRecursivo (TNo *auxRaiz, int auxcartaoSUS)
{
	while ((auxRaiz != NULL) && (auxRaiz->paciente.cartaoSUS != auxcartaoSUS))
	{
		if (auxcartaoSUS < auxRaiz->paciente.cartaoSUS)
		{
			auxRaiz = auxRaiz->esq;
		}
		else
		{
			auxRaiz = auxRaiz->dir;
		}
	}
	if (auxRaiz->paciente.cartaoSUS == auxcartaoSUS)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int consultarRecursivo (TNo *auxRaiz, int auxcartaoSUS)
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
				return consultarRecursivo (auxRaiz->esq, auxcartaoSUS);
			}
			else
			{
				return consultarRecursivo (auxRaiz->dir, auxcartaoSUS);
			}
		}
	}
}

int sobeMaiorDireita (TNo *aux)
{
	while (aux->dir != NULL) // busca enquanto o lado direito for diferente de nulo
	{
		aux = aux->dir;
	}
	return (aux->paciente.cartaoSUS);  // retorna o cartaoSUS 
}

TNo* remover (TNo *raiz, int auxcartaoSUS) // fun��o remover
{
	if (raiz == NULL)  // verifica��o se tem paciente na raiz
	{
		printf("\n Cartao SUS nao encontrado!");
	}
	else  // busca por deslocamento do cartaoSUS
	{
		if (auxcartaoSUS < raiz->paciente.cartaoSUS)  //  verificar se o cartaoSUS � menor que o cartaoSUS da raiz
		{
			raiz->esq = remover (raiz->esq, auxcartaoSUS);
		}
		else
		{
			if (auxcartaoSUS > raiz->paciente.cartaoSUS)  // verificar se o cartaoSUS � maior que o cartaoSUS da raiz
			{
				raiz->dir = remover (raiz->dir, auxcartaoSUS);
			}
			else //encontrei o cartaoSUS
			{
				//se o paciente n�o tiver sub-�rvore direita
				{
					if (raiz->dir == NULL) //  verifica se o lado direito do ponteiro raiz � nulo e apaga o cartaoSUS
					{
						TNo *aux;
						aux = raiz;
						raiz = raiz->esq;
						free(aux);
					}
					else  // se o paciente n�o tiver sub-�rvore esquerda
					{
						if (raiz->esq == NULL)  // verifica se o lado direito do ponteiro raiz � nulo e apaga o cartaoSUS
						{
							TNo *aux;
							aux = raiz;
							raiz = raiz->dir;
							free(aux);
						}
						else //n� possui 2 sub-�rvores
						{
							raiz->paciente.cartaoSUS = sobeMaiorDireita (raiz->esq);  //  chama a fun��o
							raiz->esq = remover (raiz->esq, raiz->paciente.cartaoSUS); // exclui o cartaoSUS
						}
					}
				}
			}
		}
	}
	return raiz;  //  retorna raiz
}

TNo* removerNaoRecursivo (TNo *raiz, int auxcartaoSUS)
{
	TNo *atual, *anterior;	
	atual = raiz;
	anterior = raiz;
	
	while (atual != NULL)
	{
		if (atual->paciente.cartaoSUS == auxcartaoSUS)
		{
			if ((atual->esq == NULL) && (atual->dir == NULL)) // s� um paciente na �rvore
			{
				raiz = NULL;
				break;
			}
			else
			{			
				if (atual->paciente.cartaoSUS > anterior->paciente.cartaoSUS)
				{			
					if (atual->dir == NULL)
					{
						anterior->dir = anterior->esq;
						break;
					}
					else
					{
						if (atual->esq == NULL)
						{
							anterior->dir = atual->dir;
							break;
						}
					}
				}
				else
				{
					if (atual->paciente.cartaoSUS < anterior->paciente.cartaoSUS)
					{
						if (atual->dir == NULL)
						{
							anterior->esq = atual->esq;
							break;
						}
						else
						{
							if (atual->esq == NULL)
							{
								anterior->esq = atual->dir;
							}
						}
					}
				}
			}
		}
		else
		{
			if (auxcartaoSUS < atual->paciente.cartaoSUS)
			{
				anterior = atual;
				atual = atual->esq;
			}
			else
			{
				if (auxcartaoSUS > atual->paciente.cartaoSUS)
				{
					anterior = atual;
					atual = atual->dir;
				}
			}
		}
	}
	if (atual == NULL)
	{
		printf ("\n Cartao SUS nao foi encontrado");
	}
	else
	{
		free (atual);
	}	
	return raiz;
}

int main()
{
	TNo *raiz;
	raiz = NULL; // inicializa��o da raiz da �rvore
	
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
		printf ("\n  5 - Inserir nao recursivo");
		printf ("\n  6 - Apresentar menor Cartao SUS");
		printf ("\n  7 - Apresentar maior Cartao SUS");
		printf ("\n  8 - Consultar Cartao SUS - nao recurssivo");
		printf ("\n  9 - Consultar Cartao SUS - recurssivo");
		printf ("\n 10 - Excluir Cartao SUS da arvore");
		printf ("\n 11 - Excluir nao recursivo Cartao SUS da arvore");
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
				lerDados (&paciente);
				inserirNaoRecursivo (raiz, &paciente); break;
			}
			case 6:
			{				
				apresentarMenorcartaoSUS (raiz); break;
			}
			case 7:
			{
				apresentarMaiorcartaoSUS (raiz); break;
			}
			case 8:
			{
				int auxcartaoSUS, encontrou;
				printf ("\n Informe cartaoSUS a ser consultado: ");
				scanf ("%d", &auxcartaoSUS);
				encontrou = consultarNaoRecursivo (raiz, auxcartaoSUS);
				if (encontrou == 1)
				{
					printf ("\n cartaoSUS encontrado");
				}
				else
				{
					printf ("\n cartaoSUS nao encontrado");
				}
				getch();
				break;
			}
			case 9:
			{
				int auxcartaoSUS, encontrou;
				printf ("\n Informe cartaoSUS a ser consultado: ");
				scanf ("%d", &auxcartaoSUS);
				encontrou = consultarRecursivo (raiz, auxcartaoSUS);
				if (encontrou == 1)
				{
					printf ("\n cartaoSUS encontrado");
				}
				else
				{
					printf ("\n cartaoSUS nao encontrado");
				}
				getch();
				break;
			}
			case 10:
			{
				int auxcartaoSUS;
				printf("\n Informe cartaoSUS para ser excluido");
				scanf("%d", &auxcartaoSUS);
				raiz = remover (raiz, auxcartaoSUS);
			}
			case 11:
			{
				int auxcartaoSUS;
				printf("\n Informe cartaoSUS para ser excluido");
				scanf("%d", &auxcartaoSUS);
				raiz = removerNaoRecursivo (raiz, auxcartaoSUS);		
			}
		}
	}while (opcao != 0);	
}



