#ifndef POLIGONO_H
#define POLIGONO_H

/**
 * Classe corrspondente
 * aos polígonos a serem desenhados.
 */
class poligonoidiota
{
public:
/**
 * Construtor.
 */
    poligonoidiota(float i = 0, float j = 0, float a = 0.1)
    {
        x = j * a; // Coordenada x do polígono
        y = i * a; // Coordenada y do polígono
        edge = a;  // Tamamho da aresta no polígono  
        visitated = false;// Especifica cada polígono como não visitado.
        up=left=right=down = true;// Todas as paredes abertas.

    }

/**
 * Especifica o tamanho da aresta.
 * @param a tamanho da aresta.
 */
    void SetEdge(float a){edge = a;}    

/**
 * Especifica a coordenada x do polígono.
 * @param j Número da coluna correspondente
 * ao polígono na matriz.
 */
    void setx(int j){x = j * edge;}

/**
 * Especifica a coordenada y do polígono.
 * @param i Número da linha correspondente
 * ao polígono na matriz.
 */
    void sety(int i){y = i * edge;}
    
/**
 * Especifica a célula como visitada.
 */    
    void SetVisit(void){visitated = true;}

/**
 * Retorna verdadeiro caso a célula
 * já tenha sido visitada e falso caso contrário.
 * @return visitated estado da célula.
 */
    bool WasVisitated(void){return visitated;}
         
/**
 * Função que desenha um polígono simples
 * em OpenGL, utilizando as coordenadas (x,y)
 * e o tamanho da aresta do polígono.
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
 * Pinta a célula de vermelho.
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
 * Pinta a célula de amarelo.
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
     * superior do polígono esteja aberta e
     * falso caso contrário.
     */
    bool IsUpOpen(void){return up;}
    
    /**
     * Retorna verdadeiro caso a parede
     * inferior do polígono esteja aberta e
     * falso caso contrário.
     */    
    bool IsDownOpen(void){return down;}
    
    /**
     * Retorna verdadeiro caso a parede
     * direita do polígono esteja aberta e
     * falso caso contrário.
     */
    bool IsRightOpen(void){return right;}
    
    /**
     * Retorna verdadeiro caso a parede
     * esquerda do polígono esteja aberta e
     * falso caso contrário.
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
   * Itens já explicados no construtor da classe.
   *
   */
   float x, y, edge;
   bool visitated,up,left,right,down;

};



#endif
