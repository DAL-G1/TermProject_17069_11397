#include <vector>
#include <iostream>
#include "SolidSphere.h"
#include "Light.h"

using namespace std;

#define WIDTH 600
#define HEIGHT 600

#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2

vector<SolidSphere> spheres;
Light* light;

void init() {
	//light = new Light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
	light->setAmbient(0.5, 0.5, 0.5, 1.0);
	light->setDiffuse(0.7, 0.7, 0.7, 1.0);
	light->setSpecular(1.0, 1.0, 1.0, 1.0);

	SolidSphere sphere1(50, 100, 100);
	sphere1.setCenter(0, -200, 0);
	sphere1.setVelocity(5, 5, 0);
	spheres.push_back(sphere1);

	SolidSphere sphere2(sphere1);
	sphere2.setCenter(100, 200, 0);
	sphere2.setVelocity(-7, 4, 0);
	spheres.push_back(sphere2);

	SolidSphere sphere3(sphere1);
	sphere2.setCenter(-100, 0, 0);
	sphere2.setVelocity(10, -10, 0);
	spheres.push_back(sphere2);
}

void idle() {
	// collision handling
	for (int i = 0; i < spheres.size(); i++)
		for (int j = i + 1; j < spheres.size(); j++)
			spheres[i].collisionHandling(spheres[j]);

	/* Implementation: boundary check */

	for (int i = 0; i < spheres.size(); i++) {
		//upper
		if (spheres[i].getProperties()[0] + spheres[i].getCenter()[1] > boundaryY) {
			spheres[i].setVelocity(spheres[i].getVelocity()[0], -spheres[i].getVelocity()[1], spheres[i].getVelocity()[2]); 
		}

		//lower
		if (-spheres[i].getProperties()[0] + spheres[i].getCenter()[1] < -boundaryY) {
			spheres[i].setVelocity(spheres[i].getVelocity()[0], -spheres[i].getVelocity()[1], spheres[i].getVelocity()[2]);
		}

		//right
		if (spheres[i].getProperties()[0] + spheres[i].getCenter()[0] > boundaryX) {
			spheres[i].setVelocity(-spheres[i].getVelocity()[0], spheres[i].getVelocity()[1], spheres[i].getVelocity()[2]);
		}

		//left
		if (-spheres[i].getProperties()[0] + spheres[i].getCenter()[0] < -boundaryX) {
			spheres[i].setVelocity(-spheres[i].getVelocity()[0], spheres[i].getVelocity()[1], spheres[i].getVelocity()[2]);
		}
	}
	glutPostRedisplay();
	/*for (int i = 0; i < spheres.size(); i++) {
		spheres[i].move();
	}*/
}

void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	light->draw();

	/*int a = 1;
	auto& b = a;*/
	for (auto& sph : spheres)
		//위와 같은 이유로, for (auto& sph : spheres)를 사용하면 안됨. 값의 복사가 일어나기떄문
		//따라서, &를 붙여줘서 복사자를 사용해야함.
	{
		sph.draw();
		sph.move();
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(650, 300);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Move spheres and handle collisions");
	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
