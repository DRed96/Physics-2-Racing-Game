#include "Globals.h"
#include "Application.h"
#include "PhysBody3D.h"
#include "ModuleCamera3D.h"
#include "PhysVehicle3D.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 10.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 20.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{


	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0, 0, 0);
	float speed = 3.0f * dt;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 20.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;


	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;



	Position += newPos;
	Reference += newPos;

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		char degug = '\0';
	}
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		debug = !debug;
	}

	if (debug)
	{
		// Mouse motion ----------------

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;

			Position -= Reference;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				Y = rotate(Y, DeltaY, X);
				Z = rotate(Z, DeltaY, X);

				if (Y.y < 0.0f)
				{
					Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					Y = cross(Z, X);
				}
			}

			Position = Reference + Z * length(Position);
		}
	}
	else
	{
		btTransform transform = App->player->vehicle->GetBody()->getWorldTransform();
		btVector3 vehicle_pos = (transform.getOrigin());

		Reference = { vehicle_pos.getX(), vehicle_pos.getY(), vehicle_pos.getZ() };
		LookAt(Reference);

		btQuaternion* quat = &(transform.getRotation());
		float angle = quat->getAngle();

		btVector3 a = quat->getAxis();
		vec3 axis = { a.getX(), a.getY(), a.getZ() };

		if (quat != q)
		{
			X = rotate(X, angle, axis);
			Y = rotate(Y, angle, axis);
			Z = rotate(Z, angle, axis);
			q = quat;
		}

		vec3 c_pos = Reference + Z * CAMERA_DISTANCE;

		if (c_pos.y < Reference.y + CAMERA_HEIGHT)
		{
			c_pos.y = Reference.y + CAMERA_HEIGHT;
		}

		Position = c_pos;
	}
	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}


/*Bad code
	
	//float* matrix = new float[16];


	//vec3 targetPos = App->player->vehicle->GetPos();
	//vec3 cameraPos = targetPos;
	//cameraPos.y += 1.0f;

	/*
	
	if (App->player->isMoving)
	{
		vec3 vehicleDirection = App->player->vehicle->GetForwardVector();
		Position -= vehicleDirection * MAX_ACCELERATION * dt;
	}

	
	*

	Position.x = targetPos.x;
	Position.z = targetPos.z - 20;
	Position.y = targetPos.y + 5;

	/*
	Fer que la camera apunti cap on mira el cotxe en un pla, que si puja o baixa no s'alteri
	Trobar per quin valor s'ha de multiplicar la posició de la camera pq sigui constant. Potser la diferéncia de pixels que s'ha mogut
	Si la camera está X aprop del cotxe, es manté a aquella distancia.
	*
Look(Position, targetPos, true);

//------------------
vec3 vehicleDirection = App->player->vehicle->GetForwardVector();

Position.x *= vehicleDirection.x *-1;
Position.z *= vehicleDirection.z;
if (App->player->isMoving)
{


	//if ()
}
//------------------

		
*/
// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}
//HoI! Iterate the camera position to match the vehicle orientation!
void ModuleCamera3D::alignWithVehicle()
{
	/*CameraAngle - VehicleAngle*/
	App->player->vehicle->GetForwardVector();
//	for ()
}