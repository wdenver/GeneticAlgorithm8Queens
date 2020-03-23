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

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT com um botão pressionado
void MoveMouseBotaoPressionado(int x, int y)
{
    // sprintf(texto, "Botao pressionado (%d,%d)", x, y);
    // glutPostRedisplay();
}

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT 
void MoveMouse(int x, int y)
{


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
           
// Gerenciamento do menu com as opções de cores           
void MenuMemoria(int op)
{
    
}           


// Gerenciamento do menu com as opções de cores           
void MenuNaval(int op)
{
  
}   
        
// Gerenciamento do menu principal           
void MenuPrincipal(int op)
{
    exit(0);
}
              
// Criacao do Menu
void CriaMenu() 
{
//     int menu,submenu1,submenu2;
//     submenu1 = glutCreateMenu(MenuMemoria);
//     glutAddMenuEntry("Facil",0);
//     glutAddMenuEntry("Difícil",1);
//     submenu2 = glutCreateMenu(MenuNaval);
//     glutAddMenuEntry("Pequeno (20x20)",0);
//     glutAddMenuEntry("Medio   (30x30)",1); 
//     glutAddMenuEntry("Grande  (40x40)",2);
//     glutAddMenuEntry("Gigante (50x50)",3);
//     glutAddMenuEntry("Revelar Embarcações",4);
//     menu = glutCreateMenu(MenuPrincipal);
//     glutAddSubMenu("Memoria",submenu1);
//     glutAddSubMenu("Batalha Naval",submenu2);
//     glutAddMenuEntry("Sair",0);  
//     glutAttachMenu(GLUT_RIGHT_BUTTON);
 }
       
           
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{        
    // if (button == GLUT_RIGHT_BUTTON)
    //      if (state == GLUT_DOWN) 
    //         CriaMenu();
    
    //  if (button == GLUT_LEFT_BUTTON)
    //      if (state == GLUT_DOWN){      
            
    //         }           
    // glutPostRedisplay();   
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
     sprintf(texto, "Click com o botao direito.");    
     glutInit ( &argc, argv );
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
     glutInitWindowSize(TELA_LARGURA,TELA_ALTURA);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Jogo da Memoria e Batalha Naval");
     glutDisplayFunc(Desenha);
     glutTimerFunc(10, Timer, 1);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutMotionFunc(MoveMouseBotaoPressionado); 
     glutPassiveMotionFunc(MoveMouse);
     glutMouseFunc(GerenciaMouse);    
     glutSpecialFunc(TeclasEspeciais); 
     Inicializa();
     glutMainLoop();
}
