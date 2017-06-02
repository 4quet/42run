/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 16:26:28 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_HPP
# define APP_HPP

# define TABLES	10
# define COMP	20
# define OBST	20
# define WIN	10
# define CAM_Z	-30.0f

class App {

	private:
		int 	keys[350];
		Plane	cat;

		glm::mat4	catModel;

		glm::mat4	model;

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
		Plane	go;

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

		void		handleInput(GLFWwindow *window);
		GLboolean	isPressed(GLFWwindow *window, GLenum key);

		void	initPlanes();
		void	initObstacles();
		void	initTables();
		void	initComputersSprites();
		void	initWindowsSprites();

		void	drawObstacles(Shader & shader);
		void	drawTables(Shader & shader);
		void	drawComputersSprites(Shader & shader);
		void	drawWindowsSprites(Shader & shader);

		void	applyGravity();
		void	jump();
		void	moveLeft();
		void	moveRight();

		void	resetGame();
		void	pause();

		void	checkCollision(glm::vec3 obsPos);


	public:

		App();
		~App();

		void	start(GLFWwindow *window);
};

#endif
