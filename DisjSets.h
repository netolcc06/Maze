#ifndef DISJSETS_H_
#define DISJSETS_H_

#include "vector.h"

class DisjSets{
	public:
		DisjSets( int n = 5 );
		DisjSets( const DisjSets& a );
		int Find( int n );
		void Union( int a, int b );
		void ReSize( int n );
		int NumOfSets();
		int & operator []( int index );
		bool operator ==( const DisjSets a );
		bool operator !=( const DisjSets a );
		void Print();
		
	private:
		vector<int> v;
};

#include "DisjSets.cpp"

#endif
