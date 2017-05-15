/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/15 16:22:17 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_HPP
# define APP_HPP

class App {

	private:
		int 	keys[350];
		Plane	cat;

		App &	operator=(App const & rhs);
		App(App const & rhs);

		void	handleInput(GLFWwindow *window);

	public:

		App();
		~App();

		void	start(GLFW & glfw);
};

#endif
