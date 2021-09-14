#ifndef H_TERRAIN
#define H_TERRAIN

#include <engine/Buffer.h>
#include <engine/VertexArrayObject.h>
#include <engine/shader/ShaderProgram.h>
#include <engine/Texture.h>
#include <glm/glm.hpp>

namespace Engine {

    class TerrainGenerator {
        public:
            Engine::Texture heightMap;

            TerrainGenerator() {
                
            }
    };

    class Terrain {
        private:
            Engine::Buffer<glm::vec2> _terrainVertex;
            Engine::Buffer<unsigned int> _indexData;
            Engine::VertexArrayObject _vao;

            Engine::ShaderProgram& _program;

            glm::mat4& proj;

            unsigned int _w, _h;
        public:
            Terrain(int w, int h, glm::mat4& proj, Engine::ShaderProgram& program): _w(w), _h(h), proj(proj), _terrainVertex(Engine::Buffer<glm::vec2>(h * w)), _indexData(Engine::Buffer<unsigned int>((h-1) * (w-1) * 6, GL_ELEMENT_ARRAY_BUFFER)), _program(program) {
                unsigned int index = 0;
                for (int ih = 0; ih < h; ++ih) {
                    for (int iw = 0; iw < w; ++iw) {
                        _terrainVertex[index++] = glm::vec2(iw/(float)w, ih/(float)h);
                    }
                }
                _terrainVertex.flush();

                index = 0;
                for (int y = 0; y < h - 1; ++y) {
                    for (int x = 0; x < w - 1; ++x) {
                        // 1.triangle
                        _indexData[index++] = ((x + 0) + (y + 0) * w);
                        _indexData[index++] = ((x + 0) + (y + 1) * w);
                        _indexData[index++] = ((x + 1) + (y + 0) * w);
                        // 2.triangle
                        _indexData[index++] = ((x + 1) + (y + 0) * w);
                        _indexData[index++] = ((x + 0) + (y + 1) * w);
                        _indexData[index++] = ((x + 1) + (y + 1) * w);
                    }
                }
                _indexData.flush();

                _vao.setBuffer(0, _terrainVertex);
                _vao.setBuffer(0, _indexData);

            }

            void render() {
                _program.use();
                _vao.bind();

                glDrawElements(GL_TRIANGLES, _indexData.size() - 1, GL_UNSIGNED_INT, 0);
            }

            void setFactor(float f) {
                _program.use();
                glUniform1f(_program.getUniformLocation("factor"), f);
            }

            int heightAtPoint() {
                return 0;
            }
    };
}

#endif
