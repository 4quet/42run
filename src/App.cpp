/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/23 16:16:08 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

App::App() {
	catModel = glm::translate(catModel, glm::vec3(0.0f, 0.5f, -23.0f));
	catModel = glm::rotate(catModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	cat.setModelMatrix(catModel);

	velocityY = 0.0f;
	gravity = 0.01f;
	onGround = true;
	gameOver = false;

	speed = 0.002f;
	depth = 50.0f;
	floorWidth = 30.0f;
	wallsHeight = 50.0f;
	initPlanes();
	initComputersSprites();
}

void	App::handleInput(GLFWwindow *window) {
	catModel = cat.getModelMatrix();

	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && keys[GLFW_KEY_LEFT] != GLFW_PRESS && onGround)
	{
		catModel = glm::translate(catModel, glm::vec3(1.0f, 0.0f, 0.0f));
		cat.setModelMatrix(catModel);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && keys[GLFW_KEY_RIGHT] != GLFW_PRESS && onGround)
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

void	App::applyGravity() {
	catModel = glm::translate(cat.getModelMatrix(), glm::vec3(0.0f, 0.0f, velocityY));
	if (catModel[3].y < 0.5f) 
	{
		catModel[3].y = 0.5f;
		onGround = true;
	}
	cat.setModelMatrix(catModel);
}

void	App::start(GLFWwindow *window) {

	Shader shader;
	shader.link("shaders/vertex.glsl", GL_VERTEX_SHADER);
	shader.link("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	GLfloat mv;

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


	Cube	obstacles[OBST];
	glm::mat4	obstacleModel;

	for (int i = 0; i < OBST; ++i) 
	{
		obstacles[i].loadTexture("assets/cr8.jpg", GL_RGB);
		obstacleModel = glm::translate(glm::mat4(), glm::vec3((GLfloat)randInt(-1, 2), 0.5f,
					(GLfloat)randInt(0, (int)depth)));
		obstacles[i].setModelMatrix(obstacleModel);
	}


	GLfloat current;
	GLfloat	last = 0.0f;
	GLfloat delta;
	int count = 0;
	int steps[] = { 0, 1, 2, 1 };

	glm::mat4	compModel;


	while (!glfwWindowShouldClose(window))
	{
		handleInput(window);
		if (gameOver == false)
		{
			glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			velocityY += gravity;
			if (onGround == false)
				applyGravity();

			current = glfwGetTime();
			delta = current - last;

			if (delta >= 0.2f - speed * 10.0f)
			{
				count++;
				cat.loadTexture("assets/bwcat" + std::to_string(steps[count % 4]) + ".png", GL_RGBA);
				last = current;
				counter.addOne();
				speed += 0.00001f;
			}
			mv = -speed * depth;

			floor.draw(shader, speed);

			leftWall.draw(shader, speed);
			rightWall.draw(shader, speed);


			for (int i = 0; i < TABLES; ++i)
				leftTables[i]->draw(shader, speed, depth);
			for (int i = 0; i < TABLES; ++i)
				rightTables[i]->draw(shader, speed, depth);

			for (int i = COMP; i >= 0; --i)
			{
				compModel = glm::translate(comp[i].getModelMatrix(), glm::vec3(0.0f, mv, 0.0f));
				if (compModel[3].z < camZ)
					compModel = glm::translate(compModel, glm::vec3(0.0f, depth, 0.0f));
				comp[i].setModelMatrix(compModel);
				comp[i].draw(shader, 0.0f);
			}


			for (int i = 0; i < OBST; ++i)
			{
				obstacleModel = glm::translate(obstacles[i].getModelMatrix(), glm::vec3(0.0f, 0.0f, mv));
				if (obstacleModel[3].z < camZ)
					obstacleModel = glm::translate(obstacleModel, glm::vec3(0.0f, 0.0f,
								randInt((int)depth, (int)depth * 2)));
				obstacles[i].setModelMatrix(obstacleModel);
				obstacles[i].draw(shader, 0.0f);
			}

			cat.draw(shader, 0.0f);
			counter.draw(shader);

			for (int i = 0; i < OBST; ++i)
			{
				checkCollision(obstacles[i].getModelMatrix()[3]);
			}



			glfwSwapBuffers(window);
		}
	}	
}

void	App::checkCollision(glm::vec3 obsPos) {
	if (catModel[3].x < obsPos.x + 0.5f && catModel[3].x > obsPos.x - 0.5f
			&& catModel[3].y < obsPos.y + 0.5f && catModel[3].y > obsPos.y - 0.5f
			&& catModel[3].z < obsPos.z + 0.5f && catModel[3].z > obsPos.z - 0.5f)
		gameOver = true;
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
	GLfloat		halfFloor = floorWidth / 2.0f;
	GLfloat		offset;

	for (int i = 0; i < COMP; i += 2)
	{
		offset = (i % 4) ? 8.0f : 4.0f;

		comp[i].loadTexture("assets/comp.png", GL_RGBA);
		comp[i + 1].loadTexture("assets/comp.png", GL_RGBA);

		compModel = glm::translate(glm::mat4(), glm::vec3(halfFloor - offset, 1.4f, 5.0f * ((GLfloat)i / 2.0f)));
		compModel = glm::rotate(compModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		comp[i].setModelMatrix(compModel);

		compModel = glm::translate(glm::mat4(), glm::vec3(-halfFloor + offset, 1.4f, 5.0f * ((GLfloat)i / 2.0f)));
		compModel = glm::rotate(compModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		comp[i + 1].setModelMatrix(compModel);
	}
}

App::~App() {

}
