/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Counter.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:15:24 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 12:17:07 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

Counter::Counter(TextureManager & tm) {
	glm::mat4	model;

	model = glm::translate(model, glm::vec3(-13.0f, 8.0f, -10.0f));	
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	uSprite.setModelMatrix(model);

	model = glm::translate(glm::mat4(), glm::vec3(-12.0f, 8.0f, -10.0f));	
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tSprite.setModelMatrix(model);

	model = glm::translate(glm::mat4(), glm::vec3(-11.0f, 8.0f, -10.0f));	
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	hSprite.setModelMatrix(model);

	reset(tm);
}

void	Counter::reset(TextureManager & tm) {
	units = 0;
	tens = 0;
	hundreds = 0;
	uSprite.setTexture(tm.get("assets/0.png"));
	tSprite.setTexture(tm.get("assets/0.png"));
	hSprite.setTexture(tm.get("assets/0.png"));
}

void	Counter::draw(Shader & shader) {
	uSprite.draw(shader, 0.0f);
	tSprite.draw(shader, 0.0f);
	hSprite.draw(shader, 0.0f);
}

void	Counter::addOne(TextureManager & tm) {
	units += 1;
	if (units == 10)
	{
		addTen(tm);
		units = 0;
	}
	uSprite.setTexture(tm.get("assets/" + std::to_string(units) + ".png"));
}

void	Counter::addTen(TextureManager & tm) {
	tens += 1;
	if (tens == 10)
	{
		addHundred(tm);
		tens = 0;
	}
	tSprite.setTexture(tm.get("assets/" + std::to_string(tens) + ".png"));
}

void	Counter::addHundred(TextureManager & tm) {
	hundreds += 1;
	if (hundreds < 10)
		hSprite.setTexture(tm.get("assets/" + std::to_string(hundreds) + ".png"));
}

Counter::~Counter() {

}
