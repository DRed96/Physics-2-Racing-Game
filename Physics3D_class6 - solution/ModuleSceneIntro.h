#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	//Platform Factory
	void createPlatform(vec3 position, vec3 size , bool isSensor = false, int check = -1, bool isVisible = true, float rot = 0.0f, float rot_x = 1.0f,
						float rot_y = 0.0f, float rot_z = 0.0f, float mass = 0.0f);

public:
	
	Cube s;
	PhysBody3D* sensor;
	//List of all the elements that must be rendered
	p2List<Cube> platforms;
	//Lap counter
	int laps;
	p2List<PhysBody3D*> sensors;

	vec3 standardSize;
	//Is it necessary a list of sensors?
	
};
