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

	//Heavy Loading function
	createAllElements();
	/*
	
	PhysBody3D* pbody0 = NULL;
	PhysBody3D* pbody1 = NULL;
	PhysBody3D* pbody2 = NULL;
	PhysBody3D* pbody3 = NULL;
	PhysBody3D* pbody4 = NULL;
	PhysBody3D* pbody5 = NULL;
	PhysBody3D* pbody6 = NULL;
	PhysBody3D* pbody7 = NULL;
	PhysBody3D* pbody8 = NULL;
	PhysBody3D* pbody9 = NULL;
	PhysBody3D* pbody10 = NULL;
	PhysBody3D* pbody11 = NULL;
	PhysBody3D* pbody12 = NULL;
	PhysBody3D* pbody13 = NULL;
	PhysBody3D* pbody14 = NULL;
	PhysBody3D* pbody15 = NULL;


	Cube* cube0;
	Cube* cube1;
	Cube* cube2;
	Cube* cube3;
	Cube* cube4;
	Cube* cube5;
	Cube* cube6;
	Cube* cube7;
	Cube* cube8;
	Cube* cube9;
	Cube* cube10;
	Cube* cube11;
	Cube* cube12;
	Cube* cube13;
	Cube* cube14;
	Cube* cube15;*/

		/*
	cube0 = createPlatform({ 0.0f, 16.0f, 7.5f }, { 9.0f, 1.0f, 7.0f },  pbody0);
	cube1 = createPlatform({ 0.0f, 13.0f, 16.0f }, { 9.0f, 1.0f, 7.0f }, pbody1);
	
	cube2 = createPlatform({ 0.0f, 13.0f, 23.0f }, { 9.0f, 1.0f, 7.0f }, pbody2);
	
	cube3 = createPlatform({ 0.0f, 13.0f, 30.0f }, { 9.0f, 1.0f, 7.0f }, pbody3);
																		 
	cube4 = createPlatform({ 0.0f, 13.0f, 37.0f }, { 9.0f, 1.0f, 7.0f }, pbody4);
																		 
	cube5 = createPlatform({ 0.0f, 13.0f, 44.0f }, { 9.0f, 1.0f, 7.0f }, pbody5);
																		 
	cube6 = createPlatform({ 0.0f, 13.0f, 51.0f }, { 9.0f, 1.0f, 7.0f }, pbody6);
																		 
	cube7 = createPlatform({ 0.0f, 13.0f, 58.0f }, { 9.0f, 1.0f, 7.0f }, pbody7);
																		 
	cube8 = createPlatform({ 0.0f, 13.0f, 65.0f }, { 6.0f, 1.0f, 7.0f }, pbody8);
																		 
	cube9 = createPlatform({ 0.0f, 13.0f, 72.0f }, { 6.0f, 1.0f, 7.0f }, pbody9);
	
	cube10 = createPlatform({ 0.0f, 13.0f, 79.0f }, { 6.0f, 1.0f, 7.0f }, pbody10);
	
	cube11 = createPlatform({ 0.0f, 13.0f, 86.0f }, { 6.0f, 1.0f, 7.0f }, pbody11);
	
	cube12 = createPlatform({ 0.0f, 13.0f, 93.0f }, { 6.0f, 1.0f, 7.0f }, pbody12);
	
	cube13 = createPlatform({ 0.0f, 13.0f, 100.0f }, { 6.0f, 1.0f, 7.0f },pbody13);
	
	cube14 = createPlatform({ 0.0f, 13.0f, 107.0f }, { 6.0f, 1.0f, 7.0f },pbody14);

	

	AttachPlatform(pbody0, pbody1, cube0, cube1, RIGHT);
	AttachPlatform(pbody0, pbody2, cube0, cube2, LEFT);
	AttachPlatform(pbody0, pbody3, cube0, cube3, BACK);
	AttachPlatform(pbody0, pbody4, cube0, cube4, FRONT);
	AttachPlatform(pbody0, pbody5, cube0, cube5, BELOW);
	AttachPlatform(pbody0, pbody6, cube0, cube6, TOP);
	AttachPlatform(pbody6, pbody7, cube6, cube7, TOP);
	AttachPlatform(pbody7, pbody8, cube7, cube8, TOP);
	AttachPlatform(pbody8, pbody9, cube8, cube9, TOP);
	AttachPlatform(pbody9, pbody10, cube9, cube10, TOP);
	AttachPlatform(pbody10, pbody11, cube10, cube11, TOP);
	*/

	circuitConstruction();
	vec3 posPlane(0);
	posPlane.x = 0.0f;
	posPlane.y = 12.0f;
	posPlane.z = 0.0f;

	vec3 sizeTile(0);
	sizeTile.x = 3.0f;
	sizeTile.y = 3.0f;
	sizeTile.z = 3.0f;

	float angle = 45.0f;

	vec3 Rotation(0);
	Rotation.x = 0.0f;
	Rotation.y = 1.0f;
	Rotation.z = 0.0f;

	/*
	CreatePlane(posPlane, sizeTile, 1, 1);
	posPlane.x = 0.0f;
	posPlane.y = 5.0f;
	posPlane.z = 0.0f;
	CreatePlane(posPlane, sizeTile, 2, 2);
	posPlane.x = 0.0f;
	posPlane.y = 8.0f;
	posPlane.z = 0.0f;
	CreatePlane(posPlane, sizeTile, 3, 3);
	posPlane.x = 0.0f;
	posPlane.y = 11.0f;
	posPlane.z = 0.0f;
	
	CreatePlane(posPlane, sizeTile, 4, 4);*/
	/*
	posPlane.x = 0.0f;
	posPlane.y = 14.0f;
	posPlane.z = 0.0f;*/
		//vec3 finalPos = CreatePlane(posPlane, sizeTile, 6, 6, angle, Rotation);
	/*posPlane.x += sizeTile.x/4;
	posPlane.y = 17.0f;
	posPlane.z += sizeTile.z/4;
	CreatePlane(posPlane, sizeTile, 5, 5);
	posPlane.x += sizeTile.x / 4;
	posPlane.y = 20.0f;
	posPlane.z += sizeTile.z / 4;
	CreatePlane(posPlane, sizeTile, 4, 4);
	posPlane.x += sizeTile.x / 4;
	posPlane.y = 23.0f;
	posPlane.z += sizeTile.z / 4;
	CreatePlane(posPlane, sizeTile, 3, 3);
	posPlane.x += sizeTile.x / 4;
	posPlane.y = 26.0f;
	posPlane.z += sizeTile.z / 4;
	CreatePlane(posPlane, sizeTile, 2, 2);
	*/
	laps = antiCheat = 0;
	declareChecks();
	vec3 rotation = {0.0f, 1.0f, 0.0f};

	//CreateCurve30(finalPos, sizeTile, 3, rotation);

	return ret;
}

