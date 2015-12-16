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
	Cube p9;
	createPlatform({ 0.0f, 13.0f, 16.0f }, { 9.0f, 1.0f, 7.0f }, p9);
	Cube pl0;
	createPlatform({ 0.0f, 13.0f, 23.0f }, { 9.0f, 1.0f, 7.0f }, pl0);
	Cube pl1;
	createPlatform({ 0.0f, 13.0f, 30.0f }, { 9.0f, 1.0f, 7.0f }, pl1);
	Cube pl2;
	createPlatform({ 0.0f, 13.0f, 37.0f }, { 9.0f, 1.0f, 7.0f }, pl2);
	Cube pl3;
	createPlatform({ 0.0f, 13.0f, 44.0f }, {6.0f, 1.0f, 7.0f }, pl3);
	Cube pl4;
	createPlatform({ 0.0f, 13.0f, 51.0f }, { 6.0f, 1.0f, 7.0f }, pl4);
	Cube pl5;
	createPlatform({ 0.0f, 13.0f, 58.0f }, { 6.0f, 1.0f, 7.0f }, pl5);
	Cube pl6;
	createPlatform({ 0.0f, 13.0f, 65.0f }, { 6.0f, 1.0f, 7.0f }, pl6);
	Cube pl7;
	createPlatform({ 0.0f, 13.0f, 72.0f }, { 6.0f, 1.0f, 7.0f }, pl7);
	Cube pl8;
	createPlatform({ 0.0f, 13.0f, 79.0f }, { 6.0f, 1.0f, 7.0f }, pl8);
	Cube pl9;
	createPlatform({ 0.0f, 13.0f, 86.0f }, { 6.0f, 1.0f, 7.0f }, pl9);
	Cube p20;
	createPlatform({ 0.0f, 13.0f, 93.0f }, { 6.0f, 1.0f, 7.0f }, p20);
	Cube p21;
	createPlatform({ 0.0f, 13.0f, 100.0f }, { 6.0f, 1.0f, 7.0f }, p21);
	Cube p22;
	createPlatform({ 0.0f, 13.0f, 107.0f }, { 6.0f, 1.0f, 7.0f }, p22);

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

void ModuleSceneIntro::AttachPlatform()
{


}