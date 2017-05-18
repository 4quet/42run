/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:12:00 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/18 14:40:18 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_HPP
# define PLANE_HPP

class Plane {
	private:
		GLuint	VAO;
		GLuint	VBO;
		GLuint	EBO;


		GLfloat	offset;

		glm::mat4 	model;

		Plane(Plane const & rhs);
		Plane &	operator=(Plane const & rhs);

	public:
		GLuint texture;

		Plane();
		
		void	draw(Shader & shader, float speed);
		void	loadTexture(std::string path, GLenum type);

		void	setModelMatrix(glm::mat4 m);
		glm::mat4	getModelMatrix() const;

		~Plane();
};

#endif
