/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/05 13:40:17 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

App::App() {
}

void	App::drawSlice() {

	
}

void	App::start(GLFWwindow *window) {

	Shader shader;
	shader.link("shaders/vertex.glsl", GL_VERTEX_SHADER);
	shader.link("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	Camera camera(glm::vec3(0.0f, 3.0f, -8.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));
	camera.setPerspective(45.0f);

	shader.use();

	shader.addUniform("model");
	shader.addUniform("view");
	shader.addUniform("projection");

	shader.addUniform("offset");

	shader.setUniformMatrix(camera.view(), "view");
	shader.setUniformMatrix(camera.projection(), "projection");

	GLfloat speed = 0.005f;

	Plane		floor;
	glm::mat4	floorModel;

	floor.loadTexture("assets/darkfloor.png");
	floorModel = glm::scale(floorModel, glm::vec3(6.0f, 1.0f, 10.0f));
	floor.setModelMatrix(floorModel);

	Plane		leftWall;
	glm::mat4	leftWallModel;

	leftWall.loadTexture("assets/sandwall.png");
	leftWallModel = glm::translate(leftWallModel, glm::vec3(3.0f, 2.0f, 0.0f));
	leftWallModel = glm::rotate(leftWallModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	leftWallModel = glm::scale(leftWallModel, glm::vec3(4.0f, 1.0f, 10.0f));
	leftWall.setModelMatrix(leftWallModel);

	Plane		rightWall;
	glm::mat4	rightWallModel;

	rightWall.loadTexture("assets/sandwall.png");
	rightWallModel = glm::translate(rightWallModel, glm::vec3(-3.0f, 2.0f, 0.0f));
	rightWallModel = glm::rotate(rightWallModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rightWallModel = glm::scale(rightWallModel, glm::vec3(4.0f, 1.0f, 10.0f));
	rightWall.setModelMatrix(rightWallModel);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		floor.draw(shader, speed);
		leftWall.draw(shader, speed);
		rightWall.draw(shader, speed);

		glfwSwapBuffers(window);
	}	
}

App::~App() {

}
