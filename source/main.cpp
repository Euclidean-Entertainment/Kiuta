#include "common/bst.hpp"
#include "engine/engine.h"
#include "gl/buffer.h"
#include "loader/bitmap.h"
#include "math/mat4.h"

#include <iostream>

int main(int argc, char** argv)
{
    //CMSBitmap bitmap("bmptest.bmp");

    CEngine engine(argc, argv);
    engine.init();

    return 0;
}
