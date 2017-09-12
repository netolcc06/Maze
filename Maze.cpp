#include "Maze.h"
#include <stdlib.h>
#include <time.h>

/**
 * Construtor da classe
 *@param m Número de linhas
 *@param n Número de colunas
 */
Maze::Maze(int m, int n){
	maze = new Cell[m*n];
	NumLines = m;
	NumColuns = n;
	disjSets.ReSize( m*n );
}
;
/**
 * Destrutor da classe
 */
Maze::~Maze(){
	delete [] maze;
}

/**
 * Método que retorna o número de linhas do labirinto
 */
int Maze::GetNumLines(){
	return NumLines;
}

/**
 * Método que retorna o número de colunas do labirinto
 */
int Maze::GetNumColuns(){
	return NumColuns;
}

/**
 * Método que retorna o número de células do labirinto
 */
int Maze::GetNumCells(){
	return NumLines * NumColuns;
}

/**
 * Método que conecta duas células adjacentes do labirinto destruindo suas paredes. 
 * Observe que 'a' estar conectada com 'b' implica 'b' estar conectada com 'a'.
 *@param a posição da célula a ser conectada com outra (inicia com 0)
 *@param b posição da célula a ser conectada com outra (inicia com 0)
 */
void Maze::Connect( int a, int b ){
	
	if( a+1==b ){
		maze[a].DestroyRight();
		maze[b].DestroyLeft();
		disjSets.Union(a,b);
		//cout << "Conexão de " << a << " >>>> " << b << endl;
		return;
	}
	if( a-1==b ){
		maze[a].DestroyLeft();
		maze[b].DestroyRight();
		disjSets.Union(a,b);
		//cout << "Conexão de " << a << " >>>> " << b << endl;
		return;
	}
	if( a+NumColuns==b ){
		maze[a].DestroyBottom();
		maze[b].DestroyTop();
		disjSets.Union(a,b);
		//cout << "Conexão de " << a << " >>>> " << b << endl;
		return;
	}
	if( a-NumColuns==b ){
		maze[a].DestroyTop();
		maze[b].DestroyBottom();
		disjSets.Union(a,b);
		//cout << "Conexão de " << a << " >>>> " << b << endl;
		return;
	}
}

/**
 * Sobrecarga do operador []
 *@param index índice da célula que se deseja acessar
 *@return Célula na posição index do labirinto
 */
Cell & Maze::operator []( int index ){
	/**
	 *Efetua teste para verificar se o índice está na faixa contemplada pelo labirinto
	 */
	if ( index < 0 or index >= NumLines*NumColuns ){
		std::cout << index << " ERRO: Valor fora da faixa do labirinto\n";
		return maze[ 0 ];
	} else {
		return maze[ index ];
	}
}
/**
 * Método utilizado para gerar o labirinto totalmente conexo
 */
void Maze::Generate(){
	int rCell, rWall;
	srand( time(NULL) );
	/**
	 * Realiza loop até todas as células pertencerem ao mesmo conjunto
	 */
	while (disjSets.NumOfSets() != 1){
		/**
		 * Gera valores randômicos para selecionar célula e para selecionar
		 * paredes da célula
		 */
		rCell = rand() % ( NumColuns*NumLines );
		rWall = rand() % 4;
		/**
		 * Conjunto de testes que verifica qual parede da célula será derrubada
		 */
		if( rWall==0 ){
			/**
			 * Testa se a célula pertence a parede superior do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if( rCell>=NumColuns and disjSets.Find(rCell-NumColuns)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell-NumColuns);
			}
		} else if( rWall==1 ){
			/**
			 * Testa se a célula pertence a parede direita do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if( rCell%NumColuns!=NumColuns-1 and disjSets.Find(rCell+1)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell+1);
			}
		} else if( rWall==2 ){
			/**
			 * Testa se a célula pertence a parede inferior do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if( rCell/NumColuns!=NumLines-1 and disjSets.Find(rCell+NumColuns)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell+NumColuns);
			}
		} else if( rWall==3 ){
			/**
			 * Testa se a célula pertence a parede esquerda do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if(rCell%NumColuns!=0 and disjSets.Find(rCell-1)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell-1);
			}
		}
	}
}
/**
 * Método utilizado para gerar o labirinto totalmente conexo
 */
void Maze::GenerateValid(){
	int rCell, rWall;
	srand( time(NULL) );
	/**
	 * Realiza loop até o início e o fim do labirinto pertencerem ao mesmo conjunto
	 */
	while ( disjSets.Find(0) != disjSets.Find(NumColuns*NumLines-1) ){
		/**
		 * Gera valores randômicos para selecionar célula e para selecionar
		 * paredes da célula
		 */
		rCell = rand() % ( NumColuns*NumLines );
		rWall = rand() % 4;
		/**
		 * Conjunto de testes que verifica qual parede da célula será derrubada
		 */
		if( rWall==0 ){
			/**
			 * Testa se a célula pertence a parede superior do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if( rCell>=NumColuns and disjSets.Find(rCell-NumColuns)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell-NumColuns);
			}
		} else if( rWall==1 ){
			/**
			 * Testa se a célula pertence a parede direita do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if( rCell%NumColuns!=NumColuns-1 and disjSets.Find(rCell+1)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell+1);
			}
		} else if( rWall==2 ){
			/**
			 * Testa se a célula pertence a parede inferior do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if( rCell/NumColuns!=NumLines-1 and disjSets.Find(rCell+NumColuns)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell+NumColuns);
			}
		} else if( rWall==3 ){
			/**
			 * Testa se a célula pertence a parede esquerda do labirinto.
			 * Testa se a célula a ser conectada ainda não pertence ao conjunto.
			 */
			if(rCell%NumColuns!=0 and disjSets.Find(rCell-1)!=disjSets.Find(rCell) ){
				Connect(rCell,rCell-1);
			}
		}
	}
}

void Maze::PrintDSets(){
	disjSets.Print();
}
