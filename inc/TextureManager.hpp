/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 11:09:05 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 11:49:35 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MANAGER_HPP
# define TEXTURE_MANAGER_HPP

class TextureManager {

	private:
		std::map<std::string, GLuint>	textures;

		TextureManager(TextureManager const & rhs);
		TextureManager &	operator=(TextureManager const & rhs);

	public:
		TextureManager();

		void	loadFromDir(std::string path);
		void	load(std::string path, GLenum type);
		GLuint	get(std::string name);

		~TextureManager();
};

#endif
