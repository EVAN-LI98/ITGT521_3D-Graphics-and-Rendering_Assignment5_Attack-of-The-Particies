//
// Created by YifanLi.
//

#include "scene_objects.h"
#include <GL/glut.h>
#include <gmtl/gmtl.h>

namespace scene_object
{
    // Materials ʹ�õ�����ɫ ��������ں������ֱ��ʹ��
    const GLfloat DARKRED_COL[] = { 0.1, 0.0, 0.0, 1.0 };
    const GLfloat BRIGHTRED_COL[] = { 0.7, 0.0, 0.0, 1.0 };
    const GLfloat DARKBLUE_COL[] = { 0.0, 0.0, 0.1, 1.0 };
    const GLfloat BRIGHTBLUE_COL[] = { 0.0, 0.0, 0.7, 1.0 };
    const GLfloat BLUE_COL[] = { 0.0, 0.3, 0.1, 1.0 };
    const GLfloat DARK_COL[] = { 0.1, 0.1, 0.1, 1.0 };
    const GLfloat MEDIUMWHITE_COL[] = { 0.7, 0.7, 0.7, 1.0 };
    const GLfloat SPECULAR_COL[] = { 0.7, 0.7, 0.7, 1.0 };
    const GLfloat GREEN_COL[] = { 0.55,0.95,0.64,1.0 };
	const GLfloat LGREEN_COL[] = { 0.62,0.43,0.90,1.0 };
	const GLfloat LBLUEE_COL[] = { 0.13,1.00,0.84,1.0 };
	const GLfloat LBLUE_COL[] = { 0.62,0.43,0.90,1.0 };
	const GLfloat LLGREEN_COL[] = { 0.72,0.23,0.65,1.0 };
	const GLfloat LYELLOW_COL[] = { 0.0,0.08,0.31,1.0 };
    const GLfloat DARKGREEN_COL[] = { 0.0, 0.1, 0.0, 1.0 };
    const GLfloat DARKGRAY_COL[] = { 0.26, 0.26, 0.26, 1.0 };
    const GLfloat GRAY_COL[] = { 0.75, 0.75, 0.75, 1.0 };
    const GLfloat WHITE_COL[] = { 1.0, 1.0, 1.0, 1.0 };
	const GLfloat O_COL[] = { 0.96, 0.88, 0.96, 1.0 };
    const GLfloat PASTEL_COL[] = { 1.0, 0.69, 0.94, 1.0 };
    const GLfloat PASTELDARKER_COL[] = { 0.90, 0.59, 0.69, 1.0 };
    const GLfloat RED_COL[] = { 0.90, 0.00, 0.00, 1.0 };
	const GLfloat LRED_COL[] = { 0.03, 0.88, 0.94, 1.0 };
	const GLfloat MEDIUMYELLOW_COL[] = { 0.75, 0.40, 0.00, 1.0 };
	const GLfloat LIGHT_COL[] = { 199, 237, 204, 1.0 };
	const GLfloat Purple_COL[] = { 0.65, 0.91, 0.95, 1.0 };
	const GLfloat GREENL_COL[] = { 0.36, 0.51, 0.85, 1.0 };

    // Textures
    enum TextureID { TID_SKYBACK = 0, TID_SKYLEFT, TID_SKYBOTTOM, TID_SKYTOP, TID_SKYFRONT, TID_SKYRIGHT, TEXTURE_NB };  // Texture IDs, with the last ID indicating the total number of textures
    
   // Textures  //��Ҫ��ӵĲ�������
    GLuint textures[TEXTURE_NB];                           // Textures
    GLuint satellite_wing;
    GLuint cloud_texture;
    GLuint flower_texture;
    GLuint plane_wing2;
	GLuint CAT_texture;

