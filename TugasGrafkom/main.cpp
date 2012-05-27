/* Program OpenGl 3D Grafika Komputer */
#include <windows.h>
#include <GL\glut.h>
#include <stdlib.h>
#include <math.h>

//Variabel Animasi
static int spin = 0, spin1=0;
static float light_x = 0.0,light_y=0.0, light_z = 0.4;
static float plane_go = 0.0, plane_move = 0.0;
static float ball_z=0.4;
static int wire_angle=0, ball_count=5;

static float m=1.0;
static int light0 =1, light1=1, light2=1;


   GLuint listName;

   GLfloat normal_mat_ambient[]= { 0.8, 0.2, 0.2, 1.0 };
   GLfloat normal_mat_diffuse[]= { 0.8, 0.8, 0.8, 1.0 };
   GLfloat normal_mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
   GLfloat normal_mat_shininess[] = { 5.0 };

   GLfloat desk_mat_ambient[]= { 0.2, 0.4, 0.0, 1.0 };
   GLfloat desk_mat_diffuse[]= { 0.0, 0.3, 0.8, 1.0 };
   GLfloat desk_mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
   GLfloat desk_mat_shininess[] = { 10.0 };

   GLfloat cy_mat_ambient[]= { 0.2, 0.4, 0.0, 1.0 };
   GLfloat cy_mat_diffuse[]= { 1.0, 1.0, 0.0, 1.0 };
   GLfloat cy_mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
   GLfloat cy_mat_shininess[] = { 0.0 };

   GLUquadricObj *pobj;
//Deklarasi Fungsi



void teapot(void){
 glTranslatef(0.0, -0.5, 1.0);
    glutSolidTeapot(0.3);
}


