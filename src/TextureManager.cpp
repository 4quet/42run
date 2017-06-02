/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 11:12:49 by lfourque          #+#    #+#             */
/*   Updated: 2017/06/02 11:50:38 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42run.h>
#include <dirent.h>

TextureManager::TextureManager() {
	loadFromDir("assets/");
}

void	TextureManager::loadFromDir(std::string path) {
	DIR *dir;
	struct dirent *ent;
	std::string	filename;
	GLenum	type;

	if ((dir = opendir(path.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] != '.')
			{
				filename = ent->d_name;
				if (filename.substr(filename.find_last_of(".")) == ".png")
					type = GL_RGBA;
				else
					type = GL_RGB;
				load(path + filename, type);
			}
		}
		closedir (dir);
	} else {
		perror ("");
	}
}

void	TextureManager::load(std::string path, GLenum type) {
	int width, height;
	GLenum	soilType;
	GLuint	texture;

	soilType = (type == GL_RGBA) ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB;
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, soilType); 

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	textures.insert(std::pair<std::string, GLuint>(path, texture));
	std::cout << "Loaded " << path << " with id " << texture << std::endl;
}

GLuint	TextureManager::get(std::string name) {
	return textures.at(name);
}

TextureManager::~TextureManager() {

}
