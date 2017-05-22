/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/22 15:36:52 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_HPP
# define APP_HPP

# define TABLES	10
# define COMP	20

class App {

	private:
		int 	keys[350];
		Plane	cat;
		glm::mat4	catModel;

		GLfloat		velocityY;
		GLfloat		gravity;
		GLboolean	onGround;

		Counter		counter;

		Plane	leftWall;
		Plane	rightWall;
		Plane	floor;

		Table	*rightTables[TABLES];
		Table	*leftTables[TABLES];

		Plane	comp[COMP];

		GLfloat	floorWidth;
		GLfloat	wallsHeight;
		GLfloat	depth;
		GLfloat	speed;

		App &	operator=(App const & rhs);
		App(App const & rhs);

		void	handleInput(GLFWwindow *window);
		void	initPlanes();
		void	initComputersSprites();

		void	applyGravity();

		void	checkCollision(glm::mat4 obstacle);

	public:

		App();
		~App();

		void	start(GLFWwindow *window);
};

#endif
