
#pragma once
#include "header1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#define PI glm::pi<float>()

/*
viewMatrix este matricea transformarii de observare. Parametrii functiei

lookAt sunt trei vectori ce reprezinta, in ordine:
- pozitia observatorului
- punctul catre care priveste observatorul
- directia dupa care este orientat observatorul
*/

using namespace std;
GLuint shader_programme, vao;

glm::mat4 projectionMatrix, viewMatrix;

glm::vec3 pozObs= pozObss, punctObs= punctObss, rotDir= rotDirr;

float points[] = {
ox,oy,oz
};
float xv = 2, yv = 1, zv = 30; //originea sistemului de observare
float xObs=0, yObs=0, zObs=0;
float xDir = 0, yDir = 1, zDir = 0; //in picioare / cu fundul in sus

std::string textFileRead(char* fn)
{
	std::ifstream ifile(fn);
	std::string filetext;
	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		filetext.append(line + "\n");
	}
	return filetext;
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_programme);
	float rotationAngle = PI / 2;
	glm::mat4 modelMatrix=glm::mat4(1.0f);
	glBindVertexArray(vao);
	GLuint matrixID = glGetUniformLocation(shader_programme,
											"modelViewProjectionMatrix");
	//desenare axe coordonate
	glUniformMatrix4fv(matrixID, 1, GL_FALSE,
						glm::value_ptr(
							projectionMatrix *
							viewMatrix *
							modelMatrix));
	glDrawArrays(GL_LINES, 0, 6);

	//desenare cub in centrul sistemului de coordonate
	/*
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix *
		viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 0, 24);

	*/

	

	//desenare cub 2
	/*
	modelMatrix = glm::translate(. . .) * glm::scale(. . .);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix *
		viewMatrix * modelMatrix));
	glDrawArrays(GL_LINES, 0, 24);	
	*/

	//desenare cub 3
	
	//desenare cub 4

	glFlush();
}
void init()
{
	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	glClearColor(1, 1, 1, 0);
	glewInit();
	GLuint vbo = 1;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//modificat
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	std::string vstext = textFileRead("vertex.vert");
	std::string fstext = textFileRead("fragment.frag");
	const char* vertex_shader = vstext.c_str();
	const char* fragment_shader = fstext.c_str();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	projectionMatrix = glm::perspective(PI / 2, (float)w / h, 0.1f, 100.0f);
	/*
	viewMatrix este matricea transformarii de observare. Parametrii functiei

	lookAt sunt trei vectori ce reprezinta, in ordine:
	- pozitia observatorului
	- punctul catre care priveste observatorul
	- directia dupa care este orientat observatorul
	*/
	viewMatrix = glm::lookAt(pozObs,punctObs,rotDir);
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(700, 700);
	glutCreateWindow("SPG");
	init();
	glutDisplayFunc(display);
	
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse_miscare);
	
	glutMainLoop();
	return 0;
}