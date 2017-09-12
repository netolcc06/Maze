#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "poligono.h"
#include "mapa.h"

mapa *map;// Labirinto a ser gerado.
float m = 20;// Número de linhas default do labirinto.
float n = 33;// Número de colunas default do labirinto.

/**
 * Inicializa as variáveis globais do programa.
 * Faz os testes necessários para saber se os parâmetros de
 * entrada foram passados corretamente.
 */
void Init(int * argc, char * argv[])
{
   bool mr = false;
   bool valid = false;
  
/**
 * O sistema não permite que mais de 3
 * parâmetros de entrada sejam passados 
 * para o programa.
 */
   if( *argc > 4 ){
	  cout << "ERRO: Parâmetros incorretos\n";
	  cout << "Utilize até 3 argumentos\n";
	  exit(0);
   }

/**
 * Lê os valores de forma adequada.
 */
   for( int i =1; i<*argc; i++ ){
	  if( argv[i][0] == '-' and argv[i][1]=='v' )
		 valid = true;
	  else if( mr == false ){
		 m = atoi(argv[i]);
		 mr = true;
	  } else {
		 n = atoi(argv[i]);
	  }
   }

/**
 * Valores negativos ou maiores que 100
 * ou menores que 1 não são aceitos como
 * número de linhas ou colunas para o labirinto.
 */
   if( n<=1 or m<=1 or n>100 or m>100 ){
	  cout<< "ERRO: Não é possível gerar um labirinto com esses parâmetros\n";
	  exit(0);
   }
    
    glMatrixMode(GL_MODELVIEW);// Matriz de inicialização do modelo. 
    map = new mapa(m,n,valid);// Mapa é alocado dinamicamente.
}

/**
 * Função onde o labirinto é desenhado e constantemente atualizado.
 * @param x Valor usado para setar 
 * o tempo entre um frame e outro do programa
 * através da glutTimerFunc(30,Desenha,30).
 */
void Desenha(int x)
{
    glClearColor(255, 255, 255, 0);// Especifica a cor branca a ser usada para limpar a tela.
    glClear(GL_COLOR_BUFFER_BIT);// Limpa a tela com a cor especificada anteriormente.

    glLoadIdentity();// Carrega a matriz identidade.

    glPushMatrix();// Prepara a matriz para as transformações a serem especificadas

/**
 * Utiliza-se a glScalef para especificar o tamanho adequado
 * às células do labirinto para que todas essas possam 
 * ser visualizadas.
 */
    if(m>n)
        glScalef((1.5f/m)*10,((1.5f/n)*10)/(m/n),0.0f);
    else
		glScalef(((1.5f/m)*10)/(n/m),(1.5f/n)*10,0.0f);

/**
 * Translada o labirinto para o centro da tela.
 */
	glTranslatef((-1)*(n/2)*0.1,(m/2)*0.1, 0.0f);  


/**
 * A fim de preservar as células como o desenho de um quadrado,
 * utiliza-se a glPixelZoom para manter a relação de igualdade
 * entre as arestas das células a serem desenhadas.
 */
    if(m>n)
        glPixelZoom(m/n,1.0f);
    else
		glPixelZoom(1.0f,n/m);
/**
 * Rotaciona o labirinto 270 graus no eixo z.
 */
    glRotatef(270.0f,0.0f,0.0f,1.0f);


/**
 * Enquanto o mapa não estiver construido,
 * a função Controy continua a ser chamada.
 * Após sua construção, o mapa é desenhado, completo,
 * frame a frame, assim como é chamada da função Backtracking().
 */
    if(!map->IsConstroyed())
        map->Constroy();
    else
    {
        map->draw();
        map->Backtracking();
    }   

/**
 * Pop na matriz, a fim de que as transformações executadas
 * não afetem as coordenadas do mundo.
 */
    glPopMatrix();

    glutSwapBuffers();// Swap dos buffers. Necessário à animação.

    glutTimerFunc(30,Desenha,30);// Chamada da função glutTimerFunc().
}  

/**
 * Função de callback de desenho.
 * Chama a função Desenha().
 */
void dpdraw1()
{
     Desenha(30);
}

/**
 * Função de callback de teclado.
 * Ao pressionar-se a tecla ESC,
 * o labirinto é destruido e o 
 * programa encerrado.
 */
void Teclado(unsigned char tecla, int x, int y)
{

    if(tecla==27)// tecla 27 == ESC
	{
        delete map; // Desaloca o ponteiro map.
        exit(0); // Encerra-se o programa.
    }
}

/**
 * Função principal do programa.
 */
int main(int argc, char* argv[])
{
    Init(&argc,argv);
 
    glutInit(&argc,argv);// Inicializa a glut.

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );// Habilita 2 buffers e as componentes RGB para as cores.

    glutInitWindowSize(800,600);// Tamanho padrão da janela a ser criada.    

    glutCreateWindow(".:: M A Z E ::.");// Título da janela a ser criada.
    
    glutSetCursor(GLUT_CURSOR_NONE);// Desabilita o desenho do cursor do mouse.
    
	glutKeyboardFunc(Teclado);// Registra função de callback do teclado.

    glutFullScreen();// Habilita a janela no modo Fullscreen.

    glutDisplayFunc(dpdraw1);// Registra função de callback de desenho da glut.

    glutTimerFunc(30,Desenha,30);// Especifica o tempo entre 2 chamadas da função Desenha(int x). 

    glutMainLoop();// Loop do programa.

}
