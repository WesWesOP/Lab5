#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Screen.h" 
#include "Shaders.h"
#include "GameMesh.h"
#include "Textures.h"
#include "transform.h"
#include "Sounds.h"
#include "Overlays.h"

enum class GameState{PLAY, EXIT};

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	unsigned int skyboxVAO, skyboxVBO, cubemapTexture;
	vector<std::string> faces;

	void systemInit();
	void inputProcc();
	void Loop();
	void Draw();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void audioPlay(unsigned int Source, glm::vec3 pos);
	void effectBlob();
	//void ADSLighting();
	void ToonLighting();
	void RimShader();
	void RimToon();
	void setLighting();
	void Light();
	void LightFog();
	void BlinnPhong();
	void Skybox();
	void Reflection();


	Screen _gameDisplay;
	GameState _gameState;
	GameMesh mesh1;
	GameMesh mesh2;
	GameMesh mesh3;
	GameMesh mesh4;
	GameMesh mesh5;
	GameMesh mesh6;
	GameMesh mesh7;
	GameMesh mesh8;
	Textures texture;
	Textures texture1;
	Textures skybox;
	Overlays overlay;
	Shaders shaderPass;
	Shaders shaderBlur;
	Shaders shaderToon;
	Shaders shaderRim;
	Shaders shaderRimToon;
	Shaders shaderLighting;
	Shaders shaderLight;
	Shaders shaderLightFog;
	Shaders shaderBlinnPhong;
	Shaders shaderSkybox;
	Shaders shaderReflect;
	//Shaders shaderIridiscent;


	glm::mat4 modelView;

	Camera myCamera;
	Sounds audioDevice;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;
};

