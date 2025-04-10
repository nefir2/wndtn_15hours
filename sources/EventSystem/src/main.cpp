#include <iostream>
#include <GLFW/glfw3.h>
#include "window.h"

using namespace Core;

int main() {
	Window& window = Window::getInstance();

	while (!glfwWindowShouldClose(window.getGLFWwindow())) {
		glfwPollEvents();
		glfwSwapBuffers(window.getGLFWwindow());
	}

	return 0;
}