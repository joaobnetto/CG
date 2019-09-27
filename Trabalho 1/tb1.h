/* Trabalho 1 - Grupo 5
 * 1. Transformações de translação, escala e rotação 2D.
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max(x,y) (x > y ? x : y)

/* Base para a criação de poligonos
 * Vamos gerar um triângulo */
typedef struct coordenadasPoligono{
	int nLados;
	GLfloat x[3], y[3], z[3];
}coordenadasTriangulo;

coordenadasTriangulo Triangulo;
GLint view_w, view_h;
GLfloat xf, yf, win;
float escala = 1.0;
float tx = 1.0;
float ty = 1.0;
const double valorRotacao = 30.0;

void desenha();
void inicializa();
void alteraTamanhoJanela(GLsizei w, GLsizei h);
void rotacionar(double angulo);
void gerenciaTeclado(unsigned char key, int x, int y);