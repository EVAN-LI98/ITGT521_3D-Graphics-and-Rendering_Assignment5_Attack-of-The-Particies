//
// Created by YifanLi.
//

#include "scene_renderer.h"
#include "scene_objects.h"
#include <GL/glut.h>
#include <gmtl/gmtl.h>

namespace scene_renderer
{
    // Lighting 可以调整光的大小
    const GLfloat NO_LIGHT[] = { 0.0, 0.0, 0.0, 1.0 };
    const GLfloat AMBIENT_LIGHT[] = { 0.5, 0.5, 0.5, 1.0 };
    const GLfloat DIFFUSE_LIGHT[] = { 0.55, 0.55, 0.55, 1.0 };
    const GLfloat SPECULAR_LIGHT[] = { 0.7, 0.7, 0.7, 1.0 };

    /*const GLfloat NO_LIGHT[] = { 0.0, 0.0, 0.0, 1.0 };
    const GLfloat AMBIENT_LIGHT[] = { 0.2, 0.2, 0.2, 1.0 };
    const GLfloat DIFFUSE_LIGHT[] = { 0.7, 0.7, 0.7, 1.0 };
    const GLfloat SPECULAR_LIGHT[] = { 0.7, 0.7, 0.7, 1.0 };
    */


    gmtl::Point4f light_pos(420.0, 120.0, 200.0, 1.0);
    //gmtl::Point4f light_pos(0.0, 600.0, 0.0, 1.0);

    /* Plane Constant */
    // Plane dimensions
    const float P_WIDTH = 3.0f;
    const float P_LENGTH = 3.0f;
    const float P_HEIGHT = 1.5f;

    // Propeller dimensions (subpart)
    const float PP_WIDTH = 0.25f;
    const float PP_LENGTH = 1.5f;

    // Propeller transforms
    const gmtl::Point3f PROPELLER_POS(5, 0.25, 5.5);     // Propeller0 position on the plane (w.r.t. plane's frame) 
    const gmtl::Point3f PROPELLER_POS1(-5, 0.25, 5.5);     // Propeller1 position on the plane (w.r.t. plane's frame) 
    const gmtl::Point3f PROPELLER_POS2(0, 0, 0);         // Propeller2 position on the plane (w.r.t. plane's frame)
    const float PROPELLER_ROTATION = 5.0f;               // Propeller rotated by 5 degs per input

    // Propeller rotation (subpart)
    bool isRotateUp = true;

    float pp_angle = 0;         // Rotation angle 
    float pp_angle_l = 0;         // Rotation front angle
    float pp_angle_t = 0;         // Rotation left angle
    float pp_angle_ss = 0;         // Rotation subpropeller1 angle
    float pp_angle_ss2 = 0;         // Rotation subpropeller2 angle
    
    void SceneInit() {

        // Disable global ambient
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, NO_LIGHT);

        // NOTE: for specular reflections, the "local viewer" model produces better
        // results than the default, but is slower. The default would not use the correct
        // vertex-to-eyepoint vector, treating it as always parallel to Z.
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

        // Disable two sided lqighting because we cannot see the inside of the most object in the scene (except satellite)
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

