//#include <iostream>

// http://www.glfw.org/documentation.html

#include <GLFW/glfw3.h>
#include <math.h>

const int width = 1200;
const int height = 800;

// Color = (RED, GREEN, BLUE)
float* pixels = new float[width * height * 3];
//float* pixels

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

//void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
//{
//	for (int i = i0; i <= i1; i++)
//	{
//		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
//
//		drawPixel(i, j, red, green, blue);
//	}
//}

void drawLine(int i0, int j0, int i1, int j1, float red, float green, float blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawLineT(int i0, int j0, int i1, int j1, int t, float red, float green, float blue) {

	int x0 = i0;
	int y0 = j0;
	int x1 = i1;
	int y1 = j1;

	//float a = (i1 - i0) / (j1 - j0);

	for (int t1 = 0; t1 < t; t1++) {
//		x0 = ()
		drawLine(x0, y0, x1, y1, red, green, blue);
		x0 = x0 + 1;
		y0 = y0 - 1;
		x1 = x1 + 1;
		y1 = y1 - 1;
	}
}

void drawBox(int x0, int y0, int x1, int y1, int fill, float r, float g, float b) {

	for (int x = x0; x < x1; x++) {
		drawPixel(x, y0, r, g, b);
		drawPixel(x, y1, r, g, b);
	}
	for (int y = y0; y < y1; y++) {
		drawPixel(x0, y, r, g, b);
		drawPixel(x1, y, r, g, b);
	}

	if (fill == 1) {
		for (int x = x0; x < x1; x++)
			for (int y = y0; y < y1; y++)
				drawPixel(x, y, r, g, b);
	}
}

void drawTriangle(int* x, int* y, float r, float g, float b) {
	int p;
	for (p = 0; p < 2; p++) {
		drawLine(x[p], y[p], x[p + 1], y[p + 1], r, g, b);
	}
	drawLine(x[0], y[0], x[2], y[2], r, g, b);
}

void drawPentagon(int* x, int* y, float r, float g, float b) {
	int p;
	for (p = 0; p < 4; p++) {
		drawLine(x[p], y[p], x[p + 1], y[p + 1], r, g, b);
	}
	drawLine(x[4], y[4], x[0], y[0], r, g, b);
}

//void drawCircle(int x, int y, int r, float r, float g, float b) {
//
//	int d = 0;
//
//	const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
//
//	drawPixel()
//
//}

void draw() {

	const int i = 50, j = 50;

	pixels[(i + width * j) * 3 + 0] = 1.0f;
	pixels[(i + width * j) * 3 + 1] = 1.0f;
	pixels[(i + width * j) * 3 + 2] = 1.0f;
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Coloring Background
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++) {
				pixels[(i + width * j) * 3 + 0] = 1.0f;
				pixels[(i + width * j) * 3 + 1] = 1.0f;
				pixels[(i + width * j) * 3 + 2] = 1.0f;
			}


//		draw();
//		drawLine(10, 10, 50, 100, 1.0f, 0.0f, 0.0f);
		drawLineT(20, 500, 110, 700, 50, 1.0f, 0.0f, 0.0f);
		drawBox(500, 500, 700, 700, 0, 1.0f, 0.0f, 0.0f);
		drawBox(800, 500, 1000, 700, 1, 1.0f, 0.0f, 0.0f);

		int x[10];
		int y[10];

		x[0] = 50;
		y[0] = 50;
		x[1] = 200;
		y[1] = 200;
		x[2] = 350;
		y[2] = 50;

		drawTriangle(x, y, 1.0f, 0.0f, 0.0f);

		x[0] = 700;
		y[0] = 400;
		x[1] = 800;
		y[1] = 150;
		x[2] = 750;
		y[2] = 50;
		x[3] = 600;
		y[3] = 50;
		x[4] = 550;
		y[4] = 100;

		drawPentagon(x, y, 1.0f, 0.0f, 0.0f);
		//		drawCircle(900, 200, 100, 1.0f, 0.0f, 0.0f);


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels;

	return 0;
}
