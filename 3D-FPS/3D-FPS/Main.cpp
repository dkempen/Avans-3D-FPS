#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Math/Vec.h"
#include "Components/Control/PlayerComponent.h"
#include <sstream>
#include <iomanip>
#include "Data/DataManager.h"

// Window, keys and mouse
int width = 1280;
int height = 720;

// Key and mouse input
bool keys[255];
bool leftMouse;
Vec2f cursorOffset;
bool justMovedMouse = false;

// Clock
std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
float deltaTime;

// Game
GameLogic gameLogic;

// Function declarations
void initGL();
void initData();

void onIdle();
void onDisplay();

void onKey(unsigned char keyId, int x, int y);
void onKeyUp(unsigned char keyId, int x, int y);
void onMotion(int x, int y);
void onMousePassiveMotion(int x, int y);
void onMouse(int button, int state, int x, int y);
void onReshape(int w, int h);

void displayText();

int main(int argc, char *argv[])
{
	// Glut setup
	std::cout << "Hello World!" << std::endl;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
	glutCreateWindow("3D Graphics First Person Shooter - Daan van Kempen 2019");
	glutFullScreen();

	// Callback functions
	glutIdleFunc(onIdle);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKey);
	glutKeyboardUpFunc(onKeyUp);
	glutPassiveMotionFunc(onMousePassiveMotion);
	glutMotionFunc(onMotion);
	glutMouseFunc(onMouse);

	// Inits
	glutWarpPointer(width / 2, height / 2);
	initGL();
	initData();
	glutMainLoop();
}

void initGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f, 0.6f, 0.8f, 1.0f);
	glutSetCursor(GLUT_CURSOR_NONE);
	reinterpret_cast<BOOL(WINAPI*)(int)>(wglGetProcAddress("wglSwapIntervalEXT"))(0);
}

void initData()
{
	DataManager::getInstance().init();
	gameLogic.init();
}

void onDisplay()
{
	// Standard operations
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, width / float(height), 0.1f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set camera position
	auto player = gameLogic.getPlayer();
	glRotatef(player->rotation.x, 1, 0, 0);
	glRotatef(player->rotation.y, 0, 1, 0);
	glRotatef(player->rotation.z, 0, 0, 1);
	glTranslatef(
		player->position.x,
		player->position.y + player->getComponent<PlayerComponent>()->headHeight,
		player->position.z);

	//Lighting
	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat matShininess[] = { 50.0 };
	GLfloat lightPosition[] = { -5.0, -2.0, -5.0, 0.0 };
	GLfloat lightAmbient[] = { 0.0, 0.0, 0.0, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	// Draw stuff
	gameLogic.draw();
	displayText();

	glutSwapBuffers();
}

void displayText()
{
	// Create a string that displays the fps, current camera location, rotation and velocity
	const auto player = gameLogic.getPlayer();
	std::stringstream ss;
	ss << std::fixed << std::setprecision(5) <<
		"fps " + std::to_string(int(1 / deltaTime)) <<
		"\npx " + std::to_string(player->position.x) <<
		"\npy " + std::to_string(player->position.y) <<
		"\npz " + std::to_string(player->position.z) <<
		"\n\nrx " + std::to_string(player->rotation.x) <<
		"\nry " + std::to_string(player->rotation.y) <<
		"\n\nvx " + std::to_string(player->velocity.x) <<
		"\nvy " + std::to_string(player->velocity.y) <<
		"\nvz " + std::to_string(player->velocity.z);
	auto text = ss.str();

	const auto xPos = 20;
	auto yPos = 30;
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
	glRasterPos2f(GLfloat(xPos), GLfloat(yPos));
	const auto len = int(text.length());
	for (auto i = 0; i < len; i++)
	{
		if (text[i] == '\n')
		{
			yPos += 20;
			glRasterPos2f(GLfloat(xPos), GLfloat(yPos));
			continue;
		}
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void onIdle()
{
	// Get elapsed time
	const auto frameTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> elapsed = frameTime - lastFrameTime;
	deltaTime = elapsed.count() / 1000.0f;
	lastFrameTime = frameTime;
	if (deltaTime <= 0 || deltaTime > 1)
		return;

	// Update stuff
	gameLogic.update(deltaTime);

	cursorOffset = { 0, 0 };
	glutPostRedisplay();
}

void onKey(const unsigned char keyId, int x, int y)
{
	if (keyId == VK_ESCAPE)
		exit(1);
	keys[keyId] = true;
}

void onKeyUp(const unsigned char keyId, int x, int y)
{
	keys[keyId] = false;
}

void onMotion(const int x, const int y)
{
	onMousePassiveMotion(x, y);
}

void onMousePassiveMotion(const int x, const int y)
{
	// Get cursor offset
	const auto dx = x - width / 2.0f;
	const auto dy = y - height / 2.0f;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
		cursorOffset = { dx, dy };
	if (!justMovedMouse)
	{
		glutWarpPointer(width / 2, height / 2);
		justMovedMouse = true;
	}
	else
		justMovedMouse = false;
}

void onMouse(const int button, const int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		leftMouse = !state;
}

void onReshape(const int w, const int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}
