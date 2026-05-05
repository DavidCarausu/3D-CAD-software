
#include "header1.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
using namespace std;
using namespace glm;

float modul(vec3 vector)
{
	return sqrt(vector.x * vector.x + 
				vector.y * vector.y + 
				vector.z * vector.z);
}
/// <summary>
/// aici calculam directia normalei (1 normala, 2 modulul, 3 normalizat)
/// adaugam pe directia normalei la xObs + dir.x * incrementZoom; si la restul y z
/// </summary>
/// <param name="dir"></param>
void functiaZoom(bool dir)
{
    vec3 normala = NORMALA; // 1
    float modulNormala = modul(normala); //2
    vec3 directie = normala / modulNormala; // 3 

    if (dir) // zoom in
    {
        xv += directie.x * incrementZoom;
        yv += directie.y * incrementZoom;
        zv += directie.z * incrementZoom;
    }
    else // zoom out
    {
        xv -= directie.x * incrementZoom;
        yv -= directie.y * incrementZoom;
        zv -= directie.z * incrementZoom;
    }

    viewMatrix = look;
    glutPostRedisplay();
}
void afis()
{
    viewMatrix = look;
    glutPostRedisplay();
}
void mouse_miscare(int button, int state, int x, int y) {
	if (state = 1)
	{
		if (button == 3)
		{
		
			functiaZoom(true);
		}
		else if(button == 4)
		{

			
			functiaZoom(false);
		}

	} 
    if (button == GLUT_LEFT_BUTTON && state=1)
    {

        {
            cout << "up";
            viewMatrix = translate(viewMatrix, vec3(5.0, 0.0, 0.5));
            afis();
        }
    }
}