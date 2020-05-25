#include <windows.h>
#include <ctime>
#include <iostream>
#include <string>

#include "glut.h"


char algo[40];


int Solve();
int Execute_Moves(char[]);
int Finishing_Moves(char);
void keyboard(unsigned char key, int x, int y);
void mousebuttons(int button, int state,int x, int y);
void mouse(void (*func)(int x, int y));
bool cameralock();
int DrawCube();
int DrawRubiksCube();
int DrawSticker(char face, char color, int stickerx, int stickery);
int MovingSticker(char face, int coord1, int coord2);

void Cross();
void F2L(int);
short int counter;
short int counter2;
void OLL();
void PLL();

float startclock;
float endclock = 1;
char movingface = 'N';
char todolist[100];
int Turns;

const float col[4] = {0.0,0.0,0.0,0.7};
float angler;
float anglet;
float yawx;
float yawz;
float angle;
float angley;   //x  y  z
bool MovingPieces[3][3][3] = {
	 //  y1        y2        y3
	{{0, 0, 0},{0, 0, 0},{0, 0, 0}}, //x 1 

	{{0, 0, 0},{0, 0, 0},{0, 0, 0}}, //x 2

	{{0, 0, 0},{0, 0, 0},{0, 0, 0}}  //x 3

	
};

 

char CF[3][3]={{'B','B','B'},{'B','B','B'},{'B','B','B'}};
char CB[3][3]={{'G','G','G'},{'G','G','G'},{'G','G','G'}};
char CL[3][3]={{'O','O','O'},{'O','O','O'},{'O','O','O'}};
char CR[3][3]={{'R','R','R'},{'R','R','R'},{'R','R','R'}};
char CU[3][3]={{'Y','Y','Y'},{'Y','Y','Y'},{'Y','Y','Y'}};
char CD[3][3]={{'W','W','W'},{'W','W','W'},{'W','W','W'}};
float rotatec[3];
char FRONT = CF[1][1];
char BACK = CB[1][1];
char LEFT = CL[1][1];
char RIGHT = CR[1][1];
char TOP = CU[1][1];
char DOWN = CD[1][1];
bool SOLVE = false;
bool ACTIVE = true;

using namespace std;
void Init(){
	glClearColor(0.0, 0.2, 0.5, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, 1920/1080.0, 0.1, 1000.0);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
	
	
}

void keyboard(unsigned char key, int x, int y){

	switch(key){
	
	case 'a':
		ACTIVE = false;
		break;

	case 'A':
		ACTIVE = true;
		break;
	case 'M':
		Execute_Moves("RbrFRBrfRBrFRbrf");
		break;

	case 'o':
		SOLVE = true;
		break;

	case 'O':
		SOLVE = false;
		break;

	case 'L':
		Execute_Moves("L");
		break;
	case 'l':
		Execute_Moves("l");
		break;
	case 'R':
		Execute_Moves("R");
		break;
	case 'r':
		Execute_Moves("r");
		break;
	case 'F':
		Execute_Moves("F");
		break;
	case 'f':
		Execute_Moves("f");
		break;
		case 'B':
		Execute_Moves("B");
		break;
	case 'b':
		Execute_Moves("b");
		break;
		case 'U':
		Execute_Moves("U");
		break;
	case 'u':
		Execute_Moves("u");
		break;
	case 'D':
		Execute_Moves("D");
		break;
	case 'd':
		Execute_Moves("d");
		break;
	case 'Y':
		Execute_Moves("Y");
		break;
	case 'y':
		Execute_Moves("y");
		break;


	
	
	
	case 'x':
		exit(0);
	
	}
}
void mousebuttons(int button, int state,int x, int y){

	if (state == GLUT_UP){
		if (ACTIVE)
		SetCursorPos(1920/2,1080/2);
	}




}
void mouse(int moux, int mouy){
	
	const float speed = 0.08;


	mouy = 1080 - mouy;

	angle -= (moux-(1920/2))*speed;
	angley -= (mouy-(1080/2))*speed;

	if (angle <= 90){
			yawx = (90-angle)/90.0;
			yawz = (angle)/90.0;		
		} else if (angle <= 180) {
			yawx = (angle-90)/-90.0;
			yawz = (180-angle)/90.0;
		} else if (angle <= 270) {
			yawx = (270-angle)/-90.0;
			yawz = (angle-180)/-90.0;
		} else if (angle <= 360) {
			yawx = (angle-270)/90.0;
			yawz = (360-angle)/-90.0;
		}

		
	if (ACTIVE)	
	glutSetCursor(GLUT_CURSOR_NONE);
	else 
		glutSetCursor(1);

	if (!cameralock()){
	glutPostRedisplay();
	}
}

bool cameralock(){

	if (angle > 360)
		angle -= 360;

	if (angle < 0)
		angle += 360;

	if (angley > 50)
		angley = 50;

	if (angley < -50)
		angley = -50;


	//ROTATIONS
	//Y

	if (angle <= 310 && angle > 180){
		angle = 45;
		Execute_Moves("V");
		return 1;
	}

	if (angle >= 50 && angle < 180){
		angle = 315;
		Execute_Moves("v");
		return 1;
	}

	return 0;
}

