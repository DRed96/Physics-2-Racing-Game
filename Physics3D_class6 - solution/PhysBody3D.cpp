#include "PhysBody3D.h"
#include "glmath.h"
#include "Bullet\src\btBulletDynamicsCommon.h"

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{
	body->setUserPointer(this);

}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	delete body;
}

// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);
}

void PhysBody3D::SetPos(vec3& vec)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(vec.x, vec.y, vec.z));
	body->setWorldTransform(t);
}

vec3 PhysBody3D::GetPos()const
{
	btTransform t = body->getWorldTransform();
	btVector3 btv3 = t.getOrigin();
	vec3 v3 = {btv3.getX(), btv3.getY(), btv3.getZ()};
	return v3;
}

vec3 PhysBody3D::GetSize()const
{
	btVector3 t = body->getCollisionShape()->getLocalScaling();
	vec3 vec;
	vec.x = t.m_floats[0];
	vec.y = t.m_floats[1];
	vec.z = t.m_floats[2];
	return vec;
}


// ---------------------------------------------------------
void PhysBody3D::SetAsSensor(bool is_sensor)
{
	if(this->is_sensor != is_sensor)
	{
		this->is_sensor = is_sensor;
		if(is_sensor == true)
			body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		else
			body->setCollisionFlags(body->getCollisionFlags() &~ btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
}

// ---------------------------------------------------------
bool PhysBody3D::IsSensor() const
{
	return is_sensor;
}