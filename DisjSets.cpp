#include "DisjSets.h"

/**
 * Construtor da classe
 */
DisjSets::DisjSets( int n ){
	v.ReSize( n );
	for( int i=0; i<n; i++ ){
		v[i] = -1;
	}
}

/**
 * Construtor do tipo cópia
 */
DisjSets::DisjSets( const DisjSets& a ){
	v = a.v;
}

/**
 * Método que realiza busca por compressão de caminhos
 */
int DisjSets::Find( int n ){
	/**
	 * Verifica se pertence ou não à algum conjunto
	 */
	if ( v[ n ] < 0 ){
		return n;
	} else {
		/**
		 * Faz a compressão dos caminhos
		 */
		v[ n ] = Find( v[ n ] );
		/**
		 * Continua e realiza a busca recursivamente
		 */
		return v[ n ];
	}
}

/**
 * Método que realiza a operação de união dos conjuntos
 */
void DisjSets::Union( int a, int b ){
	a = Find(a);
	if( Find(b)==b ){
		/**
		* Testa se a e b são conjuntos diferentes;
		*/
		if ( a==b ){
			std::cout << "Impossível efetuar união: CONJUNTOS IGUAIS" << std::endl;
			return;
		}
		/**
		* Verifica qual das árvores é mais profunda
		*/
		if ( v[ b ] < v[ a ] ){
			v[ a ] = b;
		} else { 
			if ( v[ b ] == v[ a ] ){
				v[ a ] = v[ a ]-1;
			}
			v[ b ] = a;
		}
	} else Union(Find(a),Find(b));
	
}

void DisjSets::ReSize( int n ){
	//int oldsize = v.Length();
	v.ReSize(n);
	for ( int i=0; i<n; i++ ){
		v[i] = -1;
	}
}

/**
 * Método que informa quantos conjuntos diferentes existem
 */
int DisjSets::NumOfSets(){
	int nSets=0;
	for( int i=0; i<v.Length(); i++ ){
		if( v[ i ]<0 ){
			nSets++;
		}
	}
	return nSets;
}
/**
 * Sobrecarga do operador []
 *@param index índice do DisjSets que se deseja acessar
 *@return Elemento na posição index do DisjSets
 */
int & DisjSets::operator []( int index ){
	return v[index];
}

/**
 * Sobrecarga do operador de comparação de igualdade
 */
bool DisjSets::operator ==( const DisjSets a ){
	if( v==a.v ){
		return true;
	} else {
		return false;
	}
}

/**
 * Sobrecarga do operador de comparação de diferença
 */
bool DisjSets::operator !=( const DisjSets a ){
	if( v!=a.v ){
		return true;
	} else {
		return false;
	}
}

/**
 * Método utilizado para imprimir o conteúdo do vetor na saída padrão
 */
void DisjSets::Print(){
	v.Print();
}
