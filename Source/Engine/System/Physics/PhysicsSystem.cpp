#include "PhysicsSystem.h"
#include "../Scene/Component/PhysicsRBody.h"
#include "../Scene/GameObject.h"
#include <cstdlib>

PhysicsSystem* PhysicsSystem::Instance = 0;

PhysicsSystem* PhysicsSystem::GetInstance() {
	if (!Instance) {
		Instance = new PhysicsSystem();
	}
	return Instance;
}

void PhysicsSystem::AddRigidBody(PhysicsRBody* rigidBody) {
	rigidBodies.push_back(rigidBody);
}

bool PhysicsSystem::IsGrounded(PhysicsRBody* rigidBody) {
	for (std::vector<PhysicsRBody*>::iterator i = rigidBodies.begin(); i != rigidBodies.end(); ++i) {
		PhysicsRBody* rb = *(i);
		if (rb != rigidBody) {
			if (rigidBody->aabb.bLeft.x < rb->aabb.tRight.x
				&& rigidBody->aabb.tRight.x > rb->aabb.bLeft.x
				&& std::abs(rigidBody->aabb.bLeft.y - rb->aabb.tRight.y) <= GROUNDED_TOL) {
				if (std::abs(rigidBody->currentVelocity.y) < GROUNDED_TOL) {
					return true;
				}
			}
		}
	}

	return false;
}

void PhysicsSystem::Update(float dT) {
	CheckCollisions();
	ResolveCollisions(dT);
	IntegrateBodies(dT);
}

float PhysicsSystem::DotProduct(sf::Vector2f a, sf::Vector2f b) {
	return a.x*b.x + a.y*b.y;
}

void PhysicsSystem::IntegrateBodies(float dT) {
	for (std::vector<PhysicsRBody*>::iterator i = rigidBodies.begin(); i != rigidBodies.end(); ++i) {
		(*i)->Integrate(dT);
	}
}

void PhysicsSystem::CheckCollisions() {
	sf::Vector2f zero;

	for (int i = 0; i < rigidBodies.size() - 1; ++i) {
		PhysicsRBody* bodyA = rigidBodies[i];
		sf::Vector2f posA = bodyA->GetGameObject()->GetTransform().transformPoint(zero);

		for (int j = i; j < rigidBodies.size(); ++j) {
			PhysicsRBody* bodyB = rigidBodies[j];
			sf::Vector2f posB = bodyB->GetGameObject()->GetTransform().transformPoint(zero);
			if (bodyA != bodyB) {
				std::pair<PhysicsRBody*, PhysicsRBody*> pair = std::make_pair(bodyA, bodyB);
				CollisionInfo info;

				sf::Vector2f distance = posB - posA;

				sf::Vector2f halfSizeA = (bodyA->aabb.tRight - bodyA->aabb.bLeft) / 2.0f;
				sf::Vector2f halfSizeB = (bodyB->aabb.tRight - bodyB->aabb.bLeft) / 2.0f;

				sf::Vector2f gap(std::abs(distance.x), std::abs(distance.y));

				if (gap.x < 0 && gap.y < 0) {
					if (collisions.count(pair)) {
						collisions.erase(pair);
					}

					if (gap.x > gap.y) {
						if (distance.x > 0) {
							info.collisionNormal = Vector2f(1.0f, 0.0f);
						}
						else {
							info.collisionNormal = Vector2f(-1.0f, 0.0f);
						}
						info.penetration = gap.x;
					}
					else {
						if (distance.y > 0) {
							info.collisionNormal = Vector2f(0.0f, 1.0f);
						}
						else {
							info.collisionNormal = Vector2f(0.0f, -1.0f);
						}
						info.penetration = gap.y;
					}
					collisions[pair] = info;
				}
				else if (collisions.count(pair)) {
					collisions.erase(pair);
				}
			}
		}
	}
}

void PhysicsSystem::ResolveCollisions(float dT) {
	for (std::map<std::pair<PhysicsRBody*,PhysicsRBody*>, CollisionInfo>::iterator i = collisions.begin(); i != collisions.end(); ++i) {
		std::pair<PhysicsRBody*,PhysicsRBody*> p = (*i).first;

		float minBounce = std::min(p.first->bounciness, p.second->bounciness);
		float velAlongNormal = DotProduct(p.second->currentVelocity - p.first->currentVelocity,
			collisions[p].collisionNormal);
		if (velAlongNormal > 0) continue;
		
		float k = -(1 + minBounce) * velAlongNormal;
		float invMassA, invMassB;
		if (p.first->mass == 0) {
			invMassA = 0;
		}
		else {
			invMassA = 1 / p.first->mass;
		}
		if (p.second->mass == 0) {
			invMassB = 0;
		}
		else {
			invMassB = 1 / p.second->mass;
		}
		k /= invMassA + invMassB;

		sf::Vector2f impulse = k * collisions[p].collisionNormal;

		p.first->AddForce(-impulse / dT);
		p.second->AddForce(impulse / dT);

		if (std::abs(collisions[p].penetration) > 0.01f) {
			PositionalCorrection(p);
		}
	}
}

void PhysicsSystem::PositionalCorrection(std::pair<PhysicsRBody*,PhysicsRBody*> c) {
	float percent = 0.2f;

	float invMassA, invMassB;
	if (c.first->mass == 0) {
		invMassA = 0;
	}
	else {
		invMassA = 1 / c.first->mass;
	}
	if (c.second->mass == 0) {
		invMassB = 0;
	}
	else {
		invMassB = 1 / c.second->mass;
	}

	sf::Vector2f correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

	c.first->GetGameObject()->GetTransform().translate(-(invMassA * correction));
	c.second->GetGameObject()->GetTransform().translate(invMassB * correction);
}