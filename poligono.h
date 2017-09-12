#ifndef POLIGONO_H
#define POLIGONO_H

/**
 * Classe corrspondente
 * aos pol�gonos a serem desenhados.
 */
class poligonoidiota
{
public:
/**
 * Construtor.
 */
    poligonoidiota(float i = 0, float j = 0, float a = 0.1)
    {
        x = j * a; // Coordenada x do pol�gono
        y = i * a; // Coordenada y do pol�gono
        edge = a;  // Tamamho da aresta no pol�gono  
        visitated = false;// Especifica cada pol�gono como n�o visitado.
        up=left=right=down = true;// Todas as paredes abertas.

    }

/**
 * Especifica o tamanho da aresta.
 * @param a tamanho da aresta.
 */
    void SetEdge(float a){edge = a;}    

/**
 * Especifica a coordenada x do pol�gono.
 * @param j N�mero da coluna correspondente
 * ao pol�gono na matriz.
 */
    void setx(int j){x = j * edge;}

/**
 * Especifica a coordenada y do pol�gono.
 * @param i N�mero da linha correspondente
 * ao pol�gono na matriz.
 */
    void sety(int i){y = i * edge;}
    
/**
 * Especifica a c�lula como visitada.
 */    
    void SetVisit(void){visitated = true;}

/**
 * Retorna verdadeiro caso a c�lula
 * j� tenha sido visitada e falso caso contr�rio.
 * @return visitated estado da c�lula.
 */
    bool WasVisitated(void){return visitated;}
         
/**
 * Fun��o que desenha um pol�gono simples
 * em OpenGL, utilizando as coordenadas (x,y)
 * e o tamanho da aresta do pol�gono.
 */ 
    void draw()
    {
       glLineWidth(3);// especifica largura da linha.

       glBegin(GL_LINES);

       glColor3f(0.0,0.0,0.0);// Linhas pretas.

           if(right){glVertex2f(x,y);glVertex2f(x + edge,y);}//lateral direita.

           if(down){glVertex2f(x + edge,y);glVertex2f(x + edge,y - edge);}// parte de baixo.

           if(left){glVertex2f(x + edge,y - edge); glVertex2f(x,y - edge);}// lateral esquerda.

           if(up){glVertex2f(x,y - edge); glVertex2f(x,y);}// parte de cima.

       glEnd();

    }
    
/**
 * Pinta a c�lula de vermelho.
 */
    void marca(void)
    {
       glBegin(GL_POLYGON);

           glColor3f(1.0f,0.0f,0.0f);
           glVertex2f(x,y); glVertex2f(x + edge,y);
           glVertex2f(x + edge,y - edge); glVertex2f(x,y - edge);

       glEnd();
    }
    
/**
 * Pinta a c�lula de amarelo.
 */
    void desmarca(void)
    {
       glBegin(GL_POLYGON);

           glColor3f(1.0f,1.0f,0.0f);

           glVertex2f(x,y); glVertex2f(x + edge,y);

           glVertex2f(x + edge,y - edge); glVertex2f(x,y - edge);

       glEnd();
    }
    
    /**
     * Retorna verdadeiro caso a parede
     * superior do pol�gono esteja aberta e
     * falso caso contr�rio.
     */
    bool IsUpOpen(void){return up;}
    
    /**
     * Retorna verdadeiro caso a parede
     * inferior do pol�gono esteja aberta e
     * falso caso contr�rio.
     */    
    bool IsDownOpen(void){return down;}
    
    /**
     * Retorna verdadeiro caso a parede
     * direita do pol�gono esteja aberta e
     * falso caso contr�rio.
     */
    bool IsRightOpen(void){return right;}
    
    /**
     * Retorna verdadeiro caso a parede
     * esquerda do pol�gono esteja aberta e
     * falso caso contr�rio.
     */
    bool IsLeftOpen(void){return left;}

    /**
     * Especifica a parede correspondente
     * como fechada (false) ou como aberta (true).
     * @param boolean estado da respectiva parede.
     */
    void SetUp(bool boolean){up = boolean;}

    /**
     * Especifica a parede correspondente
     * como fechada (false) ou como aberta (true).
     * @param boolean estado da respectiva parede.
     */
    void SetDown(bool boolean){down = boolean;}

    /**
     * Especifica a parede correspondente
     * como fechada (false) ou como aberta (true).
     * @param boolean estado da respectiva parede.
     */
    void SetLeft(bool boolean){left = boolean;}

    /**
     * Especifica a parede correspondente
     * como fechada (false) ou como aberta (true).
     * @param boolean estado da respectiva parede.
     */
    void SetRight(bool boolean){right = boolean;}            
    
private:

   /**
   * Itens j� explicados no construtor da classe.
   *
   */
   float x, y, edge;
   bool visitated,up,left,right,down;

};



#endif
