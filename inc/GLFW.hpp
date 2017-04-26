/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLFW.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/04/26 16:52:12 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFW_HPP
# define GLFW_HPP

class GLFW {

	private:
		GLFWwindow	*_window;

		GLFW &	operator=(GLFW const & rhs);
		GLFW(GLFW const & rhs);

	public:
		GLFW();
		~GLFW();

		void	init();
		void	start();

};

#endif
