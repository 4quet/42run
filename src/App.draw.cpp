/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.draw.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:17:37 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 16:26:50 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

void	App::drawTables(Shader & shader) {
	for (int i = 0; i < TABLES; ++i)
		leftTables[i]->draw(shader, speed, depth);
	for (int i = 0; i < TABLES; ++i)
		rightTables[i]->draw(shader, speed, depth);
}

void	App::drawComputersSprites(Shader & shader) {
	GLfloat mv = -speed * depth;
	for (int i = 0; i < COMP; ++i)
	{
		model = glm::translate(comp[i].getModelMatrix(), glm::vec3(0.0f, mv, 0.0f));
		if (model[3].z < CAM_Z)
		{
			model = glm::translate(model, glm::vec3(0.0f, depth, 0.0f));
			comp[i].setTexture(tm.get("assets/comp-" + std::to_string(randInt(0, 6)) + ".png"));
		}
		comp[i].setModelMatrix(model);
		comp[i].draw(shader, 0);
	}
}

void	App::drawObstacles(Shader & shader) {
	GLfloat mv = -speed * depth;
	for (int i = 0; i < OBST; ++i)
	{
		model = glm::translate(obstacles[i].getModelMatrix(), glm::vec3(0.0f, 0.0f, mv));
		if (model[3].z < CAM_Z)
			model = glm::translate(model, glm::vec3(0.0f, 0.0f,
						randInt((int)depth, (int)depth * 2)));
		obstacles[i].setModelMatrix(model);
		obstacles[i].draw(shader, 0.0f);
	}
}

void	App::drawWindowsSprites(Shader & shader) {
	GLfloat mv = -speed * depth;
	for (int i = 0; i < WIN; ++i)
	{
		model = glm::translate(leftWindows[i].getModelMatrix(), glm::vec3(mv / 4.0f, 0.0f, 0.0f));
		if (model[3].z < CAM_Z)
		{
			model = glm::translate(model, glm::vec3(depth / 4.0f, 0.0f, 0.0f));
			if (i == 5)
				leftWindows[i].setTexture(
						tm.get("assets/art-" + std::to_string(randInt(0, 6)) + ".png"));
		}
		leftWindows[i].setModelMatrix(model);
		leftWindows[i].draw(shader, 0);
	}

	for (int i = 0; i < WIN; ++i)
	{
		model = glm::translate(rightWindows[i].getModelMatrix(), glm::vec3(-mv / 4.0f, 0.0f, 0.0f));
		if (model[3].z < CAM_Z)
		{
			model = glm::translate(model, glm::vec3(-depth / 4.0f, 0.0f, 0.0f));
			if (i == 0)
				rightWindows[i].setTexture(
						tm.get("assets/art-" + std::to_string(randInt(0, 6)) + ".png"));
		}
		rightWindows[i].setModelMatrix(model);
		rightWindows[i].draw(shader, 0);
	}
}