void ModuleSceneIntro::CreateCurve45(vec3 pos, vec3 sizeTile, int rows, float angle)
{
		

}

void ModuleSceneIntro::CreateCurve30(vec3 pos, vec3 sizeTile, int rows, vec3 rot)
{
	float arc = 30.0f / 3;

	vec3 orientation = CreatePlane(pos, sizeTile, 1, rows, arc, rot);
	orientation = CreatePlane(orientation, sizeTile, 1, rows, arc*2, rot);
	orientation = CreatePlane(orientation, sizeTile, 1, rows, arc*3, rot);

}



vec3 ModuleSceneIntro::CreatePlane(vec3 positionPlane, vec3 sizeTile, int rows, int cols, float angle, vec3 rot)
{
	vec3 vec = positionPlane;
	vec.y = 0.0f;
	float nextRow = sizeTile.x;
	float nextCol = sizeTile.z;
	int i, j;

	vec3 posTile = positionPlane;

	for (i = 0; i < rows; i++)
	{
	
		for (j = 0; j < cols; j++)
		{
			PhysBody3D* pbody;
			

			Cube* cube = createPlatform((positionPlane + vec ), sizeTile, pbody, angle, rot.x, rot.y, rot.z);
			if (angle != 0)
			{
				vec.z += nextCol/2;
				vec.x += nextRow/2;
			}
			else
			{
				vec.x += nextRow;
			}
				
		}

		if (angle != 0)
		{
			vec.z = positionPlane.z;
			vec.z += (nextCol * i)/2;
			vec.x =  -(nextRow * i)/2;
		}
		else
		{
			vec.z += nextCol;
			vec.x = positionPlane.x;

		}
		
	
	}

	if (angle != 0)
	{
		vec.x -= nextCol/2 * j;
		vec.z -= nextRow/2 * j;
	}

	return (positionPlane+vec);


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
	if (body1->check_point_num >= 0)
	{
		Checkpoint(body1->check_point_num);
	}
	if (body2->check_point_num >= 0)
	{
		Checkpoint(body2->check_point_num);
	}
	
}

//Platform Factory

