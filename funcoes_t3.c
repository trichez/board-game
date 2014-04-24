#include "funcoes_t3.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_ACAO 20					//divide o retorno da função rand() e o resto da divisao varia de 0 a 19 o que simula as açoes
#define MAX_DADO 7					//divide o retorno da função rand() e o resto da divisao varia de 1(1 por causa do laço) a 6 o que simula o dado
//#define TIME_SLEEP 1				//constante que define quantos por segundos o programa ficara parado pela funcao sleep() 
#define L_MATRIZ 21					//numero de linhas da matriz
#define C_MATRIZ 21					//numero de colunas da matriz
#define MAX_PLAYERS 4				//numero maximo de jogadores

void desenha_tabuleiro(int N_jogadores, int Nmatriz[L_MATRIZ][C_MATRIZ], player_t vet[MAX_PLAYERS]){
		int controle_desenho, i, j, n;
		printf("--------------------------------------------------------------\n");
		for(i=0;i<L_MATRIZ;i++){										//desenha o tabuleiro na tela
			printf("\n");																
			for(j=0;j<C_MATRIZ;j++){																				
				controle_desenho=0;											
				for(n=0;n<N_jogadores;n++){				
					if(Nmatriz[i][j]!=-999 && Nmatriz[i][j]==vet[n].posicao){//enquanto desenha verifica se a variavel 'posicao' do jogador é igual  ao valor que existe naquele espaço de memoria, se sim o numero do jogador é colocado na tela(desde que o jogador nao esteja na posicao '0')
						printf("%d", n+1);							
						controle_desenho=1;								//quando uma posicao for desenhada com o numero de um jogador essa variavel evitara(no proximo 'if()'), que essa posicao seja desenhada denovo
						break;
					}
				}
				if(Nmatriz[i][j]!=-999 && controle_desenho==0){
					printf("{}");
				}else if(Nmatriz[i][j]==-999 && controle_desenho==0){
					printf("  ");
				}	
			}
		}
		printf("\n--------------------------------------------------------------\n");
}
int jogo_acabou(player_t vet[MAX_PLAYERS], int N_jogadores){
	int test=0, x;
	
	for(x=0;x<N_jogadores;x++){
		if(vet[x].posicao>=39 ||vet[x].life<=0){						// veririfica se o jogador da vez ja chegou ao fim ou morreu
			vet[x].posicao*=2;
			vet[x].life=-1000;					 
			test++;														// evita que seja feito mais de uma vez o calculo do bonus pela vida extra
		}
	}
	if(test==N_jogadores){
		return 1;
	}else{
		return 0;
	}
}
void verifica_posicao(player_t vet[MAX_PLAYERS], int N_jogadores){
	int i,j;
	for(i=0;i<N_jogadores;i++){										//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
		for(j=0;j<N_jogadores;j++){
			if(vet[i].posicao==vet[i+1].posicao && i!=j && i!=0){
				vet[i].posicao--;
			}
		}
	}
}
int acao(){
	int Ndado;
	Ndado=0;
	srand(time(NULL));
	Ndado=rand()%MAX_ACAO;	
	return Ndado;
}
int dado(){
	int Ndado;
	Ndado=0;
	srand(time(NULL));
	do {
		Ndado=rand()%MAX_DADO;
	}while(Ndado==0);	
	return Ndado;
}
void turno(player_t vet[MAX_PLAYERS], int N_jogadores, int recursividade){
	int Ndado, x, j, indice=0, i;
	char Sdado[]="dado";
	char entrada[MAX_NAME];
	int Nmatriz[L_MATRIZ][C_MATRIZ];
	
	for(i=0;i<L_MATRIZ;i++){											//ordena alguns indices da matriz de 0-39 no formato do tabuleiro
		for(j=0;j<C_MATRIZ;j++){
			if( (i==0 && j<(C_MATRIZ/2))     ||      ((i<=(L_MATRIZ/2)-1)  &&  j==(C_MATRIZ/2))    ||    (i==((L_MATRIZ/2)-1) && j>=(C_MATRIZ/2))    ||  (i>=((L_MATRIZ/2)-1) && j==(C_MATRIZ-1)) ){				
				Nmatriz[i][j]=indice;
				indice++;
			}else{
				Nmatriz[i][j]=-999;
			}
		}	
	}	
	for(x=0;x<N_jogadores;x++){											// aqui começa um laço com a variavel 'x' que vai correr o vetor de strutcs (players)
		if(recursividade!=-1){											//quando o jogador acha o diamante (case 8) vai usar recursividade, passando como parametro o numero do jogador que esta jogando atualmente que ira variar de 0~4; 
			x=recursividade;
		}
		if(jogo_acabou(vet, N_jogadores)==1){
			break;
		}
		if(vet[x].controle==1){
				printf("\n\t---Jogador %d voce esta preso e nao jogara esta rodada---", x+1);
				vet[x].controle=0;
				continue;
			}		
		if(vet[x].posicao>=39){											// veririfica se o jogador da vez ja chegou ao fim
				if(vet[x].controle==2){										// evita que seja feito mais de uma vez o calculo do bonus pela vida extra
					continue;
				}else{
					vet[x].controle=2;
					vet[x].posicao*=2;
					continue;
				}
			}
			if(vet[x].life<=0){												// veririfica se o jogador da vez 'morreu'
				if(vet[x].controle==3){										// evita que seja feito mais de uma vez o calculo do bonus pela vida extra
					continue;
				}else{
					vet[x].controle=3;
					continue;
				}
			}		
		do{																//jogando o dado
			printf("\n  Jogador %d, digite dado para jogar o dado: ", x+1);
			scanf("%s", entrada);
		}while(strcmp(Sdado, entrada)!=0);
		Ndado=dado();
		printf("  O dado retornou %d! voce e andou %d casas ...", Ndado, Ndado);
		
		
		switch(acao()){
			case 0:{
				printf("\n\tEXPLORADOR, avance duas casas\n");
				vet[x].posicao+=(Ndado+2);
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras			
				recursividade=-1;
				break;
			}
			case 1:{
				printf("\n\tSORTUDO, voce recebeu 20 ouro\n");
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				vet[x].bag+=20;
				recursividade=-1;
				break;
			}
			case 2:{
				printf("\n\tCADEIA, fique uma rodada sem jogar\n");
				vet[x].controle=1;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				recursividade=-1;
				break;
			}
			case 3:{
				printf("\n\tMONSTRO, voce encontrou um montro e voltou tres casas\n");
				vet[x].posicao+=(Ndado-3);
				if(vet[x].posicao<0){
					vet[x].posicao=0;
				}
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				recursividade=-1;
				break;
			}
			case 4:{
				printf("\n\tBURRACO, voce caiu em um burraco e perdeu uma vida\n");
				vet[x].life-=1;
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				recursividade=-1;
				break;
			}
			case 5:{
				printf("\n\tLADRAO, voce foi roubado e perdeu 10 ouro\n");
				vet[x].bag-=10;
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				recursividade=-1;
				break;
			}
			case 6:{
				int k;
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				printf("\n\tMAGIA NEGRA, escolha um jogador para voltar cinco casas(digite o numero dele): ");												
				do{
					scanf("%d",&k);
					k--;
				}while(k<0 || k>(N_jogadores-1));
				vet[k].posicao-=5;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				if(vet[k].posicao<0){
					vet[k].posicao=0;
				}
				printf("\n");
				recursividade=-1;
				break;
			}
			case 7:{
				int i;
				printf("\n\tMALDIÇÃO, todos os jogadores perdem 10 ouro\n");
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele esta. se sim, ele é colocado uma casa atras
				for(i=0;i<N_jogadores;i++){
					vet[i].bag-=10;
				}
				recursividade=-1;
				break;
			}
			case 8:{
				printf("\n\tDIAMANTE, voce achou um diamante. jogue denovo\n");
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);
				turno(vet, N_jogadores, x);
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras					
				recursividade=-1;
				break;
			}
			case 9:{
				int k;
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				printf("\n\tCEIFADOR, digite o numero de um jogador para perder uma vida\n");
				do{
					scanf("%d",&k);
					k--;
				}while((k<0|| k>(N_jogadores-1)) && k!=x && vet[k].life>0);				
				vet[k-1].life-=1;
				recursividade=-1;
				break;
			}
			case 10:{
				printf("\n\tATALHO, voce avancou tres casas\n");
				vet[x].posicao+=(Ndado+3);
				verifica_posicao(vet, N_jogadores);     				//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				recursividade=-1;
				break;
			}
			case 11:{
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				printf("\n\tCOMPANHEIRO, digite o numero de outro jogador para que ele receba 20 ouro: ");
				int k;
				do{
					scanf("%d",&k);
					k--;
				}while((k<0 || k>(N_jogadores-1)) && vet[x].life>0);
				vet[k].bag+=20;
				printf("\tO jogador %d agradece!\n", k+1);
				recursividade=-1;
				break;
			}
			case 12:{
				printf("\n\tPEDRA, voce encontrou uma no caminho. voltou uma casa\n");
				vet[x].posicao+=(Ndado-1);
				verifica_posicao(vet, N_jogadores);     				//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				if(vet[x].posicao<0){
					vet[x].posicao=0;
				}
				recursividade=-1;
				break;
			}case 13:{
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				printf("\n\tIMPOSTO, Para passar pela ponte do TROLL voce teve que pagar 30 ouro\n");
				vet[x].bag-=30;
				recursividade=-1;
				break;
			}case 14:{
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				printf("\n\tSORTUDO, voce recebeu 20 ouro\n");
				vet[x].bag+=20;
				recursividade=-1;
				break;
			}case 15:{
				printf("\n\tCAMINHO ERRADO, voce voltou 5 casas\n");
				vet[x].posicao-=(Ndado-5);
				verifica_posicao(vet, N_jogadores);     				//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				if(vet[x].posicao<0){
					vet[x].posicao=0;
				}
				recursividade=-1;
				break;	
			}case 16:{
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				printf("\n\tCURA, suas vidas foram restauradas\n");
				vet[x].life=3;
				recursividade=-1;
				break;
			}case 17:{
				printf("\n\tPORTAL MAGICO, voce foi teleportado 4 casas a frente\n");
				vet[x].posicao+=(Ndado+4);
				verifica_posicao(vet, N_jogadores);    				 //verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				recursividade=-1;
				break;
			}case 18:{
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				printf("\n\tPENHASCO, voce caiu de um penhasco e perdeu 2 vidas\n");
				vet[x].life-=2;
				recursividade=-1;
				break;
			}case 19:{
				int k;
				vet[x].posicao+=Ndado;
				verifica_posicao(vet, N_jogadores);					//verifica se algum jogador ja está na posição que ele ocupou. se sim, ele é colocado uma casa atras
				do{
					k=rand()%N_jogadores;								//sorteia um jogador para receber uma vida
				}while(k==x);
				printf("\n\tLADRAO, o jogador de numero %d roubou uma vida sua\n", k+1);
				vet[x].life-=1;
				vet[k].life+=1;
				recursividade=-1;
				break;
			}			
		}			
		if(x==(N_jogadores-1)){
			desenha_tabuleiro(N_jogadores, Nmatriz, vet);
		}
	} 							
	recursividade=-1;
}
