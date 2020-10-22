#include "glut.h"
#include  <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h> 
using namespace std;

//bien dieu khien hanh tinh
int hanhTinhSo = 0;

//tốc độ quay của hanh tinh
static GLfloat spin = 200.0;
static GLfloat spinSaoThuy = 0.0;
static GLfloat spinSaoKim = 0.0;
static GLfloat spinTraiDat = 0.0;
static GLfloat spinSaoHoa = 0.0;
static GLfloat spinSaoMoc = 0.0;
static GLfloat spinSaoTho = 0.0;
static GLfloat spinSaoThienVuong = 0.0;
static GLfloat spinSaoHaiVuong = 0.0;
static GLfloat spinSaoDiemVuong = 0.0;

//cái fps
const int FPS = 60;
const float frameDelay = 1000 / 60;

//x y z đầu của cái gluLookAt keyboard
static float trucX = 0.0;
static float trucY = 0.0;
static float trucZ = 5.0;

//trong hàm timer
int initial_time = time(NULL);
int final_time;
int frame_count = 0;

//khai báo cho hàm mouse
float deltaAngle = 0.0f;
int xOrigin = -1;
float angle;
float lx, lz;
//struct màu rgb
struct rgb {
	int r;
	int g;
	int b;
};

//struct thông số mỗi hành tinh
struct thongSo {
	struct rgb mau;
	float banKinh;
	float banKinhQuay;
	float speed;
	GLfloat spin;
};


//struct quản lý các hành tinh
struct hanhTinh {
	struct thongSo saoThuy;
	struct thongSo saoKim;
	struct thongSo traiDat;
	struct thongSo saoHoa;
	struct thongSo saoMoc;
	struct thongSo saoTho;
	struct thongSo saoThienVuong;
	struct thongSo saoHaiVuong;
	struct thongSo saoDiemVuong;
};
static hanhTinh ht; //declare global


//thong so set cho hành trinh 
void thongSo(int r, int g, int b, float bankinhquay, float speed) {
	glPushMatrix();
	glColor3f(r, g, b);

	// cach 1
	//glRotatef(speed, 0, 0.0, 1.0);
	//glTranslatef(bankinhquay, 0, 1.0);

	//cach 2
	float x = -sin(speed) * (bankinhquay);
	float y = cos(speed) * (bankinhquay);
	glTranslatef(x, y, 0.0);
}

//thong số set riêng cho mặt trời
void thongSo1(int r, int g, int b, float speed) {
	glColor3f(r, g, b);
	glRotatef(speed, 0, 0.0, 1.0);
}

//vẽ cái hành tịn
void draw(float bankinh) {
	glutSolidSphere(bankinh, 200, 200);
	glPopMatrix();
}


//vẽ và set thông số cho hành tinh
void veHanhTinh(int r, int g, int b, float banKinh, float banKinhQuay, float spin) {
	thongSo(r, g, b, banKinhQuay, spin);
	draw(banKinh);
}


//vẽ và set thông số riêng cho mặt trời
void matTroi() {
	thongSo1(1, 0, 0, spin);
	draw(0.4);
}