int Solve(){
	FRONT = CF[1][1];
	BACK = CB[1][1];
	LEFT = CL[1][1];
	RIGHT = CR[1][1];
	TOP = CU[1][1];
	DOWN = CD[1][1];

	//om vita korset inte är löst
	if (CF[1][0] != FRONT || CB[1][0] != BACK || CL[1][0] != LEFT || CR[1][0] != RIGHT || CD[1][0] != DOWN ||  CD[1][2] != DOWN ||  CD[0][1] != DOWN ||  CD[2][1] != DOWN){
		Cross();
		

	

	//om första 2 lagren inte är löst
	}else if (CF[0][1] != FRONT || CF[0][0] != FRONT ||CF[2][1] != FRONT || CF[2][0] != FRONT ||CR[0][1] != RIGHT || CR[0][0] != RIGHT ||CR[2][1] != RIGHT || CR[2][0] != RIGHT   ||   CB[0][1] != BACK || CB[0][0] != BACK ||CB[2][1] != BACK || CB[2][0] != BACK ||CL[0][1] != LEFT || CL[0][0] != LEFT ||CL[2][1] != LEFT || CL[2][0] != LEFT  || CD[0][0] != DOWN || CD[2][0] != DOWN || CD[0][2] != DOWN || CD[2][2] != DOWN){
		if (CF[0][0] != FRONT || CF[2][0] != FRONT || CR[0][0] != RIGHT || CR[2][0] != RIGHT   || CB[0][0] != BACK || CB[2][0] != BACK || CL[0][0] != LEFT || CL[2][0] != LEFT  || CD[0][0] != DOWN || CD[2][0] != DOWN || CD[0][2] != DOWN || CD[2][2] != DOWN)
		F2L(1);
		else
		F2L(2);
		
	}else if( CU[0][0] != TOP || CU[0][1] != TOP || CU[0][2] != TOP || CU[1][0] != TOP || CU[1][1] != TOP || CU[1][2] != TOP || CU[2][0] != TOP || CU[2][1] != TOP || CU[2][2] != TOP){
		
		OLL();
		
	}else if( CF[0][2] != FRONT || CF[2][2] != FRONT || CR[0][2] != RIGHT || CR[2][2] != RIGHT || CB[0][2] != BACK || CB[2][2] != BACK || CL[0][2] != LEFT || CL[2][2] != LEFT || CR[1][2] != RIGHT || CR[1][2] != RIGHT || CB[1][2] != BACK || CL[1][2] != LEFT){

		PLL();
	} else  {
		cout << "The Cube is finished!!" << endl;
		cout << "it only took " << Turns << " Turns." << endl;
		SOLVE = false;
	}

return 0;

}

void Cross(){

	if (CU[1][0] == DOWN){
		if (CF[1][2] == FRONT)
			Execute_Moves("FF");
		else
			Execute_Moves("uY");
	
	}else if (CF[1][2] == DOWN){
		
		Execute_Moves("FrfR");
	
	}else if (CF[2][1] == DOWN || CR[0][1] == DOWN){
	if(CF[2][1] == DOWN)
		Execute_Moves("RUr");
	else
		Execute_Moves("fUFu");
	
	}else if (CF[0][1] == DOWN || CL[2][1] == DOWN){
	if(CF[0][1] == DOWN)
		Execute_Moves("luL");
	else
		Execute_Moves("FUfu");
	
	}else if (CF[1][0] == DOWN || CD[1][2] == DOWN && CF[1][0] != FRONT){
		
		Execute_Moves("FF");
	
	} else 
	Execute_Moves("Y");



}

void F2L(int state){
	//FL
	if (state == 1){
	if (CF[2][2] == DOWN){

		if (CU[2][0] == FRONT)
			Execute_Moves("URur");
		else 
			Execute_Moves("u");

	}else if (CF[0][2] == DOWN){

		if (CU[0][0] == FRONT)
			Execute_Moves("ulUL");
		else 
			Execute_Moves("u");

	}else if (CF[0][0] == DOWN){
		
			Execute_Moves("ulUL");
	
	}else if (CF[2][0] == DOWN){
		
			Execute_Moves("URur");
	
	}else if (CU[0][0] == DOWN){
		
			Execute_Moves("luuLU");
	
	}else if (CU[2][0] == DOWN){
		
			Execute_Moves("RUUru");
	
	}else if (CF[0][0] == DOWN){
		
			Execute_Moves("luL");
	
	}else if (CF[2][0] == DOWN){
		
			Execute_Moves("RUr");
	}else 
	Execute_Moves("Y");
	}else{

	//2L
	if(CF[1][2] == FRONT && CU[1][0] != TOP){

		counter2 = 0;
		if(CU[1][0] == RIGHT)
			Execute_Moves("URurufUF");
		else
			Execute_Moves("ulULUFuf");
		
	}else if(CF[0][1] != FRONT && counter2 >= 4 || CF[2][1] != FRONT && counter2 >= 4 ){

	counter2 = 0;

		if(CF[1][0] != FRONT)
			Execute_Moves("ulULUFuf");
		else
			Execute_Moves("URurufUF");
		
		
	}else if (counter <= 3){ 
		Execute_Moves("U");
	counter ++;
	}else{
		Execute_Moves("Y");
		counter = 0;
		counter2++;
	}

	}

}

