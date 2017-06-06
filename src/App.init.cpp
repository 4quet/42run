/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.init.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 15:59:06 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/06 15:21:37 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

void	App::initTables() {
	for (int i = 0; i < TABLES; ++i)
	{
		leftTables[i] = new Table(glm::vec3(floorWidth / 2.0f - 6.0f, 0.0f, 5.0f * (GLfloat)i), tm);
		rightTables[i] = new Table(glm::vec3(-(floorWidth / 2.0f - 6.0f), 0.0f, 5.0f * (GLfloat)i), tm);
	}
}

void	App::freeTables() {
	for (int i = 0; i < TABLES; ++i)
	{
		delete leftTables[i];
		delete rightTables[i];
	}
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

void	App::initWindowsSprites() {
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
}

void	App::initPlanes() {
	glm::mat4	leftWallModel;
	glm::mat4	rightWallModel;
	glm::mat4	floorModel;
	glm::mat4	goModel;

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

	go.setTexture(tm.get("assets/go.png"));
	goModel = glm::translate(goModel, glm::vec3(0.0f, 2.8f, -28.0f));
	goModel = glm::rotate(goModel, glm::radians(100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	goModel = glm::rotate(goModel, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	goModel = glm::scale(goModel, glm::vec3(2.0f, 1.0f, 2.0f));
	go.setModelMatrix(goModel);
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
