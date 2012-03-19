#include "gb_screen.h"

#include <GL/glfw.h>

GLuint gb_screen_texture;

gb_error gb_screen_init() {
	glfwInit();

	if (!glfwOpenWindow(256, 256, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
		return GB_ERROR_SCREEN_FAILURE;

	glfwSetWindowTitle("gbem");

	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glGenTextures(1, &gb_screen_texture);
	glBindTexture(GL_TEXTURE_2D, gb_screen_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return GB_ERROR_OK;
}

void gb_screen_draw(const unsigned char *buffer) {
	glClear(GL_COLOR_BUFFER_BIT);

	glTexImage2D(GL_TEXTURE_2D, 0, 1, 256, 256, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(0, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, 1);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(1, 1);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(1, 0);
	glEnd();

	glfwSwapBuffers();
}
