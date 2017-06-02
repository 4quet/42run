/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLFW.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 16:11:59 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

void GLFW::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	(void)scancode;
	(void)mode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
} 

GLFW::GLFW() {
	init();
}

GLFWwindow *	GLFW::getWindow() const {
	return _window;
}

void	GLFW::init() {
	int width, height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "42run", NULL, NULL);
	if (_window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(_window);
	glfwGetFramebufferSize(_window, &width, &height);
	glfwSetKeyCallback(_window, key_callback); 

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, width, height);
}

GLFW::~GLFW() {
	glfwTerminate();
}
