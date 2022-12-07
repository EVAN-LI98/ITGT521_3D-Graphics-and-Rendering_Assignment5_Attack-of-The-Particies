//
// Created by YifanLi.
//

#if _MSC_VER >= 1400
#define _CRT_SECURE_NO_DEPRECATE				// shut up the vc8 compiler
#define _CRT_NONSTDC_NO_DEPRECATE
#endif

#ifndef ASSIGNMENT5_SCENE_OBJECTS_H
#define ASSIGNMENT5_SCENE_OBJECTS_H

#include <gmtl/gmtl.h>

namespace scene_object
{
    void LoadPPM(const char *fname, unsigned int *w, unsigned int *h, unsigned char **data, int mallocflag);
    void LoadTexture();
    void drawCylinder(const float radius, const float height);
    void DrawPlaneBody(const float width, const float length, const float height);
    void DrawPropeller(const float width, const float length, const float height);
    void DrawPropeller2(const float width, const float length, const float height);
    void DrawSubPropeller(const float width, const float length, const float height);
    void DrawSubPropeller2(const float width, const float length, const float height);
    void DrawSkybox(const float s);
    void DrawLightSource(const float radius);
}

#endif //ASSIGNMENT5_SCENE_OBJECTS_H
