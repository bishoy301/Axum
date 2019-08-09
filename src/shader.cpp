#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <GL/glew.h>

std::string read_from_file(const char *file_path)
{
    std::string content;
    std::ifstream file_stream(file_path, std::ios::in);

    if (!file_stream.is_open())
    {
        std::cout << "Could not read file " << file_path << ". File path does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!file_stream.eof())
    {
        std::getline(file_stream, line);
        content.append(line + "\n");
    }

    file_stream.close();
    std::cout << "'" << content << "'" << std::endl;
    return content;
}

void load_shader(const char *vertex_path, const char *fragment_path)
{
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vert_shader_string = read_from_file(vertex_path);
    std::string frag_shader_string = read_from_file(fragment_path);
    const char *vert_shader_src = vert_shader_string.c_str();
    const char *frag_shader_src = frag_shader_string.c_str();

    std::cout << vert_shader_src << std::endl;
    std::cout << frag_shader_src << std::endl;
}