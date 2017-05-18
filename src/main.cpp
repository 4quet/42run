/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:45 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/18 18:09:35 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

int	main() {

	GLFW	glfw;
	App		app;

	srand(static_cast <unsigned> (time(0)));
	std::cout << "42run start" << std::endl;
	app.start(glfw.getWindow());

	return (0);
}
