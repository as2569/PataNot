#include <glm/glm.hpp>  
#include <iostream>
#include <fstream>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp> 
#include <SDL.h>
#include <SDL_mixer.h>
#include <SOIL.h>
#include <time.h>

#include "Leap.h"
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "sprite.h"
#include "entity.h"
#include "gameFunctions.h"
#include "scoring.h"
#include "interface.h"

GameFunctions gamefunctions;
GLuint vbo;
GLuint uvs;
GLuint tex;
GLuint bar;
GLuint baruvs;
GLuint barTex;
GLuint digitTex;
GLuint digit;
GLuint digituvs;

glm::mat4 VP;
Leap::Vector leapVec;

glm::mat4 barPosition;
int bpm = 25;
int fb = 5;

Leap::Controller controller;
Leap::Listener listener;
Leap::FingerList extended;
extern float delta;

//class SampleListener : public Listener {
//  public:
//    virtual void onInit(const Controller&);
//    virtual void onConnect(const Controller&);
//    virtual void onDisconnect(const Controller&);
//    virtual void onExit(const Controller&);
//    virtual void onFrame(const Controller&);
//    virtual void onFocusGained(const Controller&);
//    virtual void onFocusLost(const Controller&);
//    virtual void onDeviceChange(const Controller&);
//    virtual void onServiceConnect(const Controller&);
//    virtual void onServiceDisconnect(const Controller&);
//    virtual void onServiceChange(const Controller&);
//    virtual void onDeviceFailure(const Controller&);
//    virtual void onLogMessage(const Controller&, MessageSeverity severity, int64_t timestamp, const char* msg);
//};
//
//const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
//const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
//
//void SampleListener::onInit(const Controller& controller) {
//  std::cout << "Initialized" << std::endl;
//}
//
//void SampleListener::onConnect(const Controller& controller) {
//  std::cout << "Connected" << std::endl;
//}
//
//void SampleListener::onDisconnect(const Controller& controller) {
//  // Note: not dispatched when running in a debugger.
//  std::cout << "Disconnected" << std::endl;
//}
//
//void SampleListener::onExit(const Controller& controller) {
//  std::cout << "Exited" << std::endl;
//}
//
//void SampleListener::onFrame(const Controller& controller) {
//	//Get the most recent frame and report some basic information
//	const Frame frame = controller.frame();
//
//	HandList hands = frame.hands();
//
//	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl)\
//	{
//		// Get the first hand	
//		const Hand hand = *hl;
//		std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
//
//		// Get the hand's normal vector and direction
//		const Vector normal = hand.palmNormal();
//		const Vector direction = hand.direction();
//    }
//  }
//
//void SampleListener::onFocusGained(const Controller& controller) {
//  std::cout << "Focus Gained" << std::endl;
//}
//
//void SampleListener::onFocusLost(const Controller& controller) {
//  std::cout << "Focus Lost" << std::endl;
//}
//
//void SampleListener::onDeviceChange(const Controller& controller) {
//  std::cout << "Device Changed" << std::endl;
//  const DeviceList devices = controller.devices();
//
//  for (int i = 0; i < devices.count(); ++i) {
//    std::cout << "id: " << devices[i].toString() << std::endl;
//    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
//    std::cout << "  isSmudged:" << (devices[i].isSmudged() ? "true" : "false") << std::endl;
//    std::cout << "  isLightingBad:" << (devices[i].isLightingBad() ? "true" : "false") << std::endl;
//  }
//}
//
//void SampleListener::onServiceConnect(const Controller& controller) {
//  std::cout << "Service Connected" << std::endl;
//}
//
//void SampleListener::onServiceDisconnect(const Controller& controller) {
//  std::cout << "Service Disconnected" << std::endl;
//}
//
//void SampleListener::onServiceChange(const Controller& controller) {
//  std::cout << "Service Changed" << std::endl;
//}
//
//void SampleListener::onDeviceFailure(const Controller& controller) {
//  std::cout << "Device Error" << std::endl;
//  const Leap::FailedDeviceList devices = controller.failedDevices();
//
//  for (FailedDeviceList::const_iterator dl = devices.begin(); dl != devices.end(); ++dl) {
//    const FailedDevice device = *dl;
//    std::cout << "  PNP ID:" << device.pnpId();
//    std::cout << "    Failure type:" << device.failure();
//  }
//}
//
//void SampleListener::onLogMessage(const Controller&, MessageSeverity s, int64_t t, const char* msg) {
//  switch (s) {
//  case Leap::MESSAGE_CRITICAL:
//    std::cout << "[Critical]";
//    break;
//  case Leap::MESSAGE_WARNING:
//    std::cout << "[Warning]";
//    break;
//  case Leap::MESSAGE_INFORMATION:
//    std::cout << "[Info]";
//    break;
//  case Leap::MESSAGE_UNKNOWN:
//    std::cout << "[Unknown]";
//  }
//  std::cout << "[" << t << "] ";
//  std::cout << msg << std::endl;
//}

