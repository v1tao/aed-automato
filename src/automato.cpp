#include <iostream>
#include <cstdlib>
#include <random>
#include <fstream>
#include <string>
#include "pvaa.h"
#include "conway_life.h"
#include "incendio.h"

//tamanho maximo da matriz
#define M 50
#define N 50
//estados
#define VAZIO 0
#define VEGETACAO 1
#define FOGO 2
#define AGUA 3

int main(int argc, char **argv)
{
	
	//variaveis principais
    int opcao;

    //loop principal para menu dos jogos
    do
    {
       	system("clear");	
       	azul();
    	printf("\t\t############################\n");
    	printf("----------------## \033[0;33m   AUTOMATO CELULAR\033[0m    \033[0;34m##----------------\n");
    	printf("\t\t############################\n\n");reset(); 
        printf("\033[0;34m|1|\033[0m \033[0;33mJogo da Vida (Conway Life)\033[0m\n\
\033[0;34m|2|\033[0m \033[0;33mSimulacao de Incendio\033[0m \n\
\033[0;34m|0|\033[0m \033[0;33mSair do programa\033[0m\n");
        amarelo();
        printf("\nDigite a operacao desejada: ");reset();
        scanf("%i", &opcao);
        estetica1();

            switch (opcao) {
                case 1:
                {
					menu_conway_life();
                    break;
                }
                case 2:
                {
                    printf("\033[0;34m--|\033[0m \033[0;33mSimulacao de Incendio selecionado |--\n");
					menu_incendio();                    
                    break;
                }
                
                case 0:
                {
                    printf("Desligando...\n");
                    break;
                }
                default:
                   printf("ERRO!! Opcao nao existente!\n");
            }
        }while (opcao != 0);


	return 0;
}
