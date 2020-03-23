/**************************
 * Includes
 *
 **************************/

//#include <windows.h>
#include <GL/gl.h>
#include "GL/glut.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>




#define NPOPULACAO 36

struct MM{
      int ponteiro;
      int valor;
}; 

 int compare (const void * a, const void * b){ 
    const MM *ia = (const MM *)a; // casting pointer types
    const MM *ib = (const MM *)b;     
    return ( ia->valor -ib->valor );
}



class Genetico
{

public:

/**************************
 * Function Declarations
 *
 **************************/
int tabuleiroDesenha[12][10];


int nPopulacao;
int fatorMutacao;
int marcacao;
int populacao[NPOPULACAO][8];
int novaPopulacao[NPOPULACAO][8];
int valor[NPOPULACAO];
int preSelecionados[4];
int selecionados[4];           //4 por vez
int cruzados[4][8];            //4 por vez
int Velocidade;
int altomatico;
bool acabou;

int tabFim;



Genetico(){
    nPopulacao =NPOPULACAO;
    fatorMutacao = 2;
    Velocidade = 10;
    altomatico = false;
    acabou = false;
    tabFim = -1;
}





void inicializacao(){
     marcacao = 0;
   srand(time(NULL));
   
   //quantos tabuleiros serao testados
    for(int i = 0;i < nPopulacao;i++){
       for(int j = 0;j < 8;j++){
          populacao[i][j] = rand()%8;
       }
    }
       //pontua as populacoes
       pontuacao();
}

void pontuacao(){
     
    //loop iniciara aqui
   for(int i = 0;i < nPopulacao;i++){
      valor[i] = 0;
   }
     
     
   for(int i = 0;i < nPopulacao;i++){
       for(int j = 0;j < 8;j++){
          for(int k = 0;k < 8;k++){
             if(j != k){
               //horizontal
               if(populacao[i][j] == populacao[i][k]){
                  valor[i]++;
               }
              
               if(abs(populacao[i][j]-populacao[i][k]) == abs(j-k) ){
               //   cout << populacao[i][j] << " e " << j << " cruza " << populacao[i][j+k] << " e " << j + k <<endl;
                  valor[i]++;   
               } 
            
            }
         }
      }
   }
}


void selecao(){

   tabuleiroDesenha[0][8] = preSelecionados[0];
   tabuleiroDesenha[1][8] = preSelecionados[1];
   tabuleiroDesenha[2][8] = preSelecionados[2];
   tabuleiroDesenha[3][8] = preSelecionados[3];
   
   for(int i = 0 ; i < 4;i++)
   for(int j = 0 ; j < 8; j++)
    tabuleiroDesenha[i][j] = populacao[tabuleiroDesenha[i][8]][j];  
}



void cruzamento(){
     
   int sorte = rand()%2;
   
   for(int i = 0;i < 4;i++){
   
            if (sorte == 0){
            
                 cruzados[0][i]   = populacao[preSelecionados[0]][i];
                 cruzados[0][i+4] = populacao[preSelecionados[1]][i+4];                     
                 tabuleiroDesenha[4][8] = 0;
                 tabuleiroDesenha[4][9] = 1;
                 
                 
                 cruzados[1][i]   = populacao[preSelecionados[1]][i];
                 cruzados[1][i+4] = populacao[preSelecionados[0]][i+4];                     
                 tabuleiroDesenha[5][8] = 1;
                 tabuleiroDesenha[5][9] = 0;
                 
                 
                 cruzados[2][i]   = populacao[preSelecionados[2]][i];
                 cruzados[2][i+4] = populacao[preSelecionados[3]][i+4];                     
                 tabuleiroDesenha[6][8] = 2;
                 tabuleiroDesenha[6][9] = 3;
                 
                 
                 cruzados[3][i]   = populacao[preSelecionados[3]][i];
                 cruzados[3][i+4] = populacao[preSelecionados[2]][i+4];                     
                 tabuleiroDesenha[7][8] = 3;
                 tabuleiroDesenha[7][9] = 2;
               
            }else
            if(sorte==1){
                
                 cruzados[0][i]   = populacao[preSelecionados[0]][i];
                 cruzados[0][i+4] = populacao[preSelecionados[2]][i+4];                     
                 tabuleiroDesenha[4][8] = 0;
                 tabuleiroDesenha[4][9] = 2;
                 
                 
                 cruzados[1][i]   = populacao[preSelecionados[2]][i];
                 cruzados[1][i+4] = populacao[preSelecionados[0]][i+4];                     
                 tabuleiroDesenha[5][8] = 2;
                 tabuleiroDesenha[5][9] = 0;
                 
                 
                 cruzados[2][i]   = populacao[preSelecionados[1]][i];
                 cruzados[2][i+4] = populacao[preSelecionados[3]][i+4];                     
                 tabuleiroDesenha[6][8] = 1;
                 tabuleiroDesenha[6][9] = 3;
                 
                 
                 cruzados[3][i]   = populacao[preSelecionados[3]][i];
                 cruzados[3][i+4] = populacao[preSelecionados[1]][i+4];                     
                 tabuleiroDesenha[7][8] = 3;
                 tabuleiroDesenha[7][9] = 1;
             
                        
            }
   }
     
   
   
   for(int i = 0 ; i < 4;i++)
   for(int j = 0 ; j < 8; j++)
    tabuleiroDesenha[i+4][j] = cruzados[i][j];  
   
}

void mutacao(){
   for(int j = 0;j < fatorMutacao;j++){
      for(int i = 0;i < 4;i++){
         cruzados[i][rand()%8] = rand()%8;
      }
   }
   
   for(int i = 0 ; i < 4;i++)
   for(int j = 0 ; j < 8; j++)
    tabuleiroDesenha[i+8][j] = cruzados[i][j];
   
}

void preencheNovaPopulacao(){
   for(int j = marcacao;j < (marcacao + 4);j++){
      for(int i = 0;i < 8;i++){
         novaPopulacao[j][i] = cruzados[j-marcacao][i];
      }
   }
}

void iteracao(){
    //while(marcacao < nPopulacao){//necessario para preencher nova populacao
       //pre-seleciona quatro
       
if(acabou)
  return;

       
    if( marcacao < nPopulacao){
       MM menores[nPopulacao];
       //ordena com menores recebendo valores
       for(int j = 0;j < nPopulacao;j++){
          menores[j].ponteiro = j;     
          menores[j].valor = valor[j];
       }
       
       qsort (menores, nPopulacao, sizeof(MM), compare);



 
       preSelecionados[0] = menores[marcacao/4].ponteiro;
       preSelecionados[1] = menores[marcacao/4+1].ponteiro;
       preSelecionados[2] = menores[marcacao/4+2].ponteiro;
       preSelecionados[3] = menores[marcacao/4+3].ponteiro;

          //selecionados escolhidos
          selecao();
   
    
          //cruzamento
          cruzamento();
          
          
    
          //mutacao
          mutacao();
    
          //preencher novaPopulacao
          preencheNovaPopulacao();
          
          
        /*  for(int i = 0;i < nPopulacao;i++){
                   cout << i << ":  ";
              for(int j = 0;j < 8;j++){
                 cout << novaPopulacao[i][j] << " ";
              }
              cout  << endl;
           }
           cout << endl;
          cout << "m " << marcacao << endl; */
           
          marcacao += 4;  
           
    } else
    {      marcacao = 0;
    
           for(int j = 0;j < nPopulacao;j++){
             for(int i = 0;i < 8;i++){
                populacao[j][i] = novaPopulacao[j][i];
                novaPopulacao[j][i]=0;
             }
           }
           
               
          
           //pontua as populacoes
           pontuacao();
           
           
          for(int i = 0; i < nPopulacao;i++){
          if(valor[i] == 0){
            tabFim = i;
            acabou = true;
             return ;
             } 
          }
               
           
    }
}
//--------------------------------------------------------------------------------









/**************************
 * WinMain
 *
 **************************/ 
 
void DesenhaRainha(float x, float y ){
  
  glPushMatrix ();
  glTranslatef(x*0.1+0.01,y*0.1+0.01,0);
 
  glScalef(0.08,0.09,1);
   // glColor3f (1.0f, 1.0f, 1.0f);   
    //glBegin (GL_TRIANGLE_STRIP);
    glBegin (GL_LINE_STRIP);
 //  glVertex2f (0.5, 0.5);
  
    glVertex2f (0.5, 1.0);
    glVertex2f (0.6, 0.9);
    glVertex2f (0.8, 0.9);
    glVertex2f (0.7, 0.8);
    glVertex2f (0.7, 0.7);
    glVertex2f (0.8, 0.6);
    glVertex2f (0.7, 0.5);
    glVertex2f (0.8, 0.2);
    glVertex2f (1.0, 0.1);
    glVertex2f (1.0, 0.0);
    
    glVertex2f (0.0, 0.0);
    glVertex2f (0.0, 0.1);
    glVertex2f (0.2, 0.2);
    glVertex2f (0.3, 0.5);
    glVertex2f (0.2, 0.6);
    glVertex2f (0.3, 0.7);
    glVertex2f (0.3, 0.8);
    glVertex2f (0.2, 0.9);
    glVertex2f (0.4, 0.9);
    glVertex2f (0.5, 1.0);
       
    
   glEnd (); 
  glPopMatrix ();
     
} 
 
void DesenhaTabuleiro(float x , float y , int tabuleiro[],int tipo1,int tipo2 ){

    glPushMatrix ();
    glTranslatef(x,y,0);
    glScalef(0.5,0.5,0);

    for (int i=0; i < 8 ; i++)
    for (int j=0; j < 8 ; j++)
    {   
        if ((i+j)%2==0)
          glColor3f (0.5f, 0.5f, 0.5f);
        else
          glColor3f (0.0f, 0.0f, 0.0f);   
        glBegin (GL_QUADS);
              glVertex2f (0.1*i    , 0.1*j);
              glVertex2f (0.1*(i+1), 0.1*j);
              glVertex2f (0.1*(i+1), 0.1*(j+1));
              glVertex2f (0.1*i    , 0.1*(j+1));
        glEnd ();
    }
    
        glColor3f (1.0f, 1.0f, 1.0f);   
        glBegin (GL_LINE_STRIP);
              glVertex2f (0.0  , 0.0);
              glVertex2f (0.8  , 0.0);
              glVertex2f (0.8  , 0.8);
              glVertex2f (0.0  , 0.8);
              glVertex2f (0.0  , 0.0);
        glEnd ();
       
    

    if (tipo1 == 0)
     glColor3f (1.0f, 1.0f, 1.0f);
    else   
    if (tipo1 == 1)  
     glColor3f (1.0f, 1.0f, 0.0f);
    else
    if (tipo1 == 2)   
     glColor3f (1.0f, 0.0f, 0.0f);
    else
     if (tipo1 == 3)   
     glColor3f (0.0f, 1.0f, 0.0f);
    
    DesenhaRainha(0,7-tabuleiro[0]);  
    DesenhaRainha(1,7-tabuleiro[1]);  
    DesenhaRainha(2,7-tabuleiro[2]);  
    DesenhaRainha(3,7-tabuleiro[3]);
    
    
     if (tipo2 == 0)
     glColor3f (1.0f, 1.0f, 1.0f);
    else   
    if (tipo2 == 1)  
     glColor3f (1.0f, 1.0f, 0.0f);
    else
    if (tipo2 == 2)   
     glColor3f (1.0f, 0.0f, 0.0f);
    else
     if (tipo2 == 3)   
     glColor3f (0.0f, 1.0f, 0.0f);
   
       
    DesenhaRainha(4,7-tabuleiro[4]);  
    DesenhaRainha(5,7-tabuleiro[5]);  
    DesenhaRainha(6,7-tabuleiro[6]);  
    DesenhaRainha(7,7-tabuleiro[7]);  
    
    glColor3f (1.0f, 1.0f, 1.0f); 

    glTranslatef(0.01,-0.1,0);
    glRasterPos2f(0, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'[');
    for (int j=0; j < 8 ; j++){
       
     
      
       
         
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,tabuleiro[j]+'0');
      if (j<7)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,',');
    }
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,']');

        
    glPopMatrix (); 
} 