    void LoadPPM(const char *fname, unsigned int *w, unsigned int *h, unsigned char **data, int mallocflag) {
        FILE *fp;
        char P, num;
        int max;
        char s[1000];

        if (!(fp = fopen(fname, "rb"))) {
            perror("cannot open image file\n");
            exit(0);
        }

        fscanf(fp, "%c%c\n", &P, &num);
        if ((P != 'P') || (num != '6')) {
            perror("unknown file format for image\n");
            exit(0);
        }

        do {
            fgets(s, 999, fp);
        } while (s[0] == '#');


        sscanf(s, "%d%d", w, h);
        fgets(s, 999, fp);
        sscanf(s, "%d", &max);

        if (mallocflag)
            if (!(*data = (unsigned char *) malloc(*w * *h * 3))) {
                perror("cannot allocate memory for image data\n");
                exit(0);
            }

        fread(*data, 3, *w * *h, fp);

        fclose(fp);
    }

    void LoadTexture() {
        unsigned char *img_data;               // Texture image data
        unsigned int width;                   // Texture width
        unsigned int height;                  // Texture height

        // Describe how data will be stored in memory
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Select the method for combining texture color with the lighting equation
        // (look up the third parameter)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        // Generate and setup texture objects
        glGenTextures(TEXTURE_NB, textures);

        // Skybox back wall ��պ��Ӻ�
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYBACK]);
        LoadPPM("skybox_back.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Skybox left wall ��պ�����
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYLEFT]);
        LoadPPM("skybox_left.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Skybox buttom wall ��պ����·�
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYBOTTOM]);
        LoadPPM("skybox_bottom.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // TODO: Initializes the remaining textures

        // Skybox front wall ��պ���ǰ��
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYFRONT]);
        LoadPPM("skybox_front.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Skybox right wall ��պ����ҷ�
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYRIGHT]);
        LoadPPM("skybox_right.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Skybox top wall ��պ����Ϸ�
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYTOP]);
        LoadPPM("skybox_top.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Wings Texture1 ������ͼ
        glGenTextures(1, &cloud_texture);
        glBindTexture(GL_TEXTURE_2D, cloud_texture);
        LoadPPM("cloud_texture.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Wings Texture1 ������ͼ1
        glGenTextures(1, &flower_texture);
        glBindTexture(GL_TEXTURE_2D, flower_texture);
        LoadPPM("flower_texture.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Wings Texture2 ������ͼ2
        glBindTexture(GL_TEXTURE_2D, plane_wing2);
        LoadPPM("wings_texture2.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Satellite Wing Texture  ������ͼ
        glGenTextures(1, &satellite_wing);
        glBindTexture(GL_TEXTURE_2D, satellite_wing);
        LoadPPM("satellite_wing.ppm", &width, &height, &img_data, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
        free(img_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//CAT Texture  èè��ͼ
		glGenTextures(1, &CAT_texture);
		glBindTexture(GL_TEXTURE_2D, CAT_texture);
		LoadPPM("CAT_texture.ppm", &width, &height, &img_data, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
		free(img_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        /*
        glGenTextures          ��������������ĺ���
        glBindTexture          ������һ���󶨵�Ŀ������������Ƶ�����
        glTexImage2D          �����Ǹ���ָ���Ĳ���������һ��2D����
        glTexParameteri          (������˺���),ͼ�������ͼ��ռ�ӳ�䵽֡����ͼ��ռ�(ӳ����Ҫ���¹�������ͼ��,
        �����ͻ����Ӧ�õ�������ϵ�ͼ��ʧ��),��ʱ�Ϳ���glTexParmeteri()������ȷ����ΰ���������ӳ�������.
        GL_UNSIGNED_BYTE          ��һ������������������ָʾ������ָ���д���GLubyte��sizeof(GLubyte)���ݶ�������1
        GL_LINEAR         Ҳ�����Թ���,(Bi)linear Filtering)��������������긽������������,�����һ����ֵ,���Ƴ���Щ��������֮�����ɫ,
        һ���������ص����ľ�����������Խ��,��ô����������ص���ɫ�����յ�������ɫ�Ĺ���Խ��
        */
    }

    void drawCylinder(const float radius, const float height) {
        int a;
        float x, y, xp, yp, mag;
        bool bright_col = true;

        xp = radius;
        yp = 0;
        glBegin(GL_QUADS);
        for (a = 1; a <= 360; a++) {
            x = radius * cos(gmtl::Math::deg2Rad((float) a));
            y = radius * sin(gmtl::Math::deg2Rad((float) a));

            //mag = sqrt(pow(x, 2) + pow(y, 2) + pow(height / 2, 2));
            gmtl::Vec3f normal(x, y, 0.0);
            gmtl::normalize(normal);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(xp, yp, height);
            glVertex3f(xp, yp, 0);
            glVertex3f(x, y, 0);
            glVertex3f(x, y, height);

            xp = x;
            yp = y;
        }
        glEnd();
    }

	//�ɻ�1
	void DrawPlaneBody(const float width, const float length, const float height)
	{
		float w = width / 2;
		float l = length / 2;


		glBegin(GL_POLYGON);
		//1
		//���ŵ��²���
		// Sets materials
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 110.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREENL_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LBLUEE_COL);
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�ǰ�ɫwhite
		glVertex3f(0.0f, 1.0f, 0.5f);//
		glVertex3f(0.0f, 0.25f, 1.0f);//
		glVertex3f(0.0f, 0.5f, 4.0f);//
		glVertex3f(0.0f, 1.4f, 2.0f);//
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�ǰ�ɫwhite

		//���ŵ��ϲ���
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, RED_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		glColor3f(0.0f, 3.0f, 1.0f);//��ɫ����ɫblue
		glVertex3f(0.0f, 1.4f, 2.0f);//
		glVertex3f(0.0f, 3.0f, 1.0f);//
		glVertex3f(0.0f, 3.0f, 0.0f);//
		glVertex3f(0.0f, 1.0f, 0.5f);//
		glColor3f(0.0f, 3.0f, 1.0f);//��ɫ����ɫblue
		glEnd();

		//2
		glBegin(GL_POLYGON);
		//���ŵ��Ұ벿��
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LGREEN_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREENL_COL);
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�ǰ�white
		glVertex3f(0.0f, 2.0f, 0.25f);//
		glVertex3f(1.0f, 2.0f, -0.5f);//
		glVertex3f(2.0f, 2.0f, -0.5f);//
		glVertex3f(0.0f, 2.0f, 1.40f);//

		//���ŵ���벿��
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LGREEN_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREENL_COL);
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�ǰ�white
		glVertex3f(0.0f, 2.0f, 0.25f);//
		glVertex3f(-1.0f, 2.0f, -0.5f);//
		glVertex3f(-2.0f, 2.0f, -0.5f);//
		glVertex3f(0.0f, 2.0f, 1.40f);//
		glEnd();

		//3
		//��ͷ����
		glBegin(GL_TRIANGLES);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RED_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, WHITE_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LLGREEN_COL);
		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ�Ǻ�red
		glVertex3f(-1.0f, 0.5f, 10.0f);//
		glVertex3f(1.0f, 0.5f, 10.0f);//
		glVertex3f(0.0f, 0.0f, 13.5f);//
		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ�Ǻ�red
		glEnd();
		glBegin(GL_TRIANGLES);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GREEN_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LGREEN_COL);
		//glColor3f(0.0f, 0.0f, 0.0f);//��ɫ�Ǻ�black
		glColor3f(0.3f, 0.0f, 0.0f);//��ɫ�ǵ���red
		glVertex3f(1.0f, 0.5f, 10.0f);//
		glVertex3f(2.0f, -0.2f, 10.0f);//
		glVertex3f(0.0f, 0.0f, 13.5f);//
		glColor3f(0.3f, 0.0f, 0.0f);//��ɫ�ǵ���red
		glEnd();
		glBegin(GL_TRIANGLES);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RED_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LGREEN_COL);
		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ�Ǻ�red
		glVertex3f(2.0f, -0.2f, 10.0f);//
		glVertex3f(-2.0f, -0.2f, 10.0f);//
		glVertex3f(0.0f, 0.0f, 13.5f);//
		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ�Ǻ�red
		glEnd();
		glBegin(GL_TRIANGLES);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		//glColor3f(0.0f, 0.0f, 0.0f);//��ɫ�Ǻ�black
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�ǰ�
		glVertex3f(-2.0f, -0.2f, 10.0f);//
		glVertex3f(-1.0f, 0.5f, 10.0f);//
		glVertex3f(0.0f, 0.0f, 13.5f);//
		glEnd();

		//4
		//�ɻ���ʻ��
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(0.0f, 0.5f, 10.0f);//
		glVertex3f(0.25f, 1.5f, 9.25f);//
		glVertex3f(-0.25f, 1.5f, 9.25f);//
		glEnd();
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(0.0f, 0.5f, 10.0f);//
		glVertex3f(0.25f, 1.5f, 9.25f);//
		glVertex3f(1.0f, 0.5f, 9.0f);//
		glEnd();
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(0.0f, 0.5f, 10.0f);//
		glVertex3f(-0.25f, 1.5f, 9.25f);//
		glVertex3f(-1.0f, 0.5f, 9.0f);//
		glEnd();

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 110.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(-1.0f, 0.5f, 9.0f);//
		glVertex3f(-0.25f, 1.5f, 9.25f);//
		glVertex3f(-0.25f, 1.5f, 7.75f);//
		glVertex3f(-1.0f, 0.5f, 8.0f);//
		glEnd();
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(0.25f, 1.5f, 9.25f);//
		glVertex3f(-0.25f, 1.5f, 9.25f);//
		glVertex3f(-0.25f, 1.5f, 7.75f);//
		glVertex3f(0.25f, 1.5f, 7.75f);//
		glEnd();
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(1.0f, 0.5f, 9.0f);//
		glVertex3f(0.25f, 1.5f, 9.25f);//
		glVertex3f(0.25f, 1.5f, 7.75f);//
		glVertex3f(1.0f, 0.5f, 8.0f);//
		glEnd();

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(0.0f, 0.5f, 7.0f);//
		glVertex3f(0.25f, 1.5f, 7.75f);//
		glVertex3f(-0.25f, 1.5f, 7.75f);//
		glEnd();
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(0.0f, 0.5f, 7.0f);//
		glVertex3f(0.25f, 1.5f, 7.75f);//
		glVertex3f(1.0f, 0.5f, 8.0f);//
		glEnd();
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����blue
		glVertex3f(0.0f, 0.5f, 7.0f);//
		glVertex3f(-0.25f, 1.5f, 7.75f);//
		glVertex3f(-1.0f, 0.5f, 8.0f);//
		glEnd();

		//5
		//����
		glBegin(GL_QUADS);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DARK_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, DARKRED_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LLGREEN_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LRED_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LRED_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LBLUE_COL);
		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ�Ǻ�red
		glVertex3f(-0.25f, 0.25f, 1.0f);//
		glVertex3f(0.25f, 0.25f, 1.0f);//
		glVertex3f(0.6f, 0.5f, 4.0f);//
		glVertex3f(-0.6f, 0.5f, 4.0f);//
		glEnd();
		glBegin(GL_QUADS);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DARK_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, DARKRED_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LLGREEN_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Purple_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Purple_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LLGREEN_COL);
		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ�Ǻ�red
		glVertex3f(0.6f, 0.5f, 4.0f);//
		glVertex3f(-0.6f, 0.5f, 4.0f);//
		glVertex3f(-1.0f, 0.5f, 10.0f);//
		glVertex3f(1.0f, 0.5f, 10.0f);//
		glEnd();

		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, flower_texture);
		glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMYELLOW_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LGREEN_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, LRED_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LRED_COL);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RED_COL);
		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ�Ǻ�red
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.2f, -1.0f);//
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.25f, 0.2f, 1.0f);//
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.25f, 0.2f, 1.0f);//
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.2f, -1.0f);//
		glEnd();

		glBegin(GL_POLYGON);

		glColor3f(0.0f, 0.0f, 0.0f);//��ɫ�Ǻ�black
		glVertex3f(2.0f, -0.2f, 10.0f);//
		glVertex3f(1.0f, 0.5f, 10.0f);//
		glVertex3f(0.6f, 0.5f, 4.0f);//
		glVertex3f(0.25f, 0.2f, 1.0f);//
		glVertex3f(0.5f, -0.2f, -1.0f);//
		glVertex3f(0.5f, -0.2f, -1.0f);//
		glVertex3f(1.2f, -0.2f, 4.0f);//
		glEnd();
		glBegin(GL_POLYGON);

		glColor3f(0.0f, 0.0f, 0.0f);//��ɫ�Ǻ�black
		glVertex3f(0.0f, 0.0f, 13.5f);//
		glVertex3f(-2.0f, -0.2f, 10.0f);//
		glVertex3f(-0.5f, -0.2f, -1.0f);//
		glVertex3f(0.5f, -0.2f, -1.0f);//
		glVertex3f(2.0f, -0.2f, 10.0f);//
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�Ǻ�black
		glVertex3f(-2.0f, -0.2f, 10.0f);//
		glVertex3f(-1.0f, 0.5f, 10.0f);//
		glVertex3f(-0.6f, 0.5f, 4.0f);//
		glVertex3f(-0.25f, 0.2f, 1.0f);//
		glVertex3f(-0.5f, -0.2f, -1.0f);//
		glVertex3f(-0.5f, -0.2f, -1.0f);//
		glVertex3f(-1.2f, -0.2f, 4.0f);//
		glEnd();

		//6
		//�ɻ�����
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glBegin(GL_POLYGON);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LGREEN_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREENL_COL);
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�Ǻ�red 
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.75f, 0.0f, 10.0f);//
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-5.0f, 0.0f, 7.5f);//
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-5.0f, 0.25f, 4.1f);//
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, 0.25f, 4.0f);//
		glVertex3f(-1.75f, 0.0f, 10.0f);//
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cloud_texture);
		glBegin(GL_POLYGON);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DARK_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GREENL_COL);
		glColor3f(0.0f, 0.0f, 0.0f);//��ɫ�Ǻ�black
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-5.0f, 0.0f, 7.5f);//
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(-5.0f, 0.25f, 4.1f);//
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(-9.0f, 0.45f, 2.5f);//
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(-10.0f, 0.2f, 5.5f);//
		glEnd();
		glBegin(GL_POLYGON);

		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glBegin(GL_POLYGON);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LGREEN_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREENL_COL);
		glColor3f(1.0f, 1.0f, 1.0f);//��ɫ�Ǻ�red 
		glVertex3f(1.75f, 0.0f, 10.0f);//
		glVertex3f(5.0f, 0.0f, 7.5f);//
		glVertex3f(5.0f, 0.25f, 4.1f);//
		glVertex3f(1.0f, 0.25f, 4.0f);//
		glVertex3f(1.75f, 0.0f, 10.0f);//
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cloud_texture);
		glBegin(GL_POLYGON);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DARK_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GREEN_COL);
		glColor3f(0.0f, 0.0f, 0.0f);//��ɫ�Ǻ�black
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, 7.5f);//
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(5.0f, 0.25f, 4.1f);//
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(9.0f, 0.45f, 2.5f);//
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(10.0f, 0.2f, 5.5f);//
		glEnd();

		//7
		//�ɻ�����
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, cloud_texture);
		glBegin(GL_POLYGON);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LGREEN_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREENL_COL);
		glColor3f(1.0f, 1.0f, 0.0f);//��ɫ�ǻ�ɫyellow
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.25f, -1.0f);//
		//glTexCoord2f(0.0f, 0.5f);
		glVertex3f(-0.55f, 0.1f, 1.0f);//
		//glTexCoord2f(0.5f, 0.5f);
		glVertex3f(-2.75f, 0.1f, -0.25f);//
		//glTexCoord2f(0.5f, 0.0f);
		glVertex3f(-2.5f, -0.25f, -1.1f);//
		glEnd();

		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, cloud_texture);
		glBegin(GL_POLYGON);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LGREEN_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREENL_COL);
		glColor3f(1.0f, 1.0f, 0.0f);//��ɫ�ǻ�ɫyellow
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.25f, -1.0f);//
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.55f, 0.1f, 1.0f);//
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.75f, 0.1f, -0.25f);//
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.5f, -0.25f, -1.1f);//
		glEnd();

		/*  GL_SHININESS ������ֻ��һ��ֵ, ��Ϊ������ָ����, ȡֵ��Χ��0��128����ֵԽС, ��ʾ����Խ�ֲ�,
			���Դ����Ĺ������䵽����, Ҳ���Բ����ϴ�����㡣��ֵԽ��, ��ʾ����Խ�����ھ���, ��Դ���䵽�����, ������С�����㡣
			GL_FRONT_AND_BACK ��ʾ�޳�������ͱ�����
			GL_AMBIENT ��ʾ���ֹ������䵽�ò�����, �����ܶ�η�������������ڻ����еĹ���ǿ��(��ɫ)
			GL_DIFFUSE ��ʾ�������䵽�ò�����, ������������γɵĹ���ǿ��(��ɫ)
			GL_SPECULAR ��ʾ�������䵽�ò�����, �������淴����γɵĹ���ǿ��(��ɫ)
         */

	}

	//|____________________________________________________________________
	//|
	//| Function: DrawPropeller
	//|
	//! \param width       [in] Width  of the propeller.
	//! \param length      [in] Length of the propeller.
	//! \return None.
	//!
	//! Draws a propeller.
	//|____________________________________________________________________

	//���
	void DrawPropeller(const float width, const float length, const float height)  //���ұ߷�������
	{
		float w = width / 2;
		float l = length / 2;

		/*����������
		������ת
		��ϰ�����
		r,Rotates right propeller
		y,Rotates left propeller
		t,Rotates top propeller
		*/

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is blue
		//glColor3f(-0.2f, 1.0f, 1.0f);
		// Propeller is black
		glColor3f(1.00f, 1.00f, 1.00f);
		glVertex3f(0.0f, 0.25f, -2.0f);
		glVertex3f(0.5f, 0.25f, -2.0f);
		glVertex3f(0.0f, 0.25f, 0.0f);
		glEnd();

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is blue
		//glColor3f(-0.2f, 1.0f, 1.0f);
		// Propeller is black
		glColor3f(1.00f, 1.00f, 1.00f);
		glVertex3f(0.0f, 0.25f, 2.0f);
		glVertex3f(-0.5f, 0.25f, 2.0f);
		glVertex3f(0.0f, 0.25f, 0.0f);
		glEnd();

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is white
		glColor3f(1.00f, 1.00f, 1.00f);
		glVertex3f(2.0f, 0.25f, 0.0f);
		glVertex3f(2.0f, 0.25f, 0.5f);
		glVertex3f(0.0f, 0.25f, 0.0f);
		glEnd();

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is white
		//glColor3f(0.69f, 0.88f, 0.9f);
		glColor3f(1.00f, 1.00f, 1.00f);
		glVertex3f(-2.0f, 0.25f, 0.0f);
		glVertex3f(-2.0f, 0.25f, -0.5f);
		glVertex3f(0.0f, 0.25f, 0.0f);
		glEnd();
	}

	void DrawPropeller2(const float width, const float length, const float height)  //ǰ�������� Front Propeller
	{
		float w = width / 2;
		float l = length / 2;

		/*����������
		������ת
		��ϰ�����
		r,Rotates right propeller
		y,Rotates left propeller
		t,Rotates top propeller
		*/

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is blue
		//glColor3f(-0.2f, 1.0f, 1.0f);
		//Propeller is black
		glColor3f(1.0f, 0.98f, 0.84f);
		glVertex3f(0.0f, 3.0f, 13.5f);
		glVertex3f(1.0f, 3.0f, 13.5f);
		glVertex3f(0.0f, 0.0f, 13.5f);
		glEnd();

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is blue
		//glColor3f(-0.2f, 1.0f, 1.0f);
		//Propeller is black
		//glColor3f(0.69f, 0.97f, 0.09f);
		glColor3f(1.0f, 0.98f, 0.84f);
		glVertex3f(-1.0f, -3.0f, 13.5f);
		glVertex3f(0.0f, -3.0f, 13.5f);
		glVertex3f(0.0f, 0.0f, 13.5f);
		glEnd();

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is white
		glColor3f(1.0f, 0.98f, 0.84f);
		glVertex3f(3.0f, 0.0f, 13.5f);
		glVertex3f(3.0f, -1.0f, 13.5f);
		glVertex3f(0.0f, 0.0f, 13.5f);
		glEnd();

		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		// Propeller is white
		//glColor3f(0.22f, 0.93f, 0.53f);
		glColor3f(1.0f, 0.98f, 0.84f);
		glVertex3f(-3.0f, 0.0f, 13.5f);
		glVertex3f(-3.0f, 1.0f, 13.5f);
		glVertex3f(0.0f, 0.0f, 13.5f);
		glEnd();
	}

	/*draw circular cone
	N---> Circular cone smoothness N = integer
	H---> Hight
	R---> Radius
	PI----> ��
	�����(Lateral area) =��*r^2=��*1=��
	�����(Bottom area) =��*r*l=��*1*2=2��
	*/

	void DrawSubPropeller(const float width, const float length, const float height)  //SubPropeller
	{
		//����Բ׶
		int N = 66; // ����Բ׶��ƽ���̶ȣ�
		float R = 1.0f; // �뾶
		float H = 1.0f; // ��
		float PI = 3.141593f;
		glBegin(GL_TRIANGLE_FAN);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, DARKGRAY_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DARKGREEN_COL);
		glVertex3f(10.0f, H, 11.0f);
		for (int i = 0; i < N; i++)
		{
			glVertex3f(10.0f + R * cos(i * 2 * PI / N), 3.0f, 11.0f + R * sin(i * 2 * PI / N));
			glVertex3f(10.0f + R * cos((i + 1) * 2 * PI / N), 3.0f, 11.0f + R * sin(i * 2 * PI / N));
		}
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GREEN_COL);
		glVertex3f(10.0f, 4.0f, 11.0f);
		for (int i = 0; i < N; i++)
		{
			glVertex3f(10.0f + R * cos(i * 2 * PI / N), 3.0f, 11.0f + R * sin(i * 2 * PI / N));
			glVertex3f(10.0f + R * cos((i + 1) * 2 * PI / N), 3.0f, 11.0f + R * sin(i * 2 * PI / N));
		}
		glEnd();
	}

	void DrawSubPropeller2(const float width, const float length, const float height)  //SubPropeller2
	{   
		/*glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.36, 0.51, 0.85);//��ɫ�ǰ�white
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);//
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);//
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 2.0f, 0.0f);//
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);//
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.36, 0.51, 0.85);//��ɫ�ǰ�white
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);//
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);//
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 0.0f, 2.0f);//
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 2.0f);//
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.36, 0.51, 0.85);//��ɫ�ǰ�white
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);//
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);//
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.0f, 2.0f, 2.0f);//
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 2.0f);//
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.36, 0.51, 0.85);//��ɫ�ǰ�white
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);//
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.0f, 2.0f, 0.0f);//
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 2.0f, 2.0f);//
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 2.0f);//
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.36, 0.51, 0.85);//��ɫ�ǰ�white
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.0f, 2.0f, 0.0f);//
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);//
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 0.0f, 2.0f);//
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2.0f, 2.0f, 2.0f);//
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, CAT_texture);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MEDIUMWHITE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, LBLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Purple_COL);
		glBegin(GL_QUADS);
		glColor3f(0.36, 0.51, 0.85);//��ɫ�ǰ�white
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 2.0f);//
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 2.0f);//
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2.0f, 0.0f, 2.0f);//
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 0.0f);//
		glEnd();
		*/

		//����Բ׶2 
		int N = 36; // ����Բ׶��ƽ���̶ȣ�
		float R = 1.0f; // �뾶
		float H = 1.0f; // ��
		float PI = 3.141593f;
		glBegin(GL_TRIANGLE_FAN);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, RED_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Purple_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RED_COL);
		glColor3f(0.0f, 0.85f, 0.55f);//��ɫ�ǻ�ɫyellow
		glVertex3f(20.0f, H, 10.0f);
		for (int i = 0; i < N; i++)
		{
			glVertex3f(20.0f + R * cos(i * 2 * PI / N), 5.0f, 10.0f + R * sin(i * 2 * PI / N));
			glVertex3f(20.0f + R * cos((i + 1) * 2 * PI / N), 5.0f, 10.0f + R * sin(i * 2 * PI / N));
		}
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RED_COL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE_COL);
		glColor3f(0.0f, 0.0f, 0.0f);//��ɫ�ǻ�ɫyellow
		glVertex3f(20.0f, 5.0f, 10.0f);
		for (int i = 0; i < N; i++)
		{
			glVertex3f(20.0f + R * cos(i * 2 * PI / N), 5.0f, 10.0f + R * sin(i * 2 * PI / N));
			glVertex3f(20.0f + R * cos((i + 1) * 2 * PI / N), 5.0f, 10.0f + R * sin(i * 2 * PI / N));
		}
		glEnd();
	}


	/*
	// ///----------------------------- unused part------------------------///
	//	//// ------------------------�����----------------------------////
	//                             Pentagram
	// ������ǵ��������ֲ�λ�ù�ϵ���£�
	//        A
	// E ++++++++++++ B
	//      ++++++
	//    D        C
	// ���ȣ��������Ҷ����з��̣���������ǵ����ĵ�����ľ���a
	// ����������Ƕ�Ӧ������εı߳�Ϊ.0��
	// a = 1 / (2-2*cos(72*Pi/180));
	// Ȼ�󣬸������Һ����ҵĶ��壬����B��x����bx��y����by���Լ�C��y����
	// ����������ǵ�����������ԭ�㣩
	// bx = a * cos(18 * Pi/180);
	// by = a * sin(18 * Pi/180);
	// cy = -a * cos(18 * Pi/180);
	// ����������Ϳ���ͨ�������ĸ�����һЩ�����򵥵ı�ʾ����
		const GLfloat Pi = 3.1415926536f;
		GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
		GLfloat bx = a * cos(18 * Pi / 180);
		GLfloat by = a * sin(18 * Pi / 180);
		GLfloat cy = -a * cos(18 * Pi / 180);
		GLfloat
			PointA[2] = { 0, a },
			PointB[2] = { bx, by},
			PointC[2] = { 0.5, cy},
			PointD[2] = { -0.5, cy},
			PointE[2] = { -bx, by};
		glClear(GL_COLOR_BUFFER_BIT);
		// ����A->C->E->B->D->A��˳�򣬿���һ�ʽ�����ǻ���
		glBegin(GL_LINE_LOOP);
		glVertex2fv(PointA);
		glVertex2fv(PointC);
		glVertex2fv(PointE);
		glVertex2fv(PointB);
		glVertex2fv(PointD);
		glEnd();
		glFlush();
		*/

    void DrawSkybox(const float s) {
        float s2 = s / 2;

        // Turn on texture mapping and disable lighting
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);

        // Back wall
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYBACK]);  // Specify which texture will be used
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-s2, -s2, -s2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(s2, -s2, -s2);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(s2, s2, -s2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-s2, s2, -s2);
        glEnd();

        // Left wall
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYLEFT]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-s2, -s2, s2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-s2, -s2, -s2);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-s2, s2, -s2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-s2, s2, s2);
        glEnd();

        // Bottom wall
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYBOTTOM]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-s2, -s2, s2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(s2, -s2, s2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(s2, -s2, -s2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-s2, -s2, -s2);
        glEnd();

        // Top Wall
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYTOP]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-s2, s2, s2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(s2, s2, s2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(s2, s2, -s2);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-s2, s2, -s2);
        glEnd();

        // Front Wall
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYFRONT]);  // Specify which texture will be used
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-s2, -s2, s2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(s2, -s2, s2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(s2, s2, s2);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-s2, s2, s2);
        glEnd();

        // Right Wall
        glBindTexture(GL_TEXTURE_2D, textures[TID_SKYRIGHT]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(s2, -s2, s2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(s2, -s2, -s2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(s2, s2, -s2);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(s2, s2, s2);
        glEnd();

        // Turn off texture mapping and enable lighting
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }

    void DrawLightSource(const float radius) {
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidSphere(radius, 100, 100);
        glEnable(GL_LIGHTING);
    }
}


