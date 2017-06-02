/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 16:00:28 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 16:07:51 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) : _position(pos), _target(target), _up(up) {
	_view = glm::lookAt(pos, target, up);
}

glm::vec3 &	Camera::position() { return (_position); }
glm::mat4 &	Camera::projection() { return (_projection); }
glm::mat4 &	Camera::view() { return (_view); }

void		Camera::setTarget(glm::vec3 target) {
	_target = target;
	_view = glm::lookAt( _position, _target, _up);
}

void		Camera::setPosition(glm::vec3 position) {
	_position = position;
	_view = glm::lookAt( _position, _target, _up);
}

void		Camera::setPerspective(float fov) {
	_projection = glm::perspective(glm::radians(fov),
			(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
			(float)Z_NEAR, (float)Z_FAR);
}

Camera::~Camera() {

}
