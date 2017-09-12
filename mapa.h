#ifndef MAPA_H
#define MAPA_H

#include "poligono.h"
#include "Maze.h"
#include "StackAr.h"

using namespace MyQueue;// Namespace que contém a pilha utilizada pela classe mapa.

class mapa
{
 /**
 * Classes amigas da classe mapa.
 */
    friend class Cell;
    friend class Maze;
    //friend class StackAr<int>;

public:
    
/**
 * Construtor.
 * @param x número de linhas do labirinto.
 * @param y número de colunas do labirinto.
 * @param v habilita ou não o modo para gerar um labirinto válido.	
 */   
    mapa(int x = 20, int y = 33, bool v = false): m(x), n(y) 
    {
        int i;

/**
 * Alocação de espaço para as pilhas a serem utilizadas pelo 
 * método Backtracking().
 */
        marcados = new StackAr<int>(m*n); 
  	    desmarcados = new StackAr<int>(m*n);

/**
 * Coloca o primeiro elemento do labirinto na 
 * pilha de elementos marcados pelo Backtracking().
 */
        marcados->push(0);

	    edge = 0.3;// Tamanho default da aresta dos polígonos.
        constroyed = false;// Especifica o labirinto como ainda não construido.   

        maze = new Maze(m,n);// Cria-se a estrutura lógica do labirinto.
/**
 * Se v for uma condição verdadeira,
 * um labirinto apenas válido é gerado.
 * Caso contrário, é gerado um labirinto 
 * totalmente conexo.
 */
		if( v )
         maze->GenerateValid();
		else
		   maze->Generate();

        matrix = new poligonoidiota[m*n];// Aloca espaço para a matriz dos polígonos a ser desenhada.
        grade = new poligonoidiota[m*n];// Aloca espaço para a matriz de desenho auxiliar - contém todos os polígonos completos.         
        

/**
 * Seta a posição de todos os polígonos que compõem o 
 * labirinto, assim como a existência ou não de
 * suas paredes - Left, Right, Up, Down.
 */ 
        for(i=0;i<m*n;i++)
        {
             matrix[i].setx(i/n);// Seta a posição x do elemento i da matriz de desenho.
             matrix[i].sety(i%n);// Seta a posição y do elemnto i da matriz de desenho.

             grade[i].setx(i/n);// Seta a posição x do elemento i da grade auxiliar 
             grade[i].sety(i%n);// Seta a posição y do elemento i da grade auxiliar.
	         
             matrix[i].SetLeft(maze->maze[i].ExistLeft());// Seta a existência de parede esquerda no poligono i.
             matrix[i].SetRight(maze->maze[i].ExistRight());// Seta a existência de parede direita no poligono i.
             matrix[i].SetUp(maze->maze[i].ExistTop());// Seta a existência de parede superior no poligono i.
	         matrix[i].SetDown(maze->maze[i].ExistBottom());// Seta a existência de parede inferior no poligono i.
               
        }

/**
 * O primeiro poligono do labirinto e do 
 * labirinto auxiliar
 * deve possuir a primeira parede esquerda
 * destruida.
 * O mesmo vale para a parede direita
 * do último polígono.
 */
	     grade[0].SetLeft(false);
         grade[(m*n)-1].SetRight(false);
    	 matrix[0].SetLeft(false);
         matrix[(m*n)-1].SetRight(false);

         matrix[0].SetVisit();// Primeiro elemento é naturalmente visitado.
    }

/**
 * Diz se o labirinto já terminou de ser construído.
 * @return constroyed valor booleano que indica se
 * o labirinto foi ou não construído.
 */
    bool IsConstroyed(void){return constroyed;}
    
/**
 * Destrutor: desaloca todos os ponteiros alocados.
 */
    ~mapa(){delete[]matrix;delete[]grade;delete marcados;delete desmarcados;delete maze;}

/**
 * Realiza a operação do Backtracking.
 * A cada chamada, um novo local do 
 * labirinto é visitado. Caso não haja
 * caminho a se seguir, o algoritmo
 * regride ao último local válido -
 * onde ainda haveria possibilidade de prosseguir.
 */
   void Backtracking()
	{
        static int aux = 0;// Indica sempre o último polígono visitado.

/**
 * Caso o último polígono do labirinto
 * tenha sido atingido, o Backtracking()
 * já realizou seu trabalho.
 */
        if(aux == (m*n)-1)
            return;

/**
 * Os booleanos usados para armazenar 
 * as condições das paredes de cada polígono
 * devem ser diferentes dos da função draw().
 * Assim, seus valores são negados e posteriormente -
 * após as operações lógicas do Backtracking() -negados
 * mais uma vez, voltando ao seu valor original,
 * anterior à função.
 */
        matrix[aux].SetLeft(!matrix[aux].IsLeftOpen());
        matrix[aux].SetRight(!matrix[aux].IsRightOpen());
        matrix[aux].SetUp(!matrix[aux].IsUpOpen());        
        matrix[aux].SetDown(!matrix[aux].IsDownOpen());

/**
 * Caso o elemento em questão não esteja localizado
 * na borda direita do labirinto, sua parede direita esteja aberta
 * e o polígono da direita ainda não tenha sido visitado,
 * este é preenchido.
 */
        // right
        if(((aux%n)!= n-1)&&(matrix[aux].IsRightOpen())&&(!matrix[aux+1].WasVisitated()))
        {
			matrix[aux].SetLeft(!matrix[aux].IsLeftOpen());
            matrix[aux].SetRight(!matrix[aux].IsRightOpen());
            matrix[aux].SetUp(!matrix[aux].IsUpOpen());        
            matrix[aux].SetDown(!matrix[aux].IsDownOpen());

            /**
			 * Atualiza o elemento corrente do algoritmo,
			 * coloca-o na pilha, seta-o como visitado. Fim do método.	 
             */ 
            aux++; marcados->push(aux); matrix[aux].SetVisit();return;
        }

/**
 * Caso o elemento em questão não esteja localizado
 * na borda inferior do labirinto, sua parede inferior esteja aberta
 * e o polígono abaixo ainda não tenha sido visitado,
 * este é preenchido.
 */
		//down
        if(((aux/n)!=m-1)&&(matrix[aux].IsDownOpen())&&(!matrix[aux+n].WasVisitated()))
        {
			matrix[aux].SetLeft(!matrix[aux].IsLeftOpen());
            matrix[aux].SetRight(!matrix[aux].IsRightOpen());
            matrix[aux].SetUp(!matrix[aux].IsUpOpen());        
            matrix[aux].SetDown(!matrix[aux].IsDownOpen());

            /**
			 * Atualiza o elemento corrente do algoritmo,
			 * coloca-o na pilha, seta-o como visitado. Fim do método.	 
             */ 			
            aux = aux + n; marcados->push(aux); matrix[aux].SetVisit(); return;
        }

/**
 * Caso o elemento em questão não esteja localizado
 * na borda esquerda do labirinto, sua parede esquerda esteja aberta
 * e o polígono esquerdo ainda não tenha sido visitado,
 * este é preenchido.
 */
		//left
        if(((aux%n)!=0)&&(matrix[aux].IsLeftOpen())&&(!matrix[aux-1].WasVisitated()))
        {
			matrix[aux].SetLeft(!matrix[aux].IsLeftOpen());
            matrix[aux].SetRight(!matrix[aux].IsRightOpen());
            matrix[aux].SetUp(!matrix[aux].IsUpOpen());        
            matrix[aux].SetDown(!matrix[aux].IsDownOpen());

            /**
			 * Atualiza o elemento corrente do algoritmo,
			 * coloca-o na pilha, seta-o como visitado. Fim do método.	 
             */             
			aux--;marcados->push(aux); matrix[aux].SetVisit(); return;
        }

/**
 * Caso o elemento em questão não esteja localizado
 * na borda superior do labirinto, sua parede supeior esteja aberta
 * e o polígono superior ainda não tenha sido visitado,
 * este é preenchido.
 */
        //up
        if((aux>=n)&&(matrix[aux].IsUpOpen())&&(!matrix[aux-n].WasVisitated()))
        {
            
			matrix[aux].SetLeft(!matrix[aux].IsLeftOpen());
            matrix[aux].SetRight(!matrix[aux].IsRightOpen());
            matrix[aux].SetUp(!matrix[aux].IsUpOpen());        
            matrix[aux].SetDown(!matrix[aux].IsDownOpen());

            /**
			 * Atualiza o elemento corrente do algoritmo,
			 * coloca-o na pilha, seta-o como visitado. Fim do método.	 
             */     		    
			aux = aux - n; marcados->push(aux); matrix[aux].SetVisit();
			return;
        }

/** Parte do Backtracking referente
 * a uma c�lula comtodos os seus caminhos
 * bloqueados.
 * Os valores booleanos referentes
 * � c�lula retornam ao estado 
 * anterior ao m�todo.
 */
			matrix[aux].SetLeft(!matrix[aux].IsLeftOpen());
            matrix[aux].SetRight(!matrix[aux].IsRightOpen());
            matrix[aux].SetUp(!matrix[aux].IsUpOpen());        
            matrix[aux].SetDown(!matrix[aux].IsDownOpen());

/** A pilha dos elementos desmarcados
 * recebe o pol�gono em quest�o.
 */
        if(marcados->size()>0)
            desmarcados->push(marcados->pop());

/** O elemento corrente do BackTracking()
 * volta a ser o pen�ltimo elemento visitado.
 * Assim, caso ainda haja algum caminho poss�vel
 * atrav�s dele, este ser� seguido.
 */
		if(marcados->size()>0)
            aux = marcados->top();
	}
    
