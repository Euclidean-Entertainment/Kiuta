#include <iostream>
#include "engine/engine.h"
#include "common/bst.hpp"

#include "gl/buffer.h"
#include "math/mat4.h"


int main(int argc, char** argv)
{
    CEngine engine(argc, argv);
    engine.init();

    return 0;
}