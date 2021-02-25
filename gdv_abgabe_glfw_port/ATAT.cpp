#include "ATAT.h"

void ATAT::drawBodySetup(GLfloat scale) {



    //yellow -> top left
    //red -> top right
    //blue -> bottom left
    //green -> bottom right

    float vertices[] = {
        // positions                                                                    colors                  texture coord

    //========== mittelteil ==========

    //mittlere unterseite
    bLength * scale, bLowerHight * scale, (-bLowerWidth) * scale,          1.0f, 1.0f, 1.0f,      1.0f, 1.0f,     // top right        0
    bLength * scale,  bLowerHight * scale, (bLowerWidth)*scale,             1.0f, 1.0f, 1.0f,     1.0f, 0.0f,     // bottom right     1
    (-bLength) * scale,  bLowerHight * scale, (bLowerWidth)*scale,         1.0f, 1.0f, 1.0f,     0.0f, 0.0f,     // bottom left      2
    (-bLength) * scale, bLowerHight * scale, (-bLowerWidth) * scale,          1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     // top left         3

    //mittlere linke Seite
     bLength * scale, bUpperHight * scale, (-bUpperWidth) * scale,         1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // top right        4
     bLength * scale, bLowerHight * scale, (-bLowerWidth) * scale,         1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     //bottom right      5                                                  // bottom right
    (-bLength) * scale, bLowerHight * scale, (-bLowerWidth) * scale,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // bottom left      6
    (-bLength) * scale,  bUpperHight * scale, (-bUpperWidth) * scale,      1.0f, 1.0f, 1.0f,       0.0f, 1.0f,      // top left        7

    ///rechte mittlere Seite
     bLength * scale, bUpperHight * scale, bUpperWidth * scale,            1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // top right        8
     bLength * scale, bLowerHight * scale, (bLowerWidth)*scale,           1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     //bottom right      9                                           // bottom right
    (-bLength) * scale, bLowerHight * scale, (bLowerWidth)*scale,        1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // bottom left      10
    (-bLength) * scale,  bUpperHight * scale, bUpperWidth * scale,         1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // top left         11

    //mittlere oberseite
    bLength * scale, bUpperHight * scale, (-bUpperWidth) * scale,          1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     //                  12
    bLength * scale,  bUpperHight * scale, bUpperWidth * scale,             1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // top left         13
    (-bLength) * scale,  bUpperHight * scale, bUpperWidth * scale,         1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     //                  14
    (-bLength) * scale, bUpperHight * scale, (-bUpperWidth) * scale,       1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     //                  15

    //========== schrägen hinten ==========

    //linke schrägseite
    (-bLength) * scale,  bUpperHight * scale, (-bUpperWidth) * scale,                                           1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 16 top right
    (-bLength) * scale, bLowerHight * scale, (-bLowerWidth) * scale,                                           1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 17 bottom left
    (-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                  1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 18 bottom
    (-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 19 top right

    //untere Schrägseite
    (-bLength) * scale,  bLowerHight * scale, (-bLowerWidth) * scale,                                          1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 20 top right
    (-bLength) * scale, bLowerHight * scale, (bLowerWidth)*scale,                                            1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 21 bottom left
    (-bLength - zLengthMod) * scale,  bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                  1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 22 top right
    (-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                  1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 23 bottom left

    //rechte schrägseite
    (-bLength) * scale,  bUpperHight * scale, (bUpperWidth)*scale,                                           1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 24 top right
    (-bLength) * scale, bLowerHight * scale, (bLowerWidth)*scale,                                            1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 25 bottom left
    (-bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                   1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 26 bottom
    (-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 27 top right

    //obere Schrägseite
     (-bLength) * scale,  bUpperHight * scale, (-bUpperWidth) * scale,                                         1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 28 top right
    (-bLength) * scale, bUpperHight * scale, (bUpperWidth)*scale,                                            1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 29 bottom left
    (-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 30 top right
    (-bLength - zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 31 bottom left

    //========== hintere Seiten ==========

    //unterseite
    (-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                              1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 32 bottom left
    (-bLength - zLengthMod) * scale,  bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                              1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 33 top right
    (-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,        1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //34
    (-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //35

    //linke seite
    (-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,                                               1.0f, 1.0f, 1.0f,       1.0f, 1.0f, // 36 bottom left
    (-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                                                              1.0f, 1.0f, 1.0f,       1.0f, 0.0f, // 37 bottom left
    (-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,                                    1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //38
    (-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //39

    //oberseite
    (-bLength - zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,                                                1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 40 bottom left
    (-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,                                                1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 41 top right
    (-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,      1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //42
    (-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //43

    //rechte Seite
    (-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,                                               1.0f, 1.0f, 1.0f,       1.0f, 1.0f, // 44 bottom left
    (-bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                                                              1.0f, 1.0f, 1.0f,       1.0f, 0.0f, // 45 bottom left
    (-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,                                    1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //46
    (-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //47

    //hintere Seite
    (-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       1.0f, 1.0f, //48
    (-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,      1.0f, 1.0f, 1.0f,       1.0f, 0.0f, //49
    (-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,                                     1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //50
    (-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,                                    1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //51

    //========== schrägen vorne ==========

     //linke schrägseite
    (bLength)*scale,  bUpperHight * scale, (-bUpperWidth) * scale,                                           1.0f, 1.0f, 1.0f,       0.2f, 1.0f,     // 52 top right
    (bLength)*scale, bLowerHight * scale, (-bLowerWidth) * scale,                                            1.0f, 1.0f, 1.0f,       0.2f, 0.0f,     // 53 bottom left
    (bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                   1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 54 bottom
    (bLength + zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 55 top right

    //untere Schrägseite
    (bLength)*scale,  bLowerHight * scale, (-bLowerWidth) * scale,                                           1.0f, 1.0f, 1.0f,       0.2f, 1.0f,     // 56 top right
    (bLength)*scale, bLowerHight * scale, (bLowerWidth)*scale,                                              1.0f, 1.0f, 1.0f,       0.2f, 0.0f,     // 57 bottom left
    (bLength + zLengthMod) * scale,  bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                   1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 58 top right
    (bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                   1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 59 bottom left

    //rechte schrägseite
    (bLength)*scale,  bUpperHight * scale, (bUpperWidth)*scale,                                             1.0f, 1.0f, 1.0f,       0.2f, 1.0f,     // 60 top right
    (bLength)*scale, bLowerHight * scale, (bLowerWidth)*scale,                                               1.0f, 1.0f, 1.0f,       0.2f, 0.0f,     // 61 bottom left
    (bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                    1.0f, 1.0f, 1.0f,   0.0f, 0.0f,     // 62 bottom
    (bLength + zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     // 63 top right

    //obere Schrägseite
     (bLength)*scale,  bUpperHight * scale, (-bUpperWidth) * scale,                                               1.0f, 1.0f, 1.0f,       0.5f, 0.3f,     // 64 top right
    (bLength)*scale, bUpperHight * scale, (bUpperWidth)*scale,                                                   1.0f, 1.0f, 1.0f,       0.0f, 0.3f,     // 65 bottom left
    (bLength + zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,         1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 66 top right
    (bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,         1.0f, 1.0f, 1.0f,       0.5f, 0.0f,     // 67 bottom left


    //========== vordere Seiten ==========

    //unterseite
    (bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,     // 68 bottom left
    (bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,     // 69 top right
    (cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //70
    (cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //71

    //linke seite
    (bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 72 bottom left
    (bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 73 bottom left
    (cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //74
    (cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //75

    //oberseite
    (bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,     // 76 bottom left
    (bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,     // 77 top right
    (cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //78
    (cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //79

    //rechte Seite
    (bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 80 bottom left
    (bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 81 bottom left
    (cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //82
    (cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //83

    //hintere Seite
    (cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //84
    (cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //85
    (cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //86
    (cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //87

    };
    unsigned int indices[] = {  // note that we start from 0!

        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,

        24, 25, 26,
        26, 27, 24,

        28, 29, 30,
        30, 31, 28,

        32, 33, 34,
        34, 35, 32,

        36, 37, 38,
        38, 39, 36,

        40, 41, 42,
        42, 43, 40,

        44, 45, 46,
        46, 47, 44,

        48, 49, 50,
        50, 51, 48,

        52, 53, 54,
        54, 55, 52,

        56, 57, 58,
        58, 59, 56,

        60, 61, 62,
        62, 63, 60,

        64, 65, 66,
        66, 67, 64,

        68, 69, 70,
        70, 71, 68,

        72, 73, 74,
        74, 75, 72,

        76, 77, 78,
        78, 79, 76,

        80, 81, 82,
        82, 83, 80,

        84, 85, 86,
        86, 87, 84,
    };


    glGenVertexArrays(1, &testVAO);
    glGenBuffers(1, &testVBO);
    glGenBuffers(1, &testEBO);


    //bind the VAO first, then bind and set vertex buffer(s), then config vertex attributes.
    glBindVertexArray(testVAO);

    glBindBuffer(GL_ARRAY_BUFFER, testVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);


    //uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//load and create a texture
void ATAT::loadTextures() {

    //unsigned int darkMetalTexture;
    //darkMetalTexture = SOIL_load_
    glGenTextures(1, &darkMetalTexture);
    glBindTexture(GL_TEXTURE_2D, darkMetalTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width, height, nrChannels;
    //unsigned char* data = SOIL_load_image("resources/greymetal.jpg", &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load("resources/greymetal.jpg", &width, &height, &nrChannels, 0);

    if (data) {
        std::cout << "data is valid" << std::endl;

        //The crash problem is probably caused by glTexImage2D reading past the bounds of your data buffer.

        //glPixelStorei sets pixel storage modes that affect the operation of subsequent glReadPixels
        //as well as the unpacking of texture patterns (see glTexImage2D and glTexSubImage2D).

        //Specifies the alignment requirements for the start of each pixel row in memory. The allowable values are
        //1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load greymetalTexture" << std::endl;
    }

    stbi_image_free(data);

}

void ATAT::redrawBody()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, darkMetalTexture);

    glBindVertexArray(testVAO);
    glDrawElements(GL_TRIANGLES, 132, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
    //glActiveTexture(0);
}


void ATAT::drawLFUpperLegSetup(GLfloat scale) {

    //yellow -> top left
    //red -> top right
    //blue -> bottom left
    //green -> bottom right

    float vertices[] = {
        // positions                                                                    colors                  texture coord

    //========== mittelteil ==========

    //oberseite
        ((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      1.0f, 1.0f,  //0 vorne links
        ((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      1.0f, 0.0f,  //1 vorne rechts
        ((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.0f, 0.0f,  //2 hinten rechts
        ((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      0.0f, 1.0f,  //3 hinten links

    //unterseite
        ((legLength)*scale), ((kneeHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      1.0f, 1.0f,  //4
        ((legLength)*scale), ((kneeHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      1.0f, 0.0f,  //5
        ((-legLength) * scale), ((kneeHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.0f, 0.0f,  //6
        ((-legLength) * scale), ((kneeHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      0.0f, 1.0f,  //7

    //bei den seiten 0 und 1 oben, 2 und 3 unten
        //linke Seite
        ((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      1.0f, 1.0f,  //8
        ((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      1.0f, 0.0f,  //9
        ((-legLength) * scale), ((kneeHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.0f, 0.0f,  //10
        ((legLength)*scale), ((kneeHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.0f, 1.0f,  //11

        //rechte Seite
        ((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      1.0f, 1.0f,  //12
        ((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      1.0f, 0.0f,  //13
        ((legLength)*scale), ((kneeHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      0.0f, 0.0f,  //14
        ((-legLength) * scale), ((kneeHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      0.0f, 1.0f,  //15

        //vordere Seite
        ((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      1.0f, 1.0f,  //16
        ((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      1.0f, 0.0f,  //17
        ((legLength)*scale), ((kneeHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.0f, 0.0f,  //18
        ((legLength)*scale), ((kneeHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      0.0f, 1.0f,  //19

        //hintere Seite
        ((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      1.0f, 1.0f,  //20
        ((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      1.0f, 0.0f,  //21
        ((-legLength) * scale), ((kneeHeight)*scale), ((legWidth)*scale),             1.0f, 1.0f, 1.0f,      0.0f, 0.0f,  //22
        ((-legLength) * scale), ((kneeHeight)*scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.0f, 1.0f,  //23

    };
    unsigned int indices[] = {  // note that we start from 0!

        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
    };


    glGenVertexArrays(1, &legVAO);
    glGenBuffers(1, &legVBO);
    glGenBuffers(1, &legEBO);


    //bind the VAO first, then bind and set vertex buffer(s), then config vertex attributes.
    glBindVertexArray(legVAO);

    glBindBuffer(GL_ARRAY_BUFFER, legVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, legEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);


    //uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void ATAT::redrawUpperLeg() {

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, darkMetalTexture);

    glActiveTexture(0);
    glBindTexture(NULL, 0);

    glBindVertexArray(legVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
    //glActiveTexture(0);

}




void ATAT::initialDraw() {

    glm::mat4 model = glm::mat4(1.0f);
    atatShader.use();

    model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
    atatShader.setMat4("model", model);
    redrawBody();

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(bLength * 2, 0.0f, bLowerWidth * 2));
    atatShader.setMat4("model", trans);
    redrawUpperLeg();

    model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
    atatShader.setMat4("model", model);
    redrawUpperLeg();
    //atat.redrawUpperLeg();
    //model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
    //sm.setMat4("model", model);
    //atat.redrawBody();
}


/*
    model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
    sm.setMat4("model", model);
    atat.redrawBody();
    atat.redrawUpperLeg();
    model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
    sm.setMat4("model", model);
    atat.redrawUpperLeg();
    //atat.redrawUpperLeg();
    //model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
    //sm.setMat4("model", model);
    //atat.redrawBody();
    */