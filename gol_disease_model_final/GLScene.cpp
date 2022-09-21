#include "GLScene.h"


int size = 400;

int window_width;
int window_height;
int g_GLUTWindowHandle;
int g_ErrorCode;
float y_offset;
float x_offset;
float scal = 0.0f;

float rot_x = 0.1f;
float rot_y = 0.7f;
float rot_z = 0.3f;
float rot_angle = 0.1f;
bool b_rot = true;
bool sim = false;
bool shade = false;
int time_e = clock();

bool graphic = true;


unsigned int mode = 4;
float tick = 0.0f;

unsigned int time_offset = 10;


Life* life = new Life(size, size, mode);


Scene g_current = scene1;

void GLScene(int argc, char* argv[])
{
	GLScene(900, 900, argc, argv);
}

void GLScene(int x, int y, int argc, char* argv[])
{
	DWORD currentTime = GetTickCount64() % 1000;
	srand(currentTime);
	//for (int i = 0; i < 10000; i++)
	//{
	//	int x = rand() % size + 1;
	//	int y = rand() % size + 1;
	//	life->setLife(x, y, 1);
	//}

	if (mode != 4)
	{
		for (int i = 0; i < 4000; i++)
		{
			int x = rand() % (size + 1);
			int y = rand() % (size + 1);
			life->setLife(x, y, 0);
		}
	}
	else
	{
		for (int i = 0; i < 5000; i++)
		{
			int x = rand() % (size + 1);
			int y = rand() % (size + 1);
			life->setLife(x, y, life->healthy_threshold - 1);
		}
	}

	if (graphic == true) 
	{
		cout << glutGet(GLUT_ELAPSED_TIME) << endl;
		window_height = y;
		window_width = x;

		glutInit(&argc, argv);

		glutInitWindowPosition(30, 30);
		glutInitWindowSize(window_width, window_height);

		window_width = glutGet(GLUT_SCREEN_WIDTH);
		window_height = glutGet(GLUT_SCREEN_HEIGHT);

		glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);


		g_GLUTWindowHandle = glutCreateWindow("Conway's Game of Life");
		glutInitWindowSize(window_width, window_height);

		displaytext();


		glutDisplayFunc(DisplayGL);
		glutKeyboardFunc(KeyboardGL);
		glutReshapeFunc(ReshapeGL);


		glClearColor(0.056f, 0.072f, 0.103f, 1.00f);
		glClearDepth(1.0f);
		glShadeModel(GL_SMOOTH);

	}
	else
	{

		std::cout << "INITIALIZED" << std::endl;
		int i = 0;
		while (i <= 100)
		{
			life->update_main(mode);
			i++;
		}
		life->export_data();
		life->~Life();
		std::cout << "finished" << std::endl;
	}
}

void displaytext()
{
	const unsigned char string[] = "The quick god jumps over the lazy brown fox.";
	int w;
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string);
 
	glRasterPos2f(0.7, 0);
	int len = sizeof(string)/sizeof(unsigned char);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (int)string);
	}
}

void Cleanup()
{
	if (g_GLUTWindowHandle != 0)
	{
		glutDestroyWindow(g_GLUTWindowHandle);
		g_GLUTWindowHandle = 0;
	}
	if (false)
	{
		exit(g_ErrorCode);
	}

}

void newLife()
{
	// ew--calling a destructor
	life->~Life();
	life = new Life(size, size, mode);

	if (mode == 1 || mode == 2)
	{
		for (int i = 0; i < .3 * size * size; i++)
		{
			int x = rand() % size + 1;
			int y = rand() % size + 1;
			life->setLife(x, y, 1);
		}
	}

	else if (mode == 3)
	{
		for (int i = 0; i < .05 * size * size; i++)
		{
			int x = rand() % size + 1;
			int y = rand() % size + 1;
			life->setLife(x, y, life->healthy_threshold);
		}
	}

	else if (mode == 4)
	{
		for (int i = 0; i < .05 * size * size; i++)
		{
			int x = rand() % size + 1;
			int y = rand() % size + 1;
			life->setLife(x, y, life->healthy_threshold-1);
		}
	}

	else if (mode == 5)
	{
		for (int i = 0; i < .3 * size * size; i++)
		{
			int x = rand() % size + 1;
			int y = rand() % size + 1;
			life->setLife(x, y, 1);
		}
	}


}


void DisplayGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displaytext();
	if (g_current == 0)
	{
		render();
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void KeyboardGL(unsigned char c, int x, int y)
{
	if (c == ' ')
	{
		sim = !sim;
	}

	if (c == 'n')
	{
		newLife();
	}

	//brian brain
	if (c == '1')
	{
		mode = 1;
	}

	//gol
	if (c == '2')
	{
		mode = 2;
	}

	//gol infect
	if (c == '3')
	{
		mode = 3;
	}
	if (c == '4')
	{
		mode = 4;
	}

	if (c == '5')
	{
		mode = 5;
	}

	if (c == 'd')
	{
		life->disease(1000);
	}
	if (c == 'p')
	{
		std::cout << "------------------------" << std::endl;
		std::cout << "IMMUNE POPULATION: " <<life->count_immune(mode) <<std::endl;
		std::cout << "DISEASE POPULATION: "<<life->count_sick(mode) << std::endl;
		std::cout << "SUSCEPTIBLE POPULATION:" << life->count_susceptible(mode) << std::endl;
		std::cout << "------------------------" << std::endl;

	}
	if (c == 'l')
	{
		unsigned int offsetX = 0;
		unsigned int offsetY = 0;

		for (int i = 0; i< 7; i ++)
		{ 
			life->glider(20+ offsetY, 20);
			offsetX += 20;
			offsetY += 40;
		}
		
	}
	if (c == 'c')
	{
		life->clear();
	}

	if (c == 's')
	{
		
		time_offset += 10;
		if (time_offset >= 100)
			time_offset = 0;
	}

	if (c == 'r')
	{
		life->export_data();
	}

	if (c == '	')
	{
		if (g_current == scene1)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			(g_current = scene2);
		}
		else
			if (g_current == scene2)
			{
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				g_current = scene1;
			}
	}

}

