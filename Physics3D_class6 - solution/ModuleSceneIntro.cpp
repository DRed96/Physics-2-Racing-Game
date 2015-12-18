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
	circuitConstruction();

	vec3 posPlane(0);
	posPlane.x = 0.0f;
	posPlane.y = 12.0f;
	posPlane.z = 0.0f;

	vec3 sizeTile(0);
	sizeTile.x = 4.0f;
	sizeTile.y = 0.5f;
	sizeTile.z = 7.0f;

	float angle = 45.0f;

	vec3 Rotation(0);
	Rotation.x = 0.0f;
	Rotation.y = 1.0f;
	Rotation.z = 0.0f;

	//TMP PLATFORM
	CreatePlaneC(vec3{ -2.5f, 25.0f, 0.0f }, sizeTile, 1, 1, Red);
	//Plane petit 1
	/*CreatePlane(posPlane, sizeTile, 1, 1);
	posPlane.x = 0.0f;
	posPlane.y = 8.0f;
	posPlane.z = 0.0f;
	//Plane petit 2
	CreatePlane(posPlane, sizeTile, 1, 1);*/
	
	
	//Grid
	/*CreatePlane(posPlane, sizeTile, 4, 4, angle, Rotation);
	posPlane.x = 0.0f;
	posPlane.y = 8.0f;
	posPlane.z = 0.0f;*/
	
	//Plane petit 2
	/*CreatePlane(posPlane, sizeTile,5,1);
	
	posPlane.x = 0.0f;
	posPlane.y = 14.0f;
	posPlane.z = 0.0f;*/
	
	//Grid
	vec3 finalPos = CreatePlane(posPlane, sizeTile, 6, 6, angle, Rotation);



	// Piramide ---------------
	vec3 highPyramidPos = posPlane;

	highPyramidPos.x += sizeTile.x / 4;
	highPyramidPos.y += 8.0f;
	highPyramidPos.z += sizeTile.z / 4;
	CreatePlane(highPyramidPos, sizeTile, 9, 9);

	vec3 mediumPyramidPos = highPyramidPos;
	mediumPyramidPos.x += sizeTile.x / 4;
	mediumPyramidPos.y += 8.0f;
	mediumPyramidPos.z += sizeTile.z / 4;
	CreatePlane(mediumPyramidPos, sizeTile, 7, 7);
	
	vec3 mediumLowPyramidPos = mediumPyramidPos;
	mediumLowPyramidPos.x += sizeTile.x / 4;
	mediumLowPyramidPos.y += 8.0f;
	mediumLowPyramidPos.z += sizeTile.z / 4;
	CreatePlane(mediumLowPyramidPos, sizeTile, 5, 5);

	vec3 lowPyramidPos = mediumLowPyramidPos;
	lowPyramidPos.x += sizeTile.x / 4;
	lowPyramidPos.y += 8.0f;
	lowPyramidPos.z += sizeTile.z / 4;
	CreatePlane(lowPyramidPos, sizeTile, 3, 3);

	//Pyramid Roads ---------------
		//Road 1
	vec3 proadVec1 = highPyramidPos;
	proadVec1.x += sizeTile.x* 1.5f;
	proadVec1.z -= sizeTile.z * 2.5f;
	//7,20,15.75
	CreatePlaneC({proadVec1.x , proadVec1.y, proadVec1.z}, sizeTile, 10,3,Red);
	//Road 2
	vec3 proadVec2 = lowPyramidPos;
	proadVec2.x -= (sizeTile.x* 4.0f);
	proadVec2.z += (sizeTile.z * 0.3);
	CreatePlaneC({ proadVec2.x , proadVec2.y, proadVec2.z }, sizeTile, 2, 10, Blue);
	//Pyramid Ramps ---------------
	
	vec3 rotation = {0.0f, 1.0f, 0.0f};


	//Ramp
	vec3 posRamp = mediumLowPyramidPos;
	posRamp.x += sizeTile.x/2;
	posRamp.z -= sizeTile.x/2;

	float angleRamp = 45.0f;
	vec3 axisRamp = {0.0f,50.0f,0.0f};
	CreatePlane(posRamp, sizeTile, angleRamp, axisRamp.x, axisRamp.y, axisRamp.z);
	
	


	//CreateCurve30(finalPos, sizeTile, 3, rotation);

	//Plane que funciona
	/*CreatePlane(posPlane, sizeTile, 4, 4);
	posPlane.x = 0.0f;
	posPlane.y = 14.0f;
	posPlane.z = 0.0f;*/
	

	vec3 posPyramid1;
	posPyramid1.x = -30.0f;
	posPyramid1.y = 1.6f;
	posPyramid1.z = 30.0f;
	
	vec3 sizePyramid1;
	sizePyramid1.x = 0.5f;
	sizePyramid1.y = 0.125f;
	sizePyramid1.z = 0.5f;

	//Pyramids
	int levels;
	levels = 6;

	CreatePyramidNormal(posPyramid1, sizePyramid1, levels);
	//CreateWeridSculpture(posPyramid1, sizePyramid1, levels);


	vec3 posSlowGrid1;
	posSlowGrid1.x = 15.0f;
	posSlowGrid1.y = 15.0f;
	posSlowGrid1.z = 15.0f;


	//CreateSlowGrid(posSlowGrid1, sizeTile, 4, 4, angle, Rotation);

	//Create Lap Counters
	laps = antiCheat = 0;
	declareChecks();

	vec3 MainRoad;
	MainRoad.x = 10.0f;
	MainRoad.y = 0.0f;
	MainRoad.z = 10.0f;

	vec3 SizeTile;