void OLL(){
	//Cross
	if (CU[1][0] != TOP || CU[0][1] != TOP || CU[2][1] != TOP || CU[2][1] != TOP ){
	
		if(CU[1][0] != TOP && CU[0][1] != TOP && CU[2][1] != TOP && CU[2][1] != TOP)
			Execute_Moves("FRUruf");
		else if (CU[0][1] == TOP && CU[1][0] != TOP)
			Execute_Moves("FRUruf");
		else 
			Execute_Moves("U");






	}else if(CU[0][0] == TOP && CU[2][0] == TOP){
	
		
			if(CR[2][2] == TOP)
				Execute_Moves("uRUrURUUrUUruRurUUR");
			else
				Execute_Moves("UURRDrUURdrUUr");

			
	
	
	
	}else if(CU[0][0] == TOP && CU[0][2] != TOP){
	
		
			if(CU[0][2] != TOP){
				if(CF[2][2] == TOP)
					Execute_Moves("RUrURUUr");
				else
					Execute_Moves("UruRurUUR");
			}else{
				if(CF[2][2] == TOP)
				Execute_Moves("urFRbrfRB");
				else 
				Execute_Moves("UrFRbrfRB");
			}
	
	
	
	}else if(CU[0][0] != TOP && CU[2][0] != TOP && CU[0][2] != TOP && CU[2][2] != TOP){
	
		
			if(CF[0][2] == TOP && CF[2][2] == TOP && CR[2][2] != TOP)
					Execute_Moves("RUUruRUruRur");
			else if (CL[0][2] == TOP && CL[2][2] == TOP && CF[2][2] == TOP)
					Execute_Moves("RUURRuRRuRRUUR");
			else 
				Execute_Moves("U");
	
	
	}else {
		Execute_Moves("U");
	}



}

void PLL(){

	if(CF[0][2] != CF[2][2] || CR[0][2] != CR[2][2] || CB[0][2] != CB[2][2] || CL[0][2] != CL[2][2]){
	
		if (CB[0][2] == CB[2][2])
			Execute_Moves("rFrBBRfrBBRR");
		else if (counter2 >=3){
			Execute_Moves("RbrFRBrfRBrFRbrf");
			counter2 = 0;
		}else{
			Execute_Moves("U");
			counter2++;
		}
	
	}else if (CF[1][2] == CR[0][2] && CB[1][2] == CB[0][2] || CF[1][2] == CL[0][2] && CB[1][2] == CB[0][2]){

		if (CF[1][2] == CR[0][2])
			Execute_Moves("RuRURURuruRR");
		else 
			Execute_Moves("RRURUrururUr");

	}else if(CF[1][2] == BACK && CB[1][2] == FRONT  &&  CF[0][2] == FRONT|| CF[1][2] == CR[0][2] && CR[1][2] == CF[0][2]){
	
		if (CF[1][2] == BACK)
			Execute_Moves("RRUURUURRUURRUURUURR");
		else
			Execute_Moves("ruRRURUruRURuRurUU");
	}else
		Execute_Moves("U");

}

int Execute_Moves(char algorythm[]){
	const int speed = 300;

	if (algorythm[0] != 'C')
		strcat(todolist, algorythm);

	if (movingface == 'N'){

	//LEFT FACE
	if (todolist[0] == 'L' || todolist[0] == 'l'){
		movingface = 'L';
		for (int y = 0; y<=2;y++){
			for (int z = 0;z<=2;z++)
				MovingPieces[0][y][z] = 1;
		}
			rotatec[0] = 1;
			if (todolist[0] == 'l'){
				movingface = 'l';
				rotatec[0] = -1;}
			anglet = 90.0;
			startclock = clock();
			endclock = speed;
		
	}
	//RIGHT FACE
	if (todolist[0] == 'R' || todolist[0] == 'r'){
		
		movingface = 'R';
		for (int y = 0; y<=2;y++){
			for (int z = 0;z<=2;z++){
				MovingPieces[2][y][z] = 1;
			 
			}
			}
			rotatec[0] = -1;
			if (todolist[0] == 'r'){
				movingface = 'r';
				rotatec[0] = 1;}
			anglet = 90.0;
			startclock = clock();
			endclock = speed;
			
		
	}
	//FRONT FACE
	if (todolist[0] == 'F' || todolist[0] == 'f'){
		movingface = 'F';
		for (int y = 0; y<=2;y++){
			for (int x = 0;x<=2;x++){
				MovingPieces[x][y][2] = 1;
			 
			}
			}
			rotatec[2] = -1;
			if (todolist[0] == 'f'){
				movingface = 'f';
				rotatec[2] = 1;}
			anglet = 90.0;
			startclock = clock();
			endclock = speed;
		
	}
	//BACK FACE
	if (todolist[0] == 'B' || todolist[0] == 'b'){
		movingface = 'B';
		for (int y = 0; y<=2;y++){
			for (int x = 0;x<=2;x++){
				MovingPieces[x][y][0] = 1;
			 
			}
			}
			rotatec[2] = 1;
			if (todolist[0] == 'b'){
				movingface = 'b';
				rotatec[2] = -1;}
			anglet = 90.0;
			startclock = clock();
			endclock = speed;
		
	}
	//TOP FACE
	if (todolist[0] == 'U' || todolist[0] == 'u'){
		movingface = 'U';
		for (int z = 0; z<=2;z++){
			for (int x = 0;x<=2;x++){
				MovingPieces[x][2][z] = 1;
			 
			}
			}
			rotatec[1] = -1;
			if (todolist[0] == 'u'){
				movingface = 'u';
				rotatec[1] = 1;}
			anglet = 90.0;
			startclock = clock();
			endclock = speed;
		
	}
	//DOWN FACE
	if (todolist[0] == 'D' || todolist[0] == 'd'){
		movingface = 'D';
		for (int z = 0; z<=2;z++){
			for (int x = 0;x<=2;x++){
				MovingPieces[x][0][z] = 1;
			 
			}
			}
			rotatec[1] = 1;
			if (todolist[0] == 'd'){
				movingface = 'd';
				rotatec[1] = -1;}
			anglet = 90.0;
			startclock = clock();
			endclock = speed;
		
	}
	//ROTATIONS
	//Y
	if (todolist[0] == 'Y' || todolist[0] == 'y'){
		movingface = 'Y';
		for (int z = 0; z<=2;z++){
			for (int x = 0;x<=2;x++){
				for (int y = 0;y<=2;y++){
				MovingPieces[x][y][z] = 1;
				}
			}
		}
		rotatec[1] = -1;
			if (todolist[0] == 'y'){
				movingface = 'y';
				rotatec[1] = 1;
			}
			anglet = 90.0;
			startclock = clock();
			endclock = speed;
		
	}

	//ROTATIONS
	//Y
	if (todolist[0] == 'V' || todolist[0] == 'v'){
		movingface = 'Y';
			if (todolist[0] == 'v')
				movingface = 'y';
			anglet = 0.0;
			startclock = clock();
			endclock = 1;
		
	}

	}

	
	angler = ((clock()-startclock)/endclock)*anglet;
	

	if (angler >= anglet){
	rotatec[0] = 0;
	rotatec[1] = 0;
	rotatec[2] = 0;
	Turns++;
	angler = 0;
	Finishing_Moves(movingface);
	movingface = 'N';
	for (int y = 0; y<=2;y++){
			for (int z = 0;z<=2;z++)
				for (int  x= 0;x<=2;x++)
					MovingPieces[y][z][x] = 0;
	}

	for(int r = 1; r < 100; r++)
		todolist[r-1] = todolist[r];

	
	}
	
	if (todolist[0] == '\0'){
		return 1;
	}
	
	return 0;
}

