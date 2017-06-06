/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/06 15:29:34 by lfourque         ###   ########.fr       */
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
	paused = false;
	speed = 0.002f;
	depth = 50.0f;
	floorWidth = 30.0f;
	wallsHeight = 50.0f;
	counter = new Counter(tm);
	initPlanes();
	initComputersSprites();
	initTables();
	initObstacles();
	initWindowsSprites();
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

void	App::addStep() {
	static int 		count = 0;
	static GLfloat	last = 0.0f;
	GLfloat 		current;
	GLfloat 		delta;
	int steps[] = { 0, 1, 2, 1 };

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
}

void	App::start(GLFWwindow *window) {
	Camera camera(glm::vec3(0.0f, 3.0f, CAM_Z),
				  glm::vec3(0.0f, 0.0f, 0.0f),
				  glm::vec3(0.0f, 1.0f, 0.0f));
	camera.setPerspective(45.0f);

	Shader shader;
	shader.link("shaders/vertex.glsl", GL_VERTEX_SHADER);
	shader.link("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	shader.use();
	shader.addUniform("model");
	shader.addUniform("view");
	shader.addUniform("projection");
	shader.addUniform("offset");
	shader.setUniformMatrix(camera.view(), "view");
	shader.setUniformMatrix(camera.projection(), "projection");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		handleInput(window);
		velocityY += gravity;
		if (onGround == false && !paused)
			applyGravity();
		addStep();

		floor.draw(shader, speed);
		leftWall.draw(shader, speed);
		rightWall.draw(shader, speed);
		drawTables(shader);
		drawComputersSprites(shader);
		drawObstacles(shader);
		drawWindowsSprites(shader);
		cat.draw(shader, 0.0f);
		counter->draw(shader);

		for (int i = 0; i < OBST; ++i)
			checkCollision(obstacles[i].getModelMatrix()[3]);
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

App::~App() {
	delete counter;
	freeTables();
}
