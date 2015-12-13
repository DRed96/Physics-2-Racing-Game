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
	void createPlatform(vec3 position, vec3 size, Cube& obj, float rot = 0.0f, float rot_x = 1.0f,
						float rot_y = 0.0f, float rot_z = 0.0f, float mass = 0.0f);

public:
	Cube s;
	p2List<PhysBody3D*> lazyness;
	p2List<Cube> platforms;

	PhysBody3D* sensor;
};
