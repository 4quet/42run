/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 15:26:57 by lfourque          #+#    #+#             */
/*   Updated: 2017/04/26 17:40:25 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP

class	Shader {
	private:
		std::map<std::string, int>	_uniform;

		Shader(Shader const & rhs);
		Shader &	operator=(Shader const & rhs);

	public:
		GLuint	programId;

		Shader();

		inline void			use() { glUseProgram(programId); };
		inline void			disable() { glUseProgram(0); };

		std::string		readFile(std::string path);
		GLuint			compile(std::string source, GLenum type);
		GLint			uniform(std::string name);
		void			addUniform(std::string name);
		void			setUniformMatrix(glm::mat4 mat, std::string name);

		~Shader();
};


#endif