void DesenhaPopulacao(float x, float y , int populacao[][8], bool ponto){
     
     
  glPushMatrix ();
  glTranslatef(x,y,0);
  glScalef(0.5,0.5,0);
  
  
  
   for (int i=0; i < nPopulacao ; i++){
   glColor3f (1.0f, 0.8f, 0.0f);     
     if (ponto){  
       glPushMatrix ();
       glTranslatef(-0.2,-0.13*i,0);
       glRasterPos2f(0, 0);
            char p[3] ;
            sprintf(p, "%d", valor[i]);    
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,p[0]);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,p[1]);    
        glPopMatrix ();  
     } 
       
        glColor3f (1.0f, 1.0f, 1.0f); 
        glPushMatrix ();
        glTranslatef(0.0,-0.13*i,0);
        glRasterPos2f(0, 0);
       
        
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'[');
        
        for (int j=0; j < 8 ; j++){
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,populacao[i][j]+'0');
          if (j<7)
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,',');
        }
        
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,']');
        glPopMatrix (); 
   }   
    
   glPopMatrix ();     
     
}


void DesenhatabuleiroGrande(int t){ 
     
     static int tab;
         
     glPushMatrix (); 
     glScalef(5,5,0);
     DesenhaTabuleiro(0.1,-0.4,populacao[tab],0,0);   
     glPopMatrix (); 
}