int Finishing_Moves(char face){
	//WARNINNG: VERY LONG!
char CFc[3][3]={{CF[0][0],CF[0][1],CF[0][2]},{CF[1][0],CF[1][1],CF[1][2]},{CF[2][0],CF[2][1],CF[2][2]}};
char CBc[3][3]={{CB[0][0],CB[0][1],CB[0][2]},{CB[1][0],CB[1][1],CB[1][2]},{CB[2][0],CB[2][1],CB[2][2]}};
char CLc[3][3]={{CL[0][0],CL[0][1],CL[0][2]},{CL[1][0],CL[1][1],CL[1][2]},{CL[2][0],CL[2][1],CL[2][2]}};
char CRc[3][3]={{CR[0][0],CR[0][1],CR[0][2]},{CR[1][0],CR[1][1],CR[1][2]},{CR[2][0],CR[2][1],CR[2][2]}};
char CUc[3][3]={{CU[0][0],CU[0][1],CU[0][2]},{CU[1][0],CU[1][1],CU[1][2]},{CU[2][0],CU[2][1],CU[2][2]}};
char CDc[3][3]={{CD[0][0],CD[0][1],CD[0][2]},{CD[1][0],CD[1][1],CD[1][2]},{CD[2][0],CD[2][1],CD[2][2]}};

// RIGHT FACE 
	if(face == 'R'){
		CR[0][0] = CRc[2][0];
		CR[0][1] = CRc[1][0];
		CR[0][2] = CRc[0][0];
		CR[1][0] = CRc[2][1];
		CR[1][1] = CRc[1][1];
		CR[1][2] = CRc[0][1];
		CR[2][0] = CRc[2][2];
		CR[2][1] = CRc[1][2];
		CR[2][2] = CRc[0][2];

		CF[2][0] = CDc[2][0];
		CF[2][1] = CDc[2][1];
		CF[2][2] = CDc[2][2];

		CU[2][0] = CFc[2][0];
		CU[2][1] = CFc[2][1];
		CU[2][2] = CFc[2][2];

		CB[0][0] = CUc[2][2];
		CB[0][1] = CUc[2][1];
		CB[0][2] = CUc[2][0];

		CD[2][0] = CBc[0][2];
		CD[2][1] = CBc[0][1];
		CD[2][2] = CBc[0][0];
	}
	// RIGHT FACE Prime 
	if(face == 'r'){
		CR[0][0] = CRc[0][2];
		CR[0][1] = CRc[1][2];
		CR[0][2] = CRc[2][2];
		CR[1][0] = CRc[0][1];
		CR[1][1] = CRc[1][1];
		CR[1][2] = CRc[2][1];
		CR[2][0] = CRc[0][0];
		CR[2][1] = CRc[1][0];
		CR[2][2] = CRc[2][0];

		CF[2][0] = CUc[2][0];
		CF[2][1] = CUc[2][1];
		CF[2][2] = CUc[2][2];

		CU[2][0] = CBc[0][2];
		CU[2][1] = CBc[0][1];
		CU[2][2] = CBc[0][0];

		CB[0][0] = CDc[2][2];
		CB[0][1] = CDc[2][1];
		CB[0][2] = CDc[2][0];

		CD[2][0] = CFc[2][0];
		CD[2][1] = CFc[2][1];
		CD[2][2] = CFc[2][2];
	}





	// LEFT FACE 
	if(face == 'L'){
		CL[0][0] = CLc[2][0];
		CL[0][1] = CLc[1][0];
		CL[0][2] = CLc[0][0];
		CL[1][0] = CLc[2][1];
		CL[1][1] = CLc[1][1];
		CL[1][2] = CLc[0][1];
		CL[2][0] = CLc[2][2];
		CL[2][1] = CLc[1][2];
		CL[2][2] = CLc[0][2];

		CF[0][0] = CUc[0][0];
		CF[0][1] = CUc[0][1];
		CF[0][2] = CUc[0][2];

		CU[0][0] = CBc[2][2];
		CU[0][1] = CBc[2][1];
		CU[0][2] = CBc[2][0];

		CB[2][0] = CDc[0][2];
		CB[2][1] = CDc[0][1];
		CB[2][2] = CDc[0][0];

		CD[0][0] = CFc[0][0];
		CD[0][1] = CFc[0][1];
		CD[0][2] = CFc[0][2];

		
	}
	// LEFT FACE Prime 
	if(face == 'l'){
		CL[0][0] = CLc[0][2];
		CL[0][1] = CLc[1][2];
		CL[0][2] = CLc[2][2];
		CL[1][0] = CLc[0][1];
		CL[1][1] = CLc[1][1];
		CL[1][2] = CLc[2][1];
		CL[2][0] = CLc[0][0];
		CL[2][1] = CLc[1][0];
		CL[2][2] = CLc[2][0];

		CF[0][0] = CDc[0][0];
		CF[0][1] = CDc[0][1];
		CF[0][2] = CDc[0][2];

		CU[0][0] = CFc[0][0];
		CU[0][1] = CFc[0][1];
		CU[0][2] = CFc[0][2];

		CB[2][0] = CUc[0][2];
		CB[2][1] = CUc[0][1];
		CB[2][2] = CUc[0][0];

		CD[0][0] = CBc[2][2];
		CD[0][1] = CBc[2][1];
		CD[0][2] = CBc[2][0];
	}




	// TOP FACE 
	if(face == 'U'){
		CU[0][0] = CUc[2][0];
		CU[0][1] = CUc[1][0];
		CU[0][2] = CUc[0][0];
		CU[1][0] = CUc[2][1];
		CU[1][1] = CUc[1][1];
		CU[1][2] = CUc[0][1];
		CU[2][0] = CUc[2][2];
		CU[2][1] = CUc[1][2];
		CU[2][2] = CUc[0][2];

		CF[0][2] = CRc[0][2];
		CF[1][2] = CRc[1][2];
		CF[2][2] = CRc[2][2];

		CL[0][2] = CFc[0][2];
		CL[1][2] = CFc[1][2];
		CL[2][2] = CFc[2][2];

		CB[0][2] = CLc[0][2];
		CB[1][2] = CLc[1][2];
		CB[2][2] = CLc[2][2];

		CR[0][2] = CBc[0][2];
		CR[1][2] = CBc[1][2];
		CR[2][2] = CBc[2][2];
	}
	// TOP FACE Prime 
	if(face == 'u'){
		CU[0][0] = CUc[0][2];
		CU[0][1] = CUc[1][2];
		CU[0][2] = CUc[2][2];
		CU[1][0] = CUc[0][1];
		CU[1][1] = CUc[1][1];
		CU[1][2] = CUc[2][1];
		CU[2][0] = CUc[0][0];
		CU[2][1] = CUc[1][0];
		CU[2][2] = CUc[2][0];

		CF[0][2] = CLc[0][2];
		CF[1][2] = CLc[1][2];
		CF[2][2] = CLc[2][2];

		CL[0][2] = CBc[0][2];
		CL[1][2] = CBc[1][2];
		CL[2][2] = CBc[2][2];

		CB[0][2] = CRc[0][2];
		CB[1][2] = CRc[1][2];
		CB[2][2] = CRc[2][2];

		CR[0][2] = CFc[0][2];
		CR[1][2] = CFc[1][2];
		CR[2][2] = CFc[2][2];
	}
	



	// DOWN FACE 
	if(face == 'D'){
		CD[0][0] = CDc[2][0];
		CD[0][1] = CDc[1][0];
		CD[0][2] = CDc[0][0];
		CD[1][0] = CDc[2][1];
		CD[1][1] = CDc[1][1];
		CD[1][2] = CDc[0][1];
		CD[2][0] = CDc[2][2];
		CD[2][1] = CDc[1][2];
		CD[2][2] = CDc[0][2];

		CF[0][0] = CLc[0][0];
		CF[1][0] = CLc[1][0];
		CF[2][0] = CLc[2][0];

		CL[0][0] = CBc[0][0];
		CL[1][0] = CBc[1][0];
		CL[2][0] = CBc[2][0];

		CB[0][0] = CRc[0][0];
		CB[1][0] = CRc[1][0];
		CB[2][0] = CRc[2][0];

		CR[0][0] = CFc[0][0];
		CR[1][0] = CFc[1][0];
		CR[2][0] = CFc[2][0];
	}
	// DOWN FACE Prime 
	if(face == 'd'){
		CD[0][0] = CDc[0][2];
		CD[0][1] = CDc[1][2];
		CD[0][2] = CDc[2][2];
		CD[1][0] = CDc[0][1];
		CD[1][1] = CDc[1][1];
		CD[1][2] = CDc[2][1];
		CD[2][0] = CDc[0][0];
		CD[2][1] = CDc[1][0];
		CD[2][2] = CDc[2][0];

		CF[0][0] = CRc[0][0];
		CF[1][0] = CRc[1][0];
		CF[2][0] = CRc[2][0];

		CL[0][0] = CFc[0][0];
		CL[1][0] = CFc[1][0];
		CL[2][0] = CFc[2][0];

		CB[0][0] = CLc[0][0];
		CB[1][0] = CLc[1][0];
		CB[2][0] = CLc[2][0];

		CR[0][0] = CBc[0][0];
		CR[1][0] = CBc[1][0];
		CR[2][0] = CBc[2][0];
	}




	// FRONT FACE 
	if(face == 'F'){
		CF[0][0] = CFc[2][0];
		CF[0][1] = CFc[1][0];
		CF[0][2] = CFc[0][0];
		CF[1][0] = CFc[2][1];
		CF[1][1] = CFc[1][1];
		CF[1][2] = CFc[0][1];
		CF[2][0] = CFc[2][2];
		CF[2][1] = CFc[1][2];
		CF[2][2] = CFc[0][2];

		CU[0][0] = CLc[2][0];
		CU[1][0] = CLc[2][1];
		CU[2][0] = CLc[2][2];

		CL[2][0] = CDc[2][2];
		CL[2][1] = CDc[1][2];
		CL[2][2] = CDc[0][2];

		CD[0][2] = CRc[0][0];
		CD[1][2] = CRc[0][1];
		CD[2][2] = CRc[0][2];

		CR[0][0] = CUc[2][0];
		CR[0][1] = CUc[1][0];
		CR[0][2] = CUc[0][0];
	}
	// FRONT FACE Prime 
	if(face == 'f'){
		CF[0][0] = CFc[0][2];
		CF[0][1] = CFc[1][2];
		CF[0][2] = CFc[2][2];
		CF[1][0] = CFc[0][1];
		CF[1][1] = CFc[1][1];
		CF[1][2] = CFc[2][1];
		CF[2][0] = CFc[0][0];
		CF[2][1] = CFc[1][0];
		CF[2][2] = CFc[2][0];

		CU[0][0] = CRc[0][2];
		CU[1][0] = CRc[0][1];
		CU[2][0] = CRc[0][0];

		CL[2][0] = CUc[0][0];
		CL[2][1] = CUc[1][0];
		CL[2][2] = CUc[2][0];
		//wrong 
		CD[0][2] = CLc[2][2];
		CD[1][2] = CLc[2][1];
		CD[2][2] = CLc[2][0];

		CR[0][0] = CDc[0][2];
		CR[0][1] = CDc[1][2];
		CR[0][2] = CDc[2][2];
	}

	// BACK FACE 
	if(face == 'B'){
		CB[0][0] = CBc[2][0];
		CB[0][1] = CBc[1][0];
		CB[0][2] = CBc[0][0];
		CB[1][0] = CBc[2][1];
		CB[1][1] = CBc[1][1];
		CB[1][2] = CBc[0][1];
		CB[2][0] = CBc[2][2];
		CB[2][1] = CBc[1][2];
		CB[2][2] = CBc[0][2];

		CU[0][2] = CRc[2][2];
		CU[1][2] = CRc[2][1];
		CU[2][2] = CRc[2][0];

		CL[0][0] = CUc[0][2];
		CL[0][1] = CUc[1][2];
		CL[0][2] = CUc[2][2];

		CD[0][0] = CLc[0][2];
		CD[1][0] = CLc[0][1];
		CD[2][0] = CLc[0][0];

		CR[2][0] = CDc[0][0];
		CR[2][1] = CDc[1][0];
		CR[2][2] = CDc[2][0];
	}
	// BACK FACE Prime 
	if(face == 'b'){
		CB[0][0] = CBc[0][2];
		CB[0][1] = CBc[1][2];
		CB[0][2] = CBc[2][2];
		CB[1][0] = CBc[0][1];
		CB[1][1] = CBc[1][1];
		CB[1][2] = CBc[2][1];
		CB[2][0] = CBc[0][0];
		CB[2][1] = CBc[1][0];
		CB[2][2] = CBc[2][0];

		CU[0][2] = CLc[0][0];
		CU[1][2] = CLc[0][1];
		CU[2][2] = CLc[0][2];

		CL[0][0] = CDc[2][0];
		CL[0][1] = CDc[1][0];
		CL[0][2] = CDc[0][0];

		CD[0][0] = CRc[2][0];
		CD[1][0] = CRc[2][1];
		CD[2][0] = CRc[2][2];

		CR[2][0] = CUc[2][2];
		CR[2][1] = CUc[1][2];
		CR[2][2] = CUc[0][2];
	}

	// Y ROTATION
	if(face == 'Y'){
		CU[0][0] = CUc[2][0];
		CU[0][1] = CUc[1][0];
		CU[0][2] = CUc[0][0];
		CU[1][0] = CUc[2][1];
		CU[1][1] = CUc[1][1];
		CU[1][2] = CUc[0][1];
		CU[2][0] = CUc[2][2];
		CU[2][1] = CUc[1][2];
		CU[2][2] = CUc[0][2];

		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CF[x][y] = CRc[x][y];
		}
		}//for end
		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CL[x][y] = CFc[x][y];
		}
		}//for end
		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CB[x][y] = CLc[x][y];
		}
		}//for end
		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CR[x][y] = CBc[x][y];
		}
		}//for end

		CD[0][0] = CDc[0][2];
		CD[0][1] = CDc[1][2];
		CD[0][2] = CDc[2][2];
		CD[1][0] = CDc[0][1];
		CD[1][1] = CDc[1][1];
		CD[1][2] = CDc[2][1];
		CD[2][0] = CDc[0][0];
		CD[2][1] = CDc[1][0];
		CD[2][2] = CDc[2][0];
	}

	// Y ROTATION prime
	if(face == 'y'){
		CU[0][0] = CUc[0][2];
		CU[0][1] = CUc[1][2];
		CU[0][2] = CUc[2][2];
		CU[1][0] = CUc[0][1];
		CU[1][1] = CUc[1][1];
		CU[1][2] = CUc[2][1];
		CU[2][0] = CUc[0][0];
		CU[2][1] = CUc[1][0];
		CU[2][2] = CUc[2][0];

		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CF[x][y] = CLc[x][y];
		}
		}//for end
		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CL[x][y] = CBc[x][y];
		}
		}//for end
		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CB[x][y] = CRc[x][y];
		}
		}//for end
		for (int x = 0; x <= 2; x++){
		for (int y = 0; y <= 2; y++){
		CR[x][y] = CFc[x][y];
		}
		}//for end

		CD[0][0] = CDc[2][0];
		CD[0][1] = CDc[1][0];
		CD[0][2] = CDc[0][0];
		CD[1][0] = CDc[2][1];
		CD[1][1] = CDc[1][1];
		CD[1][2] = CDc[0][1];
		CD[2][0] = CDc[2][2];
		CD[2][1] = CDc[1][2];
		CD[2][2] = CDc[0][2];
	}



