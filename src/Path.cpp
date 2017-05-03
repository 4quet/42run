/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:10:38 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/03 14:44:13 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

Path::Path() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.0f, 0.5f,   0.3f, 0.6f, 0.6f,   // Top Right
		0.5f, 0.0f, -0.5f,   0.7f, 0.6f, 0.6f,   // Bottom Right
		-0.5f, 0.0f, -0.5f,   0.4f, 0.6f, 0.6f,  // Bottom Left
		-0.5f,  0.0f, 0.5f,   0.5f, 0.6f, 0.6f   // Top Left
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	glBindVertexArray(VAO);
	// 2. Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 3. Then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//4. Unbind the VAO
	glBindVertexArray(0);
}

void	Path::draw(Shader & shader, float speed) {

	model = translate(model, glm::vec3(0.0f, 0.0f, -speed));

	if (model[3].z < -4.0f) {
		model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 10.0f));
	} else {
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -speed));
	}
	shader.setUniformMatrix(model, "model");

	glBindVertexArray(VAO);

	for (int i = 0; i < 3; ++i) {
		glm::mat4 tmp = glm::translate(model, glm::vec3(0.0f, 0.0f, (float)i));
		shader.setUniformMatrix(tmp, "model");
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

Path::~Path() {

}
