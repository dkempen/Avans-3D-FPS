#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>
#include "Components/GameObject.h"
#include "Components/CubeComponent.h"
#include "Components/PlayerComponent.h"

float lastFrameTime;
float deltaTime;

int width = 1280;
int height = 720;

bool fill = TRUE;
bool perspective = TRUE;

bool keys[255];
bool justMovedMouse = false;

std::vector<GameObject*> objects;
GameObject *player;

void initGL();
void initGame();

void onIdle();
void onDisplay();
void displayText();
void onKey(unsigned char keyId, int x, int y);
void onKeyUp(unsigned char keyId, int x, int y);
void onMousePassiveMotion(int x, int y);
void onMouse(int x, int y);
void onReshape(int w, int h);

void moveCamera(float angle, float fac);

int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
	glutCreateWindow("3D Graphics First Person Shooter");

	glutIdleFunc(onIdle);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKey);
	glutKeyboardUpFunc(onKeyUp);
	glutPassiveMotionFunc(onMousePassiveMotion);

	glutWarpPointer(width / 2, height / 2);
	initGL();
	initGame();
	glutMainLoop();
}

void initGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0, 0.6, 0.8, 1.0);
	glutSetCursor(GLUT_CURSOR_NONE);
}

void initGame()
{
	// Create player object
	player = new GameObject();
	player->addComponent(new PlayerComponent());
	player->position = Vec3f(0, 0, 0);
	objects.push_back(player);

	// Create cube in the center of the world
	GameObject* o = new GameObject();
	o->addComponent(new CubeComponent(0.5));
	o->position = Vec3f(0, 0, 0);
	objects.push_back(o);
}

void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, width / float(height), 0.1f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(player->rotation.x, 1, 0, 0);
	glRotatef(player->rotation.y, 0, 1, 0);
	glTranslatef(-player->position.x, -player->position.z, -player->position.y);

	// Draw stuff
	for (auto &o : objects)
		o->draw();

	displayText();

	glutSwapBuffers();
}

void displayText()
{
	// Create a string that displays the fps, current camera location and rotation 
	std::string text =
		"fps " + std::to_string(int(1 / deltaTime)) +
		"\nx " + std::to_string(player->position.x) +
		"\ny " + std::to_string(player->position.y) +
		"\nz " + std::to_string(player->position.z) +
		"\nX " + std::to_string(player->rotation.x) +
		"\nY " + std::to_string(player->position.z);

	int xpos = 20;
	int ypos = 30;
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glClearDepth(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glRasterPos2f(xpos, ypos);
	int len = text.length();
	for (int i = 0; i < len; i++)
	{
		if (text[i] == '\n')
		{
			ypos += 20;
			glRasterPos2f(xpos, ypos);
			continue;
		}
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void onIdle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	for (auto &o : objects)
		o->update(deltaTime);

	glutPostRedisplay();
}

void onKey(unsigned char keyId, int x, int y)
{
	if (keyId == VK_ESCAPE)
		exit(1);
	keys[keyId] = true;
}

void onKeyUp(unsigned char keyId, int x, int y)
{
	keys[keyId] = false;
}

void onMousePassiveMotion(int x, int y)
{
	auto dx = x - width / 2;
	auto dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
	{
		player->rotation.y += dx / 10.0f;
		player->rotation.x += dy / 10.0f;
		if (player->rotation.x < -90)
			player->rotation.x = -90;
		if (player->rotation.x > 90)
			player->rotation.x = 90;
		if (player->rotation.y > 360)
			player->rotation.y -= 360;
		if (player->rotation.y <= 0)
			player->rotation.y += 360;
	}
	if (!justMovedMouse)
	{
		glutWarpPointer(width / 2, height / 2);
		justMovedMouse = true;
	}
	else
		justMovedMouse = false;
}

void onReshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}