        // Enable lighting
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        //Load Texture
        scene_object::LoadTexture();
    }

    //|____________________________________________________________________
    //|
    //| Function: SetLight
    //|
    //! \param pos          [in] Light position.
    //! \param is_ambient   [in] Is ambient enabled?
    //! \param is_diffuse   [in] Is diffuse enabled?
    //! \param is_specular  [in] Is specular enabled?
    //! \return None.
    //!
    //! Set light properties.
    //|____________________________________________________________________
    void SetLight(const gmtl::Point4f& pos, const bool is_ambient, const bool is_diffuse, const bool is_specular)
    {
        glLightfv(GL_LIGHT0, GL_POSITION, pos.mData);
        if (is_ambient) {
            glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT_LIGHT);
        }
        else {
            glLightfv(GL_LIGHT0, GL_AMBIENT, NO_LIGHT);
        }
        if (is_diffuse) {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE_LIGHT);
        }
        else {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, NO_LIGHT);
        }
        if (is_specular) {
            glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR_LIGHT);
        }
        else {
            glLightfv(GL_LIGHT0, GL_SPECULAR, NO_LIGHT);
        }
    }

    void AnimateWing() {
        if (isRotateUp) {
            pp_angle += PROPELLER_ROTATION;
            pp_angle_t += PROPELLER_ROTATION;
        }
        else {
            pp_angle -= PROPELLER_ROTATION;
            pp_angle_t -= PROPELLER_ROTATION;
        }

        if (pp_angle >= 30 || pp_angle_t <= 30) {
            isRotateUp = false;
        }
        else if (pp_angle <= 0 || pp_angle_t >= 0) {
            isRotateUp = true;
        }

      /*  if (pp_angle >= 30 || pp_angle_2 <= -30) {
            isRotateUp = false;
        }
        else if (pp_angle <= -10 || pp_angle_2 >= 10) {
            isRotateUp = true;
        }
        */
    }
    

    void AnimateWing2() {
        if (isRotateUp) {
            pp_angle_l += PROPELLER_ROTATION;
        }
        else {
            pp_angle_l -= PROPELLER_ROTATION;
        }

        if (pp_angle_l >= 30) {
            isRotateUp = false;
        }
        else if (pp_angle_l <= 0) {
            isRotateUp = true;
        }
    }

    void AnimateWing3() {
        if (isRotateUp) {
            pp_angle_ss += PROPELLER_ROTATION;
        }
        else {
            pp_angle_ss -= PROPELLER_ROTATION;
        }

        if (pp_angle_ss >= 30) {
            isRotateUp = false;
        }
        else if (pp_angle_ss <= 0) {
            isRotateUp = true;
        }
    }


    void RenderPlane(const gmtl::Matrix44f& ppose) {

        // Plane 2 body:
        glPushMatrix();
        glMultMatrixf(ppose.mData);
        scene_object::DrawPlaneBody(P_WIDTH, P_LENGTH, P_HEIGHT);

        //right Propeller (subpart):
        glPushMatrix();
        glTranslatef(PROPELLER_POS1[0], PROPELLER_POS1[1], PROPELLER_POS1[2]);     // Positions right propeller on the plane
        glRotatef(pp_angle, 0, 1, 0);                                           // Rotates propeller
        scene_object::DrawPropeller(P_WIDTH, P_LENGTH, P_HEIGHT);
        glPopMatrix();

        //left Propeller (subpart):
        glPushMatrix();
        glTranslatef(PROPELLER_POS[0], PROPELLER_POS[1], PROPELLER_POS[2]);     // Positions left propeller on the plane
        glRotatef(-pp_angle_t, 0, 1, 0);                                           // Rotates propeller
        scene_object::DrawPropeller(P_WIDTH, P_LENGTH, P_HEIGHT);
        glPopMatrix();

        //Front Propeller (subpart):
        glPushMatrix();
        glTranslatef(PROPELLER_POS2[0], PROPELLER_POS2[1], PROPELLER_POS2[2]);     // Positions front propeller on the plane
        glRotatef(pp_angle_l, 0, 0, 1);                                           // Rotates propeller
        scene_object::DrawPropeller2(P_WIDTH, P_LENGTH, P_HEIGHT);
        glPopMatrix();

        // Subsubpart1:
        glPushMatrix();
        glTranslatef(PROPELLER_POS2[0], PROPELLER_POS2[1], PROPELLER_POS2[2]);                                        // Positions subpropeller on the plane
        glRotatef(pp_angle_ss, 0, 0, 1);
        scene_object::DrawSubPropeller(P_WIDTH, P_LENGTH, P_HEIGHT);

        // Subsubpart2:
        glPushMatrix();
        glTranslatef(PROPELLER_POS2[0], PROPELLER_POS2[1], PROPELLER_POS2[2]);                                        // Positions subpropeller on the plane
        glRotatef(pp_angle_ss2, 0, 1, 0);
        scene_object::DrawSubPropeller2(P_WIDTH, P_LENGTH, P_HEIGHT);
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

    }

    void RenderScene(const gmtl::Matrix44f& ppose) {
        SetLight(light_pos, true, true, true);

        glPushMatrix();
        glTranslatef(light_pos[0], light_pos[1], light_pos[2]);
        scene_object::DrawLightSource(0.5);
        glPopMatrix();

        scene_object::DrawSkybox(5000);
        RenderPlane(ppose);
    }
}

