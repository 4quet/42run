/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 12:47:23 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/03 13:15:42 by lfourque         ###   ########.fr       */
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