return 0;
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	if (SOLVE && Execute_Moves("C") == 1)
		Solve();

	if(!SOLVE)
		Execute_Moves("C");
	
	glColor4f(col[0],col[1],col[2],col[3]);
	
	DrawRubiksCube();
	if (ACTIVE)
	SetCursorPos(1920/2, 1080/2);
	Sleep(15);
	
	glPopMatrix();
	glFlush();
	glutPostRedisplay();
}

int DrawCube(){
		
	glBegin(GL_QUADS); //Front
		glVertex3f( -0.2 , 0.2 , 0.2);
		glVertex3f( 0.2 , 0.2 , 0.2);
		glVertex3f( 0.2 , -0.2 , 0.2);
		glVertex3f( -0.2 , -0.2 , 0.2);
						//Back
		glVertex3f( -0.2 , 0.2 , -0.2);
		glVertex3f( 0.2 , 0.2 , -0.2);
		glVertex3f( 0.2 , -0.2 , -0.2);
		glVertex3f( -0.2 , -0.2 , -0.2);
						//Left
		glVertex3f( 0.2 , 0.2 , -0.2);
		glVertex3f( 0.2 , 0.2 , 0.2);
		glVertex3f( 0.2 , -0.2 , 0.2);
		glVertex3f( 0.2 , -0.2 , -0.2);
						//Right
		glVertex3f( -0.2 , 0.2 , -0.2);
		glVertex3f( -0.2 , 0.2 , 0.2);
		glVertex3f( -0.2 , -0.2 , 0.2);
		glVertex3f( -0.2 , -0.2 , -0.2);
						//Top
		glVertex3f( -0.2 , 0.2 , 0.2);
		glVertex3f( -0.2 , 0.2 , -0.2);
		glVertex3f( 0.2 , 0.2 , -0.2);
		glVertex3f( 0.2 , 0.2 , 0.2);
						//Down
		glVertex3f( -0.2 , -0.2 , 0.2);
		glVertex3f( -0.2 , -0.2 , -0.2);
		glVertex3f( 0.2 , -0.2 , -0.2);
		glVertex3f( 0.2 , -0.2 , 0.2);

glEnd();

	return 0;
}

