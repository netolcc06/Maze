#ifndef CELL_H_
#define CELL_H_

#include "mapa.h"

class Cell{

    friend class mapa;

	public:
		Cell();
		bool ExistTop(){
			int test = Wall;
			test &= TopWall;
			if( test==TopWall )
				return true;
			else
				return false;
		}
		bool ExistRight(){
			int test = Wall;
			test &= RightWall;
			if( test==RightWall )
				return true;
			else
				return false;
		}
		bool ExistBottom(){
			int test = Wall;
			test &= BottomWall;
			if( test==BottomWall )
				return true;
			else
				return false;
		}
		bool ExistLeft(){
			int test = Wall;
			test &= LeftWall;
			if( test==LeftWall )
				return true;
			else
				return false;
		}

		/**
		 * Métodos para demolir as Paredes
		 */
		void DestroyLeft();
		void DestroyRight();
		void DestroyBottom();
		void DestroyTop();

		/**
		 * Métodos para construir as paredes
		 */ 
		void BuildLeft();
		void BuildRight();
		void BuildBottom();
		void BuildTop();
		
		int State();
		
		void Print();

	private:
		int Wall;

		static int TopWall;
		static int RightWall;
		static int BottomWall;
		static int LeftWall;
};

#include "Cell.cpp"

#endif
