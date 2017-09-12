#ifndef STACK_EXC 
#define STACK_EXC 

/**
 * Classe genérica, usada para a chamada de exceções.
 */
class OutOfBoundsException
 {
     public :
         OutOfBoundsException (const  string&  msg = " " ) : message ( msg ){}
         virtual ~ OutOfBoundsException ( )
             { }
         virtual string toString ( ) const {
			return what();
		}
         virtual string what ( ) const
             { return message ; }

    	 private :
         string message;
 };

/**
 * Classe definida para o caso de exceção provocado pela tentativa de inclusão
 *de um objeto em uma pilha cheia. 
 */
class StackOverflowException : public OutOfBoundsException
{
public:
StackOverflowException ( const string&  msg = " " ) : OutOfBoundsException ( msg ){ }

};

/**
 * Classe definida para o caso de exceção provocado pela tentativa de retirada
 *de um objeto em uma pilha vazia. 
 */
class StackUnderflowException : public OutOfBoundsException
{

public:
StackUnderflowException ( const string&  msg = " " ) : OutOfBoundsException ( msg ){ }

};

#endif
