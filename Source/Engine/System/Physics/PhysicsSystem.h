#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#define GROUNDED_TOL 0.1f
#define TIME_STEP 0.02f

class PhysicsRBody;

enum CollisionSide {
	Up, Down, Left, Right, None
};

struct CollisionInfo {
	sf::Vector2f collisionNormal;
	float penetration;
};

class PhysicsSystem {
public:
	static PhysicsSystem* GetInstance();
	static float TimeStep;
	const static sf::Vector2f DEFAULT_GRAVITY;

	void AddRigidBody(PhysicsRBody* rigidBody);
	void RemoveRigidBody(PhysicsRBody* rigidBody);
	bool IsGrounded(PhysicsRBody* rigidBody);
	void Update(float dT);

	static float DotProduct(sf::Vector2f a, sf::Vector2f b);

private:
	static PhysicsSystem* Instance;

	//Members
	std::map<std::pair<PhysicsRBody*, PhysicsRBody*>, CollisionInfo> collisions;
	std::vector<PhysicsRBody*> rigidBodies;
	float curTime = 0.f;

	//Methods
	void IntegrateBodies(float dT);
	void CheckCollisions();
	void ResolveCollisions(float dT);
	void PositionalCorrection(std::pair<PhysicsRBody*, PhysicsRBody*> c);
};