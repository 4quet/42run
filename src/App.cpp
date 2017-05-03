/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:38:31 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/03 14:38:17 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

App::App() {
}

void	App::drawSlice() {

	
}

void	App::start(GLFWwindow *window) {

	Shader shader;
	shader.link("shaders/vertex.glsl", GL_VERTEX_SHADER);
	shader.link("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

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

	float speed = 0.06f;
	float offset = 0.0f;

	Path	path;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		offset += speed;

		path.draw(shader, speed);

/*
		for (float i = 0; i < 10; ++i)
		{
			glm::mat4 lul = glm::translate(model, glm::vec3(0.0f, 0.0f, i));
			shader.setUniformMatrix(lul, "model");
		}
		*/

		glfwSwapBuffers(window);
	}	
}

App::~App() {

}
