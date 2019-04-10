#include "PhysicsSystem.h"
#include "../Scene/Component/PhysicsRBody.h"
#include "../Scene/GameObject.h"
#include <cstdlib>

#include "../Graphics/GraphicsSystem.h"

PhysicsSystem* PhysicsSystem::Instance = 0;

float PhysicsSystem::TimeStep = TIME_STEP;

PhysicsSystem* PhysicsSystem::GetInstance() {
	if (!Instance) {
		Instance = new PhysicsSystem();
	}
	return Instance;
}

const sf::Vector2f PhysicsSystem::DEFAULT_GRAVITY = sf::Vector2f(0.f, 90.f);

void PhysicsSystem::AddRigidBody(PhysicsRBody* rigidBody) {
	rigidBodies.push_back(rigidBody);
}

void PhysicsSystem::RemoveRigidBody(PhysicsRBody* rigidBody) {
	rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), rigidBody), rigidBodies.end());
}

bool PhysicsSystem::IsGrounded(PhysicsRBody* rigidBody) {
	if (rigidBody == nullptr) return false;
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
	curTime += dT;
	if (curTime >= TimeStep) {
		CheckCollisions();
		ResolveCollisions(curTime / TimeStep);
		IntegrateBodies(curTime / TimeStep);

		curTime = 0.f;
	}

	
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

				sf::Vector2f halfSizeA = (bodyA->aabb.tRight - bodyA->aabb.bLeft) / 2.0f;
				sf::Vector2f halfSizeB = (bodyB->aabb.tRight - bodyB->aabb.bLeft) / 2.0f;

				sf::Vector2f distance = (posB + halfSizeB) - (posA + halfSizeA);

				sf::Vector2f gap(std::abs(distance.x), std::abs(distance.y));
				gap -= (halfSizeA + halfSizeB);

				if (gap.x < 0 && gap.y < 0) {
					if (collisions.count(pair)) {
						collisions.erase(pair);
					}

					CollisionSide sideA = None;
					CollisionSide sideB = None;

					if (gap.x > gap.y) {
						if (distance.x > 0) {
							info.collisionNormal = Vector2f(1.0f, 0.0f);
							sideA = Left;
							sideB = Right;
						}
						else {
							info.collisionNormal = Vector2f(-1.0f, 0.0f);
							sideA = Right;
							sideB = Left;
						}
						info.penetration = gap.x;
					}
					else {
						if (distance.y > 0) {
							info.collisionNormal = Vector2f(0.0f, 1.0f);
							sideA = Down;
							sideB = Up;
						}
						else {
							info.collisionNormal = Vector2f(0.0f, -1.0f);
							sideA = Up;
							sideB = Down;
						}
						info.penetration = gap.y;
					}
					collisions[pair] = info;

					if (bodyA->collidedWith.find(bodyB) == bodyA->collidedWith.end()) {
						bodyA->GetGameObject()->OnCollisionDetected(bodyB->GetGameObject(), sideA);
						bodyA->collidedWith.insert(bodyB);
					}
					if (bodyB->collidedWith.find(bodyA) == bodyB->collidedWith.end()) {
						bodyB->GetGameObject()->OnCollisionDetected(bodyA->GetGameObject(), sideB);
						bodyB->collidedWith.insert(bodyA);
					}
					
				}
				else if (collisions.count(pair)) {
					collisions.erase(pair);
					bodyA->collidedWith.erase(bodyB);
					bodyB->collidedWith.erase(bodyA);
				}else {
					bodyA->collidedWith.erase(bodyB);
					bodyB->collidedWith.erase(bodyA);
				}
			}
		}
	}
}

void PhysicsSystem::ResolveCollisions(float dT) {
	for (std::map<std::pair<PhysicsRBody*,PhysicsRBody*>, CollisionInfo>::iterator i = collisions.begin(); i != collisions.end(); ++i) {
		std::pair<PhysicsRBody*,PhysicsRBody*> p = (*i).first;

		if (!p.first->dynamic && !p.second->dynamic) continue;
		if (p.first == nullptr || p.second == nullptr) continue;
		
		if (std::find(rigidBodies.begin(), rigidBodies.end(), p.first) == rigidBodies.end()) {
			continue;
		}
		if (std::find(rigidBodies.begin(), rigidBodies.end(), p.second) == rigidBodies.end()) {
			continue;
		}

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

		if(p.first->dynamic) p.first->AddForce(-impulse / dT);
		if(p.second->dynamic) p.second->AddForce(impulse / dT);

		if (std::abs(collisions[p].penetration) > 0.01f) {
			PositionalCorrection(p);
		}
	}
	collisions.clear();
}

void PhysicsSystem::PositionalCorrection(std::pair<PhysicsRBody*,PhysicsRBody*> c) {
	if (c.first == nullptr || c.second == nullptr) return;
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

	c.first->GetGameObject()->Translate(-(invMassA * correction));
	c.second->GetGameObject()->Translate(invMassB * correction);
}