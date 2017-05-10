/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Table.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 11:08:32 by lfourque          #+#    #+#             */
/*   Updated: 2017/05/10 13:53:06 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_HPP
# define TABLE_HPP

class Table {
	private:
		Cube		top;
		Cube		feetA;
		Cube		feetB;
		Cube		feetC;
		glm::mat4	topModelMatrix;
		glm::mat4	feetAModelMatrix;
		glm::mat4	feetBModelMatrix;
		glm::mat4	feetCModelMatrix;

		Table();
		Table(Table const & rhs);
		Table &	operator=(Table const & rhs);

		void	buildTable(glm::vec3 pos);

	public:
		Table(glm::vec3 pos);

		void	draw(Shader & shader, GLfloat speed, GLfloat depth);
		void	translate(glm::vec3 v);

		~Table();
};

#endif
