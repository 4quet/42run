/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/06 15:39:09 by lfourque         ###   ########.fr       */
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
		GLfloat		velocityY;
		GLfloat		gravity;
		GLfloat		depth;
		GLfloat		speed;
		GLfloat		floorWidth;
		GLfloat		wallsHeight;
		GLboolean	onGround;
		GLboolean	gameOver;
		GLboolean	paused;

		Counter			*counter;
		TextureManager	tm;

		Plane	cat;
		Plane	leftWall;
		Plane	rightWall;
		Plane	floor;
		Plane	go;

		Plane	leftWindows[WIN];
		Plane	rightWindows[WIN];
		Plane	comp[COMP];

		Table	*rightTables[TABLES];
		Table	*leftTables[TABLES];

		Cube	obstacles[OBST];

		glm::mat4	catModel;
		glm::mat4	model;

		int 		keys[350];

		App &	operator=(App const & rhs);
		App(App const & rhs);

		/* App.input.cpp */
		GLboolean	isPressed(GLFWwindow *window, GLenum key);
		void		handleInput(GLFWwindow *window);
		void		jump();
		void		moveLeft();
		void		moveRight();
		void		resetGame();
		void		pause();

		/* App.init.cpp */
		void		initPlanes();
		void		freeTables();
		void		initObstacles();
		void		initTables();
		void		initComputersSprites();
		void		initWindowsSprites();

		/* App.draw.cpp */
		void		drawObstacles(Shader & shader);
		void		drawTables(Shader & shader);
		void		drawComputersSprites(Shader & shader);
		void		drawWindowsSprites(Shader & shader);

		/* App.cpp */
		void		applyGravity();
		void		addStep();
		void		checkCollision(glm::vec3 obsPos);

	public:
		App();
		~App();

		void		start(GLFWwindow *window);
};

#endif
