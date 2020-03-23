#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>

#include "genetico.hpp"


#define TELA_LARGURA 700
#define TELA_ALTURA 500


int GameAtivo =-1;

char texto[30]; 

GLfloat win;

Genetico genetico;

int intVel = 100;
bool autoInc = false;


void Timer(int value)
{
   // update 
    glutPostRedisplay();
    glutTimerFunc(intVel,Timer, 1);  

    if(autoInc)
		genetico.novaIteracao();

}




// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    win=150.0f;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    genetico.inicializacao();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 

    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, 4, -2.5, 0.1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}



// Função callback chamada para gerenciar eventos do teclado   
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
        if(intVel >20)
        	intVel -= 10; 
        autoInc = true;
    }
    if(key == GLUT_KEY_DOWN) {
    	intVel += 10;
    	autoInc = true;
         
    }

    if(key == GLUT_KEY_RIGHT) {
    	autoInc = false;
    	genetico.iteracao();
    }




    glutPostRedisplay();
}
           


        
// Gerenciamento do menu principal           
void MenuPrincipal(int op)
{
    exit(0);
}
              
      
           
    
void Desenha(void){   

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();            
   glClear(GL_COLOR_BUFFER_BIT);     
   glColor4f(0.8,0.7,0.8,1); 
   genetico.DesenhaTela(); 
    glutSwapBuffers();    
}     
    
                      
// Programa Principal 
int main( int argc, char *argv[] )
{   
     glutInit ( &argc, argv );
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
     glutInitWindowSize(TELA_LARGURA,TELA_ALTURA);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Algorítimo genético 8 rainhas");
     glutDisplayFunc(Desenha);
     glutTimerFunc(10, Timer, 1);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutSpecialFunc(TeclasEspeciais); 
     Inicializa();
     glutMainLoop();
}