//nhập thông số cho những hành tinh
void inputValue(hanhTinh& ht) {
	ht.saoThuy.mau.r = 192;
	ht.saoThuy.mau.g = 192;
	ht.saoThuy.mau.b = 192;
	ht.saoThuy.banKinh = 0.02;
	ht.saoThuy.banKinhQuay = 0.5;
	ht.saoThuy.spin = 0.0;

	// khai bao bien cho sao kim
	ht.saoKim.mau.r = 0;
	ht.saoKim.mau.g = 191;
	ht.saoKim.mau.b = 255;
	ht.saoKim.banKinh = 0.03;
	ht.saoKim.banKinhQuay = 0.6;
	ht.saoKim.spin = 0.0;

	// khai bao bien cho traiDat 0, 0, 160, 0.7 0.04
	ht.traiDat.mau.r = 0;
	ht.traiDat.mau.g = 0;
	ht.traiDat.mau.b = 160;
	ht.traiDat.banKinh = 0.04;
	ht.traiDat.banKinhQuay = 0.7;
	ht.traiDat.spin = 0.0;

	// khai bao bien cho saoHoa 1, 0, 0, 0.8 0.03
	ht.saoHoa.mau.r = 1;
	ht.saoHoa.mau.g = 0;
	ht.saoHoa.mau.b = 0;
	ht.saoHoa.banKinh = 0.03;
	ht.saoHoa.banKinhQuay = 0.8;
	ht.saoHoa.spin = 0.0;

	// khai bao bien cho saoMoc 0, 150, 0, 1 0.12
	ht.saoMoc.mau.r = 0;
	ht.saoMoc.mau.g = 150;
	ht.saoMoc.mau.b = 0;
	ht.saoMoc.banKinh = 0.12;
	ht.saoMoc.banKinhQuay = 1;
	ht.saoMoc.spin = 0.0;

	// khai bao bien cho saoTho 10, 10, 10, 1.3 0.11
	ht.saoTho.mau.r = 10;
	ht.saoTho.mau.g = 10;
	ht.saoTho.mau.b = 10;
	ht.saoTho.banKinh = 0.11;
	ht.saoTho.banKinhQuay = 1.3;
	ht.saoTho.spin = 0.0;

	// khai bao bien cho saoThienVuong  0, 128, 255, 1.7 0.09
	ht.saoThienVuong.mau.r = 0;
	ht.saoThienVuong.mau.g = 128;
	ht.saoThienVuong.mau.b = 255;
	ht.saoThienVuong.banKinh = 0.09;
	ht.saoThienVuong.banKinhQuay = 1.7;
	ht.saoThienVuong.spin = 0.0;

	// khai bao bien cho saoHaiVuong  64, 0, 128, 2.2 0.09
	ht.saoHaiVuong.mau.r = 64;
	ht.saoHaiVuong.mau.g = 0;
	ht.saoHaiVuong.mau.b = 128;
	ht.saoHaiVuong.banKinh = 0.09;
	ht.saoHaiVuong.banKinhQuay = 2.2;
	ht.saoHaiVuong.spin = 0.0;

	// khai bao bien cho saoDiemVuong  (0, 0, 64, 2.8 0.02
	ht.saoDiemVuong.mau.r = 0;
	ht.saoDiemVuong.mau.g = 0;
	ht.saoDiemVuong.mau.b = 64;
	ht.saoDiemVuong.banKinh = 0.02;
	ht.saoDiemVuong.banKinhQuay = 2.8;
	ht.saoDiemVuong.spin = 0.0;
}


//in text ra màng hình window
void renderstring2d(char string[], float r, float g, float b, float x, float y)
{
	glColor3f(r, g, b);
	glDisable(GL_LIGHTING);
	glRasterPos2f(x, y);
	for (unsigned int i = 0; i < strlen(string); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);	
	}
}


//render hành tinh
void render() {
	glPushMatrix();
	hanhTinh ht;
	inputValue(ht);
	matTroi();
	veHanhTinh(ht.saoThuy.mau.r, ht.saoThuy.mau.g, ht.saoThuy.mau.b, ht.saoThuy.banKinh, ht.saoThuy.banKinhQuay, spinSaoThuy);
	veHanhTinh(ht.saoKim.mau.r, ht.saoKim.mau.g, ht.saoKim.mau.b, ht.saoKim.banKinh, ht.saoKim.banKinhQuay, spinSaoKim);
	veHanhTinh(ht.traiDat.mau.r, ht.traiDat.mau.g, ht.traiDat.mau.b, ht.traiDat.banKinh, ht.traiDat.banKinhQuay, spinTraiDat);
	veHanhTinh(ht.saoHoa.mau.r, ht.saoHoa.mau.g, ht.saoHoa.mau.b, ht.saoHoa.banKinh, ht.saoHoa.banKinhQuay, spinSaoHoa);
	veHanhTinh(ht.saoMoc.mau.r, ht.saoMoc.mau.g, ht.saoMoc.mau.b, ht.saoMoc.banKinh, ht.saoMoc.banKinhQuay, spinSaoMoc);
	veHanhTinh(ht.saoTho.mau.r, ht.saoTho.mau.g, ht.saoTho.mau.b, ht.saoTho.banKinh, ht.saoTho.banKinhQuay, spinSaoTho);
	veHanhTinh(ht.saoThienVuong.mau.r, ht.saoThienVuong.mau.g, ht.saoThienVuong.mau.b, ht.saoThienVuong.banKinh, ht.saoThienVuong.banKinhQuay, spinSaoThienVuong);
	veHanhTinh(ht.saoHaiVuong.mau.r, ht.saoHaiVuong.mau.g, ht.saoHaiVuong.mau.b, ht.saoHaiVuong.banKinh, ht.saoHaiVuong.banKinhQuay, spinSaoHaiVuong);
	veHanhTinh(ht.saoDiemVuong.mau.r, ht.saoDiemVuong.mau.g, ht.saoDiemVuong.mau.b, ht.saoDiemVuong.banKinh, ht.saoDiemVuong.banKinhQuay, spinSaoDiemVuong);
	glPopMatrix();
}

