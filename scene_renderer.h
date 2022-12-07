//
// Created by YifanLi.
//

#if _MSC_VER >= 1400
#define _CRT_SECURE_NO_DEPRECATE				// shut up the vc8 compiler
#define _CRT_NONSTDC_NO_DEPRECATE
#endif

#ifndef ASSIGNMENT5_SCENE_RENDERER_H
#define ASSIGNMENT5_SCENE_RENDERER_H

#include <gmtl/gmtl.h>

namespace scene_renderer
{
    void SceneInit();
    void AnimateWing();
    void AnimateWing2();
    void AnimateWing3();
    void RenderPlane(const gmtl::Matrix44f& ppose);
    void RenderScene(const gmtl::Matrix44f& ppose);
}
#endif //ASSIGNMENT5_SCENE_RENDERER_H
