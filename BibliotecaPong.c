#include "BibliotecaPong.h"


void gotoxy(int coluna, int linha) {

     COORD point;

     point.X = coluna;

     point.Y = linha;

     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);

}


void textcolor (iColor) {

     HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);

     CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

     BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);

     bufferInfo.wAttributes &= 0x00F0;

     SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);

}


void textbackground (iColor) {

     HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);

     CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

     BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);

     bufferInfo.wAttributes &= 0x000F;

     SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));

}


void wait( double seconds ) {

     clock_t endwait;

     endwait = clock () + seconds * CLOCKS_PER_SEC ;

     while (clock() < endwait) {}

}


void printxy(int coluna, int linha, char texto[]){

     gotoxy(coluna, linha);

     printf(texto);

}


void Placar(){

	printxy(1, 2, "                              ");

	textbackground(9);

	printxy(15, 2,"    Play 1              Vidas               PC     ");

}


void Play(int p){


	Beep(439, 500); 

	Beep(65, 13);

	Beep(369, 250); 

	Beep(65, 13);

	Beep(391, 250);

	Beep(65, 13);

	Beep(440, 500); 

	

	if(p){

	Beep(439, 500); 

	Beep(65, 13);

	Beep(369, 250); 

	Beep(65, 13);

	Beep(391, 250);

	Beep(65, 13);

	Beep(440, 500);

	}

}


void jogo( int *vidas, double *tempo){


	textbackground(0);

	printf("                                        0%d", (*vidas));
	

	int x = 20, py = 10, pcy = 5, y = 10, velx = 1, vely = 1, score = 0, i;

	printxy(32, 4," "); 
	printf(" Pontuacao   %i", score);
	
	Placar();	



	while((*vidas)!=0){

	if((score > 90) && (score < 200)){

		if(*tempo == 0.06){
			
				*tempo = 0.05;
			}else if(*tempo == 0.04){
				*tempo = 0.03;
	 	}else{
				*tempo = 0.02;
		}
			
	}else if((score > 190) && (score < 300)){
			
			if(*tempo == 0.05){
				*tempo = 0.04;
			}else if(*tempo == 0.04){
				*tempo = 0.03;
			}else{
				*tempo = 0.01;
			}
			
	}else if((score > 290) && (score >=300)){
			
			if(*tempo == 0.04){
				*tempo = 0.03;
			}else if(*tempo == 0.03){
				*tempo = 0.02;
			}else{
				*tempo = 0.00;
			}
			
	}


		if(GetAsyncKeyState(40) && py < 20){ //* Get(capita tecla para baixo), && (py onde inicia barra de baixo em qual linha e < que (define ate onde a barra de baixo do play 1 vai barra de cima

			textbackground(0); 

			printxy(16,     py, " "); //*capita movimento do play 1 e escreve na direcao que ele aperta os passos atras com incrimento

			py++; //*incrimento para escrer caractere

		}

		if(GetAsyncKeyState(38) && py >= 7){ //* Get(capita tecla para cima), && (py onde inicia barra em qual linha e < que (define ate onde a barra de cima do play 1 vai barra de cima

			textbackground(0); 

			printxy(16, 5 + py, " "); //*capita movimento do play 1 e apaga os passos atras com decremento

			py--; //*decremento apaga o caracter

		}	

		

		if(y < 22){

			

			textbackground(0);

			printxy(64, y - 1 , " ");  

			printxy(64, y + 6, " ");

			

			textbackground(6);

			for(i = 0; i < 6; ++i){ //*barra do pc

			printxy(64, y + i, " ");

			}			

		}

		

		textbackground(6);

		for(i = 0; i < 6; ++i){ //*desenha barra do play 1

		printxy(16, i + py, " ");

		}

	

		textbackground(15); //*desenha tela apartir daqui

		

		for(i = 0; i < 21; ++i){

			

			printxy(i + 12,  6, "                                   ");//*barra de cima linha 

			printxy(i + 12, 26, "                                    ");//*barra de baixo linha

			

			if(i < 20){

				

			printxy(12, i + 6, " "); 

			printxy(67, i + 6, " ");

			}

		}

		textbackground(0);

		printxy(x - velx, y - vely, " ");

		if(y > 23  || y < 7){ //*limite onde bola bate na barra linha de baixo e na linha de cima			

			vely *= -1;

			Beep(330, 30);

		}

		

		if(x > 63){ //*ate onde bola bate na 2 na barra do pc 

		

			velx *= -1; //*se for fazer bug da maquina sera aqui, pc x e a coordenada da bola, pois assim a barra sabe sempre onde tem que ir para bater na bola,

			Beep(700, 30);

		}

		

		//*Fora

		if(x < 16){

			

			Play(0); //*faz som de que perdeu 

			

			x = 50; 

			y = 10 + rand()%4; //*recebe coordenadas radomicas quando for inciar outra rodada apos a bola ir fora

			

			Placar( ); //*se bola for fora chama funcao para mostra desenhar placar em cima e diminiu a variavel vidas com decremento

			

			(*vidas)--; 

			

			textbackground(0);

			printxy(32, 3," "); 

			printf(" Restam   0%i", (*vidas));



		}else if(y >= py && y - 7 < py && x == 17){ //*se nao refaz o caminho de volta dimiuindo os valores como se estivesse voltando, quando bate em caracter e no final recebe radomico x bolo for igial a 17 que valor da posicao do caracter

			

			velx *= -1;

			Beep(800, 30); //*beep bateu em caracter na barra

			y += (rand()%2)/2;
			
			score = score + 10;
			
			printxy(32, 4," "); 
			
			printf(" Pontuacao   %i", score);

		}

		

		textbackground(12); //*desenha bola 

		printxy(x, y, " ");

		

		x += velx; //*coordenadas sempre aumentando

		y += vely;

		wait((*tempo));		//*funcao de tempo para escrever o caracter da bola inves de for, evita loop, errado usar sleep pois não controlaria a escrita da maneira correta

	}
	
	textbackground(0);
	
	gameover( );
	
}

