
#include "header1.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <windows.h>
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
        pozObs = vec3(pozObs.x + directie.x * incrementZoom,
            pozObs.y + directie.y * incrementZoom,
            pozObs.z + directie.z * incrementZoom);
        
    }
    else // zoom out
    {
        pozObs = vec3(pozObs.x - directie.x * incrementZoom,
            pozObs.y- directie.y * incrementZoom,
            pozObs.z- directie.z * incrementZoom);
    }

    viewMatrix = look;
    glutPostRedisplay();
}

float PanSensitivity = 0.001f;
float PanDx = 0.5f*PanSensitivity;
float PanDy= PanDx, PanDz= PanDx;

/// <summary>
/// 
/// </summary>
/// <param name="UpRight"></param>
/// spune daca sa faca pan pe up-down / right-left
/// <param name="dir"></param>
/// spune daca sa faca up sau down in functie de UpRight
void functiaPan(bool UpRight, bool dir)
{
    vec3 upIndif = vec3(0, 1, 0); 
    vec3 n = normalize(pozObs - punctObs); //n=normala
    vec3 r = cross(n,upIndif);  //r= right-left vector on the camera plane
    vec3 u = cross(n, r);  //r= up-down vector on the camera plane
    vec3 pan=PanVec;
    
    if (!dir)
    {
        pan *= -1;
    }

    if (UpRight) // up - down
    {
        vec3 delta = u * pan;
        pozObs += delta;
        punctObs += delta;
    }
    else // right - left
    {
        vec3 delta = r * pan;
        pozObs += delta;
        punctObs += delta;
    }
    afis();
}

void afis()
{
    viewMatrix = look;
    glutPostRedisplay();
}
void mouse_zoom(int button, int state, int x, int y)
{
    if (state == 1)
    {
        if (button == 3)
        {
            functiaZoom(true);
        }
        else if (button == 4)
        {
            functiaZoom(false);
        }
    }
}
bool leftPressed = false;
bool rightPressed = false;
int xpos, ypos;
void mouse_pan_continuu()
{
    
    functiaPan(0, 1);
    afis();
}


float xInit = 0, yInit = 0;
void mouse_pan(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON)
        leftPressed = (state == GLUT_DOWN);
    if (button == GLUT_RIGHT_BUTTON)
        rightPressed = (state == GLUT_DOWN);

    if(leftPressed && rightPressed)
    {
        xInit = x;
        yInit = y;
        glutIdleFunc(mouse_pan_continuu);
    }
    else
    {
        glutIdleFunc(NULL);
    }
    
    afis();
}
void mouse_miscare(int button, int state, int x, int y) {
  
    mouse_zoom(button, state, x, y);
    mouse_pan(button, state, x, y);
    
  
}
    

    
    