void DesenhaTela(){



  if(acabou){
    DesenhatabuleiroGrande(tabFim);
    return;
  }


  float I_PopulacaoI_x     = 0.1;
  float I_PopulacaoF_x     = 3.4;
  float I_Populacao_y      = -0.13;
  float I_Selecao_x        = 1.0f;
  float I_Cruzamento_x     = 1.8;
  float I_Mutacao_x        = 2.5;
  float I_espaco_tabuleiro = 0.5;
  float I_Tabuleiro_y      = -0.7;
  float I_NumSelecao       = 4;
  float I_largura_Tab      = 0.4;
 // float I_Altura_Tab       = 0.4;
  float I_larguraPop       = 0.53;
  

     
 
  glClearColor (0.3f, 0.3f, 0.3f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);
  
  glPushMatrix ();
 // glTranslatef(0,300,0);
  //glScalef(0.5,0.8,0);
  
  
  
  glColor3f (0.6f, 0.8f, 0.3f);
  glPushMatrix ();
  glTranslatef(0.0,0,0);
  glRasterPos2f(0, 0);
                char* p = (char*) "Aperte a tecla LEFT para no iteracao ou as telacas Up(+) ou Down(-) para controlar a velocidade de iteracao ";
                while (*p != '\0') {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
                }  
  glPopMatrix ();  
  
            
             
  DesenhaPopulacao(I_PopulacaoI_x,I_Populacao_y,populacao,true);              
  
  
  
  
  //selecao---------------------------------------------------------------------              
  for(int i = 0 ; i < I_NumSelecao;i++){
        glColor3f (1.0f, 1.0f, 0.0f); 
        glBegin (GL_LINES);
                    glVertex2f (I_PopulacaoI_x+I_larguraPop , -tabuleiroDesenha[i][8]*0.065+I_Populacao_y);
                    glVertex2f (I_Selecao_x-0.01  ,I_largura_Tab/2+ I_Tabuleiro_y-I_espaco_tabuleiro*i);           
        glEnd ();
        DesenhaTabuleiro(I_Selecao_x,I_Tabuleiro_y - I_espaco_tabuleiro*i,tabuleiroDesenha[i],i,i); 
  }
  
  
  
  //reprodução------------------------------------------------------------------ 
  for(int i = 0 ; i < I_NumSelecao;i++){  
        glColor3f (1.0f, 1.0f, 0.0f); 
        glBegin (GL_LINES);              
                    glVertex2f (I_Selecao_x+I_largura_Tab                       ,I_largura_Tab/2+  I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][8]);
                    glVertex2f ((I_Selecao_x+I_largura_Tab +I_Cruzamento_x)/2.1 ,I_largura_Tab/2+  ((I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][8])+(I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][9]))/2);
                    glVertex2f ((I_Selecao_x+I_largura_Tab +I_Cruzamento_x)/2.1 ,I_largura_Tab/2+  ((I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][8])+(I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][9]))/2);
                    glVertex2f (I_Selecao_x+I_largura_Tab                       ,I_largura_Tab/2+  I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][9]);            
                    glVertex2f ((I_Selecao_x+I_largura_Tab +I_Cruzamento_x)/2.1 ,I_largura_Tab/2+  ((I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][8])+(I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][9]))/2);
                    glVertex2f ((I_Selecao_x+I_largura_Tab +I_Cruzamento_x)/1.9 ,I_largura_Tab/2+  ((I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][8])+(I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][9]))/2);           
                    glVertex2f ((I_Selecao_x+I_largura_Tab +I_Cruzamento_x)/1.9 ,I_largura_Tab/2+  ((I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][8])+(I_Tabuleiro_y - I_espaco_tabuleiro*tabuleiroDesenha[i+4][9]))/2);
                    glVertex2f (I_Cruzamento_x ,I_largura_Tab/2+ I_Tabuleiro_y - I_espaco_tabuleiro*i);                      
        glEnd ();         
         
        DesenhaTabuleiro(I_Cruzamento_x,I_Tabuleiro_y - I_espaco_tabuleiro*i,tabuleiroDesenha[i+4],tabuleiroDesenha[i+4][8],tabuleiroDesenha[i+4][9]); 
  }
  
  
  //mutacao---------------------------------------------------------------------             
  for(int i = 0 ; i < I_NumSelecao;i++){  
        glColor3f (1.0f, 1.0f, 0.0f); 
        glBegin (GL_LINES);              
                    glVertex2f (I_Cruzamento_x+I_largura_Tab , I_Tabuleiro_y+I_largura_Tab/2 - I_espaco_tabuleiro*i);
                    glVertex2f (I_Mutacao_x , I_Tabuleiro_y +I_largura_Tab/2  - I_espaco_tabuleiro*i);
                                        
        glEnd ();             
         
        DesenhaTabuleiro(I_Mutacao_x,I_Tabuleiro_y - I_espaco_tabuleiro*i,tabuleiroDesenha[i+8],0,0); 
  }
  
  int Iteracao = marcacao-4; 
  if (Iteracao < 0)
    Iteracao = 0;
  
  for(int i = 0 ; i < I_NumSelecao;i++){
      glColor3f (1.0f, 1.0f, 0.0f); 
      glBegin (GL_LINES);
                  glVertex2f (I_PopulacaoF_x, -((Iteracao)+i)*0.065+I_Populacao_y);
                  glVertex2f (I_Mutacao_x+I_largura_Tab  ,I_largura_Tab/2+ I_Tabuleiro_y - I_espaco_tabuleiro*i);           
      glEnd ();
  }
  
  
  DesenhaPopulacao(I_PopulacaoF_x,I_Populacao_y,novaPopulacao,false);  
  
                  
  glPopMatrix ();     
        
}


void ProgramaIniciado(){
  
  inicializacao();      
}


void  novaIteracao(){

 if (acabou==false)
   iteracao();
    
}
};