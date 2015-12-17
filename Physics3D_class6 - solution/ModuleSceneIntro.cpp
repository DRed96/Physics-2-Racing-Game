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

	//TOCHANGE: A little bit chaotic
	standardSize = { 9.0f, 1.0f, 7.0f };

	createPlatform({ 0.0f, 16.0f, 7.5f }, standardSize);
	createPlatform({ 0.0f, 13.0f, 16.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 23.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 30.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 37.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 44.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 51.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 58.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 65.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 72.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 79.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 86.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 93.0f },standardSize);
	createPlatform({ 0.0f, 13.0f, 100.0f }, standardSize);
	createPlatform({ 0.0f, 13.0f, 107.0f }, standardSize);

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
	p2List_item<PhysBody3D*> *tmp = sensors.getFirst();
	LOG("Hit!");
}

//Platform Factory
void ModuleSceneIntro::createPlatform(vec3 pos, vec3 _size,  bool isSensor,int check, bool isVisible, float rot_angle, float rot_x, float rot_y, float rot_z, float mass )
{
	
	Cube obj;
	obj.SetPos(pos.x, pos.y, pos.z);
	if(_size.x)
	obj.size = _size;
	obj.SetRotation(rot_angle, vec3{rot_x,rot_y,rot_z});
	PhysBody3D* toAdd = App->physics->AddBody(obj, mass);
	/*If we don't add the obj to the List we'll only use it's coords 
	* without saving it in the heap and it won't be rendered. */
	if(isVisible)
		platforms.add(obj);
	if (isSensor)
	{
		toAdd->SetAsSensor(true);
		toAdd->collision_listeners.add(this);
		toAdd->check_point_num = check;
	}
	return;
}
