#pragma once

#include <Gosu/Fwd.hpp>
#include <Gosu/ImageData.hpp>
#include <Gosu/Platform.hpp>
#include "GraphicsImpl.hpp"

class Gosu::Macro : public Gosu::ImageData
{
    struct Impl;
    std::shared_ptr<Impl> pimpl;
    
public:
    Macro(DrawOpQueue& queue, int width, int height);
    
    int width() const;
    int height() const;
    
    void draw(double x1, double y1, Color c1,
        double x2, double y2, Color c2,
        double x3, double y3, Color c3,
        double x4, double y4, Color c4,
        ZPos z, AlphaMode mode) const;
    
    const Gosu::GLTexInfo* gl_tex_info() const;
    
    Gosu::Bitmap to_bitmap() const;
    
    std::unique_ptr<ImageData> subimage(int x, int y, int width, int height) const;
    
    void insert(const Bitmap& bitmap, int x, int y);
};
