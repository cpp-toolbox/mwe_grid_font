#include <glm/fwd.hpp>
#include <iostream>

#include "graphics/batcher/generated/batcher.hpp"
#include "graphics/grid_font/grid_font.hpp"
#include "graphics/shader_cache/shader_cache.hpp"
#include "graphics/shader_standard/shader_standard.hpp"
#include "graphics/vertex_geometry/vertex_geometry.hpp"
#include "graphics/window/window.hpp"

int main() {
    Window window(700, 700, "mwe_grid_font", true);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // default is GL_LESS

    std::vector<ShaderType> rs = {ShaderType::ABSOLUTE_POSITION_WITH_COLORED_VERTEX};
    ShaderCache shader_cache(rs);

    Batcher batcher(shader_cache);

    shader_cache.set_uniform(ShaderType::ABSOLUTE_POSITION_WITH_COLORED_VERTEX, ShaderUniformVariable::ASPECT_RATIO,
                             glm::vec2(1, 1));

    vertex_geometry::Rectangle text_rect;
    vertex_geometry::Grid grid(6, 1);

    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    std::string numbers = "0123456789";

    draw_info::IndexedVertexPositions uppercase_ivp = grid_font::get_text_geometry(uppercase, grid.get_row(0).at(0));
    draw_info::IndexedVertexPositions lowercase_ivp = grid_font::get_text_geometry(lowercase, grid.get_row(2).at(0));
    draw_info::IndexedVertexPositions numbers_ivp = grid_font::get_text_geometry(numbers, grid.get_row(4).at(0));

    std::vector<glm::vec3> cs(uppercase_ivp.xyz_positions.size(), glm::vec3(0.5, 0.5, 0.5));

    while (!glfwWindowShouldClose(window.glfw_window)) {

        if (glfwGetKey(window.glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window.glfw_window, true);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // dark blue-gray background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(0, uppercase_ivp.indices,
                                                                                uppercase_ivp.xyz_positions, cs);

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(1, lowercase_ivp.indices,
                                                                                lowercase_ivp.xyz_positions, cs);

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(2, numbers_ivp.indices,
                                                                                numbers_ivp.xyz_positions, cs);

        batcher.absolute_position_with_colored_vertex_shader_batcher.draw_everything();

        glfwSwapBuffers(window.glfw_window);

        glfwPollEvents();
    }

    return 0;
}
