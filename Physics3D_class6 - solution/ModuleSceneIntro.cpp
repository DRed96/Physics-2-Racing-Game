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
	Cube platform1;
	createPlatform({ 0.0f, 16.0f, 7.5f }, { 9.0f, 1.0f, 7.0f }, platform1);
	Cube pl6;
	createPlatform({ 0.0f, 13.0f, 16.0f }, { 9.0f, 1.0f, 7.0f }, pl6);
	Cube pl5;
	createPlatform({ 0.0f, 13.0f, 23.0f }, { 9.0f, 1.0f, 7.0f }, pl5);
	Cube pl4;
	createPlatform({ 0.0f, 13.0f, 30.0f }, { 9.0f, 1.0f, 7.0f }, pl4);
	Cube pl2;
	createPlatform({ 0.0f, 13.0f, 37.0f }, { 9.0f, 1.0f, 7.0f }, pl2);
	Cube pl3;
	createPlatform({ 2.0f, 14.5f, 39.5f }, {6.0f, 1.0f, 7.0f }, pl3, -23.0f);
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
void ModuleSceneIntro::createPlatform(vec3 pos, vec3 _size, Cube& obj, float rot_angle, float rot_x, float rot_y, float rot_z, float mass )
{
	obj.SetPos(pos.x, pos.y, pos.z);
	obj.size = _size;
	obj.SetRotation(rot_angle, vec3{rot_x,rot_y,rot_z});
	//Just to make the code easier to read
	PhysBody3D* toAdd = App->physics->AddBody(obj, mass);
	lazyness.add(toAdd);
	platforms.add(obj);
	return;
}