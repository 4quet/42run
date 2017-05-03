/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Path.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:12:00 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/03 14:34:28 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_HPP
# define PATH_HPP

class Path {
	private:
		GLuint	VAO;
		GLuint	VBO;
		GLuint	EBO;

		glm::mat4	model;

		Path(Path const & rhs);
		Path &	operator=(Path const & rhs);

	public:
		Path();
		
		void	draw(Shader & shader, float speed);

		~Path();
};

#endif
