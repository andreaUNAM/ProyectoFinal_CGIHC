/*---------------------------------------------------------*/
/* ----------------  PROYECTO FINAL      -----------*/
/*-----------------    2022-2   ---------------------------*/
/*------------- Alumnos:                     ---------------*/
/*------------- Alfaro Alfaro, Alejandro Esaú ---------------*/
/*------------- Alfaro Domínguez, Rodrigo     ---------------*/
/*------------- Moguel Krause, Andrea         ---------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <chrono>
#include <windows.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor* monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 300.0f, 0.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	orienta = 0.0f,
joseX = 1500,
joseZ = -800.0,
joseY = 0.0,
deltaJose = 0.0,
deltaRadio = 1.0;
//Variables de cambio de la nave
float   roamingX = 1500,
roamingZ = -800,
roamingY = 500,
deltaRoamingZ = 0.0,
deltaRoamingY = 0.0,
rotarJose = 0.0;
//Variables de cambio de los rituales
float ritualZ = -800.0,
anti_ritualZ = 200.0,
union_ritualX = 2000.0,
rituales_escala = 2.0,
ritual_rot = 0.0;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
dibujaJose = true,
abducir = false,
cambiaTrayectoriaNave = false,
hacer_ritual = false,
dibuja_ritual = true,
dibuja_anti_ritual = true,
dibuja_union_ritual = false;

//Variables de control helado
bool derretir_helado = false;
int helado_opt = 0;
int cont_galleta = 0;
bool existe_charco = false;
bool ritualVoodoo = false;

//Variables de modificacion helado
float y_gota = 3.5f;
float pos_gota = -230.0f;
float ancho_gota = 3.5f;
float ancho_galleta = 0.7f;
float relleno_y = -200.0f;
float ancho_charco = 2.0f;
float y_tapa = -200.0f;

//Variables muñeco
float voodooX = 2200.0f, 
	  voodooY = -350.0f, 
	  rotVodoo = 90.0f,
	  voodooXInc = 0.0f,
	  voodooYInc = 0.0f,
	  voodooZInc = 0.0f,
	  rotVodooInc = 0.0f;
//Variables martillo
float hammerX = 2132.0f,
	  hammerY = -350.0f,
	  hammerZ = -2200.0f,
	  rotHammer = 90.0f,
	  hammerXInc = 0.0f,
	  hammerYInc = 0.0f,
	  hammerZInc = 0.0f,
	  rotHammerInc = 0.0f;
//Variables clavo1
float nailX = 2150.0f, 
      nailY = -348.0f, 
	  nailZ = -2170.0f,
      rotNail = 180.0f,
	  nailXInc = 0.0f,
	  nailYInc = 0.0f,
	  nailZInc = 0.0f,
	  rotNailInc = 0.0f;

float nail2X = 2150.0f, 
      nail2Y = -348.0f, 
	  nail2Z = -2165.0f,
	  nail2XInc = 0.0f,
	  nail2YInc = 0.0f,
	  nail2ZInc = 0.0f;


float nail3X = 2150.0f,
      nail3Y = -348.0f,
      nail3Z = -2160.0f,
      nail3XInc = 0.0f,
      nail3YInc = 0.0f, 
	  nail3ZInc = 0.0f;

// Movimiento del coche de Steven
float movX_coche1 = 0.0f, movZ_coche1 = 0.0f, giroCoche1 = 0.0f;
int edoCoche1 = 0;
// Movimiento del coche voxel
float movX_coche2 = 0.0f, movZ_coche2 = 0.0f, giroCoche2 = 0.0f;
int edoCoche2 = 0;

//Keyframes (Manipulación y dibujo)
// Movimiento BMO
float	BMOposX = 0.0f,
BMOposY = 0.0f,
BMOposZ = 0.0f,
rotBrazoDer = 0.0f,
rotBrazoIzq = 0.0f,
rotPiernaDer = 0.0f,
rotPiernaIzq = 0.0f,
giroBMO = 0.0f;
float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,
rotBrazoDerInc = 0.0f,
rotBrazoIzqInc = 0.0f,
rotPiernaDerInc = 0.0f,
rotPiernaIzqInc = 0.0f,
giroBMOInc = 0.0f;

#define MAX_FRAMES 9
int i_max_steps = 25;
int i_curr_steps = 0;
typedef struct _frame
{
	float	BMOposX,
		BMOposY,
		BMOposZ,
		rotBrazoDer,
		rotBrazoIzq,
		rotPiernaDer,
		rotPiernaIzq,
		giroBMO;

}FRAME;

bool cambioGiroVoodoo = false;

typedef struct _frame2
{
	float voodooX,
		voodooY,
		rotVodoo,
		hammerX,
		hammerY,
		rotHammer,
		nailX,
		nailY,
		nailZ,
		rotNail,
		nail2X,
		nail2Y,
		nail2Z,
		nail3X,
		nail3Y,
		nail3Z;

	 bool cambioGiroVoodoo;
}FRAME2;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;


#define MAX_FRAMES 18
int i_max_steps2 = 10;
int i_curr_steps2 = 0;
FRAME2 KeyFrame2[MAX_FRAMES];
int Frame2Index = 0;
bool play2 = false;
int playIndex2 = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	/*cout << "Frame Index = " << FrameIndex << endl;
	cout << "KeyFrame[" << FrameIndex << "].BMOposX = " << BMOposX << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].BMOposY = " << BMOposY << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].BMOposZ = " << BMOposZ << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotBrazoIzq = " << rotBrazoIzq << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotBrazoDer = " << rotBrazoDer << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotPiernaDer = " << rotPiernaDer << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotPiernaIzq = " << rotPiernaIzq << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].giroBMO = " << giroBMO << ";" << endl;*/


	KeyFrame[FrameIndex].BMOposX = BMOposX;
	KeyFrame[FrameIndex].BMOposY = BMOposY;
	KeyFrame[FrameIndex].BMOposZ = BMOposZ;

	KeyFrame[FrameIndex].rotBrazoIzq = rotBrazoIzq;
	KeyFrame[FrameIndex].rotBrazoDer = rotBrazoDer;
	KeyFrame[FrameIndex].rotPiernaIzq = rotPiernaIzq;
	KeyFrame[FrameIndex].rotPiernaDer = rotPiernaDer;
	KeyFrame[FrameIndex].giroBMO = giroBMO;

	FrameIndex++;
}

