#include <glm/glm.hpp>  
#include <iostream>
#include <fstream>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>  
#include <SDL_keyboard.h>
#include <SOIL.h>
#include "Leap.h"
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "sprite.h"
#include "entity.h"
#include "gameFunctions.h"

GameFunctions gamefunctions;
GLuint vbo;
GLuint uvs;
GLuint tex;
glm::mat4 matrixMVP;
Entity entList[5];

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
	using namespace Leap;
	//SampleListener listener;
	
	Controller controller;
	Leap::Listener listener;
    GLuint vao;
    GLuint triangleBufferObject;
    char bGameLoopRunning = 1;
	SDL_Event evn;

	int lastFrameID = controller.frame().id();
	int64_t lastFrame = controller.frame().timestamp();

	controller.addListener(listener); //Have the sample listener receive events from the controller

    init_logger("gametest3d.log");
    if (graphics3d_init(1024,1024,1,"gametest3d",33) != 0)
    {
        return -1;
    }

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &uvs);

    slog("glError: %d", glGetError());
    
	lastFrame = controller.frame().timestamp();
	SDL_Init;

	entList[0].setup();
	//entList[0].randomSpawn();
	//Entity ent;
	//ent.setup();

    while (bGameLoopRunning)
    {
		gamefunctions.deltaTime();
		matrixMVP = entList[0].getMatrix();

		////input from keyboard
  //      while( SDL_PollEvent(&evn) ) 
  //      {
  //        if(evn.type == SDL_KEYDOWN && evn.key.keysym.sym == SDLK_c)
		//  {
		//	  //spr.currentStep += 1;
		//  }
  //      }

		//print TIME when the specified frame is processed
		//if(controller.frame().timestamp() >= lastFrame + 1000000)
		//{
		//	lastFrame = controller.frame().timestamp();
		//	std::cout << "TIME" << lastFrameID << std::endl;
		//}

		bool hands = controller.frame().hands().count() > 1;
  		float angle = controller.frame().hands().leftmost().palmNormal().roll();
  		//std::cout << angle << std::endl; //Print angle of roll

        glClearColor(0.0,0.2,0.4,1.0); //background color
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(graphics3d_get_shader_program());

		GLuint modelMatrixLocation = glGetUniformLocation(graphics3d_get_shader_program(), "matrixMVP"); // Get the location of our model matrix in the shader  
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &matrixMVP[0][0]); // Send our model matrix to the shader 

		entList[0].update();
        glUseProgram(0);	
        graphics3d_next_frame();
    }

	controller.removeListener(listener); //Remove the sample listener when done
    return 0;
}

/*eol@eof*/