//hàm tính fps ko còn sử dụng
/*void timer() {
	frame_count++;
	final_time = time(NULL);
	if (final_time - initial_time > 0) {
		fpss = frame_count / (final_time - initial_time);
		
		cout << "\nFPS: " << fpss  << endl;
		frame_count = 0;
		initial_time = final_time;
	}
}*/


//hàm chiếu sáng cho hành tinh
void lighting() {
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	GLfloat diff_use[] = { 0.0, 0.5, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	GLfloat shininess = 20.0f;
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
}


//hàm in text ra window ko sài
/*void drawText(const char* text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glColor3f(1, 1, 1);
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glColor3f(1, 1, 1);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}*/


//hàm hổ trợ chuyển từ float sang string
void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then 
	// add 0s at the beginning 
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}

//hàm chuyển từ float sang string
void ftoa(float n, char* res, int afterpoint)
{
	int ipart = (int)n;

	float fpart = n - (float)ipart;

	int i = intToStr(ipart, res, 0);

	if (afterpoint != 0) {
		res[i] = '.'; 
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}
//ham này là hàm tổng hợp để xuất text từ display
void outputText() {
	char textFps[50] = "FPS: ";
	char textSpeed[50] = "Toc do: 5s/vong";
	char fpsToString[33];
	char speedToString[33];


	_itoa_s(FPS, fpsToString, 10);

	renderstring2d(textFps, 0, 1, 0, 1.0, 2.5);
	renderstring2d(fpsToString, 0, 1, 0, 1.3, 2.5);
	renderstring2d(textSpeed, 0, 1, 0, 1.0, 2.7);

	//renderstring2d(text, 0, 1, 0, 1.0, 2.5);

	//renderstring2d(fps, 0, 1, 0, 1.0, 2.5);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
//hàm hiển thị
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int timeStart = GetTickCount();

	//render hanh tinh
	render();

	//in text
	outputText();

	//tính thời gian Sleep 
	glEnable(GL_LIGHTING);
	int frameTime = GetTickCount() - timeStart;
	//cout << endl << "No sleep";
	if (frameDelay > frameTime) {
		Sleep(frameDelay - frameTime);
		//cout << endl << "Sleep" << frameDelay - frameTime;
	}
	//time
	glutSwapBuffers();
	//timer();

}

//khởi tạo mấy cái cần thiết
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	//lighting setup
	lighting();

}


//hàm chạy khi thay đổi size window
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(trucX, trucY, trucZ, lx, lz, 0, 0.0, 0.5, 0.0);


	printf("\nreshape");
}

//nhận event từ bàn phím
void keyboard(unsigned char key, int x, int y)
{
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(trucX, trucY, trucZ, lx, lz, 0, 0.0, 0.5, 0.0);


	switch (key) {
		case '1':
			hanhTinhSo++;
			if (hanhTinhSo >=11) {
				hanhTinhSo = 1;
			}
			
			break;
		case '0':
			hanhTinhSo--;
			if (hanhTinhSo <= 0) {
				hanhTinhSo = 10;
			}
			break;
		case 's':
			glPushMatrix();
			trucZ = trucZ - 0.5;
			glPopMatrix();
			printf("\npress s: %f %f %f", trucX, trucY, trucZ);
			glutPostRedisplay();
			break;
		case 'w':
			glPushMatrix();
			trucZ = trucZ + 0.5;
			glPopMatrix();
			printf("\npress w: %f %f %f", trucX, trucY, trucZ);
			glutPostRedisplay();
			break;

		case 'a':
			glPushMatrix();
			trucX = trucX - 0.5;
			glPopMatrix();
			printf("\npress a: %f %f %f", trucX, trucY, trucZ);
			glutPostRedisplay();
			break;

		case 'd':
			glPushMatrix();
			trucX = trucX + 0.5;
			glPopMatrix();
			printf("\npress d: %f %f %f", trucX, trucY, trucZ);
			glutPostRedisplay();
			break;

		case 'x':
			glPushMatrix();
			trucY = trucY - 0.5;
			glPopMatrix();
			printf("\npress x: %f %f %f", trucX, trucY, trucZ);
			glutPostRedisplay();
			break;
		case 'z':
			glPushMatrix();
			trucY = trucY + 0.5;
			glPopMatrix();
			printf("\npress z: %f %f %f", trucX, trucY, trucZ);
			glutPostRedisplay();
			break;
		default:
			break;
	}
}


