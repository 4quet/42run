/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:26:41 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/02 19:04:03 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_HPP
# define APP_HPP

class App {

	private:
		App &	operator=(App const & rhs);
		App(App const & rhs);

	public:
		App();
		~App();

		void	start(GLFWwindow *window);
		void	drawSlice();
};

#endif
