#pragma once

#include <Gosu/Fwd.hpp>
#include <Gosu/ImageData.hpp>
#include <Gosu/Platform.hpp>
#include <memory>
#include <stdexcept>
#include <vector>

namespace Gosu
{
    class LargeImageData : public ImageData
    {
        unsigned fullWidth, fullHeight, partsX, partsY, partWidth, partHeight;
        std::vector<std::shared_ptr<ImageData> > parts;

    public:
        LargeImageData(const Bitmap& source,
            unsigned partWidth, unsigned partHeight, unsigned imageFlags);

        int width() const;
        int height() const;

        void draw(double x1, double y1, Color c1,
            double x2, double y2, Color c2,
            double x3, double y3, Color c3,
            double x4, double y4, Color c4,
            ZPos z, AlphaMode mode) const;
            
        const GLTexInfo* glTexInfo() const
        {
            return 0;
        }
        
        std::unique_ptr<ImageData> subimage(int x, int y, int w, int h) const
        {
            return std::unique_ptr<ImageData>();
        }
        
        Bitmap toBitmap() const;
        void insert(const Bitmap& bitmap, int x, int y);
    };
}
