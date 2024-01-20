
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <math.h>
#include <vector>

using namespace std;

int WINDOW_WIDTH = 720;
int WINDOW_HEIGHT = 480;

float sq_pos[] = { 0.0f, 0.0f };
float sq_rot = 0.0f;
float sq_scl = 1.0f;

const float pi = 3.14;

int r;

struct Point {
	float x, y;

	Point(float _x, float _y) : x(_x), y(_y) {}
};

vector<Point> controlPoints; 
bool curveComplete = false;

Point computeBezierPoint(float t) {
	vector<Point> tempPoints = controlPoints;

	while (tempPoints.size() > 1) {
		vector<Point> newPoints;
		for (size_t i = 0; i < tempPoints.size() - 1; ++i) {
			float x = (1 - t) * tempPoints[i].x + t * tempPoints[i + 1].x;
			float y = (1 - t) * tempPoints[i].y + t * tempPoints[i + 1].y;
			newPoints.push_back(Point(x, y));
		}
		tempPoints = newPoints;
	}

	// Check if tempPoints is not empty
	if (!tempPoints.empty()) {
		return tempPoints.front();
	}
	else {
		// Return a default Point if the vector is empty (this can be adjusted based on your requirements)
		return Point(0.0, 0.0);
	}
}

void drawBezierCurve() {
	glColor3f(1.0, 1.0, 1.0);  // Set color to white

	glBegin(GL_LINE_STRIP);
	for (float t = 0; t <= 1; t += 0.01) {
		Point p = computeBezierPoint(t);
		glVertex2f(p.x, p.y);
	}
	glEnd();
}

void drawControlPoints() {
	glColor3f(0.0, 1.0, 0.0);  // Set color to green for control points

	glPointSize(5.0);  // Set point size

	glBegin(GL_POINTS);
	for (const auto& point : controlPoints) {
		glVertex2f(point.x, point.y);
	}
	glEnd();

	glPointSize(1.0);  // Reset point size
}

void axes() {
	// x axis
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); // red
	glVertex2f(-10.0f, 0.0f);
	glVertex2f(10.0f, 0.0f);
	glEnd();

	// y axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glVertex2f(0.0f, 10.0f);
	glVertex2f(0.0f, -10.0f);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	axes();

	drawBezierCurve();
	drawControlPoints();

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
	// w = aspect_ratio * h
	// h = w / aspect_ratio

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		gluOrtho2D(-11, 11, -11 / aspect_ratio, 11 / aspect_ratio);
	}
	else {
		gluOrtho2D(-11 * aspect_ratio, 11 * aspect_ratio, -11, 11);
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 13) { // Enter key
		curveComplete = !curveComplete; // Toggle curve completion state
		if (curveComplete) {
			cout << "Bezier curve completed. Press Enter to start a new curve." << endl;
		}
	}
	if (key == 'c') { // 'c' key to clear control points
		controlPoints.clear();
		curveComplete = false;
		cout << "Control points cleared. Start a new curve." << endl;
	}
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		float normalizedX = (float)x / glutGet(GLUT_WINDOW_WIDTH);
		float normalizedY = 1.0 - (float)y / glutGet(GLUT_WINDOW_HEIGHT);

		controlPoints.push_back(Point(20.0 * normalizedX - 10.0, 20.0 * normalizedY - 10.0));
		glutPostRedisplay();
	}
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(500, 300);
	glutCreateWindow("2D Graphics Template");

	cout << "Use the mouse to click and add control points." << endl;
	cout << "Press Enter to complete the curve." << endl;
	cout << "Press 'c' to clear the control points." << endl;

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	init();
	glutMainLoop();

	return 0;
}