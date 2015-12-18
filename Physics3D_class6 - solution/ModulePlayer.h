#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;
class Timer;
#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
//Victory Condtions
#define MAX_LAPS 4
#define MAX_TIME 720000
class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	
	bool CleanUp();

	//Check Victory
	void checkVictory(bool & _victory, bool &_finish);
public:
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
private:
	Timer* timer;
	bool isStarting;
	bool victory;
	bool finish;
};