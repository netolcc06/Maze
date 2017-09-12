#include "vector.h"
#include <iostream>

/**
 * Método construtor da classe
 */
template <typename T>
vector<T>::vector( int n ){
	data = new T[n];
	size = n;
}

/**
 * Construtor do tipo cópia
 */
template <typename T>
vector<T>::vector( const vector<T> & copy ){;
	data = new T[ copy.size ];
	size = copy.size;
	for( int i=0; i<size; i++ ){
		data[i] = copy.data[i];
	}
}

/**
 *Método destrutor da classe
 */
template <typename T>
vector<T>::~vector(){
	delete [] data;
}

/**
 * Método utilizado para informar o comprimento do vetor
 *@return Tamanho do vetor
 */
template <typename T>
int vector<T>::Length( void ){
	return size;
}

/**
 * Método insere elemento na posição inicial do vetor, deslocando todos os outros
 *@param a Elemento a ser inserido
 */
template <typename T>
void vector<T>::InsertFront( T a ){
	for( int i=size-2; i>0; i-- ){
		data[i+1]=data[i];
	}
	data[0] = a;
}

/**
 * Método insere elemento na posição final do vetor, deslocando todos os outros
 *@param a Elemento a ser inserido
 */
template <typename T>
void vector<T>::InsertBack( T a ){
	for( int i=0; i<size-1; i++ ){
		data[i]=data[i+1];
	}
	data[size-1] = a;
}

/**
 * Método modifica o comprimento do vetor, alterando sua capacidade de armazenamento
 *@param newsize Novo tamanho do vetor
 */
template <typename T>
void vector<T>::ReSize( int newsize ){
	/**
	 * Ponteiro auxiliar utilizado para copiar os dados já existentes no vetor
	 */
	T * reSizer;
	reSizer = data;
	data = new T[ newsize ];
	/**
	 * Teste para verificar se houve aumento ou diminuição do tamanho do vetor
	 */
	if( newsize > size ){
		/**
		 * Iteração que copia os dados já existentes no vetor
		 */
		for( int i=0; i<size; i++ ){
			data[i] = reSizer[i];
		}
	} else {
		/**
		 * Se o tamanho do vetor diminui ou se mantém, utiliza-se
		 * newsize como limitador da iteração de cópia
		 */
		for( int i=0; i<newsize; i++ ){
			data[i] = reSizer[i];
		}
	}		
	delete [] reSizer;
	size = newsize;
}

/**
 * Método que imprime o vetor na saída padrão
 */
template <typename T>
void vector<T>::Print(){
	std::cout << "[ ";
	for( int i=0; i<size; i++ ){
		std::cout << data[i] << " ";
	}
	std::cout << "]\n";
}

/**
 * Sobrecarga do operador []
 *@param index índice do vetor que se deseja acessar
 *@return Elemento na posição index do vetor
 */
template <typename T>
T & vector<T>::operator [] ( int index ){
	/**
	 *Efetua teste para verificar se o índice está na faixa contemplada pelo vetor
	 */
	if ( index < 0 or index >= size ){
		std::cout << index << " ==> Valor fora da faixa do vetor\n";
		return data[0];
	} else {
		return data[index];
	}
}

/**
 * Sobrecarga do operador de adição, utilizado, nesse contexto para concatenar
 * dois vetores.
 * @param v vetor a ser concatenado com o atual
 * @return vetor resultado da concatenação
 */
template <typename T>
vector<T> vector<T>::operator + ( const vector<T> v){
	vector<T> result( size+v.size );
	/**
	 * Iteração que cópia a primeira parte do novo vetor concatenado
	 */
	for ( int i=0; i<size; i++ ){
		result.data[i] = data[i];
	}
	/**
	 * Nova iteração que copia a segunda parte do novo vetor
	 * A ordem da operação se preserva no resultado
	 */
	for ( int i=size; i<result.size; i++ ){
		result.data[i] = v.data[i-size];
	}
	return result;
}

/**
 * Sobrecarga do operador de atribuição. Todas as características são repassadas
 */
template <typename T>
void vector<T>::operator = ( const vector<T> v ){
	delete [] data;
	data = new T[ v.size ];
	size = v.size;
	for( int i=0; i<size; i++ ){
		data[i] = v.data[i];
	}
}

/**
 * Sobrecarga do operador de comparação de igualdade
 */
template <typename T>
bool vector<T>::operator == ( const vector<T> v){
	/**
	 * Checa se o tamanho dos vetores é igual
	 */
	if( size != v.size ){ 
		return false;
	} else {
		/**
		 * Iteração checa se todos os elementos do vetor são iguais
		 */
		for( int i=0; i<size; i++ ){
			if ( data[i] != v.data[i] ){
				return false;
			}
		}
		return true;
	}
}

/**
 * Sobrecarga do operador de comparação de diferença
 */
template <typename T>
bool vector<T>::operator != ( const vector<T> v){
	/**
	 * Checa se o tamanho dos vetores é diferente
	 */
	if( size != v.size ){ 
		return true;
	} else {
		/**
		 * Iteração checa se há elementos (em mesma posição relativa) diferentes
		 */
		for( int i=0; i<size; i++ ){
			if ( data[i] != v.data[i] ){
				return true;
			}
		}
		return false;
	}
}
