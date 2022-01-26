#ifndef GLBLUR_PROGRAM_HPP
#define GLBLUR_PROGRAM_HPP

#include "GLProgram.hpp"

class GLBlurProgram final : public GLProgram
{
public:
    explicit GLBlurProgram(const Engine& engine);
};

#endif GLBLUR_PROGRAM_HPP