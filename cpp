#include <GL/glut.h>

// Variabel posisi pesawat
float planePosX = 0.0f;
float planePosY = 0.0f;

// Variabel status lompat
bool isJumping = false;
float jumpHeight = 0.0f;
float jumpSpeed = 0.05f;
float maxJumpHeight = 0.4f;

// Variabel status pergerakan
bool isMovingLeft = false;
bool isMovingRight = false;
float moveSpeed = 0.02f;

// Variabel status laser
bool isShooting = false;
float laserPosX = 0.0f;
float laserPosY = 0.0f;
float laserSpeed = 0.1f;



// Fungsi untuk menggambar pesawat
void drawPlane()
{
    // Menggambar badan pesawat
    glPushMatrix();
    glTranslatef(planePosX, planePosY + jumpHeight, 0.0f);
    glColor3f(0.0f, 0.8f, 1.0f); // Warna pesawat (biru)
    glScalef(0.2f, 0.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(planePosX - 0.2f, planePosY - 0.7f + jumpHeight, 0.0f);
    glColor3f(0.0f, 0.8f, 1.0f); // Warna pesawat (biru)
    glScalef(0.2f, 0.4f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(planePosX - 0.2f, planePosY - 0.9f + jumpHeight, 0.0f);
    glColor3f(0.0f, 0.8f, 1.0f); // Warna pesawat (biru)
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(planePosX + 0.2f, planePosY - 0.7f + jumpHeight, 0.0f);
    glColor3f(0.0f, 0.8f, 1.0f); // Warna pesawat (biru)
    glScalef(0.2f, 0.4f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(planePosX + 0.2f, planePosY - 0.9f + jumpHeight, 0.0f);
    glColor3f(0.0f, 0.8f, 1.0f); // Warna pesawat (biru)
    glScalef(0.1f, 0.1f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

   
    // Menggambar sayap kiri
    glPushMatrix();
    glTranslatef(planePosX - 0.3f, planePosY + jumpHeight, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Warna sayap (biru gelap)
    glScalef(0.4f, 0.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Menggambar sayap kanan
    glPushMatrix();
    glTranslatef(planePosX + 0.3f, planePosY + jumpHeight, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Warna sayap (biru gelap)
    glScalef(0.4f, 0.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Menggambar ekor pesawat
    glPushMatrix();
    glTranslatef(planePosX, planePosY + jumpHeight - 0.2f, -0.4f);
    glColor3f(0.0f, 0.0f, 1.0f); // Warna ekor (biru gelap)
    glScalef(0.2f, 0.5f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();


    // Menggambar laser jika sedang menembak
    if (isShooting)
    {
        glPushMatrix();
        glTranslatef(laserPosX, laserPosY, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f); // Warna laser (merah)
        glScalef(0.05f, 0.05f, 0.2f);
        glutSolidSphere(1.0f, 10, 10);
        glPopMatrix();
    }
}

// Fungsi untuk merender (menggambar) adegan
void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawPlane();

    glutSwapBuffers();
}

// Fungsi untuk mengupdate animasi
void update(int value)
{
    // Update lompatan jika sedang melompat
    if (isJumping)
    {
        jumpHeight += jumpSpeed;
        if (jumpHeight >= maxJumpHeight)
        {
            jumpSpeed = -jumpSpeed; // Mengubah arah lompatan
        }
        if (jumpHeight <= 0.0f)
        {
            jumpHeight = 0.0f;
            jumpSpeed = -jumpSpeed; // Mengubah arah lompatan menjadi ke atas lagi
            isJumping = false;
        }
    }

    // Update pergerakan ke kiri dan ke kanan
    if (isMovingLeft)
    {
        planePosX -= moveSpeed;
        if (planePosX < -2.0f)
            planePosX = -2.0f;
    }

    if (isMovingRight)
    {
        planePosX += moveSpeed;
        if (planePosX > 2.0f)
            planePosX = 2.0f;
    }

    // Update posisi laser jika sedang menembak
    if (isShooting)
    {
        laserPosY += laserSpeed;
        if (laserPosY > 2.0f)
        {
            isShooting = false;
            laserPosX = planePosX;
            laserPosY = planePosY + jumpHeight;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

// Fungsi untuk menghandle input keyboard saat tombol ditekan
void onKeyDown(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a': // Tombol 'a' untuk bergerak ke kiri
        isMovingLeft = true;
        break;
    case 'd': // Tombol 'd' untuk bergerak ke kanan
        isMovingRight = true;
        break;
    case ' ': // Tombol spasi untuk menembak
        if (!isShooting)
        {
            isShooting = true;
            laserPosX = planePosX;
            laserPosY = planePosY + jumpHeight;
        }
        break;
    }
}

// Fungsi untuk menghandle input keyboard saat tombol dilepas
void onKeyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a': // Tombol 'a' dilepas
        isMovingLeft = false;
        break;
    case 'd': // Tombol 'd' dilepas
        isMovingRight = false;
        break;
    }
}

// Fungsi untuk menghandle input mouse saat tombol diklik
void onMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (!isJumping)
        {
            isJumping = true;
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Kartun Pesawat OpenGL");

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);
    glutMouseFunc(onMouseClick);

    glutTimerFunc(0, update, 0);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
