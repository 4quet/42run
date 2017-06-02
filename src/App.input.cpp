/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.input.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:02:36 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 16:35:18 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

GLboolean	App::isPressed(GLFWwindow *window, GLenum key) {
	if (glfwGetKey(window, key) == GLFW_PRESS && keys[key] != GLFW_PRESS)
		return true;
	return false;
}

void	App::jump() {
	if (onGround == true)
	{
		velocityY = -0.2f;
		onGround = false;
	}
}

void	App::moveLeft() {
	catModel = cat.getModelMatrix();
	if (catModel[3].x < 0.5f)
	{
		catModel = glm::translate(catModel, glm::vec3(1.0f, 0.0f, 0.0f));
		cat.setModelMatrix(catModel);
	}
}

void	App::moveRight() {
	catModel = cat.getModelMatrix();
	if (catModel[3].x > -0.5f)
	{
		catModel = glm::translate(catModel, glm::vec3(-1.0f, 0.0f, 0.0f));
		cat.setModelMatrix(catModel);
	}
}

void	App::resetGame() {
	speed = 0.002f;
	gameOver = false;
	paused = false;
	counter->reset(tm);
	initTables();
	initObstacles();
	initComputersSprites();
}

void	App::pause() {
	static GLfloat	savedSpeed;

	if (gameOver == false)
	{
		paused = !paused;
		if (paused == true)
			savedSpeed = speed;
		else
			speed = savedSpeed;
	}
}

void	App::handleInput(GLFWwindow *window) {
	glfwPollEvents();
	if (isPressed(window, GLFW_KEY_LEFT) && onGround && !paused)
		moveLeft();
	if (isPressed(window, GLFW_KEY_RIGHT) && onGround && !paused)
		moveRight();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		jump();
	if (isPressed(window, GLFW_KEY_R))
		resetGame();
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && keys[GLFW_KEY_P] != GLFW_PRESS)
		pause();
	for (int i = 0; i < 350; ++i)
		keys[i] = glfwGetKey(window, i);
}
