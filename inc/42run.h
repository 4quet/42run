/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42run.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:48:48 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/02 18:50:01 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTY_TWO_RUN_H
# define FORTY_TWO_RUN_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define Z_NEAR 1
# define Z_FAR 100

# include <iostream>
# include <map>
# include <sstream>
# include <fstream>

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include <GLFW.hpp>
# include <App.hpp>
# include <Shader.hpp>
# include <Camera.hpp>

#endif