//	CreatePlane(MainRoad, );


	return ret;
}

void ModuleSceneIntro::CreatePyramidUpsideDown(vec3 posPyramid, vec3 sizeTile, int levels, float angle, vec3 Rotation)
{

	for (int i = 0; i <= levels; i++)
	{
		vec3 finalPos = CreatePlane(posPyramid, sizeTile, i, i, angle, Rotation);
		posPyramid.x -= sizeTile.x / 4;
		posPyramid.y += sizeTile.y;
		posPyramid.z -= sizeTile.z / 4;
	}

}

void ModuleSceneIntro::CreatePyramidNormal(vec3 posPyramid, vec3 sizeTile, int levels, float angle, vec3 Rotation)
{

	for (int i = levels; i > 0; i--)
	{
		vec3 finalPos = CreatePlane(posPyramid, sizeTile, i, i, angle, Rotation);
		posPyramid.x += sizeTile.x / 4;
		posPyramid.y += sizeTile.y;
		posPyramid.z += sizeTile.z / 4;
	}

}

void ModuleSceneIntro::CreateWeridSculpture(vec3 pos, vec3 sizeTile, int levels, float angle, vec3 Rotation)
{
	CreatePyramidUpsideDown(pos, sizeTile, levels);

	pos.x -= ((levels / 2) * sizeTile.x / 2);
	pos.y -= ((levels / 2) * sizeTile.y / 2);
	pos.z -= ((levels / 2) * sizeTile.z / 2);

	CreatePyramidNormal(pos, sizeTile, levels);


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

vec3 ModuleSceneIntro::CreatePlaneC(vec3 positionPlane, vec3 sizeTile, int rows, int cols, Color _color, float angle, vec3 rot )
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


			Cube* cube = createPlatformC((positionPlane + vec), sizeTile, pbody, angle, rot.x, rot.y, rot.z,false,-1,true, _color);
			if (angle != 0)
			{
				vec.x += nextRow / 2;
			}
			else
			{
				vec.x += nextRow;
			}

		}

		if (angle != 0)
		{
			vec.z += nextCol / 2;
			vec.x = positionPlane.x;
		}
		else
		{
			vec.z += nextCol / 2;
			vec.x = positionPlane.x;
		}


	}

	if (angle != 0)
	{
		vec.x -= nextCol / 2 * j;
		vec.z -= nextRow / 2 * j;
	}

	return (positionPlane + vec);
}


vec3 ModuleSceneIntro::CreateSlowGrid(vec3 positionPlane, vec3 sizeTile, int rows, int cols, float angle, vec3 rot)
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


			Cube* cube = createPlatform((positionPlane + vec), sizeTile, pbody, angle, rot.x, rot.y, rot.z);
			if (angle != 0)
			{
				vec.x += nextRow/2;
			}
			else
			{
				vec.x += nextRow;
			}

		}

		if (angle != 0)
		{
			vec.z += nextCol/2;
			vec.x = positionPlane.x;
		}
		else
		{
			vec.z += nextCol/2;
			vec.x = positionPlane.x;
		}


	}

	if (angle != 0)
	{
		vec.x -= nextCol / 2 * j;
		vec.z -= nextRow / 2 * j;
	}

	return (positionPlane + vec);


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

