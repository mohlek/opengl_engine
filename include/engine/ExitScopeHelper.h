#ifndef _H_EXITSCOPEHELPER
#define _H_EXITSCOPEHELPER

#include <functional>

namespace Engine {
  class ExitScopeHelper {
    private:
      std::function<void()> fn;
    public:
      ExitScopeHelper(std::function<void()> fn) : fn(fn) {}
      ExitScopeHelper(const ExitScopeHelper&&) = delete;
      ExitScopeHelper operator=(const ExitScopeHelper&&) = delete;
      virtual ~ExitScopeHelper() {
        this->fn();
      }
  };
}

#endif
