/**
 * Classe genérica usada como base 
 * para a classe StackAr.
 */

template <class Object>

class AbsStack {

//friend class mapa;
public :

AbsStack ( ) { /* Empty */ } // Default constructor
virtual ~ AbsStack () { /* Empty */ } // Default destructor
// Basic members
virtual void push ( const Object & x ) = 0;
virtual const Object & pop(void) = 0;
virtual const Object & top(void) const = 0;

virtual bool isEmpty ( ) const = 0;
virtual void makeEmpty ( ) = 0;

private :

// Disable copy constructor
AbsStack ( const AbsStack & ) { /* Empty */ }
};
