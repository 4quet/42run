/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:12:00 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/06 15:43:13 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_HPP
# define PLANE_HPP

class Plane {
	private:
		GLuint		VAO;
		GLuint		VBO;
		GLuint		EBO;
		GLuint		texture;
		GLfloat		offset;
		glm::mat4 	model;

		Plane(Plane const & rhs);
		Plane &	operator=(Plane const & rhs);

	public:
		Plane();
		
		void		draw(Shader & shader, float speed);
		void		setTexture(GLuint id);
		void		setModelMatrix(glm::mat4 m);
		glm::mat4	getModelMatrix() const;

		~Plane();
};

#endif
