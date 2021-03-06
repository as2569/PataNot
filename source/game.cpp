#include <glm/glm.hpp>  
#include <iostream>
#include <fstream>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp> 
#include <math.h>
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
GLuint digitGradTex;
GLuint digitGraduvs;

glm::mat4 VP;
glm::mat4 barMat;
glm::vec3 barVec;
Leap::Vector leapVec;
Leap::Vector average;
float leapVals[2];
int bpm = 50;
int diff = 0;

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
	SDL_Event evn;
	int64_t frameID;
	int64_t lastFrame = controller.frame().timestamp();
	int64_t newFrame = 0;
	int count = 0;

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
	glGenBuffers(1, &digit);
	glGenBuffers(1, &digituvs);
	glGenBuffers(1, &digitGraduvs);

    slog("glError: %d", glGetError());
    
	lastFrame = controller.frame().timestamp();

	SDL_Init(SDL_INIT_EVERYTHING);
	
	//0 for barbie, 1 for njit shanty, 2 for njit 
	if( Mix_OpenAudio( 32075, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        std::cout << "AudioFail" << std::endl;    
    }

	Mix_Init(MIX_INIT_MP3);
	gamefunctions.loadSong(1);
	Entity::reserve();
	srand(time(NULL));
	
	Scoring::readScore();
	Scoring::setupScore();
	Scoring::setupHighScore();

	barVec = glm::vec3(-0.47f, 0.27f, 0.0f);
	barMat = glm::mat4(1.0f);
	barMat = glm::translate(barMat, barVec);

	Sprite bar = Sprite();
	bar.setupBar();

    while (bGameLoopRunning)
    {
		using namespace Leap;
		Frame frame = controller.frame();
		HandList hands = frame.hands();
		leapVec = hands.leftmost().palmNormal();
		gamefunctions.playMusic();

		for( int i = 1; i < FRAME_SAMPLE_LENGTH; i++)
		{
			Frame frame = controller.frame(i);
			HandList hands = frame.hands();
			average += hands.leftmost().palmNormal();
		}
		average /= FRAME_SAMPLE_LENGTH;

		leapVals[0] = fabs(average.x);
		leapVals[1] = fabs(average.y);
		leapVals[2] = fabs(average.z);
		
		gamefunctions.deltaTime(); //time keeping
		Entity::randomSpawn(bpm);
		Entity::updateEntities();		
		Scoring::checkEntities(); //check if entity is 'scorable'

		//input from keyboard
        while( SDL_PollEvent(&evn) ) 
        {
			//Play music on press C
			if(evn.type == SDL_KEYDOWN && evn.key.keysym.sym == SDLK_x)
			{
				gamefunctions.playMusic();	
			}
			if(evn.type == SDL_KEYDOWN && evn.key.keysym.sym == SDLK_ESCAPE)
			{
				Scoring::writeScore();
				return 0;
			}
        }

		////print TIME when the specified frame is processed
		//if(controller.frame().timestamp() >= lastFrame + 100000)
		//{
		//	lastFrame = controller.frame().timestamp();
		//	frameID = controller.frame().id();
		//	std::cout << frameID << " " << lastFrame << std::endl;
		//}

		//print TIME between frame with both hand input
		HandList handLen = controller.frame().hands();

		//if(handLen.count() == 0)
		//{
		//	lastFrame = controller.frame().timestamp();
		//	count = count + 1;
		//	//std::cout << count << std::endl;
		//	//int out = controller.frame().timestamp();
		//}
		//if(handLen.count() == 1);
		//{
		//	newFrame = controller.frame().timestamp();
		//	diff = lastFrame - newFrame;
		//	std::cout << diff << std::endl;
		//	diff = 0;
		//}

//HandList handlist = controller.frame().hands();
//if((handlist.leftmost().direction().yaw() > -0.2) && (handlist.leftmost().direction().yaw() < 0.2))
//{
//	if(handlist.leftmost().fingers().extended().count() == 2)
//	{
//		std::cout << "V gesture formed " << controller.frame().timestamp() << std::endl;
//	}
//}
	
		glClearColor(leapVals[0],leapVals[1],leapVals[2],1.0); //background color
        //glClearColor(0.6,0.3,0.5,1.0); //background color
        glClear(GL_COLOR_BUFFER_BIT);
	
		
        glUseProgram(graphics3d_get_shader_program(0));
		
		Scoring::displayScore();
		Scoring::displayHighScore();
		Entity::drawEntities();
		bar.barDraw(barMat);

		GLuint modelMatrixLocation = glGetUniformLocation(graphics3d_get_shader_program(2), "VP"); // Get the location of our VP matrix in the shader  
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &VP[0][0]); // Send our VP matrix to the shader 
        glUseProgram(0);	

        graphics3d_next_frame();
    }

	gamefunctions.cleanupSong();
	controller.removeListener(listener); //Remove the sample listener when done
    return 0;
}

/*eol@eof*/