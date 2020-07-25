#include <engine/Window.h>
#include <engine/shader/Shader.h>
#include <engine/shader/ShaderProgram.h>
#include <engine/VertexArrayObject.h>

int main() {
  Engine::Window* win = new Engine::Window("Shader test", 800, 600);
  win->create();

  const char* srcVert = R"(
        #version 410

        void main() {
        }
      )";

  const char* srcFrag = R"(
        #version 410
        
        out vec4 color;

        void main() {
          color = vec4(1.0, 0.0, 0.0, 1.0);
        }
      )";

  Engine::Shader fragShader(GL_FRAGMENT_SHADER, srcFrag);
  fragShader.compile();


  static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
  };

  Engine::VertexArrayObject vao;
  Engine::Buffer buffer;
  buffer.pushData(g_vertex_buffer_data, 9);

  vao.addBuffer(buffer);

  do {
    // shader stuff...
  } while (win->loop());

  delete win;

  return 0;
}