Cube* ModuleSceneIntro::createPlatform(vec3 position, vec3 size, PhysBody3D*& pBody, float rot, float rot_x, float rot_y, float rot_z, bool isSensor, int check, bool isVisible, float mass)
{
	Cube* obj = new Cube();

	obj->SetPos(position.x, position.y, position.z);
	obj->size = size;
	obj->SetRotation(rot, vec3{ rot_x, rot_y, rot_z });

	pBody = App->physics->AddBody(*obj, mass);

	/*If we don't add the obj to the List we'll only use it's coords 
	* without saving it in the heap and it won't be rendered. */
	if(isVisible)
		platforms.add(obj);
	if (isSensor)
	{
		pBody->SetAsSensor(true);
		pBody->collision_listeners.add(this);
		pBody->check_point_num = check;
	}
	return obj;
}

Cube * ModuleSceneIntro::createSensor(vec3 position, vec3 size, PhysBody3D *& pBody, int check, bool isVisible, float rot, float rot_x, float rot_y, float rot_z, float mass)
{
	
	return createPlatform(position, size, pBody, rot, rot_x, rot_y, rot_z, true, check, isVisible, mass);
}

bool ModuleSceneIntro::AttachPlatform(PhysBody3D* obj, PhysBody3D* obj2, Cube* cObj1, Cube* cObj2, Orientation orientation)
{
	bool ret = false;
	float* obj1Transform;
	float* transformObj1 = cObj1->transform.M;
	float* transformObj2 = cObj2->transform.M;


	vec3 posObj2 = obj2->GetPos();
	vec3 sizeObj2 = obj2->GetSize();
	/*
	vec3 posObj = obj->GetPos();
	vec3 sizeObj = obj->GetSize();
	*/

	vec3 posObj;
	posObj.x = transformObj1[12];
	posObj.y = transformObj1[13];
	posObj.z = transformObj1[14];

	vec3 sizeObj = cObj1->GetSize();



	vec3 right = { -sizeObj.x , 0.0f, 0.0f};
	vec3 back = { 0.0f, 0.0f, -sizeObj.z };
	vec3 left = { sizeObj.x, 0.0f, 0.0f };
	vec3 front = { 0.0f, 0.0f, sizeObj.z};
	vec3 below = { 0.0f, -sizeObj.y, 0.0f };
	vec3 top = { 0.0f, sizeObj.y, 0.0f };


	switch (orientation)
	{
	case 0: 
		obj2->SetPos(posObj + right);
		cObj2->transform.M[12] = posObj.x + right.x;
		cObj2->transform.M[13] = posObj.y;
		cObj2->transform.M[14] = posObj.z;
		break;
	case 1:
		obj2->SetPos(posObj + back);
		cObj2->transform.M[12] = posObj.x;
		cObj2->transform.M[13] = posObj.y;
		cObj2->transform.M[14] = posObj.z + back.z;
		break;
	case 2:
		obj2->SetPos(posObj + left);
		cObj2->transform.M[12] = posObj.x + left.x;
		cObj2->transform.M[13] = posObj.y;
		cObj2->transform.M[14] = posObj.z;
		break;
	case 3:
		obj2->SetPos(posObj + front);
		cObj2->transform.M[12] = posObj.x;
		cObj2->transform.M[13] = posObj.y;
		cObj2->transform.M[14] = posObj.z + front.z;
		break;
	case 4:
		obj2->SetPos(posObj + below);
		cObj2->transform.M[12] = posObj.x;
		cObj2->transform.M[13] = posObj.y + below.y;
		cObj2->transform.M[14] = posObj.z;
		break;
	case 5:
		obj2->SetPos(posObj + top);
		cObj2->transform.M[12] = posObj.x;
		cObj2->transform.M[13] = posObj.y + top.y;
		cObj2->transform.M[14] = posObj.z;
		break;
	
	}


	return ret;
}

int ModuleSceneIntro::Checkpoint(int current)
{
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
			if (current == 0)
			{
				antiCheat = current;
				laps++;
			}
			break;
	}
	LOG("%d", antiCheat);
	return antiCheat;
}

void ModuleSceneIntro::declareChecks()
{
	PhysBody3D* tmp;

	createSensor({ 0.0f, 3.0f, 20.0f }, standardSize,tmp, 0,true);
	sensors.add(tmp);
	createSensor({ 0.0f, 3.0f, 35.0f }, standardSize, tmp, 1, true);
	sensors.add(tmp);
	createSensor({ 0.0f, 3.0f, 45.0f }, standardSize, tmp, 2, true);
	sensors.add(tmp);
	createSensor({ 0.0f, 3.0f, 60.0f }, standardSize, tmp, 3, true);
	sensors.add(tmp);
}

