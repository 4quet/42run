/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/15 16:31:24 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

#define TN 10

App::App() {
	glm::mat4	catModel;

	catModel = glm::translate(catModel, glm::vec3(0.0f, 0.5f, -23.0f));
	catModel = glm::rotate(catModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	cat.setModelMatrix(catModel);
}

void	App::handleInput(GLFWwindow *window) {
	glm::mat4	catModel = cat.getModelMatrix();

	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && keys[GLFW_KEY_LEFT] != GLFW_PRESS)
	{
		catModel = glm::translate(catModel, glm::vec3(1.0f, 0.0f, 0.0f));
		cat.setModelMatrix(catModel);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && keys[GLFW_KEY_RIGHT] != GLFW_PRESS)
	{
		catModel = glm::translate(catModel, glm::vec3(-1.0f, 0.0f, 0.0f));
		cat.setModelMatrix(catModel);
	}

	for (int i = 0; i < 350; ++i)
	{
		keys[i] = glfwGetKey(window, i);
	}
}

void	App::start(GLFW & glfw) {

	GLFWwindow	*window = glfw.getWindow();

	Shader shader;
	shader.link("shaders/vertex.glsl", GL_VERTEX_SHADER);
	shader.link("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	GLfloat speed = 0.001f;
	GLfloat depth = 50.0f;

	GLfloat mv = -speed * depth;
	std::cout << "mv: " << mv << std::endl;

	GLfloat camZ = -30.0f;

	GLfloat	floorWidth = 30.0f;
	GLfloat	wallsHeight = 50.0f;

	Camera camera(glm::vec3(0.0f, 3.0f, camZ),
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

	Table	*rightTables[TN];
	Table	*leftTables[TN];
	for (int i = 0; i < TN; ++i)
		leftTables[i] = new Table(glm::vec3(floorWidth / 2.0f - 6.0f, 0.0f, 5.0f * (GLfloat)i));
	for (int i = 0; i < TN; ++i)
		rightTables[i] = new Table(glm::vec3(-(floorWidth / 2.0f - 6.0f), 0.0f, 5.0f * (GLfloat)i));

	Plane	comp[TN];
	glm::mat4	compModel[TN];

	for (int i = 0; i < TN; ++i)
	{
		comp[i].loadTexture("assets/comp.png", GL_RGBA);
		compModel[i] = glm::translate(compModel[i], glm::vec3(floorWidth / 2.0f - 4.0f, 1.6f, 5.0f * (GLfloat)i));
		compModel[i] = glm::rotate(compModel[i], glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		comp[i].setModelMatrix(compModel[i]);
	}

	Plane	comp2[TN];
	glm::mat4	compModel2[TN];

	for (int i = 0; i < TN; ++i)
	{
		comp2[i].loadTexture("assets/comp.png", GL_RGBA);
		compModel2[i] = glm::translate(compModel2[i], glm::vec3(floorWidth / 2.0f - 8.0f, 1.6f, 5.0f * (GLfloat)i));
		compModel2[i] = glm::rotate(compModel2[i], glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		comp2[i].setModelMatrix(compModel2[i]);
	}


	Table	table(glm::vec3(floorWidth / 2.0f - 6.0f, 0.0f, 0.0f));
	Table	table2(glm::vec3(-(floorWidth / 2.0f - 6.0f), 0.0f, 0.0f));


	Plane		floor;
	glm::mat4	floorModel;

	floor.loadTexture("assets/darkfloor.png", GL_RGB);
	floorModel = glm::scale(floorModel, glm::vec3(floorWidth, 1.0f, depth));
	floor.setModelMatrix(floorModel);

	Plane		leftWall;
	glm::mat4	leftWallModel;

	leftWall.loadTexture("assets/sandwall.png", GL_RGB);
	leftWallModel = glm::translate(leftWallModel, glm::vec3(floorWidth / 2.0f, wallsHeight / 2.0f, 0.0f));
	leftWallModel = glm::rotate(leftWallModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	leftWallModel = glm::scale(leftWallModel, glm::vec3(wallsHeight, 1.0f, depth));
	leftWall.setModelMatrix(leftWallModel);

	Plane		rightWall;
	glm::mat4	rightWallModel;

	rightWall.loadTexture("assets/sandwall.png", GL_RGB);
	rightWallModel = glm::translate(rightWallModel, glm::vec3(-floorWidth / 2.0f, wallsHeight/ 2.0f, 0.0f));
	rightWallModel = glm::rotate(rightWallModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rightWallModel = glm::scale(rightWallModel, glm::vec3(wallsHeight, 1.0f, depth));
	rightWall.setModelMatrix(rightWallModel);

	GLfloat current;
	GLfloat	last = 0.0f;
	GLfloat delta;
	int count = 0;
	int steps[] = { 0, 1, 2, 1 };

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		handleInput(window);

		current = glfwGetTime();
		delta = current - last;

		if (delta >= 0.2f)
		{
			count++;
			cat.loadTexture("assets/bwcat" + std::to_string(steps[count % 4]) + ".png", GL_RGBA);
			last = current;
		}

		floor.draw(shader, speed);
		leftWall.draw(shader, speed);
		rightWall.draw(shader, speed);

		for (int i = 0; i < TN; ++i)
			leftTables[i]->draw(shader, speed, depth);
		for (int i = 0; i < TN; ++i)
			rightTables[i]->draw(shader, speed, depth);

		
		for (int i = 0; i < TN; ++i)
		{
			compModel[i] = glm::translate(compModel[i], glm::vec3(0.0f, mv, 0.0f));
			if (compModel[i][3].z < camZ)
				compModel[i] = glm::translate(compModel[i], glm::vec3(0.0f, depth, 0.0f));
			comp[i].setModelMatrix(compModel[i]);
			comp[i].draw(shader, 0);
		}

		for (int i = 0; i < TN; ++i)
		{
			compModel2[i] = glm::translate(compModel2[i], glm::vec3(0.0f, mv, 0.0f));
			if (compModel2[i][3].z < camZ)
				compModel2[i] = glm::translate(compModel2[i], glm::vec3(0.0f, depth, 0.0f));
			comp2[i].setModelMatrix(compModel2[i]);
			comp2[i].draw(shader, 0);
		}

		cat.draw(shader, 0.0f);


		glfwSwapBuffers(window);
	}	
}

App::~App() {

}
