#ifndef __Models_h_
#define __Models_h_

// cube solo vectores
const float simple_cube[] = {
    /*pos*/ -0.5f, -0.5f, -0.5f,
    /*pos*/ 0.5f, -0.5f, -0.5f,
    /*pos*/ 0.5f, 0.5f, -0.5f,
    /*pos*/ 0.5f, 0.5f, -0.5f,
    /*pos*/ -0.5f, 0.5f, -0.5f,
    /*pos*/ -0.5f, -0.5f, -0.5f,

    /*pos*/ -0.5f, -0.5f, 0.5f,
    /*pos*/ 0.5f, -0.5f, 0.5f,
    /*pos*/ 0.5f, 0.5f, 0.5f,
    /*pos*/ 0.5f, 0.5f, 0.5f,
    /*pos*/ -0.5f, 0.5f, 0.5f,
    /*pos*/ -0.5f, -0.5f, 0.5f,

    /*pos*/ -0.5f, 0.5f, 0.5f,
    /*pos*/ -0.5f, 0.5f, -0.5f,
    /*pos*/ -0.5f, -0.5f, -0.5f,
    /*pos*/ -0.5f, -0.5f, -0.5f,
    /*pos*/ -0.5f, -0.5f, 0.5f,
    /*pos*/ -0.5f, 0.5f, 0.5f,

    /*pos*/ 0.5f, 0.5f, 0.5f,
    /*pos*/ 0.5f, 0.5f, -0.5f,
    /*pos*/ 0.5f, -0.5f, -0.5f,
    /*pos*/ 0.5f, -0.5f, -0.5f,
    /*pos*/ 0.5f, -0.5f, 0.5f,
    /*pos*/ 0.5f, 0.5f, 0.5f,

    /*pos*/ -0.5f, -0.5f, -0.5f,
    /*pos*/ 0.5f, -0.5f, -0.5f,
    /*pos*/ 0.5f, -0.5f, 0.5f,
    /*pos*/ 0.5f, -0.5f, 0.5f,
    /*pos*/ -0.5f, -0.5f, 0.5f,
    /*pos*/ -0.5f, -0.5f, -0.5f,

    /*pos*/ -0.5f, 0.5f, -0.5f,
    /*pos*/ 0.5f, 0.5f, -0.5f,
    /*pos*/ 0.5f, 0.5f, 0.5f,
    /*pos*/ 0.5f, 0.5f, 0.5f,
    /*pos*/ -0.5f, 0.5f, 0.5f,
    /*pos*/ -0.5f, 0.5f, -0.5f};

// cube con vectores normales
const float cube[] = {
    /*pos*/ -0.5f, -0.5f, -0.5f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ -0.5f, 0.5f, -0.5f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*norm*/ 0.0f, 0.0f, -1.0f,

    /*pos*/ -0.5f, -0.5f, 0.5f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ -0.5f, 0.5f, 0.5f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ -0.5f, -0.5f, 0.5f, /*norm*/ 0.0f, 0.0f, 1.0f,

    /*pos*/ -0.5f, 0.5f, 0.5f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, -0.5f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, 0.5f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, 0.5f, /*norm*/ -1.0f, 0.0f, 0.0f,

    /*pos*/ 0.5f, 0.5f, 0.5f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*norm*/ 1.0f, 0.0f, 0.0f,

    /*pos*/ -0.5f, -0.5f, -0.5f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, 0.5f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*norm*/ 0.0f, -1.0f, 0.0f,

    /*pos*/ -0.5f, 0.5f, -0.5f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, 0.5f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, -0.5f, /*norm*/ 0.0f, 1.0f, 0.0f};

// quad with color and texture atributes. Uses indices
const float quad[] = {
    /*pos*/ -0.5, 0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0, /*txt*/ 0.0, 1.0,
    /*pos*/ 0.5, 0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0, /*txt*/ 1.0, 1.0,
    /*pos*/ -0.5, -0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0, /*txt*/ 0.0, 0.0,
    /*pos*/ 0.5, -0.5, 0.0, /*clr*/ 0.5, 0.0, 0.0, /*txt*/ 1.0, 0.0};
const int quadIndices[] = {
    0, 1, 2, 1, 2, 3};

// cube with texture atributes and normals
const float cube_textured_normals[] = {
    /*pos*/ -0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ -0.5f, 0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 0.0f, 0.0f, -1.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ 0.0f, 0.0f, -1.0f,

    /*pos*/ -0.5f, -0.5f, 0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ -0.5f, 0.5f, 0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 0.0f, 0.0f, 1.0f,
    /*pos*/ -0.5f, -0.5f, 0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ 0.0f, 0.0f, 1.0f,

    /*pos*/ -0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, -0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, 0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ -1.0f, 0.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ -1.0f, 0.0f, 0.0f,

    /*pos*/ 0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ 1.0f, 0.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 1.0f, 0.0f, 0.0f,

    /*pos*/ -0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, -0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ 0.5f, -0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, 0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ 0.0f, -1.0f, 0.0f,
    /*pos*/ -0.5f, -0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 0.0f, -1.0f, 0.0f,

    /*pos*/ -0.5f, 0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, -0.5f, /*txt*/ 1.0f, 1.0f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ 0.5f, 0.5f, 0.5f, /*txt*/ 1.0f, 0.0f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, 0.5f, /*txt*/ 0.0f, 0.0f, /*norm*/ 0.0f, 1.0f, 0.0f,
    /*pos*/ -0.5f, 0.5f, -0.5f, /*txt*/ 0.0f, 1.0f, /*norm*/ 0.0f, 1.0f, 0.0f};

#endif