void ModuleSceneIntro::circuitConstruction()
{
	//cubes.;
	/*PhysBody3D* pb0 = NULL;
	PhysBody3D* pb1 = NULL;
	PhysBody3D* pb2 = NULL;
	PhysBody3D* pb3 = NULL;
	PhysBody3D* pb4 = NULL;
	PhysBody3D* pb5 = NULL;
	PhysBody3D* pb6 = NULL;
	PhysBody3D* pb7 = NULL;
	PhysBody3D* pb8 = NULL;
	PhysBody3D* pb9 = NULL;
	PhysBody3D* pb10 = NULL;
	PhysBody3D* pb11 = NULL;
	PhysBody3D* pb12 = NULL;
	PhysBody3D* pb13 = NULL;
	PhysBody3D* pb14 = NULL;
	PhysBody3D* pb15 = NULL;


	Cube* c16;
	Cube* c17;
	Cube* c18;
	Cube* c19;
	Cube* c20;
	Cube* c21;
	Cube* c22;
	Cube* c23;
	Cube* c24;
	Cube* c25;
	Cube* c26;
	Cube* c27;
	Cube* c28;
	Cube* c29;
	Cube* c30;
	Cube* c31;*/

	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
}

void ModuleSceneIntro::createAllElements()
{
	//Allocate Cubes
	for (int i = 0; i++, i <= CUBE_LIMIT;)
	{
		Cube* tmp = NULL;
		cubes.PushBack(tmp);
	}
	for (int i2 = 0; i2++, i2 <= BODY_LIMIT;)
	{
		PhysBody3D* tmp= NULL;
		pbodies.PushBack(tmp);
	}
	//Allocate PhysBodyes
}
/*
cube0 = createPlatform({ 0.0f, 16.0f, 7.5f }, { 9.0f, 1.0f, 7.0f },  pbody0);
cube1 = createPlatform({ 0.0f, 13.0f, 16.0f }, { 9.0f, 1.0f, 7.0f }, pbody1);

cube2 = createPlatform({ 0.0f, 13.0f, 23.0f }, { 9.0f, 1.0f, 7.0f }, pbody2);

cube3 = createPlatform({ 0.0f, 13.0f, 30.0f }, { 9.0f, 1.0f, 7.0f }, pbody3);

cube4 = createPlatform({ 0.0f, 13.0f, 37.0f }, { 9.0f, 1.0f, 7.0f }, pbody4);

cube5 = createPlatform({ 0.0f, 13.0f, 44.0f }, { 9.0f, 1.0f, 7.0f }, pbody5);

cube6 = createPlatform({ 0.0f, 13.0f, 51.0f }, { 9.0f, 1.0f, 7.0f }, pbody6);

cube7 = createPlatform({ 0.0f, 13.0f, 58.0f }, { 9.0f, 1.0f, 7.0f }, pbody7);

cube8 = createPlatform({ 0.0f, 13.0f, 65.0f }, { 6.0f, 1.0f, 7.0f }, pbody8);

cube9 = createPlatform({ 0.0f, 13.0f, 72.0f }, { 6.0f, 1.0f, 7.0f }, pbody9);

cube10 = createPlatform({ 0.0f, 13.0f, 79.0f }, { 6.0f, 1.0f, 7.0f }, pbody10);

cube11 = createPlatform({ 0.0f, 13.0f, 86.0f }, { 6.0f, 1.0f, 7.0f }, pbody11);

cube12 = createPlatform({ 0.0f, 13.0f, 93.0f }, { 6.0f, 1.0f, 7.0f }, pbody12);

cube13 = createPlatform({ 0.0f, 13.0f, 100.0f }, { 6.0f, 1.0f, 7.0f },pbody13);

cube14 = createPlatform({ 0.0f, 13.0f, 107.0f }, { 6.0f, 1.0f, 7.0f },pbody14);



AttachPlatform(pbody0, pbody1, cube0, cube1, RIGHT);
AttachPlatform(pbody0, pbody2, cube0, cube2, LEFT);
AttachPlatform(pbody0, pbody3, cube0, cube3, BACK);
AttachPlatform(pbody0, pbody4, cube0, cube4, FRONT);
AttachPlatform(pbody0, pbody5, cube0, cube5, BELOW);
AttachPlatform(pbody0, pbody6, cube0, cube6, TOP);
AttachPlatform(pbody6, pbody7, cube6, cube7, TOP);
AttachPlatform(pbody7, pbody8, cube7, cube8, TOP);
AttachPlatform(pbody8, pbody9, cube8, cube9, TOP);
AttachPlatform(pbody9, pbody10, cube9, cube10, TOP);
AttachPlatform(pbody10, pbody11, cube10, cube11, TOP);
*/