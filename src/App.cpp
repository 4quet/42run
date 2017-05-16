/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/16 16:57:29 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

App::App() {
	glm::mat4	catModel;

	catModel = glm::translate(catModel, glm::vec3(0.0f, 0.5f, -23.0f));
	catModel = glm::rotate(catModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	cat.setModelMatrix(catModel);

	velocityY = 0.0f;
	gravity = 0.01f;
	onGround = true;

	speed = 0.002f;
	depth = 50.0f;
	floorWidth = 30.0f;
	wallsHeight = 50.0f;
	initPlanes();
	initComputersSprites();
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (onGround == true)
		{
			velocityY = -0.2f;
			onGround = false;
		}
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

	GLfloat mv = -speed * depth;

	GLfloat camZ = -30.0f;


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

	for (int i = 0; i < TABLES; ++i)
		leftTables[i] = new Table(glm::vec3(floorWidth / 2.0f - 6.0f, 0.0f, 5.0f * (GLfloat)i));
	for (int i = 0; i < TABLES; ++i)
		rightTables[i] = new Table(glm::vec3(-(floorWidth / 2.0f - 6.0f), 0.0f, 5.0f * (GLfloat)i));

	GLfloat current;
	GLfloat	last = 0.0f;
	GLfloat delta;
	int count = 0;
	int steps[] = { 0, 1, 2, 1 };

	glm::mat4	catModel;
	glm::mat4	compModel;


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		handleInput(window);

		// ---------- JUMP --
		velocityY += gravity;
		catModel = cat.getModelMatrix();
		catModel = glm::translate(catModel, glm::vec3(0.0f, 0.0f, velocityY));
		if (catModel[3].y <= 0.5f) 
		{
			catModel[3].y = 0.5f;
			onGround = true;
		}
		/*
		*/
		cat.setModelMatrix(catModel);
		// -----------

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

		for (int i = 0; i < TABLES; ++i)
			leftTables[i]->draw(shader, speed, depth);
		for (int i = 0; i < TABLES; ++i)
			rightTables[i]->draw(shader, speed, depth);

		
		for (int i = 0; i < TABLES; ++i)
		{
			compModel = compR1[i].getModelMatrix();
			compModel = glm::translate(compModel, glm::vec3(0.0f, mv, 0.0f));
			if (compModel[3].z < camZ)
				compModel = glm::translate(compModel, glm::vec3(0.0f, depth, 0.0f));
			compR1[i].setModelMatrix(compModel);
			compR1[i].draw(shader, 0);
		}
		for (int i = 0; i < TABLES; ++i)
		{
			compModel = compR2[i].getModelMatrix();
			compModel = glm::translate(compModel, glm::vec3(0.0f, mv, 0.0f));
			if (compModel[3].z < camZ)
				compModel = glm::translate(compModel, glm::vec3(0.0f, depth, 0.0f));
			compR2[i].setModelMatrix(compModel);
			compR2[i].draw(shader, 0);
		}

		cat.draw(shader, 0.0f);


		glfwSwapBuffers(window);
	}	
}

void	App::initPlanes() {
	glm::mat4	leftWallModel;
	glm::mat4	rightWallModel;
	glm::mat4	floorModel;

	floor.loadTexture("assets/darkfloor.png", GL_RGB);
	floorModel = glm::scale(floorModel, glm::vec3(floorWidth, 1.0f, depth));
	floor.setModelMatrix(floorModel);

	leftWall.loadTexture("assets/sandwall.png", GL_RGB);
	leftWallModel = glm::translate(leftWallModel, glm::vec3(floorWidth / 2.0f, wallsHeight / 2.0f, 0.0f));
	leftWallModel = glm::rotate(leftWallModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	leftWallModel = glm::scale(leftWallModel, glm::vec3(wallsHeight, 1.0f, depth));
	leftWall.setModelMatrix(leftWallModel);

	rightWall.loadTexture("assets/sandwall.png", GL_RGB);
	rightWallModel = glm::translate(rightWallModel, glm::vec3(-floorWidth / 2.0f, wallsHeight/ 2.0f, 0.0f));
	rightWallModel = glm::rotate(rightWallModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rightWallModel = glm::scale(rightWallModel, glm::vec3(wallsHeight, 1.0f, depth));
	rightWall.setModelMatrix(rightWallModel);
}

void	App::initComputersSprites() {
	glm::mat4	compModel;

	for (int i = 0; i < TABLES; ++i)
	{
		compModel = glm::mat4();
		compR1[i].loadTexture("assets/comp.png", GL_RGBA);
		compModel = glm::translate(compModel, glm::vec3(floorWidth / 2.0f - 4.0f, 1.6f, 5.0f * (GLfloat)i));
		compModel = glm::rotate(compModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		compR1[i].setModelMatrix(compModel);
	}
	for (int i = 0; i < TABLES; ++i)
	{
		compModel = glm::mat4();
		compR2[i].loadTexture("assets/comp.png", GL_RGBA);
		compModel = glm::translate(compModel, glm::vec3(floorWidth / 2.0f - 8.0f, 1.6f, 5.0f * (GLfloat)i));
		compModel = glm::rotate(compModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		compR2[i].setModelMatrix(compModel);
	}
}

App::~App() {

}
