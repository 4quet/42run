/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:12:00 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/09 15:42:09 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_HPP
# define CUBE_HPP

class Cube {
	private:
		GLuint	VAO;
		GLuint	VBO;

		GLuint texture;

		GLfloat	offset;

		glm::mat4 	model;

		Cube(Cube const & rhs);
		Cube &	operator=(Cube const & rhs);

	public:
		Cube();
		
		void	draw(Shader & shader, float speed);
		void	loadTexture(std::string path, GLenum type);

		void	setModelMatrix(glm::mat4 m);
		glm::mat4	getModelMatrix() const;

		~Cube();
};

#endif