void gameover( ){
	
	system("cls");

	textbackground(0);
	
	printf("\n\n\n\n\n\n\n");

	printf("                   -----------------------------------------------------------------\n");

	printf("                   --------------------------GAME     OVER--------------------------\n");

	printf("                   -----------------------------------------------------------------\n");

	Sleep(2000);
}


void desenha_coluna(int l, int c, int t1, int t2, int op){

	int i,j;

	if (op == 1){

		for(i=0; i<t1;i++){

			gotoxy(l,c);

			for(j=0; j<t2; j++){

				if(j==0){

					printf("%c", 178);

				}else if((j==((t2)-1))){

					printf("%c", 178);

				}else {

					printf("%c",32);

				}

			}

			c=c+1;

			printf("\n");

		}

	}else if (op == 2){

		for(i=0; i<t1;i++){

			gotoxy(l,c);

			for(j=0; j<t2; j++){

				if(j==0){

					printf("%c", 179);

				}else if((j==((t2)-1))){

					printf("%c", 179);

				}else {

					printf("%c",32);

				}

			}

			c=c+1;

			printf("\n");

		}

	}
}
void desenha_linha(int l, int c, int t1, int op, int local){

	int i;

	gotoxy(l,c);

	if (op == 1){

		for (i = 0; i < t1; i++){

			printf("%c",178 );

		}

		printf("\n");

	}else if (op == 2){

		for (i = 0; i < t1; i++){

			if (local == 1){

				if (i == 0){

					printf("%c",218 );

				}else if (i == t1-1){

					printf("%c",191);

				}else{

					printf("%c",196 );

				}

			}else if (local == 2){

				if (i == 0){

					printf("%c",192 );

				}else if (i == t1-1){

					printf("%c",217);

				}else{

					printf("%c",196 );

				}

			}

		}

		printf("\n");

	}
}

void dificuldade(int * vida){
		
	system("cls");

	desenha_linha(15,3, ((largura/2)-4),2,1);

    desenha_coluna(15,4,((altura/2)-4), ((largura/2)-4),2);

    desenha_linha(15,7,((largura/2)-4),2,2);

	int op;

	double *tempo = (double*)malloc(sizeof(double));


	gotoxy(16,4);

    printf("[1] - FACIL\n");

    gotoxy(16,5);

    printf("[2] - MEDIO\n");

    gotoxy(16,6);

    printf("[3] - DIFICIL\n");

    gotoxy(16,8);

    scanf("%d",&op);

	
    if(op == 1){

		*tempo = 0.06;

		system("cls");

    	jogo(&(*vida),&(*tempo));

	}else if(op == 2){

		*tempo = 0.04;

		system("cls");

		jogo(&(*vida),&(*tempo));

	}else if(op == 3){

		*tempo = 0.03;

		system("cls");

		jogo(&(*vida),&(*tempo));

	}

}

void rodada(){

	int *vida=(int*) malloc(sizeof(int));

	int op;

	

	desenha_linha(15,3, ((largura/2)-4),2,1);

    desenha_coluna(15,4,((altura/2)-4), ((largura/2)-4),2);

    desenha_linha(15,7,((largura/2)-4),2,2);

	gotoxy(16,4);

    printf("[1] 3 VIDAS\n");

    gotoxy(16,5);

    printf("[2] 5 VIDAS\n");

    gotoxy(16,6);

    printf("[3] 7 VIDAS\n");

    gotoxy(16,8);

    scanf("%d",&op);

    

    if(op == 1){

    	

    	*vida = 3;

    	dificuldade(&(*vida));

		system("cls");	

	

	}else if(op == 2){

		*vida = 5;

		dificuldade(&(*vida));

		system("cls");

	

	}else if(op == 3){



		*vida = 7;

		dificuldade(&(*vida));

		system("cls");

	}

}
void menu_Principal( ){

	char op;

	int jh, kj;

	do{

		
		fflush(stdin);
		system("cls");

		textbackground(0);

		printf("\n");

		gotoxy(15,2);

    	printf("PING PONG\n");

    	desenha_linha(15,3, ((largura/2)-4),2,1);

        desenha_coluna(15,4,((altura/2)-4), ((largura/2)-4),2);

        desenha_linha(15,7,((largura/2)-4),2,2);

        gotoxy(16,4);

        printf("1-PLAYER\n");

        gotoxy(16,5);

        printf("  0-SAIR\n");

        gotoxy(16,8);

        scanf("%c",&op);

        gotoxy(16,9);

        system("cls");

        

        if ((op == '1') || (op == '2')){

        	system("cls");

        	rodada();

        	system("cls");

        }else if (op == '0'){

        	printf("Obrigado, por jogar!\n");

        }

	}while(op != '0');

}