void ReshapeGL(int w, int h)
{
	//std::cout << "ReshapGL( " << w << ", " << h << " );" << std::endl;

	if (h == 0)										// Prevent A Divide By Zero error
	{
		h = 1;										// Making Height Equal One
	}

	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);

	// Setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)window_width / (GLdouble)window_height, 0.1, 100.0);

	//render();
	glutPostRedisplay();
}

void render_mode(unsigned int mode, float off, float x_t, float y_t)
{
	glBegin(GL_QUADS);
	if (mode == 4)
	{
		for (int i = 0; i < size; i++)
		{
			x_t = 0.0f;
			for (int j = 0; j < size; j++)
			{
				int a = life->getLifeform(j + 1, i + 1);

				if (a < life->healthy_threshold && a > life->disease_threshold)
				{
					//yellow
					glColor3f((100.0f / 255.0f), (100.0f / 255.0f), (50.0f / 255.0f));
					glVertex2f(x_t - off, y_t + off);
					glVertex2f(x_t + off, y_t + off);
					glVertex2d(x_t + off, y_t - off);
					glVertex2d(x_t - off, y_t - off);
				}
				if (a > life->immune_threshold && a <= life->disease_threshold)
				{
					//red
					glColor3f((200.0f / 255.0f), (50.0f / 255.0f), (100.0f / 255.0f));
					glVertex2f(x_t - off, y_t + off);
					glVertex2f(x_t + off, y_t + off);
					glVertex2d(x_t + off, y_t - off);
					glVertex2d(x_t - off, y_t - off);
				}
				if (a == life->immune_threshold)
				{
					//green
					glColor3f(100.0f / 255.0f, 200.0f / 255.0f, 100.0f / 255.0f);

					glVertex2f(x_t - off, y_t + off);
					glVertex2f(x_t + off, y_t + off);
					glVertex2d(x_t + off, y_t - off);
					glVertex2d(x_t - off, y_t - off);
				}

				x_t += (500 / (float)size) * 0.02f;
			}
			y_t += (500 / (float)size) * 0.02f;
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			x_t = 0.0f;
			for (int j = 0; j < size; j++)
			{
				int a = life->getLifeform(j + 1, i + 1);
				if (a == 1)
				{
					glColor3f(100.0f / 255.0f, 200.0f / 255.0f, 100.0f / 255.0f);

					glVertex2f(x_t - off, y_t + off);
					glVertex2f(x_t + off, y_t + off);
					glVertex2d(x_t + off, y_t - off);
					glVertex2d(x_t - off, y_t - off);
				}
				if (a == 2)
				{
					glColor3f((0.0f / 255.0f), (150.0f / 255.0f), (150.0f / 255.0f));
					glVertex2f(x_t - off, y_t + off);
					glVertex2f(x_t + off, y_t + off);
					glVertex2d(x_t + off, y_t - off);
					glVertex2d(x_t - off, y_t - off);
				}
				if (a > 2)
				{
					glColor3f((220.0f / 255.0f), (50.0f / 255.0f), (50.0f / 255.0f));
					glVertex2f(x_t - off, y_t + off);
					glVertex2f(x_t + off, y_t + off);
					glVertex2d(x_t + off, y_t - off);
					glVertex2d(x_t - off, y_t - off);
				}

				x_t += (500 / (float)size) * 0.02f;
			}
			y_t += (500 / (float)size) * 0.02f;
		}
	}

	glEnd();
	glPopMatrix();
}

void render()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float y_t = 0.0f;
	float x_t = 0.0f;
	float off = 500 / (float)size * 0.01f;

	float tick = 0;
	float r;
	float g;
	float b;

	//glScalef(1.0f+scal, 1.0f+scal, 1.0f+scal);
	glTranslatef(-5.0f + x_offset, -5.0f + y_offset, -9.0f + scal);
	//glTranslatef(-0.5f, -0.5f, 0.0f);

	//GLfloat cyan[] = { (169.0f / 255.0f), (234.0f / 255.0f), (123.0f / 255.0f), 1.f };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);


	//if (life->count >= 255)
	//{
	//	life->count = 0;
	//}
	//g = float(life->count) / 255.0f;

	render_mode(mode, off, x_t, y_t);
	if (sim == true)
	{
		if ((int)(clock() - time_e) > time_offset)
		{
			time_e = clock();
			life->update_main(mode);

		}
	}
}
