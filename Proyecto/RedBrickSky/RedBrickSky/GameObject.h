#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "SDL_mixer.h"

#include "Game.h"
#include "Vector2D.h"

class GameObject
{
protected:
	Game* game_ = nullptr; // by cleon, puede que no sea const

	Texture* text_ = nullptr;
	string textureId_ = "";	// id para TextureManager (key)

	// NCM: deberiamos inicializar todo en la constructora
	Vector2D position_ = Vector2D(0,0);
	Vector2D iniPosition_ = Vector2D(0, 0);
	Vector2D velocity_ = Vector2D(0, 0);
	Vector2D direction_ = Vector2D(0, 0);

	double width_ = 0;
	double height_ = 0;

	int colFrame_ = 0;
	int rowFrame_ = 0;
	int numFrames_ = 0;
	int animSpeed_ = 0;

	int alpha_ = 255;
	double angle_ = 0;
	int callbackId_ = 0;

public:
	GameObject(Game* gamePtr);
	virtual ~GameObject();

	int getCallbackId() const { return callbackId_; };
	void setCallbackId(int id) { callbackId_ = id; };

	//para poder acceder al juego desde los go
	Game* getGame() const { return game_; };

	//para poder modificar la textura del go
	Texture* getText() const { return text_; };
	void setText(Texture* t) { text_ = t; };
	string getTextureId() { return textureId_; };
	void setTextureId(string s) { textureId_ = s; };
	int getAlpha() const { return alpha_; };
	void setAlpha(int a) { alpha_ = a; };
	double getAngle() const { return angle_; };
	void setAngle(double a) { angle_ = a; };

	//para obtener o cambiar su posicion y direccion
	const Vector2D& getPosition() const { return position_; };
	void setPosition(const Vector2D &pos) { position_ = pos; };
	const Vector2D& getOriPos() const { return iniPosition_; };
	void setOriPos(const Vector2D &pos) { iniPosition_ = pos; };
	const Vector2D& getDirection() const { return direction_; };
	void setDirection(const Vector2D &dir) { direction_ = dir; direction_.normalize(); };
	const Vector2D& getVel() const { return velocity_; };
	void setVel(const Vector2D &vel) { velocity_ = vel; };

	//para obtener o cambiar las dimensiones del go
	inline double getWidth() const { return width_; };
	void setWidth(double width) { width_ = width; };
	inline double getHeight() const { return height_; };
	void setHeight(double height) { height_ = height; };
	inline void scale(double s) { width_ *= s; height_ *= s; };

	//para cambiar los frames
	int getRowFrame() const { return rowFrame_; };
	void setRowFrame(int rf) { rowFrame_ = rf; };
	int getColFrame() const { return colFrame_; };
	void setColFrame(int cf) { colFrame_ = cf; };
	int getNumFrames() const { return numFrames_; };
	void setNumFrames(int n) { numFrames_ = n; };
	int getAnimSpeed() const { return animSpeed_; };
	void setAniMSpeed(int a) { animSpeed_ = a; };

	//metodos abstractos que se redifiniran en clases hijas
	virtual bool handleEvent(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