int main(int argc, char *argv[])
{	
	char bGameLoopRunning = 1;
    //GLuint vao;
   // GLuint triangleBufferObject;
	SDL_Event evn;
	int64_t frameID;
	int64_t lastFrame = controller.frame().timestamp();

	barPosition = glm::mat4(1.0f);

	controller.addListener(listener); //Have the sample listener receive events from the controller

    init_logger("gametest3d.log");

    if (graphics3d_init(1024,1024,1,"gametest3d",33) != 0)
    {
        return -1;
    }

	//GLfloat 
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvs);
	glGenBuffers(1, &bar);
	glGenBuffers(1, &baruvs);

    slog("glError: %d", glGetError());
    
	lastFrame = controller.frame().timestamp();

	SDL_Init(SDL_INIT_EVERYTHING);
	
	if( Mix_OpenAudio( 32075, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        std::cout << "AudioFail" << std::endl;    
    }

	Mix_Init(MIX_INIT_MP3);
	gamefunctions.loadSong();
	Entity::reserve();
	srand(time(NULL));
	
	/*Sprite bar = Sprite();
	bar.setupBar();
	barPosition = glm::translate(barPosition, glm::vec3(0.0f, 0.0f, 0.0f));*/

    while (bGameLoopRunning)
    {
		//Get hand position
		using namespace Leap;
		const Frame frame = controller.frame();
		HandList hands = frame.hands();
		leapVec = hands.leftmost().palmNormal();
		//for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) //Not sure how iterator works
		//{
		//	const Hand hand = *hl;
		//	//std::string handType = hand.isLeft() ? "Left" : "Right";
		//	//std::cout << hand.palmNormal().pitch() << std::endl;
		//}

		gamefunctions.deltaTime();	
		Entity::randomSpawn(bpm, fb);
		Entity::updateEntities();	
			
		Scoring::checkEntities();

		//input from keyboard
        while( SDL_PollEvent(&evn) ) 
        {
			//Play music on press C
			if(evn.type == SDL_KEYDOWN && evn.key.keysym.sym == SDLK_x)
			{
				gamefunctions.playMusic();	
			}
        }

		//print TIME when the specified frame is processed
		//if(controller.frame().timestamp() >= lastFrame + 100000)
		//{
			//lastFrame = controller.frame().timestamp();
			//frameID = controller.frame().id();
			//std::cout << frameID << " " << lastFrame << std::endl;
		//}

        glClearColor(0.0,0.2,0.5,1.0); //background color
        glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(graphics3d_get_shader_program(1));
		GLuint leapVectorLocation = glGetUniformLocation(graphics3d_get_shader_program(1), "leapVec");
		glUniform3fv(leapVectorLocation, 1, GL_FALSE, &leapVec[0]);

        glUseProgram(graphics3d_get_shader_program(0));
		Entity::drawEntities();
		GLuint modelMatrixLocation = glGetUniformLocation(graphics3d_get_shader_program(0), "VP"); // Get the location of our VP matrix in the shader  
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &VP[0][0]); // Send our VP matrix to the shader 
        glUseProgram(0);	

        graphics3d_next_frame();
    }

	gamefunctions.cleanupSong();
	controller.removeListener(listener); //Remove the sample listener when done
    return 0;
}

/*eol@eof*/