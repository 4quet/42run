/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Counter.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:15:24 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/22 15:07:08 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

Counter::Counter() {
	glm::mat4	model;

	uSprite.loadTexture("assets/0.png", GL_RGBA);
	model = glm::translate(model, glm::vec3(-13.0f, 8.0f, -10.0f));	
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	uSprite.setModelMatrix(model);

	tSprite.loadTexture("assets/0.png", GL_RGBA);
	model = glm::translate(glm::mat4(), glm::vec3(-12.0f, 8.0f, -10.0f));	
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tSprite.setModelMatrix(model);

	hSprite.loadTexture("assets/0.png", GL_RGBA);
	model = glm::translate(glm::mat4(), glm::vec3(-11.0f, 8.0f, -10.0f));	
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	hSprite.setModelMatrix(model);

	units = 0;
	tens = 0;
	hundreds = 0;
}

void	Counter::draw(Shader & shader) {
	uSprite.draw(shader, 0.0f);
	tSprite.draw(shader, 0.0f);
	hSprite.draw(shader, 0.0f);
}

void	Counter::addOne() {
	units += 1;
	if (units == 10)
	{
		addTen();
		units = 0;
	}
	uSprite.loadTexture("assets/" + std::to_string(units) + ".png", GL_RGBA);
}

void	Counter::addTen() {
	tens += 1;
	if (tens == 10)
	{
		addHundred();
		tens = 0;
	}
	tSprite.loadTexture("assets/" + std::to_string(tens) + ".png", GL_RGBA);
}

void	Counter::addHundred() {
	hundreds += 1;
	if (hundreds < 10)
		hSprite.loadTexture("assets/" + std::to_string(hundreds) + ".png", GL_RGBA);
}

Counter::~Counter() {

}
