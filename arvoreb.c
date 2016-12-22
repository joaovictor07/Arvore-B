#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define linhas 4
/*
Sete a variável grauminimo na linha 15 com o grau mínimo que deseja
Nome do arquivo de entrada deve ser arqEntrada.dat e estar na pasta
*/
typedef struct {
	int numChaves;
	bool folha;
	int chave[7]; //chave[n]
	int indice[8]; //indice[n+1]
}NO;

const int grauminimo = 3;
FILE *fp;
int sizeNO = sizeof(NO);
int pos=0;
int cont=0;
int contador = 1;

void criarArvore(NO* raiz) {
	NO* x;
	x = (NO*)malloc(sizeof(NO));
	x->folha = true;
	x->numChaves = 0;
	fwrite(raiz,sizeNO,1,fp);
	raiz[0] = *x;
}

int busca(NO* no,int info) {
	//int i = 1;
	while (contador <= no->numChaves && info > no->chave[contador]) {
		contador = contador + 1;
	}
	if (contador <= no->numChaves && info == no->chave[contador]) {
		return(no->chave[contador]);
	}
	if (no->folha == true) {
		return -1;
	}
	else {
		fp = fopen("arqEntrada.dat","rb");
		if (fp == NULL) //se o arquivo binário estiver vazio sai da função
			exit(1);
		fseek(fp,cont*sizeNO,SEEK_SET);
		cont++;
		fread(no,sizeNO,1,fp);
		fclose(fp);
		return busca(&no[contador],info);
	}
}

int main () {
	NO* arv;
	NO* aux;
	NO* raiz;
	char buffer[256];
	raiz = (NO*)malloc(sizeof(NO));
	aux = (NO*)malloc(sizeof(NO));
	bool existe;
	int i,grauMin,ind,elemento,resp=0,elem;

	printf("Digite o grau mínimo da árvore:\n");
	scanf("%d",&grauMin);
	if (grauMin < 2 || grauMin > 4) {
		printf("Grau mínimo deve ser 2,3 ou 4\n");
		//main();
		return 0;
	}

	fp = fopen("arqEntrada.dat","rb");
		if (fp != NULL) {
			ind = 0;

			if (grauMin == 2) {
				arv = (NO*)malloc(linhas*sizeof(NO));
				for (i = 1; i <= linhas; i++) {
					if (arv != NULL) {
						fseek(fp,ind*sizeNO,SEEK_SET);
						fread(arv,linhas*sizeNO,1,fp);
						printf("%d %d %d %d %d\n",arv[i-1].numChaves,arv[i-1].folha,arv[i-1].chave[0],arv[i-1].indice[0],arv[i-1].indice[1]);
						//free(arv);
					}
					else
						printf("Erro alocando memória\n");
				}
			}

			if (grauMin == 3) {
				arv = (NO*)malloc(linhas*sizeof(NO));
				for (i = 1; i <= linhas; i++){	
					if (arv != NULL) {
						fseek(fp,ind*sizeNO,SEEK_SET);
						fread(arv,linhas*sizeNO,1,fp);
						printf("%d %d %d %d %d %d %d\n",arv[i-1].numChaves,arv[i-1].folha,arv[i-1].chave[0],arv[i-1].chave[1],arv[i-1].indice[0],arv[i-1].indice[1],arv[i-1].indice[2]);
						//free(arv);
					}
					else
						printf("Erro alocando memória\n");
				}
			}
			else if (grauMin == linhas) {
				for (i = 1; i <= linhas; i++) {
					arv = (NO*)malloc(linhas*sizeof(NO));
					if (arv != NULL) {
						fseek(fp,ind*sizeNO,SEEK_SET);
						fread(arv,linhas*sizeNO,1,fp);
						printf("%d %d %d %d %d %d %d %d %d\n",arv[i-1].numChaves,arv[i-1].folha,arv[i-1].chave[0],arv[i-1].chave[1],arv[i-1].chave[2],arv[i-1].indice[0],arv[i-1].indice[1],arv[i-1].indice[2],arv[i-1].indice[3]);
						//free(arv);
					}
					else
						printf("Erro alocando memória\n");
				}
			}
			else {
				printf("Erro\n");
			}
			
			fclose(fp);
		} else
			printf("Erro ao abrir arquivo\n");

	printf("Para realizar uma busca digite 1\n");
	scanf("%d",&resp);
	if (resp == 1 ) {
		fp = fopen("arqEntrada.dat","rb");
		fseek(fp,ind*sizeNO,SEEK_SET);
		//rewind(fp);
		fread(arv,sizeNO,1,fp);
		printf("Que elemento deseja buscar ?\n");
		scanf("%d",&elem);
		elemento = busca(arv,elem);
		if (elemento != -1)
			printf("%d\n",elemento);
	}
	return 0;
}
