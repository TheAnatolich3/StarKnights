#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP
#include <Texture.hpp>

class Bitmap;

class GLTexture : public Texture
{
public:
    explicit GLTexture(Bitmap bitmap);
    void active();

    uint32_t getId() const;
private:
    uint32_t _id;
};


#endif GLTEXTURE_HPP