void init(void)
{
   //Gambar Bola Kawat Berjajar
   listName = glGenLists (1);
   glNewList (listName, GL_COMPILE);
      glColor3f (0.0, 1.0, 0.0);  /*  Warna merah  */
      glutWireSphere(0.1,36,36);
      glTranslatef (0.5, 0.0, 0.0); /*  Pemindahan posisi  */
   glEndList ();

   //Cahaya1
   GLfloat light1_ambient[]= { 0.2, 0.2, 0.2, 1.0 };
   GLfloat light1_diffuse[]= { 1.0, 0.0, 0.0, 1.0 };
   GLfloat light1_specular[] = { 1.0, 0.6, 0.6, 1.0 };
   GLfloat light1_position[] = { 15.0, 9.0, -16.0, 1.0 };

   glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR,light1_specular);
   glLightfv(GL_LIGHT1, GL_POSITION,light1_position);

   //Cahaya2
   GLfloat light2_ambient[]= { 0.2, 0.2, 0.2, 1.0 };
   GLfloat light2_diffuse[]= { 0.0, 0.0, 1.0, 1.0};
   GLfloat light2_specular[] = { 1.0, 0.6, 0.6, 1.0 };
   GLfloat light2_position[] = {-4.0, 0.0, 15.0, 1.0};

   glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
   glLightfv(GL_LIGHT2, GL_SPECULAR,light2_specular);
   glLightfv(GL_LIGHT2, GL_POSITION, light2_position);


   glClearColor (0.0, 0.0, 1.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   GLfloat light0_diffuse[]= { 0.0, 1.0, 0.0, 1.0 };
   GLfloat position[] = { 2.0, 1.0, 1.0, 1.0 };

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

   glPushMatrix ();

       //Sumber pencahayaan turnning
       glPushMatrix ();
           glRotated ((GLdouble) spin, 0.0, 1.0, 0.0);
           glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
           glLightfv (GL_LIGHT0, GL_POSITION, position);
 
           glTranslated (1.0, 1.0, 2.0);

           glDisable (GL_LIGHTING);
           glColor3f (0.1, 0.1, 0.1);
           glutSolidSphere (0.03,16,16);
           glEnable (GL_LIGHTING);
       glPopMatrix ();

       //X,Y,Z kordinat garis untuk bergerak dan berputar.
       glEnable (GL_LINE_STIPPLE);
       glLineStipple (1, 0x1111);  /*  titik  */
       glColor3f (0.0, 0.0, 1.0);
       glBegin(GL_LINES); 
       glVertex3f (0.0, 0.0, 0.0);
       glVertex3f (0.0, 0.0, 5.0);
       glEnd();
       glLineStipple (1, 0xA1A1);
       glColor3f (0.0, 1.0, 0.0);
       glBegin(GL_LINES); 
       glVertex3f (0.0, 0.0, 0.0);
       glVertex3f (0.0, 5.0, 0.0);
       glEnd();
       glLineStipple (1, 0xAAAA);
       glColor3f (1.0, 0.0, 0.0);
       glBegin(GL_LINES); 
       glVertex3f (0.0, 0.0, 0.0);
       glVertex3f (5.0, 0.0, 0.0);
       glEnd();
  
    //
       gluLookAt (4.0, 1.0, 4.0, 0.0, 0.0, 0.0, -1.0, 1.0, -1.0);
  
       //pidah depan, belakang, kiri, dan kanan
       glTranslatef((plane_move/sqrt(2.0))+(plane_go/sqrt(2.0)),0.0,(plane_go/sqrt(2.0))-(plane_move/sqrt(2.0)));
       glPushMatrix ();
           glPushMatrix ();
               glTranslatef(-1.0, -1.0, -1.0); //Model gerak ke bawah
               glRotatef (-90.0, 1.0, 0.0, 0.0 ); //Model Putar
 
               //Meja
               glPushMatrix ();
                   glScalef(4.0, 4.0,0.02);
                 desk();
               glPopMatrix ();

               glTranslatef(light_x, light_y, 0.0);
      glDisable (GL_LIGHTING);
               glPushMatrix ();
                   //Dudukan Lampu                  
                   lampholder();
               glPopMatrix ();

               glPushMatrix ();
                   //down lampstander
                   downlampstander();
               glPopMatrix ();

               glTranslatef(0.0, 0.0, light_z-0.2);
               //Sambungan Bola
               connectionball();

               //up lampstander
               glPushMatrix ();
                   uplampstander();
               glPopMatrix ();
      glEnable (GL_LIGHTING);

               glTranslatef(0.0, 0.0, 0.4);
               //Kap Lampu
               glPushMatrix ();
                   lampshade();
               glPopMatrix ();

               glTranslatef(0.0, 0.0, 0.2);
               //Penutup Kap Lampu dan Bola
               glPushMatrix ();
       lampshadecover();
               glPopMatrix ();

               //Bola Padat
      glPushMatrix ();
                   solidsphere();
               glPopMatrix ();

               //SolidTorus
               glTranslatef(-1.0, 0.0, -0.8);
               glPushMatrix ();
                   torus();
               glPopMatrix ();

         //Cylinder
               glPushMatrix ();
                   cylinder();
               glPopMatrix ();
              
           glPopMatrix ();

     glPushMatrix ();
         glTranslatef(1.2, -0.5, 0.2);
      glRotatef(wire_angle,0.0,1.0,0.0);
         /*/Kawat Cone
               glPushMatrix ();
             wirecone();
               glPopMatrix ();*/
			   //up lampstander
               glPushMatrix ();
                   uplampstander();
               glPopMatrix ();
			   glTranslatef(0.8, 0.0, 0.8);

			     //Kawat Bola
               glPushMatrix ();
                   wiresphere();
               glPopMatrix ();
     glPopMatrix ();
 
           //teapot
           glPushMatrix ();
               teapot();
           glPopMatrix ();

           //Pemanggilan 5 kawat dari daftar
           glPushMatrix ();
               glTranslatef(-2.5, 1.5, -2.5);
               glRotatef(45+spin1,0.0,1.0,0.0);
               GLuint i;
               for (i = 0; i < ball_count; i++)   
                    glCallList (listName);
           glPopMatrix ();
       glPopMatrix ();
   glPopMatrix ();
  
   glFlush ();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

//still some problems when it moves. the screen always twinkle
void balljump(){
 while(ball_z<2.0){
    ball_z= ball_z+0.01;
    display();
 }
   
}

void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            spin1 = (spin1 + 30) % 360;
            glutPostRedisplay();
         }
         break;
    case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN) {
            wire_angle = (wire_angle + 30) % 360;
            glutPostRedisplay();
         }
         break;
      default:
         break;
   }
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'w':
         plane_go = plane_go-0.2;
         display();
         break;
      case 's':
         plane_go = plane_go+0.2;
         display();
         break;
      case 'd':
         plane_move = plane_move+0.2;
         display();
         break;
      case 'a':
         plane_move = plane_move-0.2;
         display();
         break;
      case 'x':
         light_x = light_x+0.2;
         display();
         break;
      case 'X':
         light_x = light_x-0.2;
         display();
         break;
      case 'y':
         light_y = light_y+0.2;
         display();
         break;
      case 'Y':
         light_y = light_y-0.2;
         display();
         break;
      case 'z':
         light_z= light_z +0.1;
         display();
         break;
      case 'Z':
         light_z = light_z-0.1;
         display();
         break;
   case '1':
    if(light0==1){
              glDisable(GL_LIGHT0);
     light0=0;
    }
    else if(light0==0){
                 glEnable(GL_LIGHT0);
        light0=1;
    }
    display();
          break;
   case '2':
          if(light1==1){
    
              glDisable(GL_LIGHT1);
     light1=0;
    }
    else if(light1==0){
                 glEnable(GL_LIGHT1);
        light1=1;
    }
    display();
          break;
   case '3':
          if(light2==1){
              glDisable(GL_LIGHT2);
     light2=0;
    }
    else if(light2==0){
                 glEnable(GL_LIGHT2);
        light2=1;
    }
    display();
          break;
      case 32:
    spin = (spin + 30) % 360;
          glutPostRedisplay();
       display();
          break;
      case 27:
         exit(0);
         break;
   }
}