Cube * ModuleSceneIntro::createPlatformC(vec3 position, vec3 size, PhysBody3D *& pBody, float rot, float rot_x, float rot_y, float rot_z, bool isSensor, int check, bool isVisible, Color _col, float mass)
{
	Cube* obj = new Cube();

	obj->SetPos(position.x, position.y, position.z);
	obj->size = size;
	obj->SetRotation(rot, vec3{ rot_x, rot_y, rot_z });
	obj->color = _col;
	pBody = App->physics->AddBody(*obj, mass);

	/*If we don't add the obj to the List we'll only use it's coords
	* without saving it in the heap and it won't be rendered. */
	if (isVisible)
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
	createSensor({ 0.0f, 3.0f, 35.0f }, standardSize, tmp, 1, true);
	createSensor({ 0.0f, 3.0f, 45.0f }, standardSize, tmp, 2, true);
	createSensor({ 0.0f, 3.0f, 60.0f }, standardSize, tmp, 3, true);

	return;
}


void ModuleSceneIntro::circuitConstruction()
{

	/*cubes[0] = createPlatform({ 0.0f, 16.0f, 7.5f }, { 9.0f, 1.0f, 7.0f }, pbodys[0]);
	cubes[1] = createPlatform({ 0.0f, 13.0f, 16.0f }, { 9.0f, 1.0f, 7.0f }, pbodys[1]);
	cubes[2] = createPlatform({ 0.0f, 13.0f, 23.0f }, { 9.0f, 1.0f, 7.0f }, pbodys[2]);
	cubes[3] = createPlatform({ 0.0f, 13.0f, 30.0f }, { 9.0f, 1.0f, 7.0f }, pbodys[3]);
	cubes[4] = createPlatform({ 0.0f, 13.0f, 37.0f }, { 9.0f, 1.0f, 7.0f }, pbodys[4]);
	cubes[5] = createPlatform({ 0.0f, 13.0f, 44.0f }, { 9.0f, 1.0f, 7.0f }, pbodys[5]);
	cubes[6] = createPlatform({ 0.0f, 13.0f, 51.0f }, { 9.0f, 1.0f, 7.0f }, pbodys[6]);
	cubes[7] = createPlatform({ 0.0f, 13.0f, 58.0f }, { 9.0f, 1.0f, 7.0f }, pbodys[7]);
	cubes[8] = createPlatform({ 0.0f, 13.0f, 65.0f }, { 6.0f, 1.0f, 7.0f }, pbodys[8]);
	cubes[9] = createPlatform({ 0.0f, 13.0f, 72.0f }, { 6.0f, 1.0f, 7.0f }, pbodys[9]);
	cubes[10] = createPlatform({ 0.0f, 13.0f, 79.0f }, { 6.0f, 1.0f, 7.0f }, pbodys[10]);
	cubes[11] = createPlatform({ 0.0f, 13.0f, 86.0f }, { 6.0f, 1.0f, 7.0f }, pbodys[11]);
	cubes[12] = createPlatform({ 0.0f, 13.0f, 93.0f }, { 6.0f, 1.0f, 7.0f }, pbodys[12]);
	cubes[13] = createPlatform({ 0.0f, 13.0f, 100.0f }, { 6.0f, 1.0f, 7.0f }, pbodys[13]);
	cubes[14] = createPlatform({ 0.0f, 13.0f, 107.0f }, { 6.0f, 1.0f, 7.0f }, pbodys[14]);



	AttachPlatform(pbodys[0], pbodys[1], cubes[0], cubes[1], RIGHT);
	AttachPlatform(pbodys[0], pbodys[2], cubes[0], cubes[2], RIGHT);
	AttachPlatform(pbodys[0], pbodys[3], cubes[0], cubes[3], RIGHT);
	AttachPlatform(pbodys[0], pbodys[4], cubes[0], cubes[4], RIGHT);
	AttachPlatform(pbodys[0], pbodys[5], cubes[0], cubes[5], RIGHT);
	AttachPlatform(pbodys[0], pbodys[6], cubes[0], cubes[6], RIGHT);
	AttachPlatform(pbodys[0], pbodys[7], cubes[6], cubes[7], RIGHT);
	AttachPlatform(pbodys[0], pbodys[8], cubes[7], cubes[8], RIGHT);
	AttachPlatform(pbodys[0], pbodys[9], cubes[8], cubes[9], RIGHT);
	AttachPlatform(pbodys[0], pbodys[10], cubes[9], cubes[10], RIGHT);
	AttachPlatform(pbodys[0], pbodys[11], cubes[10], cubes[11], RIGHT);

	*/
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

