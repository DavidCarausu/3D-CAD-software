#pragma once
#ifndef H1
#define H1
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

extern glm::vec3 pozObs, punctObs, rotDir;
#define pozObss glm::vec3(xv, yv, zv) //poz camera
#define punctObss glm::vec3(xObs, yObs, zObs) //poz punct OBS
#define rotDirr glm::vec3(xDir, yDir, zDir) //rotatia acelei axe
#define look glm::lookAt(pozObs,punctObs,rotDir)
//definim normala pentru vcs:
#define NORMALA glm::vec3(xObs-xv, yObs-yv, zObs-zv)
#define incrementZoom 0.9f


#define origin 0.0f, 0.0f, 0.0f
#define ox  origin, 16.0f, 0.0f, 0.0f
#define oy  origin, 0.0f, 16.0f, 0.0f 
#define oz  origin, 0.0f, 0.0f, 16.0f 

extern float PanDx, PanDy, PanDz;
extern float PanSensitivity;
#define PanVec vec3(PanDx,PanDy,PanDz)

extern float xv , yv , zv ; //originea sistemului de observare
extern float xObs , yObs , zObs ;
extern float xDir , yDir , zDir ;
extern glm::mat4 projectionMatrix, viewMatrix;

//functii facute de mine
void functiaZoom(bool dir);
void mouse_miscare(int button, int state, int x, int y);
float modul(glm::vec3 vector);
void afis();


#endif