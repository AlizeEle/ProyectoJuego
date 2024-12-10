#pragma once
#include "audio/include/AudioEngine.h"
#include "cocos2d.h"
class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//Metodo para generar un mensaje 
	std::string getRandomMessage();

	//Label to display the message
	cocos2d::Label* messageLabel;
	cocos2d::Label* messageLabel2;

	void updateProgressBar(float dt);

	//virtual bool init();


	CREATE_FUNC(MainScene);

private:
	//Definir la barra de carga
	cocos2d::ProgressTimer* progressBar;

protected:
};