#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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
	Cube* createPlatform(vec3 position, vec3 size, PhysBody3D*& pBody, bool isSensor = false, int check = -1, bool isVisible = true, float rot = 0.0f, float rot_x = 1.0f,
						float rot_y = 0.0f, float rot_z = 0.0f, float mass = 0.0f);
	bool AttachPlatform(PhysBody3D* obj, PhysBody3D* obj2, Cube* cObj1, Cube* cObj2, Orientation orientation);

	void CreatePlane(vec3 positionPlane, vec3 sizeTile, int rows, int cols, float angle = 0.0f, vec3 rotation = {0.0f,0.0f,0.0f});

	void CreateCurve45(vec3 pos, vec3 sizeTile, int rows, float angle);

	void CreateCurve30(vec3 pos, vec3 sizeTile, int rows, float angle);

public:
	
	Cube s;
	PhysBody3D* sensor;
	//List of all the elements that must be rendered
	p2List<Cube*> platforms;
	//Lap counter
	int laps;
	p2List<PhysBody3D*> sensors;

	vec3 standardSize;
	//Is it necessary a list of sensors?
	
};
/*PhysBody3D* createPlatform(vec3 position, vec3 size, Cube& obj, float rot = 0.0f, float rot_x = 1.0f,
	float rot_y = 0.0f, float rot_z = 0.0f, float mass = 0.0f);*/
