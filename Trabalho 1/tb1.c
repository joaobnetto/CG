#include "tb1.h"

// Função que é chamada pelo OpenGL e faz o desenho
void desenha()
{ 
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    // Canto inferior esquerdo
    glVertex3f((Triangulo.x[0]*escala)+tx, (Triangulo.y[0]*escala)+ty, Triangulo.z[0]*escala);
    // Canto inferior direito
    glVertex3f((Triangulo.x[1]*escala)+tx, (Triangulo.y[1]*escala)+ty, Triangulo.z[1]*escala);
    // Ponto superior.
    glVertex3f((Triangulo.x[2]*escala)+tx, (Triangulo.y[2]*escala)+ty, Triangulo.z[2]*escala);
    glEnd();
    glFlush();
}

// Inicializa parâmetros de rendering
void inicializa(){
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

// Função que é chamada pelo OpenGL quando o tamanho da janela é alterado. 
void alteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	view_w = w;
	view_h = h;
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-win, win, -win, win);
}

/* 
 * Função que rotaciona ao redor do eixo Z
 * @param angulo espera um valor real com o angulo de rotacao
 *
 * Nessa função a rotação é feita através de um ângulo theta qualquer a partir da origem.
 * A rotação segue o seguinte cálculo:
 * 	
 * x' = x * cos(theta) - y * sen(theta)
 * y' = y * sen(theta) + y * cos(theta)
 * 
 * Onde x e y são as coordenadas atuais de um determinado vértice antes da rotação.
 * E x' e y' são as novas coordenadas de um determinado vértice após a rotação.
 * x' e y' são representados por novoX e novoY, respectivamente.
 */
void rotacionar(double angulo){
	int i = 0;
	GLfloat novoX, novoY;
	double sen = sin(angulo), coss = cos(angulo);
	for(i = 0; i < Triangulo.nLados; ++i){
		/*Calcula as coordenadas x e y de acordo com os calculos da matriz de rotação*/
		novoX = Triangulo.x[i]*coss - Triangulo.y[i]*sen;
		novoY = Triangulo.x[i]*sen + Triangulo.y[i]*coss;
		Triangulo.x[i] = novoX;
		Triangulo.y[i] = novoY;
	}
}
// Função que gerencia eventos de teclado, chamada pelo OpenGL
void gerenciaTeclado(unsigned char key, int x, int y){
	switch (key) {
		// Aumenta a escala.
		case 'g':
		case 'G':
			escala += 0.5;
		break;
		// Diminui a escala
		case 'm':
		case 'M':
			escala = max(escala-0.5,0.5);
		break;
		// Rotaciona a imagem no sentido anti-horário pelo valor fixado.
		case 'r':
			rotacionar(valorRotacao);
			break;
		// Rotaciona a imagem no sentido horário pelo valor fixado.
		case 'R':
			rotacionar(-valorRotacao);
			break;
		// Translação pra esquerda.
		case 'a':
		case 'A':
			tx -= 0.25;	
		break;
		// Translação pra direita.
		case 'd':
		case 'D':
			tx += 0.25;
		break;
		// Translação pra cima.
		case 'w':
		case 'W':
			ty += 0.25;
		break;
		// Translação pra baixo.
		case 's':
		case 'S':
			ty -= 0.25;
		break;	
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){
    
    //Inicializacao de um triângulo
    Triangulo.nLados = 3;
    Triangulo.x[0] = 0.325;
    Triangulo.x[1] = 0.575;
    Triangulo.x[2] = 0.445;
    Triangulo.y[0] = 0.325;
    Triangulo.y[1] = 0.325;
    Triangulo.y[2] = 0.575;
    Triangulo.z[0] = 0.0;
    Triangulo.z[1] = 0.0;
    Triangulo.z[2] = 0.0;
    //-----------------------------------------------
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(0,0);
    glutCreateWindow ("Trabalho - Grupo 05");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glOrtho (0, 2, 0, 2, -2 ,2);
    glutDisplayFunc(desenha);
    glutReshapeFunc(alteraTamanhoJanela);
    glutKeyboardFunc(gerenciaTeclado);
    
    inicializa();
    glutMainLoop();
	return 0;
}