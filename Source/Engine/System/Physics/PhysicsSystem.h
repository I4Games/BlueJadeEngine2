#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#define GROUNDED_TOL 0.1f

class PhysicsRBody;

struct CollisionInfo {
	sf::Vector2f collisionNormal;
	float penetration;
};

class PhysicsSystem {
public:
	static PhysicsSystem* GetInstance();

	void AddRigidBody(PhysicsRBody* rigidBody);
	bool IsGrounded(PhysicsRBody* rigidBody);
	void Update(float dT);

	static float DotProduct(sf::Vector2f a, sf::Vector2f b);

private:
	static PhysicsSystem* Instance;

	//Members
	std::map<std::pair<PhysicsRBody*, PhysicsRBody*>, CollisionInfo> collisions;
	std::vector<PhysicsRBody*> rigidBodies;

	//Methods
	void IntegrateBodies(float dT);
	void CheckCollisions();
	void ResolveCollisions(float dT);
	void PositionalCorrection(std::pair<PhysicsRBody*, PhysicsRBody*> c);
};