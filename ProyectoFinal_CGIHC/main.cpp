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
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
orienta = 0.0f,
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

//Variables de modificacion helado
float y_gota = 3.5f;
float pos_gota = -230.0f;
float ancho_gota = 3.5f;
float ancho_galleta = 0.7f;
float relleno_y = -200.0f;
float ancho_charco = 2.0f;
float y_tapa = -200.0f;

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

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	cout << "Frame Index = " << FrameIndex << endl;
	cout << "KeyFrame[" << FrameIndex << "].BMOposX = " << BMOposX << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].BMOposY = " << BMOposY << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].BMOposZ = " << BMOposZ << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotBrazoIzq = " << rotBrazoIzq << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotBrazoDer = " << rotBrazoDer << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotPiernaDer = " << rotPiernaDer << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].rotPiernaIzq = " << rotPiernaIzq << ";" << endl;
	cout << "KeyFrame[" << FrameIndex << "].giroBMO = " << giroBMO << ";" << endl;


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

	//Vehículo
	if (animacion)
	{
		movAuto_z += 3.0f;
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
	bool played = sndPlaySound("resources/music/soy_un_cometa.wav", SND_ASYNC);
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

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
	Model roaming_eye("resources/objects/roaming_eye/roaming_eye.obj");
	// Ritual Maldito
	Model ritual("resources/objects/ritual/ritual.obj");
	Model anti_ritual("resources/objects/anti-ritual/anti-ritual.obj");
	Model union_ritual("resources/objects/union-ritual/union-ritual.obj");
	Model tapa_cat("resources/objects/gato_galleta/tapa/tapa.obj");
	Model base_cat("resources/objects/gato_galleta/base/base.obj");
	Model relleno_cat("resources/objects/gato_galleta/relleno/relleno.obj");
	Model gota_cat("resources/objects/gato_galleta/gota/gota.obj");
	Model charco_cat("resources/objects/gato_galleta/charco/charco.obj");
	//Model piernaDer("resources/objects/Personaje/piernader.obj");
	//Model piernaIzq("resources/objects/Personaje/piernader.obj");
	//Model torso("resources/objects/Personaje/torso.obj");
	//Model brazoDer("resources/objects/Personaje/brazoder.obj");
	//Model brazoIzq("resources/objects/Personaje/brazoizq.obj");
	//Model cabeza("resources/objects/Personaje/cabeza.obj");
	//Model carro("resources/objects/lambo/carroceria.obj");
	//Model llanta("resources/objects/lambo/Wheel.obj");
	//Model casaVieja("resources/objects/casa/OldHouse.obj");
	////Model cubo("resources/objects/cubo/cube02.obj");
	//Model casaDoll("resources/objects/casa/DollHouse.obj");

	//ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	//animacionPersonaje.initShaders(animShader.ID);

	//ModelAnim ninja("resources/objects/ZombieWalk/ZombieWalk.dae");
	//ninja.initShaders(animShader.ID);

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
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
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

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(1.2f));	// it's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//animShader.setMat4("model", model);
		//animacionPersonaje.Draw(animShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Segundo Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//animShader.setMat4("model", model);
		//ninja.Draw(animShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		/*model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 0.0f, -10.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		casaDoll.Draw(staticShader);*/


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
			model = glm::scale(model, glm::vec3(rituales_escala));
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

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3000.0f, -200.0f, -300.0f));
		model = glm::scale(model, glm::vec3(0.7));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		base_cat.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3000.0f, relleno_y, -300.0f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.7f,ancho_galleta,0.7f));
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
		model = glm::scale(model, glm::vec3(ancho_gota,y_gota,ancho_gota));
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
	
		

		/*
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1800.0f, 0.5f, 1550.0f));
		model = glm::scale(model, glm::vec3(35.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		house2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1900.0f, 0.0f, 1250.0f));
		model = glm::scale(model, glm::vec3(15.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		house4.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1850.0f, 0.0f, 1050.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		house3.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1850.0f, 1.5f, 750.0f));
		model = glm::scale(model, glm::vec3(0.015f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		house5.Draw(staticShader);*/


		// Faro
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1600.0f, 100.0f, -2200.0f));
		model = glm::scale(model, glm::vec3(12.0f));
		staticShader.setMat4("model", model);
		faro.Draw(staticShader);

		// BMO
		// Cuerpo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(775 + BMOposX, 31.5 + BMOposY, 25 + BMOposZ));
		tmp = model = glm::rotate(model, glm::radians(giroBMO), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
<<<<<<< HEAD
		casaVieja.Draw(staticShader);*/

		// -------------------------------------------------------------------------------------------------------------------------
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------
		//model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(15.0f + movAuto_x, -1.0f, movAuto_z));
		//tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//staticShader.setMat4("model", model);
		//carro.Draw(staticShader);

		//model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, 12.9f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Izq delantera

		//model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, 12.9f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Der delantera

		//model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, -14.5f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Der trasera

		//model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, -14.5f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Izq trase
		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje
		// -------------------------------------------------------------------------------------------------------------------------
		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//tmp = model = glm::rotate(model, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0));
		//staticShader.setMat4("model", model);
		//torso.Draw(staticShader);

		////Pierna Der
		//model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		//staticShader.setMat4("model", model);
		//piernaDer.Draw(staticShader);

		////Pie Der
		//model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		//staticShader.setMat4("model", model);
		//botaDer.Draw(staticShader);

		////Pierna Izq
		//model = glm::translate(tmp, glm::vec3(0.5f, 0.0f, -0.1f));
		//
		// model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//staticShader.setMat4("model", model);
		//piernaIzq.Draw(staticShader);

		////Pie Iz
		//model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		//staticShader.setMat4("model", model);
		//botaDer.Draw(staticShader);	//Izq trase

		////Brazo derecho
		//model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(-0.75f, 2.5f, 0));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//staticShader.setMat4("model", model);
		//brazoDer.Draw(staticShader);

		////Brazo izquierdo
		//model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.75f, 2.5f, 0));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//staticShader.setMat4("model", model);
		//brazoIzq.Draw(staticShader);

		////Cabeza
		//model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0));
		//staticShader.setMat4("model", model);
		//cabeza.Draw(staticShader);
		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente --- Siguiente Práctica
		// -------------------------------------------------------------------------------------------------------------------------
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
=======
		bmo.Draw(staticShader);
		// Pierna Izq
		model = glm::translate(tmp, glm::vec3(8.0f, -27.5f, -2.0f));
		model = glm::rotate(model, glm::radians(rotPiernaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, -2.0f, -13.0f));
>>>>>>> 427769236d10c4a4cec8a3d1ed460a61c7655f92
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

		// Limitar el framerate a 603
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
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS)
		BMOposZ += 5.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
		BMOposZ -= 5.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
		BMOposX -= 5.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
		BMOposX += 5.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		BMOposY += 5.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		BMOposY -= 5.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
		rotBrazoIzq--;
	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
		rotBrazoIzq++;
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
		rotBrazoDer--;
	if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
		rotBrazoDer++;
	if (glfwGetKey(window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS && rotPiernaDer >= -90)
		rotPiernaDer--;
	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS && rotPiernaDer <= 0)
		rotPiernaDer++;
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS && rotPiernaIzq >= -90)
		rotPiernaIzq--;
	if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS && rotPiernaIzq <= 0)
		rotPiernaIzq++;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		giroBMO--;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		giroBMO++;


	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		abducir ^= true;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		hacer_ritual ^= true;

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		derretir_helado ^= true;


	

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
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
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
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