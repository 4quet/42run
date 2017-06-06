/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLFW.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/06 15:42:06 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFW_HPP
# define GLFW_HPP

class GLFW {
	private:
		GLFWwindow	*_window;

		GLFW &	operator=(GLFW const & rhs);
		GLFW(GLFW const & rhs);

		static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

	public:
		GLFW();
		~GLFW();

		void		init();
		GLFWwindow 	*getWindow() const;
};

#endif
