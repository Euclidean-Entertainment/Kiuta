#include <iostream>
#include "engine/engine.h"
#include "common/bst.hpp"

#include "gl/buffer.h"
#include "math/mat4.h"

#include "loader/bitmap.h"
#include "loader/spritesheet.h"

int main(int argc, char** argv)
{
    //CMSBitmap bitmap("bmptest.bmp");

    CEngine engine(argc, argv);
    engine.init();

    return 0;
}