int DrawSticker(char face, char color, int stickerx, int stickery){
	if(color == 'B')
		glColor3f(0.0,0.0,1.0);
	if(color == 'G')
		glColor3f(0.0,1.0,0.0);
	if(color == 'O')
		glColor3f(1.0,127/255.0,0.0);
	if(color == 'R')
		glColor3f(1.0,0.0,0.0);
	if(color == 'Y')
		glColor3f(1.0,1.0,0.0);
	if(color == 'W')
		glColor3f(1.0,1.0,1.0);


	if (face == 'B' || face == 'F' ){
		glPushMatrix();
		if (face == 'B')
		stickerx = 2-stickerx;
		
		glTranslatef(0.42*(stickerx-1),0.42*(stickery-1),0.0);
		}

	if (face == 'F'){
	
	glBegin(GL_QUADS); //Front
		glVertex3f( -0.16 , 0.16 , 0.63);
		glVertex3f( 0.16 , 0.16 , 0.63);
		glVertex3f( 0.16 , -0.16 , 0.63);
		glVertex3f( -0.16 , -0.16 , 0.63);
	glEnd();
	glPopMatrix();
	}

		if (face == 'B'){
	
	glBegin(GL_QUADS); //Back
		glVertex3f( -0.16 , 0.16 , -0.63);
		glVertex3f( 0.16 , 0.16 , -0.63);
		glVertex3f( 0.16 , -0.16 , -0.63);
		glVertex3f( -0.16 , -0.16 , -0.63);
	glEnd();
	glPopMatrix();
	}

		if (face == 'R' || face == 'L' ){
		glPushMatrix();
		if (face == 'R')
		stickerx = 2-stickerx;
		glTranslatef(0.0,0.42*(stickery-1),0.42*(stickerx-1));
		}

			if (face == 'R'){
	
	glBegin(GL_QUADS); //Right
		glVertex3f( 0.63 , 0.16 , -0.16);
		glVertex3f( 0.63 , 0.16 , 0.16);
		glVertex3f( 0.63 , -0.16 , 0.16);
		glVertex3f( 0.63 , -0.16 , -0.16);
	glEnd();
	glPopMatrix();
	}

				if (face == 'L'){
	
	glBegin(GL_QUADS); //Left
		glVertex3f( -0.63 , 0.16 , -0.16);
		glVertex3f( -0.63 , 0.16 , 0.16);
		glVertex3f( -0.63 , -0.16 , 0.16);
		glVertex3f( -0.63 , -0.16 , -0.16);
	glEnd();
	glPopMatrix();
	}
	
	if (face == 'D' || face == 'T' ){
		glPushMatrix();
		if (face == 'T')
		stickery = 2-stickery;
		glTranslatef(0.42*(stickerx-1),0.0,0.42*(stickery-1));
		}


					if (face == 'T'){
	
	glBegin(GL_QUADS); //Top
		glVertex3f( -0.16 , 0.63 , 0.16);
		glVertex3f( -0.16 , 0.63 , -0.16);
		glVertex3f( 0.16 , 0.63 , -0.16);
		glVertex3f( 0.16 , 0.63 , 0.16);
	glEnd();
	glPopMatrix();
	}
						if (face == 'D'){
	
	glBegin(GL_QUADS); //Bottom
		glVertex3f( -0.16 , -0.63 , 0.16);
		glVertex3f( -0.16 , -0.63 , -0.16);
		glVertex3f( 0.16 , -0.63 , -0.16);
		glVertex3f( 0.16 , -0.63 , 0.16);
	glEnd();
	glPopMatrix();
	}

	
	return 0;
}

