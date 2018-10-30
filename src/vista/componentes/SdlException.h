#ifndef SDL_EXCEPTION_H
#define SDL_EXCEPTION_H
#include <string>
#include <exception>

class SdlException : public std::exception {
private:
    std::string description;
    
public:    
    SdlException(const char* description, const char* sdlError);
    const char* what() const noexcept;
};

#endif
