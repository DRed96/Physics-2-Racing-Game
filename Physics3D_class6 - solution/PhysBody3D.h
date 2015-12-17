#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

enum collisionStates
{
	COL_IN,
	COL_OUT
};

class btRigidBody;
class vec3;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	vec3 GetPos()const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void SetAsSensor(bool is_sensor);
	bool IsSensor() const;
	//provisional, to see if it works
	const btRigidBody* GetBody(){ return body; }
	//TOCHANGE: Make a struct checkpoint?
	int check_point_num;
private:
	btRigidBody* body = nullptr;
	bool is_sensor = false;

public:
	p2List<Module*> collision_listeners;
};
// =================================================
#endif // __PhysBody3D_H__