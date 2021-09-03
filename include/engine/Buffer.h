#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <GL/glew.h>
#include <stdexcept>
#include <framework/Buffer.h>
#include "Deleter.h"

namespace Engine {

  class BufferBase;  class BufferBaseDeleter {
    private:
      GLuint _bufferId = 0;
      GLenum _target;
    public:
      BufferBaseDeleter(GLenum target, GLuint bufferId) : _target(target), _bufferId(bufferId) {}

      void operator()(void* p) const {
        (void)p;
        GL::unmapBuffer(this->_target, this->_bufferId);
        GL::deleteBuffers(1, &this->_bufferId);
      }
  };

  class BufferBase {
      protected:
          std::shared_ptr<void> _ptr = nullptr;
      public:
          GLuint _bufferId = 0;
          GLenum _target = GL_ARRAY_BUFFER;
          GLenum _dataType = GL_FLOAT;
          int _size = 0;
          int _itemSize = 0;
          virtual ~BufferBase(){}

          void bind() {
            GL::bindBuffer(_target, _bufferId);
          }
          void unbind() {
            GL::unbindBuffer(_target);
          }
  };

  template<typename T>
  class Buffer : public BufferBase {
      public:
        Buffer(int size, GLenum target = GL_ARRAY_BUFFER) {
          this->_itemSize = sizeof(T);
          this->_size = size;
          this->_target = target;
          GL::createBuffers(_target, 1, &this->_bufferId);

          auto flags = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
          if (glBufferStorage) {
            flags |= GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
          }
          auto bsize = this->_size * this->_itemSize;

          GL::bufferStorage(this->_target, this->_bufferId, bsize, NULL, flags);

          map();
        }
        ~Buffer() {}

        void map() {
          auto flags = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
          if (glBufferStorage) {
            flags |= GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT;
          }
          auto bsize = this->_size * this->_itemSize;

          auto raw_ptr = (T*)GL::mapBufferRange(_target, this->_bufferId, 0, bsize, flags);
          this->_ptr = std::shared_ptr<void>(raw_ptr, BufferBaseDeleter(this->_target, this->_bufferId));
        }

        void flush() {
          if (!glBufferStorage) {
            this->_ptr.reset();
            map();
            return;
          }
          GL::flushMappedBufferRange(this->_target, this->_bufferId, 0, this->_size * this->_itemSize);
        }
        
        const T& at(int index) const {
          if (index >= this->_size || index < 0) {
            throw std::out_of_range("OUT OF RANGE");
          }
          return this->operator[](index);
        }
        T& at(int index) {
          if (index >= this->_size || index < 0) {
            throw std::out_of_range("OUT OF RANGE");
          }
          return this->operator[](index);
        }

        const T& operator[](int index) const {
          return *((T*)this->_ptr.get() + index);
        }
        T& operator[](int index) {
          return *((T*)this->_ptr.get() + index);
        }

        const T& front() const {
          return this->operator[](0);
        }
        T& front() {
          return this->operator[](0);
        }
        const T& back() const {
          return this->operator[](this->size() - 1);
        }
        T& back() {
          return this->operator[](this->size() - 1);
        }
        
        const T* data() const {
          return this->_ptr.get();
        }
        T* data() {
          return this->_ptr.get();
        }

        T* begin() {
          return &this->front();
        }
        const T* begin() const {
          return &this->front();
        }
        const T* cbegin(){
          return &this->front();
        }
        const T* cbegin() const {
          return &this->front();
        }

        T* end() {
          return &this->back();
        }
        const T* end() const {
          return &this->back();
        }
        const T* cend(){
          return &this->back();
        }
        const T* cend() const {
          return &this->back();
        }

        int size() const {
          return this->_size;
        }
  };
}


#endif
