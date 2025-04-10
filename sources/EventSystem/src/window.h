#pragma once
#include <string>
#include "GLFW/glfw3.h"
#include <functional>
#include "event.h"

namespace Core {
	class Window final {
	private:
		std::string name;
		int width, height;
		GLFWwindow* window = nullptr;
		std::function<void(Event&)> fnCallback;
	public:
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	private:
		Window(const std::string& name, int width, int height);
		~Window();
	public:
		static Window& getInstance() {
			static Window instance("Window", 1280, 720);
			return instance;
		}
	public:
		void init(const std::string& name, int width, int height);
		inline __attribute__ ((always_inline)) GLFWwindow* getGLFWwindow() const { return window; } //why it is can't be used __forceinline without msvc...
		void setfnCallback(const std::function<void(Event&)>& fn) { fnCallback = fn; }
	public:
		static void mouseMovedCallBack(GLFWwindow* window, double x, double y);
		static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void windowResizedCallback(GLFWwindow* window, int width, int height);
		static void windowClosedCallback(GLFWwindow* window);
	};
}