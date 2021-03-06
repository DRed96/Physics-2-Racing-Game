#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "Timer.h"
ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(1, 1, 2);
	car.chassis_offset.Set(0, 1.5f, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 3.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.18f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.4f;
	float wheel_width = 0.3f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	

	timer = new Timer();

	finish = false;
	victory = false;


	vehicle->SetPos(15.0f, 26.0f, -25.0f);


	return true;
}



// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	delete(timer);

	return true;
}

update_status ModulePlayer::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	checkVictory(victory,finish);
	if(finish == true)
	{
		if (victory)
		{
			ret = UPDATE_STOP;
		}
		else
		{
			ret = UPDATE_STOP;
		}
	}
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			acceleration = MAX_ACCELERATION;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
		//	if (acceleration > 0.0f) //TOSOLVE 1
				acceleration = -MAX_ACCELERATION*2;
				
		}

		vehicle->ApplyEngineForce(acceleration);

		vehicle->Turn(turn);
		

		vehicle->Render();
		
		if (vehicle->GetPos().y < 2.5)
		{
			acceleration = acceleration = 0;
			brake = BRAKE_POWER;
			vehicle->Brake(brake);
			vehicle->SetPos(18.0f, 30.0f, -25.0f);
			vehicle->Brake(0.0);
		}
		char title[80];
		float seconds = (timer->Read() / 1000);
		float residue = ((timer->Read() % 1000));
		seconds += residue / 1000;
		
	
		sprintf_s(title, "%.1f Km/h Laps: %d Current Time: %.2f Time Limit %d", vehicle->GetKmh(), App->scene_intro->laps, seconds, (MAX_TIME/1000));
		App->window->SetTitle(title);
	return UPDATE_CONTINUE;
}




void ModulePlayer::checkVictory(bool& victory, bool& finish)
{
	Uint32 currentMs = timer->Read();
	if(currentMs <= MAX_TIME && App->scene_intro->laps >= MAX_LAPS)
	{
		victory = true;
		finish = true;
	}
	else if (currentMs >MAX_TIME)
	{
		finish = true;
	}
	return;
}