    void draw(void)
    {   
        int i;// auxiliar
/** 
 * Desenha todos os elementos
 *  marcados [EM VERMELHO].
 */
        for(i=marcados->size()-1; i>=0; i--)
            preenche(marcados->vetor[i]);

/** 
 * Desenha todos os elementos desmarcados
 * [EM AMARELO].
 */
	    for(i=desmarcados->size()-1; i>=0; i--)
            despreenche(desmarcados->vetor[i]);

        preenche(0);
/**
 * Desenha todas as c�lulas.
 */
        for(i=0;i<m*n;i++){
            matrix[i].draw();
        }
    }

/**
 * Constroe a anima��o do surgimento
 * do labirinto.
 * Desenha-se as c�lulas do labirinto
 * at� um determinado ponto(i).
 * Deste ponto at� a c�lula
 * correspondente ao �ndice [(m*n-1)],
 * desenha-se a grade, causando assim
 * o efeito da anima��o.
 */
    void Constroy(void)
    {   
        static int i = 0;// �ndice do �ltimo elemeno desenhado.
        int j = 0, aux = 0;// auxiliares.
        

/**
 * Desenha todos os elementos que j� foram desenhados 
 * mais o pr�ximo.
 */
        for(j = 0; j <= i; j++)
            matrix[j].draw();

        i++;//Incrementa o n�mero de pol�gonos a serem desenhados.

/**
 * Desenha todos os elementos da grade
 * a partir do �ltimo elemento desenhado.
 */
        for(aux = i; aux <m*n; aux++) 
            grade[aux].draw();

/**
 * Caso o �ltimo elemento a ser desenhado 
 * tenha sido o elemento de �ndide [(m*n)-1],
 * o labirinto � dado como constru�do.
 */            
        if(i == m*n){
            constroyed = true;
  
        }
    }

/**
 * Pinta de vermelho a c�lula correspondente a i.
 * @param i �ndice da c�lula a ser pintada.
 */    
    void preenche(int i)
    {    
         matrix[i].marca();// Pinta de vermelho
         matrix[i].SetVisit();// Marca como visitada.
    }

/**
 * Pinta de amarelo a c�lula correspondente a i.
 * @param i �ndice da c�lula a ser pintada.
 */
    void despreenche(int i)
    {
         matrix[i].desmarca();// pinta de amarelo
    }
       
private:
    
/**
 * Elementos j� explicados no construtor da classe.
 */    
    float edge;
    int m,n;
    poligonoidiota *matrix,*grade;
    bool constroyed;
    Maze *maze;
    StackAr<int> *marcados, *desmarcados;

};

#endif
