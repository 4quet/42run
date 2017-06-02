/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 12:31:23 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

App::App() {
	catModel = glm::translate(catModel, glm::vec3(0.0f, 0.5f, -23.0f));
	catModel = glm::rotate(catModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	cat.setModelMatrix(catModel);
	
	counter = new Counter(tm);

	velocityY = 0.0f;
	gravity = 0.01f;
	onGround = true;
	gameOver = false;
	paused = false;

	speed = 0.002f;
	depth = 50.0f;
	floorWidth = 30.0f;
	wallsHeight = 50.0f;
	initPlanes();
	initComputersSprites();
	initTables();
	initObstacles();
}

void	App::handleInput(GLFWwindow *window) {
	catModel = cat.getModelMatrix();

	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && keys[GLFW_KEY_LEFT] != GLFW_PRESS
			&& onGround && !paused)
	{
		if (catModel[3].x < 0.5f)
		{
			catModel = glm::translate(catModel, glm::vec3(1.0f, 0.0f, 0.0f));
			cat.setModelMatrix(catModel);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && keys[GLFW_KEY_RIGHT] != GLFW_PRESS
			&& onGround && !paused)
	{
		if (catModel[3].x > -0.5f)
		{
			catModel = glm::translate(catModel, glm::vec3(-1.0f, 0.0f, 0.0f));
			cat.setModelMatrix(catModel);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (onGround == true)
		{
			velocityY = -0.2f;
			onGround = false;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && keys[GLFW_KEY_R] != GLFW_PRESS)
	{
		initTables();
		initObstacles();
		initComputersSprites();
		counter->reset(tm);
		speed = 0.002f;
		gameOver = false;
		paused = false;
	}

	static GLfloat	sp;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && keys[GLFW_KEY_P] != GLFW_PRESS)
	{
		paused = !paused;
		if (paused == true)
		{
			sp = speed;
		}
		else
		{
			speed = sp;
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

void	App::initTables() {
	for (int i = 0; i < TABLES; ++i)
		leftTables[i] = new Table(glm::vec3(floorWidth / 2.0f - 6.0f, 0.0f, 5.0f * (GLfloat)i), tm);
	for (int i = 0; i < TABLES; ++i)
		rightTables[i] = new Table(glm::vec3(-(floorWidth / 2.0f - 6.0f), 0.0f, 5.0f * (GLfloat)i), tm);
}

void	App::initObstacles() {
	glm::mat4	obstacleModel;

	for (int i = 0; i < OBST; ++i) 
	{
		obstacles[i].setTexture(tm.get("assets/cr8.jpg"));
		obstacleModel = glm::translate(glm::mat4(), glm::vec3((GLfloat)randInt(-1, 2), 0.5f,
					(GLfloat)randInt(0, (int)depth)));
		obstacles[i].setModelMatrix(obstacleModel);
	}
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

	Plane	go;
	glm::mat4	goModel;

	go.setTexture(tm.get("assets/go.png"));
	goModel = glm::translate(goModel, glm::vec3(0.0f, 2.8f, -28.0f));
	goModel = glm::rotate(goModel, glm::radians(100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	goModel = glm::rotate(goModel, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	goModel = glm::scale(goModel, glm::vec3(2.0f, 1.0f, 2.0f));
	go.setModelMatrix(goModel);

	glm::mat4	winModel;

	for (int i = 0; i < WIN; ++i)
	{
		leftWindows[i].setTexture(tm.get("assets/darkwin.png"));
		winModel = glm::translate(glm::mat4(), glm::vec3(floorWidth / 2.0f - 0.1f, 4.0f, (GLfloat)i * 5.0f));
		winModel = glm::rotate(winModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		winModel = glm::rotate(winModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		winModel = glm::scale(winModel, glm::vec3(4.0f, 1.0f, 4.0f));
		leftWindows[i].setModelMatrix(winModel);

		rightWindows[i].setTexture(tm.get("assets/darkwin.png"));
		winModel = glm::translate(glm::mat4(), glm::vec3(-(floorWidth / 2.0f) + 0.1f, 4.0f, (GLfloat)i * 5.0f));
		winModel = glm::rotate(winModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		winModel = glm::rotate(winModel, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		winModel = glm::scale(winModel, glm::vec3(4.0f, 1.0f, 4.0f));
		rightWindows[i].setModelMatrix(winModel);
	}

	GLfloat current;
	GLfloat	last = 0.0f;
	GLfloat delta;
	int count = 0;
	int steps[] = { 0, 1, 2, 1 };

	glm::mat4	compModel;
	glm::mat4	obstacleModel;


	while (!glfwWindowShouldClose(window))
	{
		handleInput(window);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			velocityY += gravity;
			if (onGround == false)
				applyGravity();

			current = glfwGetTime();
			delta = current - last;

			if (delta >= 0.2f - speed * 10.0f && !paused)
			{
				count++;
				cat.setTexture(tm.get("assets/bwcat" + std::to_string(steps[count % 4]) + ".png"));
				last = current;
				counter->addOne(tm);
				speed += 0.00002f;
			}
			mv = -speed * depth;


			floor.draw(shader, speed);

			leftWall.draw(shader, speed);
			rightWall.draw(shader, speed);


			for (int i = 0; i < TABLES; ++i)
				leftTables[i]->draw(shader, speed, depth);
			for (int i = 0; i < TABLES; ++i)
				rightTables[i]->draw(shader, speed, depth);

			/*
			*/
		//	for (int i = COMP; i >= 0; --i)
			for (int i = 0; i < COMP; ++i)
			{
				compModel = glm::translate(comp[i].getModelMatrix(), glm::vec3(0.0f, mv, 0.0f));
				if (compModel[3].z < camZ)
				{
					compModel = glm::translate(compModel, glm::vec3(0.0f, depth, 0.0f));
					comp[i].setTexture(tm.get("assets/comp-" + std::to_string(randInt(0, 6)) + ".png"));
				}
				comp[i].setModelMatrix(compModel);
				comp[i].draw(shader, 0);
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
			counter->draw(shader);

			for (int i = 0; i < WIN; ++i)
			{
				winModel = glm::translate(leftWindows[i].getModelMatrix(), glm::vec3(mv / 4.0f, 0.0f, 0.0f));
				if (winModel[3].z < camZ)
				{
					winModel = glm::translate(winModel, glm::vec3(depth / 4.0f, 0.0f, 0.0f));
					if (i == 5)
						leftWindows[i].setTexture(
								tm.get("assets/art-" + std::to_string(randInt(0, 6)) + ".png"));
				}
				leftWindows[i].setModelMatrix(winModel);
				leftWindows[i].draw(shader, 0);
			}

			for (int i = 0; i < WIN; ++i)
			{
				winModel = glm::translate(rightWindows[i].getModelMatrix(), glm::vec3(-mv / 4.0f, 0.0f, 0.0f));
				if (winModel[3].z < camZ)
				{
					winModel = glm::translate(winModel, glm::vec3(-depth / 4.0f, 0.0f, 0.0f));
					if (i == 0)
						rightWindows[i].setTexture(
								tm.get("assets/art-" + std::to_string(randInt(0, 6)) + ".png"));
				}
				rightWindows[i].setModelMatrix(winModel);
				rightWindows[i].draw(shader, 0);
			}

			for (int i = 0; i < OBST; ++i)
			{
				checkCollision(obstacles[i].getModelMatrix()[3]);
			}


		if (paused == true) {
			speed = 0.0f;
			if (gameOver == true)
				go.draw(shader, 0);
		}
		glfwSwapBuffers(window);
	}
}

void	App::checkCollision(glm::vec3 obsPos) {
	if (catModel[3].x < obsPos.x + 0.5f && catModel[3].x > obsPos.x - 0.5f
			&& catModel[3].y < obsPos.y + 0.5f && catModel[3].y > obsPos.y - 0.5f
			&& catModel[3].z < obsPos.z + 0.5f && catModel[3].z > obsPos.z - 0.5f)
	{
		paused = true;
		gameOver = true;
	}
}

void	App::initPlanes() {
	glm::mat4	leftWallModel;
	glm::mat4	rightWallModel;
	glm::mat4	floorModel;

	floor.setTexture(tm.get("assets/darkfloor.png"));
	floorModel = glm::scale(floorModel, glm::vec3(floorWidth, 1.0f, depth));
	floor.setModelMatrix(floorModel);

	leftWall.setTexture(tm.get("assets/sandwall.png"));
	leftWallModel = glm::translate(leftWallModel, glm::vec3(floorWidth / 2.0f, wallsHeight / 2.0f, 0.0f));
	leftWallModel = glm::rotate(leftWallModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	leftWallModel = glm::scale(leftWallModel, glm::vec3(wallsHeight, 1.0f, depth));
	leftWall.setModelMatrix(leftWallModel);

	rightWall.setTexture(tm.get("assets/sandwall.png"));
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

		comp[i].setTexture(tm.get("assets/comp-" + std::to_string(randInt(0, 6)) + ".png"));
		comp[i + 1].setTexture(tm.get("assets/comp-" + std::to_string(randInt(0, 6)) + ".png"));

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
