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

	string textureId_;	// id para TextureManager (key)

	// NCM: deberiamos inicializar todo en la constructora
	Vector2D position_;
	Vector2D iniPosition_;
	Vector2D velocity_;
	Vector2D direction_;

	double width_;
	double height_;

	int colFrame_;
	int rowFrame_;
	int numFrames_;
	int animSpeed_;

	int alpha_;
	double angle_;
	int callbackId_;

	string Message_;
public:
	GameObject();
	virtual ~GameObject();

	int getCallbackId() const { return callbackId_; };
	void setCallbackId(int id) { callbackId_ = id; };

	//para poder modificar la textura del go
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

	//Para establecer el mensaje si es necesario
	void setMessage(std::string msg) { Message_ = msg; };

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
	virtual void load(Vector2D position, int width, int height, string textureId, int numFrames, int callbackID = 0, int animSpeed = 0) = 0;
	virtual bool handleEvent(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void clean() = 0;
};

