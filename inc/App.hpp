/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 12:17:47 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_HPP
# define APP_HPP

# define TABLES	10
# define COMP	20
# define OBST	20
# define WIN	10

class App {

	private:
		int 	keys[350];
		Plane	cat;
		glm::mat4	catModel;

		GLfloat		velocityY;
		GLfloat		gravity;
		GLboolean	onGround;
		GLboolean	gameOver;
		GLboolean	paused;


		Counter		*counter;

		TextureManager	tm;

		Plane	leftWall;
		Plane	rightWall;
		Plane	floor;

		Table	*rightTables[TABLES];
		Table	*leftTables[TABLES];

		Cube	obstacles[OBST];

		Plane	leftWindows[WIN];
		Plane	rightWindows[WIN];

		Plane	comp[COMP];

		GLfloat	floorWidth;
		GLfloat	wallsHeight;
		GLfloat	depth;
		GLfloat	speed;

		App &	operator=(App const & rhs);
		App(App const & rhs);

		void	handleInput(GLFWwindow *window);
		void	initPlanes();
		void	initObstacles();
		void	initTables();
		void	initComputersSprites();

		void	applyGravity();

		void	checkCollision(glm::vec3 obsPos);

	public:

		App();
		~App();

		void	start(GLFWwindow *window);
};

#endif
