#include <iostream>
#include "window.h"
#include "mouseevent.h"
#include "keyboardevent.h"
#include "windowevent.h"

namespace Core {
	Window::Window(const std::string& name, int width, int height) {
		init(name, width, height);

		setfnCallback([this](Event& e) -> void //window = window
		{
			if (e.getType() == Event::EventType::WINDOW_CLOSED_EVENT) glfwSetWindowShouldClose(window, GL_TRUE);
			std::cout << e.format() << std::endl;
		}); //lambda expression
	}

	void Window::init(const std::string& name, int width, int height) {
		this->name = name;
		this->width = width;
		this->height = height;

		if (!glfwInit()) {
			__asm__ (
				"int $3" //set breakpoint.
			);
		}

		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

		if (!window) {
			__asm__ (
				"int $3"
			);
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		glfwSetCursorPosCallback(window, mouseMovedCallBack);
		glfwSetScrollCallback(window, mouseScrollCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetKeyCallback(window, keyboardCallback);
		glfwSetWindowSizeCallback(window, windowResizedCallback);
		glfwSetWindowCloseCallback(window, windowClosedCallback);
	}
	
	void Window::mouseMovedCallBack(GLFWwindow* window, double x, double y) {
		Window& handle = *(Window*)glfwGetWindowUserPointer(window);
		MouseMovedEvent e(x, y);
		handle.fnCallback(e);
	};
	
	void Window::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		Window& handle = *(Window*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent e(xoffset, yoffset);
		handle.fnCallback(e);
	}

	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		Window& handle = *(Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS) {
			MouseButtonPressed e(button, mods);
			handle.fnCallback(e);
		}
		else if (action == GLFW_REPEAT) {
			printf("mouse repeat");
		}
		else {
			MouseButtonReleased e(button, mods);
			handle.fnCallback(e);
		}
	}
	
	void Window::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window& handle = *(Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS) {
			KeyPressedEvent e(key, mods);
			handle.fnCallback(e);
		}
		else if (action == GLFW_REPEAT) {
			KeyRepeatedEvent e(key, mods);
		}
		else {
			KeyReleasedEvent e(key, mods);
			handle.fnCallback(e);
		}
	}
	
	void Window::windowResizedCallback(GLFWwindow* window, int width, int height) {
		Window& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowResizedEvent e(width, height);
		handle.width = width;
		handle.height = height;
		handle.fnCallback(e);
	}

	void Window::windowClosedCallback(GLFWwindow* window) {
		Window& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowClosedEvent e;
		handle.fnCallback(e);
	}

	Window::~Window() {
		glfwWindowShouldClose(window);
	}
}