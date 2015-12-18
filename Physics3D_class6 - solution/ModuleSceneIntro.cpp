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

	PhysBody3D* tmp = nullptr;
	App->camera->Move(vec3(5.0f, 20.0f, 5.0f));
	App->camera->LookAt(vec3(0.0f, 15.0f, 10.0f));

	standardSize = { 9.0f, 1.0f, 7.0f };


	vec3 posPlane(0);
	posPlane.x = 0.0f;
	posPlane.y = 12.0f;
	posPlane.z = 0.0f;

	vec3 sizeTile(0);
	sizeTile.x = 4.0f;
	sizeTile.y = 0.5f;
	sizeTile.z = 7.0f;
	

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
		CreatePlaneC({proadVec1.x , proadVec1.y, proadVec1.z}, sizeTile, 9,3,Red);

	//Save Checkpoint coords
	checkpoints[0] = proadVec1;

	//Road 2
	vec3 proadVec2 = lowPyramidPos;
	proadVec2.x += (sizeTile.x/2 * 3);
	proadVec2.z += (sizeTile.z * 0.3);
	CreatePlaneC({ proadVec2.x , proadVec2.y, proadVec2.z }, sizeTile, 2, 30, Blue);

	//Road 3
	
	vec3 proadVec3 = proadVec2;
	proadVec3.x += (sizeTile.x/2 * 30);

	CreatePlaneC(proadVec3, sizeTile, 7, 4, Blue);

	vec3 bumpPos = proadVec3;
	bumpPos.x += (sizeTile.y / 2 * 3);
	bumpPos.y += (sizeTile.y);
	bumpPos.z += (sizeTile.z / 2 * 3);
	
	CreatePyramidNormal(bumpPos, { 3.0f, 0.75f, 3.0f }, 3);

	vec3 proadVec4 = proadVec3;
	proadVec4.z += (sizeTile.z / 2 * 2);
	proadVec4.y -= (sizeTile.z / 2);

	//CreatePlaneC(proadVec4, sizeTile, 20, 3, Blue);

	vec3 proadVec5 = proadVec4;
	proadVec5.x += (sizeTile.x / 2 * 3);


	CreatePlaneC(proadVec5, sizeTile, 20, 3, Blue);


	vec3 pRamp4 = proadVec4;
	pRamp4.x += (57.0f);
	pRamp4.z += (69.0f + 10.0f);
	//pRamp4.z += 1.75;
	pRamp4.y -= 10.0f;
	createPlatformC({ pRamp4.x, pRamp4.y, pRamp4.z }, { 50.0f, 0.5f, 15.0f }, tmp, 23.0f, 0.0f, 0.0f, 1.0f, false, -1, true, Blue);


	vec3 wall1 = proadVec5;
	wall1.x += (80.0f);
	wall1.z += (85.0f);
	//pRamp4.z += 1.75;
	wall1.y += 2.0f;
	createPlatformC({ wall1.x, wall1.y, wall1.z }, { 10.0f, 3.0f, 1.0f }, tmp, 0.0f, 0.0f, 0.0f, 0.0f, false, -1, true, Blue);




	vec3 roadToWin = pRamp4;
	roadToWin.x -= (39.0f);
	//roadToWin.z += (85.0f);
	roadToWin.z -= 30.0f;
	roadToWin.y -= 20.0f/2;
	createPlatformC({ roadToWin.x, roadToWin.y, roadToWin.z }, { 35.0f, 1.0f, 70.0f }, tmp, 0.0f, 0.0f, 0.0f, 0.0f, false, -1, true, White);





	vec3 bump1Pos = roadToWin;
	bump1Pos.x -= 47.0f;
	bump1Pos.y += 1.0f;
	bump1Pos.z -= 20.0f;


	CreatePyramidNormal(bump1Pos, { 3.0f, 0.75f, 3.0f }, 3);


	vec3 bump2Pos = roadToWin;
	bump2Pos.x -= 50.0f;
	bump2Pos.y += 1.0f;
	bump2Pos.z -= 25.0f;


	CreatePyramidNormal(bump2Pos, { 3.0f, 0.75f, 3.0f }, 3);


	vec3 bump3Pos = roadToWin;
	bump3Pos.x -= 40.0f;
	bump3Pos.y += 1.0f;
	bump3Pos.z -= 30.0f;


	CreatePyramidNormal(bump3Pos, { 3.0f, 0.75f, 3.0f }, 3);


	vec3 bump4Pos = roadToWin;
	bump4Pos.x -= 49.0f;
	bump4Pos.y += 1.0f;
	bump4Pos.z -= 40.0f;


	CreatePyramidNormal(bump4Pos, { 3.0f, 0.75f, 3.0f }, 3);









	checkpoints[2] = roadToWin;


	//Connects with the beggining
	vec3 proadVec6 = proadVec1;
	proadVec6.x += ((sizeTile.x / 2) * 3.0f);
	CreatePlaneC(proadVec6, sizeTile, 3, 16, Blue);
	
	//Road3
	vec3 proadVec7 = proadVec6;
	proadVec7.x += ((sizeTile.x / 2) * 10.0f);
	proadVec7.z += ((sizeTile.z / 2) * 2.0f);
	CreatePlaneC(proadVec7, sizeTile, 12, 6, White);
	
	//Pyramid Ramps ---------------
	
	//Base&Ramp1
	vec3 pBase1 = highPyramidPos;
	pBase1.x += (sizeTile.x *2);
	pBase1.z += (sizeTile.z * 4.5);

	vec3 pBase2 = pBase1;

	pBase1.x -= (sizeTile.x * 1.5);
	CreatePlaneC({ pBase1.x , pBase1.y, pBase1.z },  sizeTile , 8, 9, Red);
	
	vec3 pRamp1 = pBase1;
	pRamp1.x += (sizeTile.x * 2);
	pRamp1.z += (sizeTile.z * 3.43);
	pRamp1.y += (sizeTile.x * 0.8);
	createPlatformC({ pRamp1.x , pRamp1.y, pRamp1.z }, {6.0f,0.5f,15.0f}, tmp, 40.0f, 1.0f, 0.0f, 0.0f, false, -1, true, Blue);

	//Base&Ramp2
	pBase2.x += (sizeTile.x * 2);
	pBase2.z -= (sizeTile.z/2 * 9);
	pBase2.x -= 1.0f;
	pBase2.y += 8.0f;
	CreatePlaneC({ pBase2.x , pBase2.y, pBase2.z }, sizeTile, 8, 9, Red);

	vec3 pRamp2 = pBase2;
	pRamp2.x += ((sizeTile.x)  * 3.65);
	pRamp2.z += ((sizeTile.z / 2) *2 );
	pRamp2.z += 1.75;
	pRamp2.y += 4.0f;
	createPlatformC({ pRamp2.x , pRamp2.y, pRamp2.z }, { 15.0f ,0.5f,6.0f }, tmp, -33.0f, 0.0f, 0.0f, 1.0f, false, -1, true, Blue);
	//Base&Ramp3
	vec3 pBase3 = mediumLowPyramidPos;

	//Save Checkpoint coords
	checkpoints[1] = pBase3;

	pBase3.z += (sizeTile.z / 4) * 10;
	CreatePlaneC({ pBase3.x , pBase3.y, pBase3.z }, sizeTile, 8, 5, Red);
	
	vec3 pRamp3 = pBase3;
	pRamp3.y += 4.0f;
	pRamp3.z += ((sizeTile.z / 2) * 4);
	pRamp3.z -= 1;
	pRamp3.x += 6.5f;
	createPlatformC({ pRamp3.x , pRamp3.y, pRamp3.z }, { 4.0f ,0.5f,12.0f }, tmp, 43.0f, 1.0f, 0.0f, 0.0f, false, -1, true, Blue);



	//Other Stuff----------
	vec3 rotation = {0.0f, 1.0f, 0.0f};
	//Ramp
	vec3 sizeTileRamp = sizeTile;
	vec3 posRamp = mediumLowPyramidPos;
	posRamp.x += sizeTile.x/2;
	posRamp.z -= sizeTile.x/2;

	sizeTileRamp.z = 20;
	PhysBody3D* rampBody;
	float angleRamp = -45.0f;
	vec3 axisRamp = {1.0f,0.0f,0.0f};
	createPlatform(posRamp, sizeTileRamp, rampBody, angleRamp, axisRamp.x, axisRamp.y, axisRamp.z);
	
	


	//CreateCurve30(finalPos, sizeTile, 3, rotation);


	vec3 posPyramid1;
	posPyramid1.x = -30.0f;
	posPyramid1.y = 0.0f;
	posPyramid1.z = 30.0f;
	
	vec3 sizePyramid1;
	sizePyramid1.x = 5.0f;
	sizePyramid1.y = 5.0f;
	sizePyramid1.z = 5.0f;

	//Pyramids
	int levels;
	levels = 6;

	



	vec3 posSlowGrid1;
	posSlowGrid1.x = 15.0f;
	posSlowGrid1.y = 15.0f;
	posSlowGrid1.z = 15.0f;


	//Create Lap Counters
	laps = antiCheat = 0;

	vec3 MainRoad;
	MainRoad.x = 10.0f;
	MainRoad.y = 0.0f;
	MainRoad.z = 10.0f;

	vec3 SizeTile;

	//Checkpoints
	vec3 current = checkpoints[0];
	
	
	current.x += 11.0f;
	current.y += (2.05f);
	current.z = ((SizeTile.x / 2) * 2);

	vec3 standardCheckSize = { 15.0f, 0.5f, 9.0f };

	CreateSensor(current, standardCheckSize, tmp, 0, false);

	current = checkpoints[1];
	current.x += 11.0f;
	current.y += (2.55f);
	current.z += (37.55f);
	CreateSensor(current, standardCheckSize, tmp, 1, false);

	current = checkpoints[2];

	current.y += (2.55f);
	standardCheckSize.x *= 4;
	CreateSensor(current, standardCheckSize, tmp, 2, false);

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

Cube * ModuleSceneIntro::CreateSensor(vec3 position, vec3 size, PhysBody3D *& pBody, int check, bool isVisible, float rot, float rot_x, float rot_y, float rot_z, float mass)
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


