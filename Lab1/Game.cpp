#include "Game.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

Game::Game()
{
	_gameState = GameState::PLAY;
	Screen* _gameDisplay = new Screen(); //new display
	GameMesh* mesh1();
	GameMesh* mesh2();
	GameMesh* mesh3();
	Sounds* audioDevice();
	Textures* texture(); //load texture
	Textures* texture1(); //load texture
	Overlays* overlay(); //load texture
	Shaders* shaderPass();
	Shaders* shaderBlur();
	Shaders* shaderToon();
	Shaders* shaderRim();
	Shaders* shaderRimToon();
	Shaders* shaderLight();
}

Game::~Game()
{
}

void Game::run()
{
	systemInit(); 
	Loop();
}

void Game::systemInit()
{
	_gameDisplay.screenInit(); 
	whistle = audioDevice.soundLoad("..\\res\\bang.wav");
	backGroundMusic = audioDevice.soundLoad("..\\res\\background.wav");
	texture.init("..\\res\\bricks.jpg"); //load texture
	texture1.init("..\\res\\water.jpg"); //load texture

	shaderReflect.init("..\\res\\shaderReflect.vert", "..\\res\\shaderReflect.frag");
	shaderBlinnPhong.init("..\\res\\shaderBlinn-Phong.vert", "..\\res\\shaderBlinn-Phong.frag");
	shaderSkybox.init("..\\res\\shaderSkybox.vert", "..\\res\\shaderSkybox.frag");
	shaderLightFog.init("..\\res\\shaderLightFog.vert", "..\\res\\shaderLightFog.frag");
	shaderLight.init("..\\res\\shaderLight.vert", "..\\res\\shaderLight.frag");
	//shaderPass.init("..\\res\\shader.vert", "..\\res\\shader.frag");
	shaderToon.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag");
	shaderRim.init("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	shaderRimToon.init("..\\res\\shaderRimToon.vert", "..\\res\\shaderRimToon.frag");
	shaderLighting.init("..\\res\\shaderLighting.vert", "..\\res\\shaderLighting.frag");
	//shaderIridiscent.init("..\\res\\shaderIridiscent.vert", "..\\res\\shaderIridiscent.frag");
	//shaderBlur.init("..\\res\\shaderBlur.vert", "..\\res\\shaderBlur.frag");
	/*Vertex2D vertices[] = { Vertex2D(glm::vec2(-0.5, 1.0), glm::vec2(0.0, 0.0)),
							Vertex2D(glm::vec2(0.5, 0.5), glm::vec2(1.0, 0.0)),
							Vertex2D(glm::vec2(0.5,-0.5), glm::vec2(1.0, 1.0)),
							Vertex2D(glm::vec2(-0.5,-0.5), glm::vec2(0.0, 1.0)) };*/

	overlay.init("..\\res\\bricks.jpg");

	mesh1.modelLoad("..\\res\\monkey3.obj");
	mesh2.modelLoad("..\\res\\monkey3.obj");
	mesh3.modelLoad("..\\res\\monkey3.obj");
	mesh4.modelLoad("..\\res\\monkey3.obj");
	mesh5.modelLoad("..\\res\\monkey3.obj");
	mesh6.modelLoad("..\\res\\monkey3.obj");
	mesh7.modelLoad("..\\res\\monkey3.obj");
	mesh8.modelLoad("..\\res\\monkey3.obj");



	//LOAD SKYBOX TEXTURES
	vector<std::string> faces
	{
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg"
	};


	cubemapTexture = skybox.loadCubemap(faces);

	float skyboxVertices[] = {
		// positions          
		-7.0f,  7.0f, -7.0f,
		-7.0f, -7.0f, -7.0f,
		7.0f, -7.0f, -7.0f,
		7.0f, -7.0f, -7.0f,
		7.0f,  7.0f, -7.0f,
		-7.0f,  7.0f, -7.0f,

		-7.0f, -7.0f,  7.0f,
		-7.0f, -7.0f, -7.0f,
		-7.0f,  7.0f, -7.0f,
		-7.0f,  7.0f, -7.0f,
		-7.0f,  7.0f,  7.0f,
		-7.0f, -7.0f,  7.0f,

		7.0f, -7.0f, -7.0f,
		7.0f, -7.0f,  7.0f,
		7.0f,  7.0f,  7.0f,
		7.0f,  7.0f,  7.0f,
		7.0f,  7.0f, -7.0f,
		7.0f, -7.0f, -7.0f,

		-7.0f, -7.0f,  7.0f,
		-7.0f,  7.0f,  7.0f,
		7.0f,  7.0f,  7.0f,
		7.0f,  7.0f,  7.0f,
		7.0f, -7.0f,  7.0f,
		-7.0f, -7.0f,  7.0f,

		-7.0f,  7.0f, -7.0f,
		7.0f,  7.0f, -7.0f,
		7.0f,  7.0f,  7.0f,
		7.0f,  7.0f,  7.0f,
		-7.0f,  7.0f,  7.0f,
		-7.0f,  7.0f, -7.0f,

		-7.0f, -7.0f, -7.0f,
		-7.0f, -7.0f,  7.0f,
		7.0f, -7.0f, -7.0f,
		7.0f, -7.0f, -7.0f,
		-7.0f, -7.0f,  7.0f,
		7.0f, -7.0f,  7.0f
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	
	myCamera.initCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)_gameDisplay.getW()/_gameDisplay.getH(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void Game::Loop()
{
	while (_gameState != GameState::EXIT)
	{
		inputProcc();
		Draw();
		collision(mesh1.SpherePos(), mesh1.SphereRadius(), mesh2.SpherePos(), mesh2.SphereRadius());
		audioPlay(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void Game::inputProcc()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool Game::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		audioDevice.listenerSet(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

void Game::audioPlay(unsigned int Source, glm::vec3 pos)
{
	
	ALint state; 
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		//audioDevice.playSound(Source, pos);
	}
}


void Game::Reflection()
{
	shaderReflect.setMat4("model", transform.GetModel());
	shaderReflect.setMat4("view", myCamera.GetView());
	shaderReflect.setMat4("projection", myCamera.GetProjection());
	shaderReflect.setVec3("cameraPos", myCamera.getPos());
	shaderReflect.setInt("skybox", 0);
}

void Game::Skybox()
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shaderSkybox.BindTo();
	shaderSkybox.setInt("skybox", 0);
	//view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	shaderSkybox.setMat4("view", myCamera.GetView());
	shaderSkybox.setMat4("projection", myCamera.GetProjection());
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

//void Game::ADSLighting()
//{
//	modelView = transform.GetModel() * myCamera.GetView();
//	
//	//shaderPass.setMat4("ModelViewMatrix", modelView);
//	shaderPass.setMat4("model", transform.GetModel());
//	shaderPass.setMat4("view", myCamera.GetView());
//	shaderPass.setMat4("ProjectionMatrix", myCamera.GetProjection()); 
//	
//	glm::mat4 normalMatrix = transpose(inverse(modelView));
//	
//	shaderPass.setMat4("NormalMatrix", normalMatrix);
//
//	shaderPass.setVec3("Position", glm::vec4(10.0f,10.0f,10.0f,1.0f));
//	shaderPass.setVec3("Intensity", glm::vec3(0.0f, 0.0f, 0.0f));
//
//	shaderPass.setVec3("ka", 0.5f, 0.5f, 0.5f);
//	shaderPass.setVec3("kd", 0.5f, 0.5f, 0.5f);
//	shaderPass.setVec3("ks", 0.5f, 0.5f, 0.5f);
//
//	shaderPass.setFloat("Shininess", 0.5);
//}

void Game::BlinnPhong()
{
	shaderBlinnPhong.setMat4("view", myCamera.GetView());
	shaderBlinnPhong.setMat4("projection", myCamera.GetProjection());
	shaderBlinnPhong.setMat4("model", transform.GetModel());

	shaderBlinnPhong.setVec3("viewPos", myCamera.getPos());
	shaderBlinnPhong.setVec3("lightPos", glm::vec3(5, 5, 5));
}

void Game::Light() //ADS Lighting
{
	shaderLight.setVec3("objectColor", 0.5f, 0.5f, 1.0f);
	shaderLight.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shaderLight.setVec3("lightPos", 5.0f, 5.0f, 5.0f);
	shaderLight.setVec3("viewPos", myCamera.getPos());
	
	shaderLight.setMat4("projection", myCamera.GetProjection());
	shaderLight.setMat4("view", myCamera.GetView());
	shaderLight.setMat4("model", transform.GetModel());
}

void Game::LightFog()
{
	shaderLightFog.setVec3("objectColor", 0.5f, 0.5f, 1.0f);
	shaderLightFog.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shaderLightFog.setVec3("lightPos", 5.0f, 5.0f, 5.0f);
	shaderLightFog.setVec3("viewPos", myCamera.getPos());

	shaderLightFog.setMat4("projection", myCamera.GetProjection());
	shaderLightFog.setMat4("view", myCamera.GetView());
	shaderLightFog.setMat4("model", transform.GetModel());


	shaderLightFog.setVec3("fogColor", glm::vec3(0.8, 0.8, 0.8));
	shaderLightFog.setFloat("minDist", -5.0f);
	shaderLightFog.setFloat("maxDist", 5.0f);
}

void Game::ToonLighting()
{
	shaderToon.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
}

void Game::RimShader()
{
	shaderRim.setMat4("u_vm", myCamera.GetView());
	shaderRim.setMat4("u_pm", myCamera.GetProjection());
}

void Game::RimToon()
{
	shaderRimToon.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shaderRimToon.setMat4("u_vm", myCamera.GetView());
	shaderRimToon.setMat4("u_pm", myCamera.GetProjection());
}

void Game::setLighting()
{
	shaderLighting.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));

	shaderLighting.setMat4("u_vm", myCamera.GetView());
	shaderLighting.setMat4("u_pm", myCamera.GetProjection());

	shaderLighting.setVec3("fogColor", glm::vec3(0.2, 0.2, 0.2));
	shaderLighting.setFloat("minDist", -5.0f);
	shaderLighting.setFloat("maxDist", 5.0f);
}

void Game::effectBlob()
{
	GLuint blockIndex = glGetUniformBlockIndex(shaderBlur.getProgram(), "BlobSettings");

	GLint blockSize;
	glGetActiveUniformBlockiv(shaderBlur.getProgram(), blockIndex,
		GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize); //get information about blobsettings and save it in blockSize

	GLubyte * blockBuffer = (GLubyte *)malloc(blockSize); //allocates the requested memory and returns a pointer to it.

														  // Query for the offsets of each block variable
	const GLchar *names[] = { "InnerColor", "OuterColor",
		"RadiusInner", "RadiusOuter" };

	GLuint indices[4];
	glGetUniformIndices(shaderBlur.getProgram(), 4, names, indices); // glGetUniformIndices retrieves the indices of a number of uniforms within program

	GLint offset[4];
	glGetActiveUniformsiv(shaderBlur.getProgram(), 4, indices, GL_UNIFORM_OFFSET, offset); //Returns information about several active uniform variables for the specified program object

	GLfloat outerColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat innerColor[] = { 1.0f, 1.0f, 0.75f, 1.0f };

	GLfloat innerRadius = 0.0f, outerRadius = 3.0f;

	memcpy(blockBuffer + offset[0], innerColor,
		4 * sizeof(GLfloat)); //destination, source, no of bytes. 
	memcpy(blockBuffer + offset[1], outerColor,
		4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[2], &innerRadius,
		sizeof(GLfloat));
	memcpy(blockBuffer + offset[3], &outerRadius,
		sizeof(GLfloat));

	GLuint uboHandle;

	glGenBuffers(1, &uboHandle);

	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer,
		GL_DYNAMIC_DRAW); //creates and initializes a buffer object's data store - targer, size, data, usage

	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, uboHandle); // bind a buffer object to an indexed buffer target - trager, index, buffer
}

void Game::Draw()
{
	_gameDisplay.screenClear(0.0f, 0.0f, 0.0f, 1.0f);

	Skybox();

	transform.SetPos(glm::vec3(-2.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderLighting.BindTo();
	setLighting();
	shaderLighting.Update(transform, myCamera);

	texture.BindTo(0);
	mesh1.gameDraw();
	mesh1.updateSphere(*transform.GetPos(), 0.62f);
	


	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderLight.BindTo();
	Light();
	shaderLight.Update(transform, myCamera);

	mesh2.gameDraw();
	mesh2.updateSphere(*transform.GetPos(), 0.62f);



	transform.SetPos(glm::vec3(2.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderReflect.BindTo();
	Reflection();
	shaderReflect.Update(transform, myCamera);

	mesh3.gameDraw();
	mesh3.updateSphere(*transform.GetPos(), 0.62f);



	transform.SetPos(glm::vec3(0.0, 2.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderToon.BindTo();
	ToonLighting();
	shaderToon.Update(transform, myCamera);

	mesh4.gameDraw();
	mesh4.updateSphere(*transform.GetPos(), 0.62f);



	transform.SetPos(glm::vec3(-2.0, 2.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderRim.BindTo();
	RimShader();
	shaderRim.Update(transform, myCamera);

	mesh5.gameDraw();
	mesh5.updateSphere(*transform.GetPos(), 0.62f);



	transform.SetPos(glm::vec3(2.0, 2.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderLightFog.BindTo();
	LightFog();
	shaderLightFog.setFloat("zValue", transform.GetPos()->z);

	mesh6.gameDraw();
	mesh6.updateSphere(*transform.GetPos(), 0.62f);



	transform.SetPos(glm::vec3(-2.0, -2.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderRimToon.BindTo();
	RimToon();
	shaderRimToon.Update(transform, myCamera);

	mesh7.gameDraw();
	mesh7.updateSphere(*transform.GetPos(), 0.62f);



	transform.SetPos(glm::vec3(2.0, -2.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shaderBlinnPhong.BindTo();
	BlinnPhong();
	shaderBlinnPhong.Update(transform, myCamera);

	mesh8.gameDraw();
	mesh8.updateSphere(*transform.GetPos(), 0.62f);


	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.buffSwap();
} 