/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/02 19:04:25 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

App::App() {
}

void	App::drawSlice() {
	
}

void	App::start(GLFWwindow *window) {

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

	Shader shader;
	shader.link("shaders/vertex.glsl", GL_VERTEX_SHADER);
	shader.link("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

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

	glm::mat4 model;

	Camera camera(glm::vec3(0.0f, 1.0f, -5.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));
	camera.setPerspective(45.0f);

	shader.use();
	shader.addUniform("model");
	shader.addUniform("view");
	shader.addUniform("projection");
	shader.setUniformMatrix(camera.view(), "view");
	shader.setUniformMatrix(camera.projection(), "projection");

	float speed = 0.05f;
	float offset = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//	shader.use();
		offset += speed;
		if (offset > 1.0f)
		{
			model = glm::mat4();
			offset = 0.0f;
		}
		else
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -speed));

		shader.setUniformMatrix(model, "model");


		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 4);


		for (float i = -3; i < 10; ++i)
		{
			glm::mat4 lul = glm::translate(model, glm::vec3(0.0f, 0.0f, i));
			shader.setUniformMatrix(lul, "model");
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}	
}

App::~App() {
}
