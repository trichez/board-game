#ifndef _FUNCOES_T3_H_
#define _FUNCOES_T3_H
#define MAX_NAME 50					// tamanho maximo do nome de cada jogador 
#define MAX_PLAYERS 4				//numero maximo de jogadores
#define L_MATRIZ 21					//numero de linhas da matriz
#define C_MATRIZ 21					//numero de colunas da matriz
typedef struct{
	int posicao;
	int controle;
	int bag;
	int life;
	char nome[MAX_NAME];
}player_t;
void verifica_posicao(player_t vet[MAX_PLAYERS], int N_jogadores);		// nao deixa que dois jogadores ocupem a mesma posicao, o jogador que chegou dps é colocado uam posicao antes
int jogo_acabou(player_t vet[MAX_PLAYERS], int N_jogadores);			//verifica se o jogo acabou, ou seja, se todos os jogadores morreram ou chegaram ao fim
int dado();																//retorna um interio de 1-6
void turno(player_t vet[MAX_PLAYERS], int N_jogadores, int recursividade);//simula a rodada 
void desenha_tabuleiro(int N_jogadores, int Nmatriz[L_MATRIZ][C_MATRIZ], player_t vet[MAX_PLAYERS]);//desenha a matriz na tela
int acao();																//retorna um nomero de 0 a 19 que sera o numero correspondente a uma ação la no switch da main
#endif