int MovingSticker(char face, int coord1, int coord2){
	int coord;
	char f;
	if (face == 'F'){
		coord = 0;
		f = 'z';
	}
	if (face == 'B'){
		coord = 2;
		f = 'z';
	}
	if (face == 'L'){
		coord = 0;
		f = 'x';
	}
	if (face == 'R'){
		coord = 2;
		f = 'x';
	}
	if (face == 'T'){
		coord = 2;
		f = 'y';
	}
	if (face == 'D'){
		coord = 0;
		f = 'y';
	}
	if (face == 'F' || face == 'B'){
		if (face == 'B')
			coord1 = 2-coord1;
		if ( MovingPieces[coord1][coord2][2-coord] == 1 ){
			return 1;
		}
		
		
		
	}if (face == 'L' || face == 'R'){
		if (face == 'R')
			coord1 = 2-coord1;

		if (MovingPieces[coord][coord2][coord1] == 1)
			return 1;
		
		
		
	}if (face == 'T' || face == 'D'){
		if (face == 'T')
			coord2 = 2-coord2;
		if (MovingPieces[coord1][coord][coord2] == 1)
			return 1;

	}
	

return 0;
}

int DrawRubiksCube(){

glTranslatef(0.0,0.0,-3.0);
glRotatef(angle,0.0,7.0,0.0);
glRotatef(angley,yawx,0.0,yawz);
	
	//draw moving pices
	for(int x = 0; x <=2 ; x++){

		for(int y = 0; y <=2 ; y++){

			for(int z = 0; z <=2 ; z++){
				if (MovingPieces[x][y][z]){
				glPushMatrix();
				glRotatef(angler, rotatec[0],rotatec[1],rotatec[2]);
				glTranslatef(0.42*(x-1), 0.42*(y-1), 0.42*(z-1));
				DrawCube();
				glPopMatrix();
				
				}
		
			}
		}
	}
	//draw moving stickers
	glPushMatrix();
	glRotatef(angler, rotatec[0],rotatec[1],rotatec[2]);
				
	for(int f = 1; f<=6; f++){
		char face;
		char color;
		
		for(int j = 0; j<= 2; j++){
			for(int k = 0; k <= 2; k++){
		 switch(f){
			
			case 1:
				face='F';
				color = CF[j][k];
				break;
			case 2:
				face='B';
				color = CB[j][k];
				break;
			case 3:
				face='L';
				color = CL[j][k];
				break;
			case 4:
				face='R';
				color = CR[j][k];
				break;
			case 5:
				face='T';
				color = CU[j][k];
				break;
			case 6:
				face='D';
				color = CD[j][k];
				break;
			 }
					if(MovingSticker(face,j,k)){
					DrawSticker(face,color,j,k);
					}
			}
		}
	}
	glPopMatrix();
	

	glColor4f(col[0],col[1],col[2],col[3]);
	//draw still pices
	for(int x = 0; x <=2 ; x++){

		for(int y = 0; y <=2 ; y++){

			for(int z = 0; z <=2 ; z++){
				if (!MovingPieces[x][y][z]){
				glPushMatrix();
				glTranslatef(0.42*(x-1), 0.42*(y-1), 0.42*(z-1));
				DrawCube();
				glPopMatrix();
				
				}
				
			}
		}
	}
	//draw still stickers

	for(int f = 1; f<=6; f++){
		char face;
		char color;
		
		for(int j = 0; j<= 2; j++){
			for(int k = 0; k <= 2; k++){
		 switch(f){
			
			case 1:
				face='F';
				color = CF[j][k];
				break;
			case 2:
				face='B';
				color = CB[j][k];
				break;
			case 3:
				face='L';
				color = CL[j][k];
				break;
			case 4:
				face='R';
				color = CR[j][k];
				break;
			case 5:
				face='T';
				color = CU[j][k];
				break;
			case 6:
				face='D';
				color = CD[j][k];
				break;
			 }
					if(!MovingSticker(face,j,k)){
					DrawSticker(face,color,j,k);
					}

			}
		}
	}

return 0;
}

int main(int iArgc, char** cppArgv)
{
	
	glutInit( &iArgc , cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rubiks cube");
	glutFullScreen();
	Init();

	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousebuttons);
	glutMotionFunc(mouse);



	glutMainLoop();
	return 0;
}