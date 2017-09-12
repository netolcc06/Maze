#ifndef VECTOR_H_
#define VECTOR_H_

template <typename T>
class vector{
	
	public:
		vector( int n = 5 );
		vector( const vector<T> & copy );
		~vector();
		int Length ( void );
		void InsertFront( T a );
		void InsertBack( T a );
		void Remove( T a );
		void ReSize( int newsize );
		void Print();
		T & operator []( int index );
		vector<T> operator +( const vector<T> v );
		void operator =( const vector<T> v);
		bool operator ==( const vector<T> v); 
		bool operator !=( const vector<T> v);
	
	private:
		T * data;
		int size;
};

#include "vector.cpp"

#endif
