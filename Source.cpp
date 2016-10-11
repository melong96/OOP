#include <iostream>
#include <vector>

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

void drawLine(int i0, int j0, int i1, int j1, float red, float green, float blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}



/*
class Line : public Object {
public:
	int x0, y0, x1, y1, thick;

	Line(int i0, int j0, int i1, int j1, int t, float red, float green, float blue) :
		x0(i0), y0(j0), x1(i1), y1(j1), thick(t) {}


	void draw() {

		for (int t1 = 0; t1 < thick; t1++) {
			//		x0 = ()
			drawLine(x0, y0, x1, y1, 1.0, 0.0, 0.0);
			x0 = x0 + 1;
			y0 = y0 - 1;
			x1 = x1 + 1;
			y1 = y1 - 1;
		}
	}
};
*/

class Box {

public:
	int x0, y0, x1, y1, fill;

	Box() 
	{
		x0 = 200, y0 = 500, x1 = 300, y1 = 600, fill = 0;
	}

	Box(int i0, int j0, int i1, int j1, int f, float red, float green, float blue) :
		x0(i0), y0(j0), x1(i1), y1(j1), fill(f) {}

	void draw() {
		for (int x = x0; x < x1; x++) {
			drawPixel(x, y0, 1.0, 0.0, 0.0);
			drawPixel(x, y1, 1.0, 0.0, 0.0);
		}
		for (int y = y0; y < y1; y++) {
			drawPixel(x0, y, 1.0, 0.0, 0.0);
			drawPixel(x1, y, 1.0, 0.0, 0.0);
		}

		if (fill == 1) {
			for (int x = x0; x < x1; x++)
				for (int y = y0; y < y1; y++)
					drawPixel(x, y, 1.0, 0.0, 0.0);
		}
	}
};


class Circle {

public:
	int center_x, center_y, radius;
	float dis;

	Circle() 
	{
		center_x = 600, center_y = 50, radius = 30;
	}

	Circle(int x, int y, int r) : center_x(x), center_y(y), radius(r) {}

	void draw() {
		for (int x = center_x - radius - 5; x < center_x + radius + 5; x++) {
			for (int y = center_y - radius - 5; y < center_y + radius + 5; y++) {
				dis = sqrt(pow((x - center_x), 2) + pow((y - center_y), 2));
				if(dis > radius - 1 && dis < radius + 1)
					drawPixel(x, y, 1.0, 0.0, 0.0);
			}
		}
	}
};

/*
class Triangle : public Object {

public:
	int px1, py1, px2, py2, px3, py3;

	Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : px1(x1), py1(y1), px2(x2), py2(y2), px3(x3), py3(y3) {}

	void draw() {
		drawLine(px1, py1, px2, py2, 1.0, 0.0, 0.0);
		drawLine(px1, py1, px3, py3, 1.0, 0.0, 0.0);
		drawLine(px2, py2, px3, py3, 1.0, 0.0, 0.0);
	}
};

class Pentagon : public Object {

public:
	int px1, py1, px2, py2, px3, py3, px4, py4, px5, py5;

	Pentagon(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5) 
		: px1(x1), py1(y1), px2(x2), py2(y2), px3(x3), py3(y3), px4(x4), py4(y4), px5(x5), py5(y5) {}

	void draw() {
		drawLine(px2, py2, px1, py1, 1.0, 0.0, 0.0);
		drawLine(px1, py1, px5, py5, 1.0, 0.0, 0.0);
		drawLine(px2, py2, px3, py3, 1.0, 0.0, 0.0);
		drawLine(px3, py3, px4, py4, 1.0, 0.0, 0.0);
		drawLine(px5, py5, px4, py4, 1.0, 0.0, 0.0);
	}

};

*/
class ObjectInterface {

public:

	virtual void draw() {}
};

template <class TYPE>
class Object : public ObjectInterface {

public:
//	virtual void draw() = 0;

	void draw() {
		TYPE obj;
		obj.draw();
	}

};








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

		// Object creation
		//Object* my_line = new Line(50, 600, 100, 650, 10, 1.0, 0.0, 0.0);
//		Box my_box(200, 500, 300, 600, 0, 1.0, 0.0, 0.0);
		//Object* my_box2 = new Box(500, 500, 600, 600, 1, 1.0, 0.0, 0.0);
		//Object* my_triangle = new Triangle(50, 50, 70, 70, 90, 50);
		//Object* my_pentagon = new Pentagon(300, 50, 250, 100, 350, 150, 400, 100, 350, 50);
		//Object* my_circle1 = new Circle(80, 620, 40);
		//Object* my_circle2 = new Circle(250, 550, 80);
		//Object* my_circle3 = new Circle(550, 550, 80);
		//Object* my_circle4 = new Circle(60, 60, 30);
		//Object* my_circle5 = new Circle(330, 90, 80);
		//Object* my_circle6 = new Circle(600, 50, 20);
//		Circle my_circle(600, 50, 30);

		std::vector<ObjectInterface*> obj_list;

		obj_list.push_back(new Object<Box>);
		obj_list.push_back(new Object<Circle>);


		// Draw function
		for (auto itr : obj_list) itr->draw();


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
