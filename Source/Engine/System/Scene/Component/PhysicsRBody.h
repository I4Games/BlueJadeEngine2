#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.h"

#define DEFAULT_MASS 1.0f
#define DEFAULT_BOUNCINESS 1.0f
#define MAX_VELOCITY_X 10.0f
#define MAX_VELOCITY_Y 10.0f

class PhysicsSystem;

struct AABB {
	sf::Vector2f bLeft;
	sf::Vector2f tRight;
};

class PhysicsRBody : public BaseComponent {
public:
	//Members

	float mass = DEFAULT_MASS;
	float bounciness = DEFAULT_BOUNCINESS;
	bool obeysGravity = true;
	sf::Vector2f gravity;

	sf::Vector2f currentVelocity;
	sf::Vector2f maxVelocity;

	bool grounded;
	bool canCollide;

	AABB aabb;

	//Methods
	PhysicsRBody();
	~PhysicsRBody();

	void AddForce(sf::Vector2f force);
	void Stop();
	bool IsGrounded();
	void Integrate(float dT);

	//BaseComponent
	virtual void Update(float msec) {}
	virtual void Init();
	virtual ComponentType GetComponentType();

private:
	//Members
	sf::Vector2f totalForces;
	PhysicsSystem* engine;

	//Methods
	void SetAABB();
};