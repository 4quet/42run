/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Counter.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:12:57 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/29 12:07:30 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COUNTER_HPP
# define COUNTER_HPP

class Counter {
	private:
		unsigned int		units;
		unsigned int		tens;
		unsigned int		hundreds;
		Plane	uSprite;
		Plane	tSprite;
		Plane	hSprite;

		Counter(Counter const & rhs);
		Counter &	operator=(Counter const & rhs);

	public:
		Counter();

		void	reset();
		void	draw(Shader & shader);
		void	addOne();
		void	addTen();
		void	addHundred();


		~Counter();
};

#endif
