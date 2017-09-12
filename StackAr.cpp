/**
 * Função para ordenar uma pilha usando apenas uma outra pilha.
 * @param *p ponteiro para a pilha genérica a ser ordenada.
 */


template < typename T>
void ordena(StackAr<T> *p){

	StackAr<T> aux( p->size() );
	int * temp = NULL;

	if( p->size() != 0){
		aux.push( p->pop() );
		while(p->size() != 0){
			while( p->size() != 0 && p->top()<aux.top() )
				aux.push( p->pop() );
			if( p->size() != 0 ){
				temp = new int;
				*temp = p->pop();
			}
			while( aux.size()>0 && temp!=NULL && aux.top()<*temp )
				p->push( aux.pop() );
			if( temp != NULL ){
				aux.push( *temp );
				delete temp;
				temp = NULL;
			}
		}
	}
	while( aux.size() != 0 )
		p->push( aux.pop() );
}

/**
 * Construtor da classe StackAr.
 * @param tamanho inteiro que representa o tamanho do vetor.
 * Todas as variáveis são inicializadas com o padrão de uma pilha vazia.
 */
template <typename T>
StackAr<T> :: StackAr(int tamanho){
	TAM = tamanho;
	topo = -1; 
	n = 0;
	vetor = new T[TAM];
}

/**
 * Função da classe StackAr que retira retorna o último elemento nela inserido.
 * Caso a StackAr esteja vazia, uma exceção é disparada.
 * @return vetor[topo+1] elemento retirado da StackAr.
 */

template <typename T>
const T & StackAr<T> :: pop(void){
	if(n == 0){
		throw StackUnderflowException("Underflow\n"); 
	}
	topo--;     
	n--;
	return vetor[topo+1];

}

/**
 * Função que insere um novo elemento na StackAr. Caso a StackAr esteja
 * cheia, uma exceção é disparada.
 * @param novo elemento a ser inserido na StackAr.
 */
template <typename T>
void StackAr<T> :: push(const T & novo){
	if(topo < TAM){
		topo++;
		vetor[topo] = novo;
		n++;
	} else throw StackOverflowException("Overflow\n");
}

/**
 * Função que imprime todos os elementos contidos na StackAr
 */
template <typename T>
void StackAr<T> :: print(void){
	for(int i = topo;i >=0; i--)
		cout << vetor[i] << " ";
}

/**
 * Função que sobrecarrega o operador de igualdade para 
 * objetos da classe StackAr.
 * Todos os campos de um objeto são copiados para outro.
 * @p objeto da classe StackAr que terá seus campos copiados.
 * @return *this permite que o operador de igualdade seja utilizado para
 * múltiplas atribuições: A = B = C.
 */
template<typename T>
const StackAr<T>& StackAr<T> :: operator= (const StackAr<T> &p){

		vetor = new T[p.TAM];
		topo = p.topo;
		n = p.n;
		TAM = p.TAM;

        for(int i=0; i<n;i++)
			vetor[i] = p.vetor[i];

		return *this;

}

/**
 * Função do construtor de cópia para a classe StackAr.
 */
template<typename T>
StackAr<T>::StackAr(const StackAr<T>& p){

		vetor = new T[p.TAM];
		topo = p.topo;
		n = p.n;
		TAM = p.TAM;

        for(int i=0; i<n;i++)
			vetor[i] = p.vetor[i];

}



