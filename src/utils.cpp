/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:47:23 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/23 16:06:10 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>
#include <iomanip>

void	pm4(glm::mat4 mat) {
	for (int x = 0; x < 4; ++x) {
		std::cout << "|";
		for (int y = 0; y < 4; ++y) {
			std::cout << std::setfill(' ') << std::setw(8) << mat[y][x] << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

GLfloat	randFloat(GLfloat low, GLfloat high)
{
	return low + static_cast <GLfloat> (rand()) /( static_cast <GLfloat> (RAND_MAX / (high - low)));
}

int	randInt(int low, int high)
{
	return low + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX / (high - low)));
}