void saveFrame2(void) {

	KeyFrame2[Frame2Index].voodooX = voodooX;
	KeyFrame2[Frame2Index].voodooY = voodooY;
	KeyFrame2[Frame2Index].rotVodoo = rotVodoo;

	KeyFrame2[Frame2Index].hammerX = hammerX;
	KeyFrame2[Frame2Index].hammerY = hammerY;
	KeyFrame2[Frame2Index].rotHammer = rotHammer;

	KeyFrame2[Frame2Index].nailX = nailX;
	KeyFrame2[Frame2Index].nailY = nailY;
	KeyFrame2[Frame2Index].nailZ = nailZ;
	KeyFrame2[Frame2Index].rotNail = rotNail;

	KeyFrame2[Frame2Index].nail2X = nail2X;
	KeyFrame2[Frame2Index].nail2Y = nail2Y;
	KeyFrame2[Frame2Index].nail2Z = nail2Z;

	KeyFrame2[Frame2Index].nail3X = nail3X;
	KeyFrame2[Frame2Index].nail3Y = nail3Y;
	KeyFrame2[Frame2Index].nail3Z = nail3Z;

	KeyFrame2[Frame2Index].cambioGiroVoodoo = cambioGiroVoodoo;

	cout << "KeyFrame2[" << Frame2Index << "].voodooX = " << voodooX << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].voodooY = " << voodooY << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].rotVodoo = " << rotVodoo << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].hammerX = " << hammerX << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].hammerY = " << hammerY << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].rotHammer = " << rotHammer << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nailX = " << nailX << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nailY = " << nailY << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nailZ = " << nailZ << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].rotNail = " << rotNail << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nail2X = " << nail2X << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nail2Y = " << nail2Y << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nail2Z = " << nail2Z << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nail3X = " << nail3X << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nail3Y = " << nail3Y << ";" << endl;
	cout << "KeyFrame2[" << Frame2Index << "].nail3Z = " << nail3Z << ";" << endl;

	cout << "KeyFrame2[" << Frame2Index << "].cambioGiroVoodoo = " << cambioGiroVoodoo << ";" << endl;

	Frame2Index++;
}

void resetElements(void)
{
	BMOposX = KeyFrame[0].BMOposX;
	BMOposY = KeyFrame[0].BMOposY;
	BMOposZ = KeyFrame[0].BMOposZ;

	rotBrazoIzq = KeyFrame[0].rotBrazoIzq;
	rotBrazoDer = KeyFrame[0].rotBrazoDer;
	rotPiernaIzq = KeyFrame[0].rotPiernaIzq;
	rotPiernaDer = KeyFrame[0].rotPiernaDer;
	giroBMO = KeyFrame[0].giroBMO;
}

void resetElements2(void) {
	voodooX = KeyFrame2[0].voodooX;
	voodooY = KeyFrame2[0].voodooY;
	rotVodoo = KeyFrame2[0].rotVodoo;

	hammerX = KeyFrame2[0].hammerX;
	hammerY = KeyFrame2[0].hammerY;
	rotHammer = KeyFrame2[0].rotHammer;

	nailX = KeyFrame2[0].nailX;
	nailY = KeyFrame2[0].nailY;
	nailZ = KeyFrame2[0].nailZ;
	rotNail = KeyFrame2[0].rotNail;

	nail2X = KeyFrame2[0].nail2X;
	nail2Y = KeyFrame2[0].nail2Y;
	nail2Z = KeyFrame2[0].nail2Z;

	nail3X = KeyFrame2[0].nail3X;
	nail3Y = KeyFrame2[0].nail3Y;
	nail3Z = KeyFrame2[0].nail3Z;

	cambioGiroVoodoo = false;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].BMOposX - KeyFrame[playIndex].BMOposX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].BMOposY - KeyFrame[playIndex].BMOposY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].BMOposZ - KeyFrame[playIndex].BMOposZ) / i_max_steps;

	rotBrazoIzqInc = (KeyFrame[playIndex + 1].rotBrazoIzq - KeyFrame[playIndex].rotBrazoIzq) / i_max_steps;
	rotBrazoDerInc = (KeyFrame[playIndex + 1].rotBrazoDer - KeyFrame[playIndex].rotBrazoDer) / i_max_steps;
	rotPiernaIzqInc = (KeyFrame[playIndex + 1].rotPiernaIzq - KeyFrame[playIndex].rotPiernaIzq) / i_max_steps;
	rotPiernaDerInc = (KeyFrame[playIndex + 1].rotPiernaDer - KeyFrame[playIndex].rotPiernaDer) / i_max_steps;
	giroBMOInc = (KeyFrame[playIndex + 1].giroBMO - KeyFrame[playIndex].giroBMO) / i_max_steps;

}

void interpolation2(void) {

	voodooXInc = (KeyFrame2[playIndex2 + 1].voodooX - KeyFrame2[playIndex2].voodooX) / i_max_steps2;
	voodooYInc = (KeyFrame2[playIndex2 + 1].voodooY - KeyFrame2[playIndex2].voodooY) / i_max_steps2;
	rotVodooInc = (KeyFrame2[playIndex2 + 1].rotVodoo - KeyFrame2[playIndex2].rotVodoo) / i_max_steps2;

	hammerXInc = (KeyFrame2[playIndex2 + 1].hammerX - KeyFrame2[playIndex2].hammerX) / i_max_steps2;
	hammerYInc = (KeyFrame2[playIndex2 + 1].hammerY - KeyFrame2[playIndex2].hammerY) / i_max_steps2;
	rotHammerInc = (KeyFrame2[playIndex2 + 1].rotHammer - KeyFrame2[playIndex2].rotHammer) / i_max_steps2;

	nailXInc = (KeyFrame2[playIndex2 + 1].nailX - KeyFrame2[playIndex2].nailX) / i_max_steps2;
	nailYInc = (KeyFrame2[playIndex2 + 1].nailY - KeyFrame2[playIndex2].nailY) / i_max_steps2;
	nailZInc = (KeyFrame2[playIndex2 + 1].nailZ - KeyFrame2[playIndex2].nailZ) / i_max_steps2;
	rotNailInc = (KeyFrame2[playIndex2 + 1].rotNail - KeyFrame2[playIndex2].rotNail) / i_max_steps2;

	nail2XInc = (KeyFrame2[playIndex2 + 1].nail2X - KeyFrame2[playIndex2].nail2X) / i_max_steps2;
	nail2YInc = (KeyFrame2[playIndex2 + 1].nail2Y - KeyFrame2[playIndex2].nail2Y) / i_max_steps2;
	nail2ZInc = (KeyFrame2[playIndex2 + 1].nail2Z - KeyFrame2[playIndex2].nail2Z) / i_max_steps2;

	nail3XInc = (KeyFrame2[playIndex2 + 1].nail3X - KeyFrame2[playIndex2].nail3X) / i_max_steps2;
	nail3YInc = (KeyFrame2[playIndex2 + 1].nail3Y - KeyFrame2[playIndex2].nail3Y) / i_max_steps2;
	nail3ZInc = (KeyFrame2[playIndex2 + 1].nail3Z - KeyFrame2[playIndex2].nail3Z) / i_max_steps2;
	cambioGiroVoodoo = KeyFrame2[playIndex2].cambioGiroVoodoo;

}

