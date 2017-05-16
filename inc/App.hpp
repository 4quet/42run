/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/16 16:45:51 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_HPP
# define APP_HPP

# define TABLES 10

class App {

	private:
		int 	keys[350];
		Plane	cat;

		GLfloat		velocityY;
		GLfloat		gravity;
		GLboolean	onGround;

		Plane	leftWall;
		Plane	rightWall;
		Plane	floor;

		Table	*rightTables[TABLES];
		Table	*leftTables[TABLES];

		Plane	compR1[TABLES];
		Plane	compR2[TABLES];
		Plane	compR3[TABLES];
		Plane	compR4[TABLES];

		GLfloat	floorWidth;
		GLfloat	wallsHeight;
		GLfloat	depth;
		GLfloat	speed;

		App &	operator=(App const & rhs);
		App(App const & rhs);

		void	handleInput(GLFWwindow *window);
		void	initPlanes();
		void	initComputersSprites();

	public:

		App();
		~App();

		void	start(GLFW & glfw);
};

#endif
