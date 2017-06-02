/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Table.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 11:12:57 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 12:08:15 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

Table::Table(glm::vec3 pos, TextureManager & tm) {
	buildTable(pos, tm);
}

void	Table::buildTable(glm::vec3 pos, TextureManager & tm) {
	top.setTexture(tm.get("assets/whitepaper.jpg"));
	topModelMatrix = glm::translate(topModelMatrix, glm::vec3(0.0f, 1.05f, 0.0f) + pos);
	topModelMatrix = glm::scale(topModelMatrix, glm::vec3(12.0f, 0.1f, 1.0f));
	top.setModelMatrix(topModelMatrix);

	feetA.setTexture(tm.get("assets/black-metal.jpg"));
	feetAModelMatrix = glm::translate(feetAModelMatrix, glm::vec3(4.0f, 0.5f, 0.0f) + pos);
	feetAModelMatrix = glm::scale(feetAModelMatrix, glm::vec3(0.1f, 1.0f, 1.0f));
	feetA.setModelMatrix(feetAModelMatrix);

	feetB.setTexture(tm.get("assets/black-metal.jpg"));
	feetBModelMatrix = glm::translate(feetBModelMatrix, glm::vec3(0.0f, 0.5f, 0.0f) + pos);
	feetBModelMatrix = glm::scale(feetBModelMatrix, glm::vec3(0.1f, 1.0f, 1.0f));
	feetB.setModelMatrix(feetBModelMatrix);

	feetC.setTexture(tm.get("assets/black-metal.jpg"));
	feetCModelMatrix = glm::translate(feetCModelMatrix, glm::vec3(-4.0f, 0.5f, 0.0f) + pos);
	feetCModelMatrix = glm::scale(feetCModelMatrix, glm::vec3(0.1f, 1.0f, 1.0f));
	feetC.setModelMatrix(feetCModelMatrix);
}

void	Table::translate(glm::vec3 v) {
	topModelMatrix = glm::translate(topModelMatrix, v);
	feetAModelMatrix = glm::translate(feetAModelMatrix, v);
	feetBModelMatrix = glm::translate(feetBModelMatrix, v);
	feetCModelMatrix = glm::translate(feetCModelMatrix, v);

	top.setModelMatrix(topModelMatrix);
	feetA.setModelMatrix(feetAModelMatrix);
	feetB.setModelMatrix(feetBModelMatrix);
	feetC.setModelMatrix(feetCModelMatrix);
}

void	Table::draw(Shader & shader, GLfloat speed, GLfloat depth) {
	translate(glm::vec3(0.0f, 0.0f, -speed * depth));
	if (topModelMatrix[3].z < -30.0f)
	{
		translate(glm::vec3(0.0f, 0.0f, depth));
	}
	top.draw(shader, 0);
	feetA.draw(shader, 0);
	feetB.draw(shader, 0);
	feetC.draw(shader, 0);
}

Table::~Table() {

}
