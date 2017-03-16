#include <glm/glm.hpp>  
#include <iostream>
#include <fstream>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>  
#include <SDL_keyboard.h>
#include <SDL_image.h>
#include "Leap.h"
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "sprite.h"

GLuint vbo;
using namespace Leap;
extern SDL_Window *__graphics3d_window;
SDL_Renderer *renderer;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
    virtual void onServiceChange(const Controller&);
    virtual void onDeviceFailure(const Controller&);
    virtual void onLogMessage(const Controller&, MessageSeverity severity, int64_t timestamp, const char* msg);
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
	//Get the most recent frame and report some basic information
	const Frame frame = controller.frame();

	HandList hands = frame.hands();

	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl)\
	{
		// Get the first hand	
		const Hand hand = *hl;
		std::string handType = hand.isLeft() ? "Left hand" : "Right hand";

		// Get the hand's normal vector and direction
		const Vector normal = hand.palmNormal();
		const Vector direction = hand.direction();

		/*if((normal.roll() * RAD_TO_DEG) > 0)
		{
			std::cout << "LEFT" << std::endl;
		}
		if((normal.roll() * RAD_TO_DEG) < 0)
		{
			std::cout << "RIGHT" << std::endl;
		}*/
    }
  }


void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    std::cout << "  isSmudged:" << (devices[i].isSmudged() ? "true" : "false") << std::endl;
    std::cout << "  isLightingBad:" << (devices[i].isLightingBad() ? "true" : "false") << std::endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

void SampleListener::onServiceChange(const Controller& controller) {
  std::cout << "Service Changed" << std::endl;
}

void SampleListener::onDeviceFailure(const Controller& controller) {
  std::cout << "Device Error" << std::endl;
  const Leap::FailedDeviceList devices = controller.failedDevices();

  for (FailedDeviceList::const_iterator dl = devices.begin(); dl != devices.end(); ++dl) {
    const FailedDevice device = *dl;
    std::cout << "  PNP ID:" << device.pnpId();
    std::cout << "    Failure type:" << device.failure();
  }
}

void SampleListener::onLogMessage(const Controller&, MessageSeverity s, int64_t t, const char* msg) {
  switch (s) {
  case Leap::MESSAGE_CRITICAL:
    std::cout << "[Critical]";
    break;
  case Leap::MESSAGE_WARNING:
    std::cout << "[Warning]";
    break;
  case Leap::MESSAGE_INFORMATION:
    std::cout << "[Info]";
    break;
  case Leap::MESSAGE_UNKNOWN:
    std::cout << "[Unknown]";
  }
  std::cout << "[" << t << "] ";
  std::cout << msg << std::endl;
}

int main(int argc, char *argv[])

{	
	using namespace Leap;
	SampleListener listener;
	Controller controller;

	glm::mat4 scaleMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 matrixMVP;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 translateVector;
	glm::vec3 scaleVector;
	glm::vec3 rotationVector;

	bool input;
    GLuint vao;
    GLuint triangleBufferObject;
    char bGameLoopRunning = 1;
    //SDL_Event e;

	int lastFrameID = controller.frame().id();
	int64_t lastFrame = controller.frame().timestamp();

	Sprite spr; //Instantiate spr instance of Sprite class
	controller.addListener(listener); // Have the sample listener receive events from the controller

	const float triangleVertices[] = {
		-0.2f, -0.2f, 0.0f, 1.0f,
        0.2f, -0.2f, 0.0f, 1.0f,
        -0.2f, 0.2f, 0.0f, 1.0f,

		0.2f, -0.2f, 0.0f, 1.0f,
		0.2f, 0.2f, 0.0f, 1.0f,
		-0.2f, 0.2f, 0.0f, 1.0f,

		.7f, .7f, .7f, 1.0f,
        .7f, .7f, .7f, 1.0f,
        .7f, .7f, .7f, 1.0f,

		.5f, .5f, .5f, 1.0f,
        .5f, .5f, .5f, 1.0f,
        .5f, .5f, .5f, 1.0f,
	};

    init_logger("gametest3d.log");
    if (graphics3d_init(1024,1024,1,"gametest3d",33) != 0)
    {
        return -1;
    }

	renderer = SDL_CreateRenderer(__graphics3d_window, -1, SDL_RENDERER_ACCELERATED);
	glGenBuffers(1, &vbo);

 //   glGenVertexArrays(1, &vao);
 //   glBindVertexArray(vao); //make our vertex array object, we need it to restore state we set after binding it. Re-binding reloads the state associated with it.
 //  
	//glGenBuffers(1, &triangleBufferObject); //create the buffer
 //   glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //we're "using" this one now
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); //formatting the data for the buffer
 //   glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind any buffers
    
    slog("glError: %d", glGetError());
    
	translateVector = glm::vec3(0, 0, 0);
	rotationVector = glm::vec3(0.0f, 0.0f, 1.0f);
	scaleVector = glm::vec3(0.5f, 0.5f, 0);
	
	matrixMVP = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);

	GLuint modelMatrixLocation = glGetUniformLocation(graphics3d_get_shader_program(), "modelMatrix"); // Get the location of our model matrix in the shader  
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader 

	lastFrame = controller.frame().timestamp();

    while (bGameLoopRunning)
    {
		//input from keyboard
   //     if ( SDL_PollEvent(&e) ) 
   //     {
   //         if (e.type == SDL_QUIT)
   //             bGameLoopRunning = 0;
   //         else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
   //             bGameLoopRunning = 0;
			//else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c)
			//	continue;
   //     }

		//print TIME when the specified frame is processed
		//if(controller.frame().timestamp() >= lastFrame + 1000000)
		//{
		//	lastFrame = controller.frame().timestamp();
		//	std::cout << "TIME" << lastFrameID << std::endl;
		//}

		bool hands = controller.frame().hands().count() > 1;
  		float angle = controller.frame().hands().leftmost().palmNormal().roll();
  		//std::cout << angle << std::endl; //Print angle of roll

		rotateMatrix = glm::rotate(glm::mat4(1.0f), angle - 1, glm::vec3(0, 0, 1));
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
		modelMatrix = scaleMatrix * rotateMatrix;

        glClearColor(0.0,0.2,0.4,1.0); //background color
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(graphics3d_get_shader_program());

		GLuint modelMatrixLocation = glGetUniformLocation(graphics3d_get_shader_program(), "modelMatrix"); // Get the location of our model matrix in the shader  
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader 

        //glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //bind the buffer we're applying attributes to
        //glEnableVertexAttribArray(0); //0 is our index, refer to "location = 0" in the vertex shader
        //glEnableVertexAttribArray(1); //attribute 1 is for vertex color data
        //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //tell gl (shader!) how to interpret our vertex data

        //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)96); //color data is 48 bytes in to the array
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        spr.draw();//use sprites draw function
        //glDisableVertexAttribArray(0);
       // glDisableVertexAttribArray(1);
        glUseProgram(0);
		
        graphics3d_next_frame();
    } 

	//Remove the sample listener when done
	controller.removeListener(listener);

    return 0;
}

/*eol@eof*/