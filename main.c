/* 
 Trabalho final - ALGORITMOS E PROGRAMAÇÃO(2012/02)
 Autor: Matheus Henrique Trichez - 2012/01 - UFFS
 Email: mh.trichez@gmail.com
 
 
 obs: compilar e rodar pelo terminal para que a mariz seja bem desenhada.
 */
#include <stdlib.h>
#include <stdio.h>
#include "funcoes_t3.h"
#define MAX_PLAYERS 4				//numero maximo de jogadores 
#define START_MONEY 100				//ouro inicial do jogador
#define START_LIFE 3				//vida inicial do jogador
#define START_CONTROLE 0			//variavel de controle para prender ou libertatr jogador (se for 1 o jogador esta preso, se 2 o jogador ja chegou ao fim, 3 esta morto)
#define START_POSICION 0			//posicao inicial dos jogadores
#define MAX_NAME 50					//tamanho maximo do nome de cada jogador


int main (){
	player_t jogador[MAX_PLAYERS];
	int Nnumero_jogadores, i, recursiva;
	recursiva=-1;
	Nnumero_jogadores=0;
	
	for(i=0;i<MAX_PLAYERS;i++){											//atribui vida e dinheiro inicial aos jogadores(constantes linha 7-10)
		jogador[i].bag=START_MONEY;
		jogador[i].life=START_LIFE;
		jogador[i].controle=START_CONTROLE;
		jogador[i].posicao=START_POSICION;
	}	
	
	printf("\n\n\nDigite o numero de jogadores que vao jogar (minimo 2, maximo 4): ");
	do{																	//nao segue o programa enquanto nao entrar com o numero correto de jogadores, 2~4 
		scanf("%d", &Nnumero_jogadores);
	}while(Nnumero_jogadores < 2 || Nnumero_jogadores > 4);
	for(i=0;i<Nnumero_jogadores;i++){									//pega o nome dos jogadores
		printf("Entre com o nome do jogador de numero %d: ", i+1);
		scanf("%s", jogador[i].nome);
	}
	while(jogo_acabou(jogador, Nnumero_jogadores)==0){ 					//este laço chama a funcao 'turno' que simula uma rodada, a cada vez que um jogador chega ao final ou morre a variavel 'final' é incrementada. quando ela for igual ao numero de jogadores que estao jogando o jogo acaba
		turno(jogador, Nnumero_jogadores, recursiva);
	}
	printf("\n\t\t\t--FIM DE JOGO--");
	for(i=0;i<Nnumero_jogadores;i++){                                   //cada vida vale 100 ouro
		if(jogador[i].life>0){
			jogador[i].bag+=jogador[i].life*100;
		}
	}
	int Maior_jogador=0;
	for(i=0;i<(Nnumero_jogadores-1);i++){                               //ganhador
		if(jogador[i].bag > jogador[i+1].bag && jogador[i].life>0){
			Maior_jogador=i+1;
		}else{
			Maior_jogador=i;
		}
	}
	printf("\nQuem ganhou foi o jogador: %s, com: %d ouros. Parabens!\n\n", jogador[i].nome, jogador[i].bag);
	return 0;
}