void menu(int id)
{
 if (id==0)  {
  glEnable(GL_LIGHT1);
  light1=1;
  display();
 }
 else if (id==1)  {
  glDisable(GL_LIGHT1);
  light1=0;
  display();
 }
 else if (id==2)  {
  glEnable(GL_LIGHT2);
  light2=1;
  display();
 }
 else if (id==3)  {
  glDisable(GL_LIGHT2);
  light2=0;
  display();
 }
    else if (id==4)  {
  glEnable(GL_LIGHT0);
  light0=1;
  display();
 }
 else if (id==5)  {
  glDisable(GL_LIGHT0);
  light0=0;
  display();
 }
 else if (id==6)  {
  ball_count=ball_count+1;
  display();
 }
 else if (id==7)  {
  ball_count=ball_count-1;
  display();
 }
 else if (id==8)  {
  balljump();}

    else if (id==10)  {
  exit(0);
 }
   
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (700, 700);
   glutInitWindowPosition (300, 300);
   glutCreateWindow("Tugas Grafkom");
   //glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);

   glutCreateMenu(menu);
   glutAddMenuEntry("light0 on", 4);
   glutAddMenuEntry("light0 off", 5);
   glutAddMenuEntry("light1 on", 0);
   glutAddMenuEntry("light1 off", 1);
   glutAddMenuEntry("light2 on", 2);
   glutAddMenuEntry("light2 off", 3);
   glutAddMenuEntry("add ball", 6);
   glutAddMenuEntry("delete ball", 7);
   glutAddMenuEntry("ball jump", 8);
   glutAddMenuEntry("quit", 10);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   glutMainLoop();
   return 0;
}
