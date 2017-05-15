/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:10:38 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/15 13:11:34 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

Plane::Plane() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	GLfloat vertices[] = {
		// Positions          // Colors         // Texture Coords
		0.5f,  0.0f, 0.5f,   1.0f, 1.0f,  // Top Right
		0.5f, 0.0f, -0.5f,   1.0f, 0.0f,	// Bottom Right
		-0.5f, 0.0f, -0.5f,  0.0f, 0.0f, // Bottom Left
		-0.5f,  0.0f, 0.5f,  0.0f, 1.0f  // Top Left
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//4. Unbind the VAO
	glBindVertexArray(0);

	offset = 0.0f;

}

void		Plane::setModelMatrix(glm::mat4 m) { model = m; }
glm::mat4	Plane::getModelMatrix() const { return model; }

void	Plane::loadTexture(std::string path, GLenum type) {
	int width, height;
	GLenum	soilType;

	soilType = (type == GL_RGBA) ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB;
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, soilType); 

	glGenTextures(1, &texture);  

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	Plane::draw(Shader & shader, GLfloat speed) {

	offset += speed;

	glBindVertexArray(VAO);


	shader.setUniformMatrix(model, "model");

	glUniform1f(shader.uniform("offset"), offset);

	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

Plane::~Plane() {

}