void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			BMOposX += incX;
			BMOposY += incY;
			BMOposZ += incZ;

			rotBrazoIzq += rotBrazoIzqInc;
			rotBrazoDer += rotBrazoDerInc;
			rotPiernaIzq += rotPiernaIzqInc;
			rotPiernaDer += rotPiernaDerInc;
			giroBMO += giroBMOInc;

			i_curr_steps++;
		}
	}

	if (play2)
	{
		if (i_curr_steps2 >= i_max_steps2) //end of animation between frames?
		{
			playIndex2++;
			if (playIndex2 > Frame2Index - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex2 = 0;
				play2 = false;
				ritualVoodoo = false;
				resetElements2();
			}
			else //Next frame interpolations
			{
				i_curr_steps2 = 0; //Reset counter
								  //Interpolation
				interpolation2();
			}
		}
		else
		{
			ritualVoodoo = true;
			std::cout << "Step " << playIndex2 << std::endl;
			//Draw animation
			voodooX += voodooXInc;
			voodooY += voodooYInc;
			rotVodoo += rotVodooInc;
			hammerX += hammerXInc;
			hammerY += hammerYInc;
			rotHammer += rotHammerInc;
			nailX += nailXInc;
			nailY += nailYInc;
			nailZ += nailZInc;
			rotNail += rotNailInc;
			nail2X += nail2XInc;
			nail2Y += nail2YInc;
			nail2Z += nail2ZInc;
			nail3X += nail3XInc;
			nail3Y += nail3YInc;
			nail3Z += nail3ZInc;

			i_curr_steps2++;
		}
	}

	// Recorrido coche Steven
	switch (edoCoche1)
	{
	case 0:
		movX_coche1 = 0.0f;
		movZ_coche1 = 0.0f;
		giroCoche1 = 0.0f;
		break;
	case 1:
		movX_coche1 = 0.0f;
		movZ_coche1 += 5.0f;
		giroCoche1 = 0.0f;
		if (movZ_coche1 >= 975.0f)
			edoCoche1 = 2;
		break;
	case 2:
		movX_coche1 += 5.0f;
		movZ_coche1 = 975.0f;
		giroCoche1 = 90.0f;
		if (movX_coche1 >= 870.0f)
			edoCoche1 = 3;
		break;
	case 3:
		movX_coche1 += 5.0f;
		movZ_coche1 -= 3.63f * 5.0f;
		giroCoche1 = 164.6f;
		if (movX_coche1 >= 1100.0f && movZ_coche1 <= 140.0f)
			edoCoche1 = 4;
		break;
	case 4:
		movX_coche1 -= 5.0f;
		movZ_coche1 = 140.0f;
		giroCoche1 = 270.0f;
		if (movX_coche1 <= 560.0f)
			edoCoche1 = 5;
		break;
	case 5:
		movX_coche1 -= 5.0f;
		movZ_coche1 -= 2.69f * 5.0f;
		giroCoche1 = 200.4;
		if (movX_coche1 <= 415.0f && movZ_coche1 <= -250.0)
			edoCoche1 = 6;
		break;
	case 6:
		movX_coche1 -= 5.0f;
		movZ_coche1 += 0.6f * 5.0f;
		giroCoche1 = 301.1f;
		if (movX_coche1 <= 0.0f && movZ_coche1 >= 0.0f)
			edoCoche1 = 0;
		break;
	}

	if (abducir) {

		if (joseY >= 500) {
			dibujaJose = false;
			cambiaTrayectoriaNave = true;
		}
		else {
			lightPosition.x = joseX = 1500 + 200 * deltaRadio * cos(deltaJose * 90);
			lightPosition.z = joseZ = -800 + 200 * deltaRadio * sin(deltaJose * 90);
			lightPosition.y = 0.0f;
			joseY = 10 * deltaJose;
			deltaJose += 0.1;
			if (deltaRadio > 0) {
				deltaRadio -= 0.005;
			}
			else {
				deltaRadio = 0;
				if (rotarJose < 90.0) {
					rotarJose++;
				}

			}
		}
		if (cambiaTrayectoriaNave) {
			roamingY += deltaRoamingY;
			roamingZ -= (deltaRoamingZ * deltaRoamingZ) / 4;
			deltaRoamingZ += 0.1;
			deltaRoamingY = deltaRoamingZ;
		}

	}
	else {
		joseX = 1500.0;
		joseY = 0.0;
		joseZ = -800;
		dibujaJose = true;
		cambiaTrayectoriaNave = false;
		deltaJose = 0.0f;
		deltaRadio = 1.0f;
		roamingX = 1500,
			roamingZ = -800,
			roamingY = 500;
		rotarJose = 0.0f;
	}

	if (hacer_ritual) {
		if (ritualZ < anti_ritualZ) {
			rituales_escala += 0.2;
			ritualZ += 5;
			anti_ritualZ -= 5;
		}
		else {
			dibuja_ritual = false;
			dibuja_anti_ritual = false;
			dibuja_union_ritual = true;
			union_ritualX += 20;
		}
	}
	else {
		dibuja_ritual = true;
		dibuja_anti_ritual = true;
		dibuja_union_ritual = false;
		ritualZ = -800.0;
		anti_ritualZ = 200.0;
		rituales_escala = 2.0;
	}

	if (derretir_helado) {


		if (pos_gota >= -270.0f && helado_opt == 0) {
			pos_gota = pos_gota - 0.2;
			y_gota = y_gota + 0.02;
		}

		if (pos_gota <= -270.0f && helado_opt == 0) {
			y_gota = 3.5f;
			helado_opt = 1;
		}

		if (pos_gota >= -290.0f && helado_opt == 1) {
			pos_gota = pos_gota - 0.2;
		}

		if (pos_gota <= -290.0f && helado_opt == 1) {
			y_gota = 0.01;
			ancho_gota = 15.0f;
			existe_charco = true;
			cont_galleta++;
		}

		if (ancho_gota >= 15 && cont_galleta < 3) {
			ancho_galleta = ancho_galleta - 0.1;
			y_tapa = y_tapa - 3.0;
			relleno_y = relleno_y + 1.0f;
			helado_opt = 0;
			y_gota = 3.5f;
			pos_gota = -230.0f;
			ancho_gota = 3.5f;
			ancho_charco = ancho_charco + 2.0f;
		}


		if (cont_galleta >= 3) {
			helado_opt = 0;
			cont_galleta = 0;
			existe_charco = false;
			y_gota = 3.5f;
			pos_gota = -230.0f;
			ancho_gota = 3.5f;
			ancho_galleta = 0.7f;
			relleno_y = -200.0f;
			ancho_charco = 2.0f;
			y_tapa = -200.0f;
			derretir_helado = false;
		}
	}
}

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	//bool played = sndPlaySound("resources/music/soy_un_cometa.wav", SND_ASYNC);
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	// Elementos del escenario
	Model mar("resources/objects/mar/mar.obj");
	Model playa("resources/objects/playa/playa.obj");
	Model piso("resources/objects/piso/piso.obj");
	// Edificios
	Model house2("resources/objects/house2/house2.obj");
	Model house4("resources/objects/house4/house4.obj");
	Model faro("resources/objects/Lighthouse/lighthouse.obj");
	Model house3("resources/objects/House3/casaBlanca.obj");
	Model house5("resources/objects/house5/house5.obj");
	Model motel("resources/objects/motel/motel.obj");
	Model center("resources/objects/pokemoncenter/pokemoncenter.obj");
	Model house2_1("resources/objects/house2_1/house2_1.obj");
	Model house3_1("resources/objects/House3_1/casaRoja.obj");
	Model house3_2("resources/objects/House3_2/casaAzul.obj");
	Model house3_3("resources/objects/House3_3/casaVerde.obj");
	Model kiosko("resources/objects/kiosko/kiosko.obj");
	Model pool("resources/objects/pool/pool.obj");
	// Personajes
	Model bmo("resources/objects/bmo/bmo.obj");
	Model brazoBMO("resources/objects/bmo/limb.obj");
	Model cow("resources/objects/cow/cow.obj");
	// Vehículos
	Model cocheSteven("resources/objects/cocheSteven/cocheSteven.obj");
	Model cocheVoxel("resources/objects/cocheVoxel/cocheVoxel.obj");
	Model roaming_eye("resources/objects/roaming_eye/roaming_eye.obj");
	// Ritual Maldito
	Model ritual("resources/objects/ritual/ritual.obj");
	Model anti_ritual("resources/objects/anti-ritual/anti-ritual.obj");
	Model union_ritual("resources/objects/union-ritual/union-ritual.obj");
	//Cookie_Cat
	Model tapa_cat("resources/objects/gato_galleta/tapa/tapa.obj");
	Model base_cat("resources/objects/gato_galleta/base/base.obj");
	Model relleno_cat("resources/objects/gato_galleta/relleno/relleno.obj");
	Model gota_cat("resources/objects/gato_galleta/gota/gota.obj");
	Model charco_cat("resources/objects/gato_galleta/charco/charco.obj");
	//Ritual Nobara
	Model hammer("resources/objects/Hammer/Hammer.obj");
	Model nail("resources/objects/nail/nail.obj");
	Model nail2("resources/objects/nail/nail.obj");
	Model nail3("resources/objects/nail/nail.obj");
	Model voodoDoll("resources/objects/VoodooDoll/VoodooDoll.obj");

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		// Baile pregrabado
		KeyFrame[0].BMOposX = 65;
		KeyFrame[0].BMOposY = 45;
		KeyFrame[0].BMOposZ = -10;
		KeyFrame[0].rotBrazoIzq = 40;
		KeyFrame[0].rotBrazoDer = -47;
		KeyFrame[0].rotPiernaDer = -91;
		KeyFrame[0].rotPiernaIzq = -91;
		KeyFrame[0].giroBMO = 0;
		KeyFrame[1].BMOposX = 0;
		KeyFrame[1].BMOposY = 45;
		KeyFrame[1].BMOposZ = -35;
		KeyFrame[1].rotBrazoIzq = -35;
		KeyFrame[1].rotBrazoDer = -105;
		KeyFrame[1].rotPiernaDer = -44;
		KeyFrame[1].rotPiernaIzq = -91;
		KeyFrame[1].giroBMO = 58;
		KeyFrame[2].BMOposX = 0;
		KeyFrame[2].BMOposY = 45;
		KeyFrame[2].BMOposZ = -35;
		KeyFrame[2].rotBrazoIzq = -105;
		KeyFrame[2].rotBrazoDer = -105;
		KeyFrame[2].rotPiernaDer = -89;
		KeyFrame[2].rotPiernaIzq = -37;
		KeyFrame[2].giroBMO = 90;
		KeyFrame[3].BMOposX = -70;
		KeyFrame[3].BMOposY = 45;
		KeyFrame[3].BMOposZ = -25;
		KeyFrame[3].rotBrazoIzq = 87;
		KeyFrame[3].rotBrazoDer = 85;
		KeyFrame[3].rotPiernaDer = -89;
		KeyFrame[3].rotPiernaIzq = -91;
		KeyFrame[3].giroBMO = 13;
		KeyFrame[4].BMOposX = -70;
		KeyFrame[4].BMOposY = 0;
		KeyFrame[4].BMOposZ = -25;
		KeyFrame[4].rotBrazoIzq = 87;
		KeyFrame[4].rotBrazoDer = 84.9999;
		KeyFrame[4].rotPiernaDer = 0.999969;
		KeyFrame[4].rotPiernaIzq = 1;
		KeyFrame[4].giroBMO = 13;
		FrameIndex = 5;
	}

	KeyFrame2[0].voodooX = 2200;
	KeyFrame2[0].voodooY = -350;
	KeyFrame2[0].rotVodoo = 90;
	KeyFrame2[0].hammerX = 2132;
	KeyFrame2[0].hammerY = -350;
	KeyFrame2[0].rotHammer = 88;
	KeyFrame2[0].nailX = 2150;
	KeyFrame2[0].nailY = -348;
	KeyFrame2[0].nailZ = -2170;
	KeyFrame2[0].rotNail = 180;
	KeyFrame2[0].nail2X = 2150;
	KeyFrame2[0].nail2Y = -348;
	KeyFrame2[0].nail2Z = -2165;
	KeyFrame2[0].nail3X = 2150;
	KeyFrame2[0].nail3Y = -348;
	KeyFrame2[0].nail3Z = -2160;
	KeyFrame2[0].cambioGiroVoodoo = 0;
	KeyFrame2[1].voodooX = 2200;
	KeyFrame2[1].voodooY = -350;
	KeyFrame2[1].rotVodoo = 9;
	KeyFrame2[1].hammerX = 2132;
	KeyFrame2[1].hammerY = -326;
	KeyFrame2[1].rotHammer = -1;
	KeyFrame2[1].nailX = 2150;
	KeyFrame2[1].nailY = -348;
	KeyFrame2[1].nailZ = -2170;
	KeyFrame2[1].rotNail = 180;
	KeyFrame2[1].nail2X = 2150;
	KeyFrame2[1].nail2Y = -348;
	KeyFrame2[1].nail2Z = -2165;
	KeyFrame2[1].nail3X = 2150;
	KeyFrame2[1].nail3Y = -348;
	KeyFrame2[1].nail3Z = -2160;
	KeyFrame2[1].cambioGiroVoodoo = 0;
	KeyFrame2[2].voodooX = 2200;
	KeyFrame2[2].voodooY = -350;
	KeyFrame2[2].rotVodoo = -5;
	KeyFrame2[2].hammerX = 2132;
	KeyFrame2[2].hammerY = -326;
	KeyFrame2[2].rotHammer = -1;
	KeyFrame2[2].nailX = 2150;
	KeyFrame2[2].nailY = -348;
	KeyFrame2[2].nailZ = -2170;
	KeyFrame2[2].rotNail = 180;
	KeyFrame2[2].nail2X = 2150;
	KeyFrame2[2].nail2Y = -348;
	KeyFrame2[2].nail2Z = -2165;
	KeyFrame2[2].nail3X = 2150;
	KeyFrame2[2].nail3Y = -348;
	KeyFrame2[2].nail3Z = -2160;
	KeyFrame2[2].cambioGiroVoodoo = 1;
	KeyFrame2[3].voodooX = 2177;
	KeyFrame2[3].voodooY = -343;
	KeyFrame2[3].rotVodoo = -173;
	KeyFrame2[3].hammerX = 2132;
	KeyFrame2[3].hammerY = -326;
	KeyFrame2[3].rotHammer = -1;
	KeyFrame2[3].nailX = 2150;
	KeyFrame2[3].nailY = -348;
	KeyFrame2[3].nailZ = -2170;
	KeyFrame2[3].rotNail = 180;
	KeyFrame2[3].nail2X = 2150;
	KeyFrame2[3].nail2Y = -348;
	KeyFrame2[3].nail2Z = -2165;
	KeyFrame2[3].nail3X = 2150;
	KeyFrame2[3].nail3Y = -348;
	KeyFrame2[3].nail3Z = -2160;
	KeyFrame2[3].cambioGiroVoodoo = 1;
	KeyFrame2[4].voodooX = 2177;
	KeyFrame2[4].voodooY = -343;
	KeyFrame2[4].rotVodoo = -173;
	KeyFrame2[4].hammerX = 2132;
	KeyFrame2[4].hammerY = -326;
	KeyFrame2[4].rotHammer = -1.00001;
	KeyFrame2[4].nailX = 2150;
	KeyFrame2[4].nailY = -307;
	KeyFrame2[4].nailZ = -2170;
	KeyFrame2[4].rotNail = 180;
	KeyFrame2[4].nail2X = 2150;
	KeyFrame2[4].nail2Y = -307;
	KeyFrame2[4].nail2Z = -2165;
	KeyFrame2[4].nail3X = 2150;
	KeyFrame2[4].nail3Y = -307;
	KeyFrame2[4].nail3Z = -2160;
	KeyFrame2[4].cambioGiroVoodoo = 1;
	KeyFrame2[5].voodooX = 2177;
	KeyFrame2[5].voodooY = -343;
	KeyFrame2[5].rotVodoo = -173;
	KeyFrame2[5].hammerX = 2132;
	KeyFrame2[5].hammerY = -326;
	KeyFrame2[5].rotHammer = -1.00001;
	KeyFrame2[5].nailX = 2150;
	KeyFrame2[5].nailY = -304;
	KeyFrame2[5].nailZ = -2197;
	KeyFrame2[5].rotNail = 180;
	KeyFrame2[5].nail2X = 2150;
	KeyFrame2[5].nail2Y = -309;
	KeyFrame2[5].nail2Z = -2197;
	KeyFrame2[5].nail3X = 2150;
	KeyFrame2[5].nail3Y = -314;
	KeyFrame2[5].nail3Z = -2197;
	KeyFrame2[5].cambioGiroVoodoo = 1;
	KeyFrame2[6].voodooX = 2177;
	KeyFrame2[6].voodooY = -343;
	KeyFrame2[6].rotVodoo = -173;
	KeyFrame2[6].hammerX = 2132;
	KeyFrame2[6].hammerY = -326;
	KeyFrame2[6].rotHammer = 33;
	KeyFrame2[6].nailX = 2150;
	KeyFrame2[6].nailY = -304;
	KeyFrame2[6].nailZ = -2197;
	KeyFrame2[6].rotNail = 151;
	KeyFrame2[6].nail2X = 2150;
	KeyFrame2[6].nail2Y = -309;
	KeyFrame2[6].nail2Z = -2197;
	KeyFrame2[6].nail3X = 2150;
	KeyFrame2[6].nail3Y = -314;
	KeyFrame2[6].nail3Z = -2197;
	KeyFrame2[6].cambioGiroVoodoo = 1;
	KeyFrame2[7].voodooX = 2177;
	KeyFrame2[7].voodooY = -343;
	KeyFrame2[7].rotVodoo = -173;
	KeyFrame2[7].hammerX = 2137;
	KeyFrame2[7].hammerY = -323;
	KeyFrame2[7].rotHammer = -7.62939e-06;
	KeyFrame2[7].nailX = 2150;
	KeyFrame2[7].nailY = -304;
	KeyFrame2[7].nailZ = -2197;
	KeyFrame2[7].rotNail = 151;
	KeyFrame2[7].nail2X = 2150;
	KeyFrame2[7].nail2Y = -309;
	KeyFrame2[7].nail2Z = -2197;
	KeyFrame2[7].nail3X = 2150;
	KeyFrame2[7].nail3Y = -314;
	KeyFrame2[7].nail3Z = -2197;
	KeyFrame2[7].cambioGiroVoodoo = 1;
	KeyFrame2[8].voodooX = 2177;
	KeyFrame2[8].voodooY = -343;
	KeyFrame2[8].rotVodoo = -173;
	KeyFrame2[8].hammerX = 2137;
	KeyFrame2[8].hammerY = -323;
	KeyFrame2[8].rotHammer = -18;
	KeyFrame2[8].nailX = 2168;
	KeyFrame2[8].nailY = -311;
	KeyFrame2[8].nailZ = -2197;
	KeyFrame2[8].rotNail = 151;
	KeyFrame2[8].nail2X = 2150;
	KeyFrame2[8].nail2Y = -309;
	KeyFrame2[8].nail2Z = -2197;
	KeyFrame2[8].nail3X = 2150;
	KeyFrame2[8].nail3Y = -314;
	KeyFrame2[8].nail3Z = -2197;
	KeyFrame2[8].cambioGiroVoodoo = 1;
	KeyFrame2[9].voodooX = 2177;
	KeyFrame2[9].voodooY = -343;
	KeyFrame2[9].rotVodoo = -174;
	KeyFrame2[9].hammerX = 2133;
	KeyFrame2[9].hammerY = -323;
	KeyFrame2[9].rotHammer = 35;
	KeyFrame2[9].nailX = 2168;
	KeyFrame2[9].nailY = -311;
	KeyFrame2[9].nailZ = -2197;
	KeyFrame2[9].rotNail = 149;
	KeyFrame2[9].nail2X = 2150;
	KeyFrame2[9].nail2Y = -309;
	KeyFrame2[9].nail2Z = -2197;
	KeyFrame2[9].nail3X = 2150;
	KeyFrame2[9].nail3Y = -314;
	KeyFrame2[9].nail3Z = -2197;
	KeyFrame2[9].cambioGiroVoodoo = 1;
	KeyFrame2[10].voodooX = 2177;
	KeyFrame2[10].voodooY = -343;
	KeyFrame2[10].rotVodoo = -173;
	KeyFrame2[10].hammerX = 2128;
	KeyFrame2[10].hammerY = -323;
	KeyFrame2[10].rotHammer = -27;
	KeyFrame2[10].nailX = 2168;
	KeyFrame2[10].nailY = -311;
	KeyFrame2[10].nailZ = -2197;
	KeyFrame2[10].rotNail = 149;
	KeyFrame2[10].nail2X = 2150;
	KeyFrame2[10].nail2Y = -309;
	KeyFrame2[10].nail2Z = -2197;
	KeyFrame2[10].nail3X = 2150;
	KeyFrame2[10].nail3Y = -314;
	KeyFrame2[10].nail3Z = -2197;
	KeyFrame2[10].cambioGiroVoodoo = 1;
	KeyFrame2[11].voodooX = 2177;
	KeyFrame2[11].voodooY = -343;
	KeyFrame2[11].rotVodoo = -173;
	KeyFrame2[11].hammerX = 2128;
	KeyFrame2[11].hammerY = -323;
	KeyFrame2[11].rotHammer = -33;
	KeyFrame2[11].nailX = 2168;
	KeyFrame2[11].nailY = -311;
	KeyFrame2[11].nailZ = -2197;
	KeyFrame2[11].rotNail = 149;
	KeyFrame2[11].nail2X = 2168;
	KeyFrame2[11].nail2Y = -314;
	KeyFrame2[11].nail2Z = -2197;
	KeyFrame2[11].nail3X = 2150;
	KeyFrame2[11].nail3Y = -314;
	KeyFrame2[11].nail3Z = -2197;
	KeyFrame2[11].cambioGiroVoodoo = 1;
	KeyFrame2[12].voodooX = 2177;
	KeyFrame2[12].voodooY = -343;
	KeyFrame2[12].rotVodoo = -173;
	KeyFrame2[12].hammerX = 2128;
	KeyFrame2[12].hammerY = -323;
	KeyFrame2[12].rotHammer = 42;
	KeyFrame2[12].nailX = 2168;
	KeyFrame2[12].nailY = -311;
	KeyFrame2[12].nailZ = -2197;
	KeyFrame2[12].rotNail = 147;
	KeyFrame2[12].nail2X = 2168;
	KeyFrame2[12].nail2Y = -314;
	KeyFrame2[12].nail2Z = -2197;
	KeyFrame2[12].nail3X = 2150;
	KeyFrame2[12].nail3Y = -314;
	KeyFrame2[12].nail3Z = -2197;
	KeyFrame2[12].cambioGiroVoodoo = 1;
	KeyFrame2[13].voodooX = 2177;
	KeyFrame2[13].voodooY = -343;
	KeyFrame2[13].rotVodoo = -173;
	KeyFrame2[13].hammerX = 2126;
	KeyFrame2[13].hammerY = -323;
	KeyFrame2[13].rotHammer = -38;
	KeyFrame2[13].nailX = 2168;
	KeyFrame2[13].nailY = -311;
	KeyFrame2[13].nailZ = -2197;
	KeyFrame2[13].rotNail = 147;
	KeyFrame2[13].nail2X = 2168;
	KeyFrame2[13].nail2Y = -314;
	KeyFrame2[13].nail2Z = -2197;
	KeyFrame2[13].nail3X = 2150;
	KeyFrame2[13].nail3Y = -314;
	KeyFrame2[13].nail3Z = -2197;
	KeyFrame2[13].cambioGiroVoodoo = 1;
	KeyFrame2[14].voodooX = 2177;
	KeyFrame2[14].voodooY = -343;
	KeyFrame2[14].rotVodoo = -173;
	KeyFrame2[14].hammerX = 2126;
	KeyFrame2[14].hammerY = -323;
	KeyFrame2[14].rotHammer = -44;
	KeyFrame2[14].nailX = 2168;
	KeyFrame2[14].nailY = -311;
	KeyFrame2[14].nailZ = -2197;
	KeyFrame2[14].rotNail = 147;
	KeyFrame2[14].nail2X = 2168;
	KeyFrame2[14].nail2Y = -314;
	KeyFrame2[14].nail2Z = -2197;
	KeyFrame2[14].nail3X = 2168;
	KeyFrame2[14].nail3Y = -317;
	KeyFrame2[14].nail3Z = -2197;
	KeyFrame2[14].cambioGiroVoodoo = 1;
	KeyFrame2[15].voodooX = 2177;
	KeyFrame2[15].voodooY = -343;
	KeyFrame2[15].rotVodoo = -173;
	KeyFrame2[15].hammerX = 2126;
	KeyFrame2[15].hammerY = -323;
	KeyFrame2[15].rotHammer = -44;
	KeyFrame2[15].nailX = 2168;
	KeyFrame2[15].nailY = -311;
	KeyFrame2[15].nailZ = -2197;
	KeyFrame2[15].rotNail = 147;
	KeyFrame2[15].nail2X = 2168;
	KeyFrame2[15].nail2Y = -314;
	KeyFrame2[15].nail2Z = -2197;
	KeyFrame2[15].nail3X = 2168;
	KeyFrame2[15].nail3Y = -317;
	KeyFrame2[15].nail3Z = -2197;
	KeyFrame2[15].cambioGiroVoodoo = 1;
	KeyFrame2[16].voodooX = 2177;
	KeyFrame2[16].voodooY = -343;
	KeyFrame2[16].rotVodoo = -173;
	KeyFrame2[16].hammerX = 2126;
	KeyFrame2[16].hammerY = -323;
	KeyFrame2[16].rotHammer = -44;
	KeyFrame2[16].nailX = 2168;
	KeyFrame2[16].nailY = -311;
	KeyFrame2[16].nailZ = -2197;
	KeyFrame2[16].rotNail = 147;
	KeyFrame2[16].nail2X = 2168;
	KeyFrame2[16].nail2Y = -314;
	KeyFrame2[16].nail2Z = -2197;
	KeyFrame2[16].nail3X = 2168;
	KeyFrame2[16].nail3Y = -317;
	KeyFrame2[16].nail3Z = -2197;
	KeyFrame2[16].cambioGiroVoodoo = 1;

	Frame2Index = 16;

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		if (ritualVoodoo) {
			staticShader.setVec3("dirLight.ambient", glm::vec3(.2f, 0.2f, 0.2f));
		}
		else {
			staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		}
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		if (dibujaJose && abducir) {
			staticShader.setVec3("pointLight[0].ambient", glm::vec3(1.f, 1.f, 0.0f));
			staticShader.setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
		}
		else {
			staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
			staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		}
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.8f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.000032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("pointLight[2].position", glm::vec3(voodooX, voodooY, -2200.0));
		if (ritualVoodoo) {
			staticShader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.169f));
			staticShader.setVec3("pointLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.169f));
		}
		else {
			staticShader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
			staticShader.setVec3("pointLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		}
		staticShader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[2].constant", 1.0f);
		staticShader.setFloat("pointLight[2].linear", 0.0009f);
		staticShader.setFloat("pointLight[2].quadratic", 0.0032f);

		staticShader.setVec3("pointLight[3].position", glm::vec3(hammerX, hammerY, hammerZ));
		if (ritualVoodoo) {
			staticShader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.545f));
			staticShader.setVec3("pointLight[3].diffuse", glm::vec3(0.0f, 0.0f, 0.545f));
		}
		else {
			staticShader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
			staticShader.setVec3("pointLight[3].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		}
		staticShader.setVec3("pointLight[3].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[3].constant", 1.0f);
		staticShader.setFloat("pointLight[3].linear", 0.0009f);
		staticShader.setFloat("pointLight[3].quadratic", 0.0032f);

		staticShader.setVec3("pointLight[4].position", glm::vec3(nailX, nailY, nailZ));
		if (ritualVoodoo) {
			staticShader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.545f));
			staticShader.setVec3("pointLight[4].diffuse", glm::vec3(0.0f, 0.0f, 0.545f));
		}
		else {
			staticShader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
			staticShader.setVec3("pointLight[4].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		}
		staticShader.setVec3("pointLight[4].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[4].constant", 1.0f);
		staticShader.setFloat("pointLight[4].linear", 0.9f);
		staticShader.setFloat("pointLight[4].quadratic", 0.032f);

		staticShader.setVec3("pointLight[5].position", glm::vec3(nail2X, nail2Y, nail2Z));
		if (ritualVoodoo) {
			staticShader.setVec3("pointLight[5].ambient", glm::vec3(0.0f, 0.0f, 0.545f));
			staticShader.setVec3("pointLight[5].diffuse", glm::vec3(0.0f, 0.0f, 0.545f));
		}
		else {
			staticShader.setVec3("pointLight[5].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
			staticShader.setVec3("pointLight[5].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		}
		staticShader.setVec3("pointLight[5].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[5].constant", 1.0f);
		staticShader.setFloat("pointLight[5].linear", 0.9f);
		staticShader.setFloat("pointLight[5].quadratic", 0.032f);

		staticShader.setVec3("pointLight[6].position", glm::vec3(nail3X, nail3Y, nail3Z));
		if (ritualVoodoo) {
			staticShader.setVec3("pointLight[6].ambient", glm::vec3(0.0f, 0.0f, 0.545f));
			staticShader.setVec3("pointLight[6].diffuse", glm::vec3(0.0f, 0.0f, 0.545f));
		}
		else {
			staticShader.setVec3("pointLight[6].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
			staticShader.setVec3("pointLight[6].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		}
		staticShader.setVec3("pointLight[6].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[6].constant", 1.0f);
		staticShader.setFloat("pointLight[6].linear", 0.9f);
		staticShader.setFloat("pointLight[6].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		/*model = glm::translate(glm::mat4(1.0f), glm::vec3(890.0f, -2.5f, 400.0f));
		model = glm::scale(model, glm::vec3(1.2f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		maldicion.Draw(animShader);*/

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2500.0f, -1550.0f, 2500.0f));
		model = glm::scale(model, glm::vec3(500.0f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);

		// Coloca las casas
		float p = 0;
		float r = 0;
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 4; i++) {

				if (i % 2 == 0) {
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(-1800.0f + p, 3.0f, 1550.0f + r));
					model = glm::scale(model, glm::vec3(35.0f));
					model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					staticShader.setMat4("model", model);
					house2.Draw(staticShader);
				}
				else {
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(-1800.0f + p, 3.0f, 1550.0f + r));
					model = glm::scale(model, glm::vec3(35.0f));
					model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					staticShader.setMat4("model", model);
					house2_1.Draw(staticShader);
				}


				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(-1900.0f + p, 0.0f, 1250.0f + r));
				model = glm::scale(model, glm::vec3(15.0f));
				model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				staticShader.setMat4("model", model);
				house4.Draw(staticShader);

				switch (i)
				{
				case 0:
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(-1850.0f + p, 0.0f, 1050.0f + r));
					model = glm::scale(model, glm::vec3(1.5f));
					model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					staticShader.setMat4("model", model);
					house3.Draw(staticShader);
					break;
				case 1:
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(-1850.0f + p, 0.0f, 1050.0f + r));
					model = glm::scale(model, glm::vec3(1.5f));
					model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					staticShader.setMat4("model", model);
					house3_1.Draw(staticShader);
					break;
				case 2:
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(-1850.0f + p, 0.0f, 1050.0f + r));
					model = glm::scale(model, glm::vec3(1.5f));
					model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					staticShader.setMat4("model", model);
					house3_2.Draw(staticShader);
					break;
				case 3:
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(-1850.0f + p, 0.0f, 1050.0f + r));
					model = glm::scale(model, glm::vec3(1.5f));
					model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					staticShader.setMat4("model", model);
					house3_3.Draw(staticShader);
					break;
				default:
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(-1850.0f + p, 0.0f, 1050.0f + r));
					model = glm::scale(model, glm::vec3(1.5f));
					model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					staticShader.setMat4("model", model);
					house3.Draw(staticShader);
					break;
				}
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(-1850.0f + p, 0.0f, 1050.0f + r));
				model = glm::scale(model, glm::vec3(1.5f));
				model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				staticShader.setMat4("model", model);
				house3.Draw(staticShader);

				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(-1850.0f + p, 3.0f, 750.0f + r));
				model = glm::scale(model, glm::vec3(1.5f));
				staticShader.setMat4("model", model);
				house5.Draw(staticShader);

				p = p + 500.0;
			}
			p = 0.0;
			r = r - 1200.0;
		}

		// Motel
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-500.0f, 6.0f, -2000.0f));
		model = glm::scale(model, glm::vec3(0.7f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		motel.Draw(staticShader);

		// Centro Pokemón 1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(200.0f, 90.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 20.0f, 50.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		center.Draw(staticShader);

		// Centro Pokemón 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(800.0f, 90.0f, -2000.0f));
		model = glm::scale(model, glm::vec3(50.0f, 20.0f, 30.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		center.Draw(staticShader);

		// Motel 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(800.0f, 6.0f, 1500.0f));
		model = glm::scale(model, glm::vec3(0.8f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		motel.Draw(staticShader);

		// Kiosko
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(550.0f, 410.0f, 800.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		kiosko.Draw(staticShader);

		// Alberca
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(400.0f, -500.0f, -700.0f));
		model = glm::scale(model, glm::vec3(15.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		pool.Draw(staticShader);

		// Vaca
		if (dibujaJose) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(joseX, joseY, joseZ));
			model = glm::scale(model, glm::vec3(0.4f));
			model = glm::rotate(model, glm::radians(rotarJose), glm::vec3(0.0f, 0.0f, 1.0f));
			staticShader.setMat4("model", model);
			cow.Draw(staticShader);
		}

		// Nave
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(roamingX, roamingY, roamingZ));
		model = glm::scale(model, glm::vec3(80.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		roaming_eye.Draw(staticShader);

		// Ritual
		if (dibuja_ritual) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(2000, -100, ritualZ));
			model = glm::scale(model, glm::vec3(rituales_escala * 7 / 8));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			staticShader.setMat4("model", model);
			ritual.Draw(staticShader);
		}

		// Antiritual
		if (dibuja_anti_ritual) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(2000, -100, anti_ritualZ));
			model = glm::scale(model, glm::vec3(rituales_escala));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			staticShader.setMat4("model", model);
			anti_ritual.Draw(staticShader);
		}

		// Unión ritual
		if (dibuja_union_ritual) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(union_ritualX, -100, -300));
			model = glm::scale(model, glm::vec3(rituales_escala));
			//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			staticShader.setMat4("model", model);
			union_ritual.Draw(staticShader);
		}

		//Animacion Galleta
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3000.0f, -200.0f, -300.0f));
		model = glm::scale(model, glm::vec3(0.7));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		base_cat.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3000.0f, relleno_y, -300.0f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.7f, ancho_galleta, 0.7f));
		staticShader.setMat4("model", model);
		relleno_cat.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3000.0f, y_tapa, -300.0f));
		model = glm::scale(model, glm::vec3(0.7));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		tapa_cat.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2890.0f, pos_gota, -300.0f));
		model = glm::scale(model, glm::vec3(ancho_gota, y_gota, ancho_gota));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		gota_cat.Draw(staticShader);

		if (existe_charco) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(2910.0f, -285.0f, -290.0f));
			model = glm::scale(model, glm::vec3(ancho_charco, 1.0f, ancho_charco));
			staticShader.setMat4("model", model);
			charco_cat.Draw(staticShader);
		}

		//Ritual Nobara
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(voodooX, voodooY, -2200.0f));
		model = glm::scale(model, glm::vec3(.1f));
		if (cambioGiroVoodoo)
			model = glm::rotate(model, glm::radians(rotVodoo), glm::vec3(0.0f, 1.0f, 0.0f));
		else
			model = glm::rotate(model, glm::radians(rotVodoo), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		voodoDoll.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(hammerX, hammerY, hammerZ));
		model = glm::scale(model, glm::vec3(3.f));
		model = glm::rotate(model, glm::radians(rotHammer), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		hammer.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(nailX, nailY, nailZ));
		model = glm::scale(model, glm::vec3(3.f));
		model = glm::rotate(model, glm::radians(rotNail), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		nail.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(nail2X, nail2Y, nail2Z));
		model = glm::scale(model, glm::vec3(3.f));
		model = glm::rotate(model, glm::radians(rotNail), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		nail2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(nail3X, nail3Y, nail3Z));
		model = glm::scale(model, glm::vec3(3.f));
		model = glm::rotate(model, glm::radians(rotNail), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		nail3.Draw(staticShader);

		// Faro
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1600.0f, 100.0f, -2200.0f));
		model = glm::scale(model, glm::vec3(12.0f));
		staticShader.setMat4("model", model);
		faro.Draw(staticShader);

		// Coche Steven
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1585.0f + movX_coche1, 0.0f, -1665.0f + movZ_coche1));
		model = glm::rotate(model, glm::radians(giroCoche1), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::scale(model, glm::vec3(20.0f));
		staticShader.setMat4("model", model);
		cocheSteven.Draw(staticShader);

		// Coche Voxel
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(movX_coche2, 20.0f, movZ_coche2));
		model = glm::rotate(model, glm::radians(giroCoche2), glm::vec3(0.0f, 1.0f, 0.0f));
		//tmp = model = glm::scale(model, glm::vec3(20.0f));
		staticShader.setMat4("model", model);
		cocheVoxel.Draw(staticShader);

		// BMO
		// Cuerpo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(775 + BMOposX, 31.5 + BMOposY, 25 + BMOposZ));
		tmp = model = glm::rotate(model, glm::radians(giroBMO), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		bmo.Draw(staticShader);
		// Pierna Izq
		model = glm::translate(tmp, glm::vec3(8.0f, -27.5f, -2.0f));
		model = glm::rotate(model, glm::radians(rotPiernaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, -2.0f, -13.0f));
		staticShader.setMat4("model", model);
		brazoBMO.Draw(staticShader);
		// Pierna Der
		model = glm::translate(tmp, glm::vec3(-8.0f, -27.5f, -2.0f));
		model = glm::rotate(model, glm::radians(rotPiernaDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.0f, -2.0f, -13.0f));
		staticShader.setMat4("model", model);
		brazoBMO.Draw(staticShader);
		// Brazo Izq
		model = glm::translate(tmp, glm::vec3(20.0f, -18.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotBrazoIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, -2.0f, -15.0f));
		staticShader.setMat4("model", model);
		brazoBMO.Draw(staticShader);
		// Brazo Der
		model = glm::translate(tmp, glm::vec3(-20.0f, -18.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotBrazoDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.0f, -2.0f, -15.0f));
		staticShader.setMat4("model", model);
		brazoBMO.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime + 50);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime + 50);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime + 50);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime + 50);
	//Cambios Voodoo
	if (glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS)
		voodooX ++;
	if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
		voodooX --;
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
		voodooY --;
	if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
		voodooY ++;
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		cambioGiroVoodoo ^= true;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		rotVodoo--;
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
		rotVodoo++;

	//Cambios Martilo
	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
		hammerX++;
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
		hammerX--;
	if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
		hammerY++;
	if (glfwGetKey(window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS)
		hammerY--;
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
		rotHammer++;
	if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
		rotHammer--;

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		nailX--;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		nailX++;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		nailY++;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		nailY--;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		nailZ++;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		nailZ--;
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		rotNail++;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		rotNail--;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		nail2X--;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		nail2X++;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		nail2Y++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		nail2Y--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		nail2Z++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		nail2Z--;
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		nail3X--;
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		nail3X++;
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
		nail3Y++;
	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
		nail3Y--;
	if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
		nail3Z++;
	if (glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS)
		nail3Z--;

	if (glfwGetKey(window, GLFW_KEY_F10) == GLFW_PRESS)
		resetElements2();

	// Activa recorrido coche Steven
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS && edoCoche1 == 0)
		edoCoche1 = 1;

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	if (key == GLFW_KEY_X && action == GLFW_PRESS)
		abducir ^= true;
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		hacer_ritual ^= true;

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		derretir_helado ^= true;

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play2 == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play2 = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play2 = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To play KeyFrame animation 
	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		if (play2 == false && (Frame2Index > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements2();
			//First Interpolation				
			interpolation2();

			play2 = true;
			playIndex2 = 0;
			i_curr_steps2 = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (Frame2Index < MAX_FRAMES)
		{
			saveFrame();
		}
	}

	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		if (Frame2Index < MAX_FRAMES)
		{
			saveFrame2();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}