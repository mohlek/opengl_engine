#include <engine/Window.h>
#include <engine/shader/Shader.h>
#include <engine/shader/ShaderProgram.h>
#include <engine/VertexArrayObject.h>

int main() {
  Engine::Window* win = new Engine::Window("Shader test", 800, 600);
  win->create();

  const char* srcVert = R"(
        #version 410
        layout(location = 0) in vec3 vertexPosition_modelspace;

        void main() {
          gl_Position.xyz = vertexPosition_modelspace;
          gl_Position.w = 1.0;
        }
      )";

  const char* srcFrag = R"(
        #version 410
        
        out vec4 color;

        void main() {
          color = vec4(1.0, 0.0, 0.0, 1.0);
        }
      )";

  Engine::ShaderPtr fragShader = std::make_shared<Engine::Shader>(GL_FRAGMENT_SHADER, srcFrag);
  Engine::ShaderPtr vertShader = std::make_shared<Engine::Shader>(GL_VERTEX_SHADER, srcVert);

  Engine::ShaderProgram prog;
  prog.shaders.push_back(vertShader);
  prog.shaders.push_back(fragShader);
  prog.link();

  static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
  };
  static const GLfloat g_vertex_buffer_data2[] = {
     0.0f,  1.0f, 0.0f,
  };
  
  Engine::VertexArrayObject vao;
  Engine::BufferPtr buffer = std::make_shared<Engine::Buffer>();
  buffer->stride = 3 * sizeof(float);

  //*buffer << std:span(g_vertex_buffer_data, 24);

  vao.addBuffer(buffer);

  do {
    auto unbind = vao.bind();
    prog.use();

    glDrawArrays(GL_TRIANGLES, 0, 9);
    // shader stuff...
  } while (win->loop());

  delete win;

  return 0;
}
