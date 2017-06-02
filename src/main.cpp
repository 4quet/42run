/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:45 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 15:18:54 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>

int	main() {
	GLFW	glfw;
	App		app;

	srand(static_cast <unsigned> (time(0)));
	app.start(glfw.getWindow());
	return (0);
}
