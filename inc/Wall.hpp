/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:12:00 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/04 15:59:56 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_HPP
# define WALL_HPP

class Wall {
	private:
		GLuint	VAO;
		GLuint	VBO;
		GLuint	EBO;

		GLuint texture;

		GLfloat	offset;

		glm::mat4 	model;

		Wall(Wall const & rhs);
		Wall &	operator=(Wall const & rhs);

	public:
		Wall();
		
		void	draw(Shader & shader, float speed);

		~Wall();
};

#endif
