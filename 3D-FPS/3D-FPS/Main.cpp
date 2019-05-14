#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

float lastFrameTime;

int width = 1280;
int height = 720;

bool fill = TRUE;
bool perspective = TRUE;

bool keys[255];
bool justMovedMouse = false;

struct Camera
{
	float posX, posY, posZ, rotX, rotY;
} camera;

void initGL();

void onIdle();
void onDisplay();
void onKey(unsigned char keyId, int x, int y);
void onKeyUp(unsigned char keyId, int x, int y);
void onMousePassiveMotion(int x, int y);
void onMouse(int x, int y);
void onReshape(int w, int h);

void move(float angle, float fac);

int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
	glutCreateWindow("3D Graphics FPS Eindopdracht");

	glutIdleFunc(onIdle);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKey);
	glutKeyboardUpFunc(onKeyUp);
	glutPassiveMotionFunc(onMousePassiveMotion);
	
	glutWarpPointer(width / 2, height / 2);
	initGL();
	glutMainLoop();
}

void initGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0, 0.6, 0.8, 1.0);
}

void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, width / (float)height, 0.1f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(-camera.posX, -camera.posZ, -camera.posY);

	// Draw stuff

	glutSwapBuffers();
}

void onIdle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 6;
	if (keys[int('a')]) move(0, deltaTime * speed);
	if (keys[int('d')]) move(180, deltaTime * speed);
	if (keys[int('w')]) move(90, deltaTime * speed);
	if (keys[int('s')]) move(270, deltaTime * speed);
	if (keys[int(' ')]) camera.posZ += deltaTime * speed;
	if (keys[int('q')]) camera.posZ -= deltaTime * speed;

	glutPostRedisplay();
}

void move(float angle, float fac)
{
	camera.posX -= float(cos((camera.rotY + angle) / 180 * M_PI)) * fac;
	camera.posY -= float(sin((camera.rotY + angle) / 180 * M_PI)) * fac;
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
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		if (camera.rotX < -90)
			camera.rotX = -90;
		if (camera.rotX > 90)
			camera.rotX = 90;
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
