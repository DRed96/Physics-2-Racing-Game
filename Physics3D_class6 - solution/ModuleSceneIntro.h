#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#define MAX_SNAKE 2


#define CAMERA_DISTANCE 15
#define CAMERA_HEIGHT 6

#define CUBE_LIMIT 40
#define BODY_LIMIT 40
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

	//bool AttachPlatform(PhysBody3D& obj, PhysBody3D& obj2, Cube& cObj1, Cube& cObj2, Orientation orientation);

	//Method that avoids player scoring if going backwards
	int Checkpoint(int);
	
	Cube* createPlatform(vec3 position, vec3 size, PhysBody3D*& pBody, float rot = 0.0f, float rot_x = 1.0f,
		float rot_y = 0.0f, float rot_z = 0.0f, bool isSensor = false, int check = -1, bool isVisible = true, float mass = 0.0f);

	Cube* createSensor(vec3 position, vec3 size, PhysBody3D*& pBody, int check = -1, bool isVisible = false,
		float rot = 0.0f, float rot_x = 1.0f, float rot_y = 0.0f, float rot_z = 0.0f, float mass = 0.0f);

	bool AttachPlatform(PhysBody3D* obj, PhysBody3D* obj2, Cube* cObj1, Cube* cObj2, Orientation orientation);

	vec3 CreatePlane(vec3 positionPlane, vec3 sizeTile, int rows, int cols, float angle = 0.0f, vec3 rotation = {0.0f,0.0f,0.0f});

	void CreateCurve45(vec3 pos, vec3 sizeTile, int rows, float angle);

	void CreateCurve30(vec3 pos, vec3 sizeTile, int rows, vec3 rot);
	


	//Checkpoint creation
	void declareChecks();

	//Checkpoint creation
	void circuitConstruction();
	
public:
	Cube s;
	PhysBody3D* sensor;
	//List of all the elements that must be rendered
	p2List<Cube*> platforms;
	//Lap counter
	int laps;
	p2List<PhysBody3D*> sensors;


	p2DynArray<Cube*> cubes;
	p2DynArray<PhysBody3D*> pbodies;

	vec3 standardSize;
	int antiCheat;
private:
	//Declare all the Cubes and PhysBodys that will be needed
	void createAllElements();
};
/*PhysBody3D* createPlatform(vec3 position, vec3 size, Cube& obj, float rot = 0.0f, float rot_x = 1.0f,
	float rot_y = 0.0f, float rot_z = 0.0f, float mass = 0.0f);*/
