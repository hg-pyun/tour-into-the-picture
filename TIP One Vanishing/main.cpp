#include<iostream>
#include<gl\glut.h>
using namespace std;

GLuint texture;

GLuint LoadTexture( const char * filename )
{
	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

	file = fopen( filename, "rb" );

	if ( file == NULL ) return 0;
//	cout <<"Load Texture" << endl; 
	width = 340;
	height = 242;
	data = (unsigned char *)malloc( width * height * 3 );
	//int size = fseek(file,);
	fread( data, width * height * 3, 1, file );
	fclose( file );

	for(int i = 0; i < width * height ; ++i)
	{
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];

		data[index] = R;
		data[index+2] = B;

	}

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );

	return texture;
}

void init(){
	cout << "Init process works" << endl; 
	glClearColor(0.0, 0.0, 0.0, 1.0);
	texture = LoadTexture( "background.bmp" );
	glEnable(GL_TEXTURE_2D);
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture (GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 0.0);
		glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 0.0);
		glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
		glNormal3f(0.0, 0.0, 1.0); glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowSize(500,500);
	glutCreateWindow("Tour Into The Picture");
	init();					// init 
	glutDisplayFunc(draw);	// draw
	// 키보드 이벤트
	glutMainLoop();


	return 0;
}