#ifndef STACKAR_H
#define STACKAR_H

#include "stackar_exc.h"
#include "AbsStack.h"
#include "mapa.h"

/**
 * Classe implementada sobre a definição clássica da estrutura
 *de dados pilha, fazendo uma herança pública a partir da classe
 *AbsStack.
 */
namespace MyQueue{
template <typename T>
class StackAr : public AbsStack<T>
{
	public: 

        T *vetor;
		explicit StackAr(int tamanho = 5);
        void push ( const T & novo );
		const T & pop(void);
		void print(void);
/**
 * Função que indica o número de elementos presentes na pilha.
 * @return n número de elementos da pilha.
 */
		int size(void){return n;}

/**
 * Destrutora da classe StackAr.
 * Desaloca o espaço de memória ocupado pelo vetor de objetos genéricos.
 */
		~StackAr(void){delete []vetor;}

/**
 * Indica se a pilha está vazia ou não.
 * @return boole retorna um valor booleano indicando se a pilha está vazia ou não.
 */
        bool isEmpty (void) const{if (n == 0) return true; else return false;}

/**
 * Retorna o elemento do topo da pilha.
 * @return vetor[topo] elemento do topo da lista - último elemento inserido.
 */
        const T & top(void) const{return vetor[topo];}

/**
 * Função que faz a pilha voltar ao status vazio: nenhum elemento inserido.
 */
        void makeEmpty (void){topo = -1; n = 0;}
		const StackAr<T>& operator= (const StackAr<T>& p);
		StackAr(const StackAr<T>& p);	

	private:

		int topo;
		int n;
		int TAM;

};

#include"StackAr.cpp"

}

#endif
