/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 16:00:56 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/02 16:07:50 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

class	Camera {
	private:
		glm::vec3	_position;
		glm::vec3	_target;
		glm::vec3	_up;
		glm::mat4	_view;
		glm::mat4	_projection;

		Camera();
		Camera(Camera const & rhs);
		Camera &	operator=(Camera const & rhs);

	public:
		Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);

		void		setTarget(glm::vec3 target);
		void		setPosition(glm::vec3 position);
		void		setPerspective(float fov);

		glm::vec3 &	position();
		glm::mat4 &	projection();
		glm::mat4 &	view();

		~Camera();
};

#endif

