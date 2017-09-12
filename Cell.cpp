#include "Cell.h"
#include <iostream>

using namespace std;

/**
 * Contrutor que cria célula com todas as paredes contruídas
 * OBS: 1111(binário) = 15(decimal)
 */
Cell::Cell(){
   Wall = 15;
}

/**
 * Declaração das varíaveis que representam as paredes da célula
 */
int Cell::TopWall = 0x01;
int Cell::RightWall = 0x02;
int Cell::BottomWall = 0x04;
int Cell::LeftWall = 0x08;


/**
 * Métodos que destroem as paredes da célula
 */
void Cell::DestroyTop(){
   Wall &= ~TopWall;
}

void Cell::DestroyRight(){
   Wall &= ~RightWall;
}

void Cell::DestroyBottom(){
   Wall &= ~BottomWall;
}

void Cell::DestroyLeft(){
   Wall &= ~LeftWall;
}

/**
 * Métodos para construção das paredes da célula
 */
void Cell::BuildTop(){
   Wall |= TopWall;
}

void Cell::BuildRight(){
   Wall |= RightWall;
}

void Cell::BuildBottom(){
   Wall |= BottomWall;
}

void Cell::BuildLeft(){
   Wall |= LeftWall;
}

/**
 * Método utilizado para verificar o estado da célula. p.e:
 *quais paredes estão destruídas
 */
int Cell::State(){
   return Wall;
}

/**
 * Método de teste para imprimir estado da célula
 */
void Cell::Print(){
   cout << Wall << endl;
}