//nhận event click chuột
void mouseButton(int button, int state, int x, int y) {
	cout << endl << "mouseButton";
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(trucX, trucY, trucZ, lx, lz, 0, 0.0, 0.5, 0.0);

	}
}

//nhận event kéo chuột
void mouseMove(int x, int y) {
	
	// this will only be true when the left button is down
	if (xOrigin >= 0) {
		cout << endl << "mouseMove"  << "/" << lx << "/" << lz;
		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
		

	}
}

//hàm set cho camera theo cái hành tinh chỉ định
void quayTheoHanhTinh(GLfloat spinQuay, float banKinhQuay) {
	float x = -sin(spinQuay) * (banKinhQuay);
	float y = cos(spinQuay) * (banKinhQuay);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(trucX, trucY, trucZ, x, y, 0, 1, 0, 1.0);
}

//idle
void idle() {
	hanhTinh ht;
	inputValue(ht);
	//	CalculateFrameRate();
	/*spin += 1;
	spinSaoThuy += ((6.0 / 8) * (30 / FPS))*2;
	spinSaoKim += ((5.0 / 8) * (30 / FPS)) * 2;
	spinTraiDat += ((4.0 / 8) * (30 / FPS)) * 2;
	spinSaoHoa += ((3.0 / 8) * (30 / FPS)) * 2;
	spinSaoMoc += ((2.0 / 8) * (30 / FPS)) * 2;
	spinSaoTho += ((1.0 / 8) * (30 / FPS)) * 2;
	spinSaoThienVuong += ((0.5 / 8) * (30 / FPS*2)) * 2;
	spinSaoHaiVuong += ((0.25 / 8) * (30 / FPS)) * 2;
	spinSaoDiemVuong += ((0.125 / 8) * (30 / FPS)) * 2;*/
	
	//--------------
	float value = 0.025;
	spin += 1;
	spinSaoThuy += value*1.5;
	spinSaoKim += value*1.3;
	spinTraiDat += value;
	spinSaoHoa += value*0.8;
	spinSaoMoc += value*0.7;
	spinSaoTho += value*0.5;
	spinSaoThienVuong += value*0.3;
	spinSaoHaiVuong += value*0.2;
	spinSaoDiemVuong += value*0.1;

	//--------------
	ht.saoThuy.spin += (6.0/ 100);
	ht.saoKim.spin += (5.0 / 100);
	ht.traiDat.spin += (4.0 / 100);
	ht.saoHoa.spin += (3.0 / 100);
	ht.saoMoc.spin += (2.0 / 100);
	ht.saoTho.spin += (1.0 / 100);
	ht.saoThienVuong.spin += (0.5 / 100);
	ht.saoHaiVuong.spin += (0.25 / 100);
	ht.saoDiemVuong.spin += (0.125	/ 100);
	//glutTimerFunc(1000 / FPS, idle, 0);

	switch (hanhTinhSo) {
		case 1:
			quayTheoHanhTinh(spinSaoThuy, ht.saoThuy.banKinhQuay);
			break;
		case 2:
			quayTheoHanhTinh(spinSaoKim, ht.saoKim.banKinhQuay);
			break;
		case 3:
			quayTheoHanhTinh(spinTraiDat, ht.traiDat.banKinhQuay);
			break;
		case 4:
			quayTheoHanhTinh(spinSaoHoa, ht.saoHoa.banKinhQuay);
			break;
		case 5:
			quayTheoHanhTinh(spinSaoMoc, ht.saoMoc.banKinhQuay);
			break;
		case 6:
			quayTheoHanhTinh(spinSaoKim, ht.saoTho.banKinhQuay);
			break;
		case 7:
			quayTheoHanhTinh(spinSaoThienVuong, ht.saoThienVuong.banKinhQuay);
			break;
		case 9:
			quayTheoHanhTinh(spinSaoHaiVuong, ht.saoHaiVuong.banKinhQuay);
			break;
		case 10:
			quayTheoHanhTinh(spinSaoDiemVuong, ht.saoDiemVuong.banKinhQuay);
			break;

	}
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	hanhTinh ht;
	inputValue(ht);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("VanTiennn");


	init();
	glutKeyboardFunc(keyboard);
	//glutKeyboardFunc(processSpecialKeys);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutDisplayFunc(display);
	//glutTimerFunc(1000 / FPS, idle, 0);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMainLoop();
}