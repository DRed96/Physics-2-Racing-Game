#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(5.0f, 20.0f, 5.0f));
	App->camera->LookAt(vec3(0.0f, 15.0f, 10.0f));

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	//TOCHANGE: Dirty
	Cube start;
	PhysBody3D* platform1 = createPlatform({ 0.0f, 16.0f, 7.5f }, { 9.0f, 1.0f, 7.0f }, start);
	Cube p9;
	PhysBody3D* platform2 = createPlatform({ 0.0f, 13.0f, 16.0f }, { 9.0f, 1.0f, 7.0f }, p9);
	Cube pl0;
	PhysBody3D* platform3 = createPlatform({ 0.0f, 13.0f, 23.0f }, { 9.0f, 1.0f, 7.0f }, pl0);
	Cube pl1;
	PhysBody3D* platform4 = createPlatform({ 0.0f, 13.0f, 30.0f }, { 9.0f, 1.0f, 7.0f }, pl1);
	Cube pl2;
	PhysBody3D* platform5 = createPlatform({ 0.0f, 13.0f, 37.0f }, { 9.0f, 1.0f, 7.0f }, pl2);
	Cube pl3;
	PhysBody3D* platform6 = createPlatform({ 0.0f, 13.0f, 44.0f }, { 6.0f, 1.0f, 7.0f }, pl3);
	Cube pl4;
	PhysBody3D* platform7 = createPlatform({ 0.0f, 13.0f, 51.0f }, { 6.0f, 1.0f, 7.0f }, pl4);
	Cube pl5;
	PhysBody3D* platform8 = createPlatform({ 0.0f, 13.0f, 58.0f }, { 6.0f, 1.0f, 7.0f }, pl5);
	Cube pl6;
	PhysBody3D* platform9 = createPlatform({ 0.0f, 13.0f, 65.0f }, { 6.0f, 1.0f, 7.0f }, pl6);
	Cube pl7;
	PhysBody3D* platform10 = createPlatform({ 0.0f, 13.0f, 72.0f }, { 6.0f, 1.0f, 7.0f }, pl7);
	Cube pl8;
	PhysBody3D* platform11 = createPlatform({ 0.0f, 13.0f, 79.0f }, { 6.0f, 1.0f, 7.0f }, pl8);
	Cube pl9;
	PhysBody3D* platform12 = createPlatform({ 0.0f, 13.0f, 86.0f }, { 6.0f, 1.0f, 7.0f }, pl9);
	Cube pl10;
	PhysBody3D* platform13 = createPlatform({ 0.0f, 13.0f, 93.0f }, { 6.0f, 1.0f, 7.0f }, pl10);
	Cube pl11;
	PhysBody3D* platform14 = createPlatform({ 0.0f, 13.0f, 100.0f }, { 6.0f, 1.0f, 7.0f }, pl11);
	Cube pl12;
	PhysBody3D* platform15 = createPlatform({ 0.0f, 13.0f, 107.0f }, { 6.0f, 1.0f, 7.0f }, pl12);



	AttachPlatform(*platform1, *platform2, start, p9,RIGHT);
	AttachPlatform(*platform2, *platform3, p9,pl0,RIGHT);
	AttachPlatform(*platform3, *platform4, pl0,pl1, RIGHT);
	AttachPlatform(*platform4, *platform5, pl1, pl2,RIGHT);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	sensor->GetTransform(&s.transform);
	s.Render();
	
	//forReal->SetTransform(&platform1.transform);
	p2List_item<Cube> * tmp = platforms.getFirst();
	while (tmp)
	{
		tmp->data.Render();
		tmp = tmp->next;
	}
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

//Platform Factory
PhysBody3D* ModuleSceneIntro::createPlatform(vec3 pos, vec3 _size, Cube& obj, float rot_angle, float rot_x, float rot_y, float rot_z, float mass)
{
	obj.SetPos(pos.x, pos.y, pos.z);
	obj.size = _size;
	obj.SetRotation(rot_angle, vec3{rot_x,rot_y,rot_z});
	//Just to make the code easier to read
	PhysBody3D* toAdd = App->physics->AddBody(obj, mass);
	lazyness.add(toAdd);
	platforms.add(obj);
	return toAdd;
}

bool ModuleSceneIntro::AttachPlatform(PhysBody3D& obj, PhysBody3D& obj2, Cube& cObj1, Cube& cObj2, Orientation orientation)
{
	bool ret = false;
	float* obj1Transform;

	vec3 posObj2 = obj2.GetPos();
	vec3 sizeObj2 = obj2.GetSize();
	
	vec3 posObj = obj.GetPos();
	vec3 sizeObj = obj.GetSize();
	

	vec3 right = { -9.0f , 0.0f, 0.0f};
	vec3 back = { 0.0f, 0.0f, 7.0f };
	vec3 left = { 9.0f, 0.0f, 0.0f};
	vec3 front = { 0.0f, 0.0f, 7.0f};
	vec3 below = {0.0f, 1.0f, 0.0f};
	vec3 top = { 0.0f, -1.0f, 0.0f };


	switch (orientation)
	{
	case 0: 
		obj2.SetPos(posObj + right);
		cObj2.transform.M[12] = posObj.x + right.x;
		cObj2.transform.M[13] = posObj.y;
		cObj2.transform.M[14] = posObj.z;
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	
	}


	return ret;


}