/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Counter.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:12:57 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/06 15:40:38 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COUNTER_HPP
# define COUNTER_HPP

class Counter {
	private:
		unsigned int	units;
		unsigned int	tens;
		unsigned int	hundreds;
		Plane			uSprite;
		Plane			tSprite;
		Plane			hSprite;

		Counter(Counter const & rhs);
		Counter &	operator=(Counter const & rhs);
		Counter();

	public:
		Counter(TextureManager & tm);

		void	reset(TextureManager & tm);
		void	draw(Shader & shader);
		void	addOne(TextureManager & tm);
		void	addTen(TextureManager & tm);
		void	addHundred(TextureManager & tm);

		~Counter();
};

#endif
