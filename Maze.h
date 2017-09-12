#ifndef MAZE_H_
#define MAZE_H_

#include "DisjSets.h"
#include "Cell.h"
#include "mapa.h"

class Maze{

	friend class mapa;
	public:
		Maze(int m = 20, int n = 33);
		~Maze();
		int GetNumLines();
		int GetNumColuns();
		int GetNumCells();
		
		void Connect( int a, int b );
		
		Cell & operator []( int index );
		
		void Generate();
		void GenerateValid();
		void PrintDSets();
	private:
		int NumLines;
		int NumColuns;
		Cell * maze;
		DisjSets disjSets;
};

#include "Maze.cpp"

#endif
