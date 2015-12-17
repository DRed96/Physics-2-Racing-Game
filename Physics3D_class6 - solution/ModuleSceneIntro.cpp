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

	standardSize = { 9.0f, 1.0f, 7.0f };

	//TOCHANGE: Dirty

	
	createPlatform({ 0.0f, 16.0f, 7.5f }, { 9.0f, 1.0f, 7.0f });
	createPlatform({ 0.0f, 13.0f, 16.0f }, { 9.0f, 1.0f, 7.0f });
	
	createPlatform({ 0.0f, 13.0f, 23.0f }, { 9.0f, 1.0f, 7.0f });
	
	createPlatform({ 0.0f, 13.0f, 30.0f }, { 9.0f, 1.0f, 7.0f });
	
	createPlatform({ 0.0f, 13.0f, 37.0f }, { 9.0f, 1.0f, 7.0f });
	
	createPlatform({ 0.0f, 13.0f, 44.0f }, { 6.0f, 1.0f, 7.0f });
	
	createPlatform({ 0.0f, 13.0f, 51.0f }, { 6.0f, 1.0f, 7.0f });
	
	createPlatform({ 0.0f, 13.0f, 58.0f }, { 6.0f, 1.0f, 7.0f });
	
	createPlatform({ 0.0f, 13.0f, 65.0f }, { 6.0f, 1.0f, 7.0f });
	
	 createPlatform({ 0.0f, 13.0f, 72.0f }, { 6.0f, 1.0f, 7.0f });
	
	 createPlatform({ 0.0f, 13.0f, 79.0f }, { 6.0f, 1.0f, 7.0f });
	
	 createPlatform({ 0.0f, 13.0f, 86.0f }, { 6.0f, 1.0f, 7.0f });
	
	 createPlatform({ 0.0f, 13.0f, 93.0f }, { 6.0f, 1.0f, 7.0f });
	
	 createPlatform({ 0.0f, 13.0f, 100.0f }, { 6.0f, 1.0f, 7.0f });
	
	 createPlatform({ 0.0f, 13.0f, 107.0f }, { 6.0f, 1.0f, 7.0f });



	/*AttachPlatform(*platform1, *platform2, start, p9,RIGHT);
	AttachPlatform(*platform2, *platform3, p9,pl0,RIGHT);
	AttachPlatform(*platform3, *platform4, pl0,pl1, RIGHT);
	AttachPlatform(*platform4, *platform5, pl1, pl2,RIGHT);*/


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
	p2List_item<Cube*> * tmp = platforms.getFirst();
	while (tmp)
	{
		tmp->data->Render();
		tmp = tmp->next;
	}
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	//It is necessary to be in both bodies?
	if (body1->check_point_num > 0)
	{
		Checkpoint(body1->check_point_num);
	}
	if (body2->check_point_num > 0)
	{
		Checkpoint(body2->check_point_num);
	}
	LOG("Hit!");
}

//Platform Factory

Cube* ModuleSceneIntro::createPlatform(vec3 pos, vec3 _size, PhysBody3D* pbody,  bool isSensor, int check, bool isVisible, float rot_angle, float rot_x, float rot_y, float rot_z, float mass)
{
	Cube* obj = new Cube();

	obj->SetPos(pos.x, pos.y, pos.z);
	obj->size = _size;
	obj->SetRotation(rot_angle, vec3{ rot_x, rot_y, rot_z });

	pbody = App->physics->AddBody(*obj, mass);

	/*If we don't add the obj to the List we'll only use it's coords 
	* without saving it in the heap and it won't be rendered. */
	if(isVisible)
		platforms.add(obj);
	if (isSensor)
	{
		pbody->SetAsSensor(true);
		pbody->collision_listeners.add(this);
		pbody->check_point_num = check;
	}
	return obj;
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

int ModuleSceneIntro::Checkpoint(int current)
{
	LOG("Checking collision!!");
	switch (antiCheat)
	{
		case 0:
			if (current == 1)
				antiCheat = current;
			break;
		case 1:
			if (current == 2)
				antiCheat = current;
			break;
		case 2:
			if (current == 3)
				antiCheat = current;
			break;
		case 3:
			if (current == 4)
				antiCheat = current;
			break;
	}
	return antiCheat;
}

void ModuleSceneIntro::declareChecks()
{
	PhysBody3D* tmp;
	createPlatform({ 0.0f, 0.0f, 7.5f }, { 9.0f, 1.0f, 7.0f },NULL,true,0,true);
}