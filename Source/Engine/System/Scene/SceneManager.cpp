#include "SceneManager.h"
#include "GameObjectManager.h"

#include "Component\TransformComponent.h"
#include "Component\PhysicsRBody.h"
#include "Component\SpriteRenderer.h"
#include "Component\AudioPlayer.h"
#include "Component\Paddle.h"
#include "Component\Brick.h"
#include "Component\Ball.h"

SceneManager* SceneManager::Instance = 0;
std::string SceneManager::assetRoot = "../Assets/";

SceneManager* SceneManager::GetInstance() {
	if (!Instance) {
		Instance = new SceneManager();
	}
	return Instance;
}

BaseComponent* SceneManager::MakeComponent(ComponentType cType) {
	switch (cType) {
	case C_Transform:
		return new TransformComponent();
		break;
	case C_PhysicsRBody:
		return new PhysicsRBody();
		break;
	case C_SpriteRenderer:
		return new SpriteRenderer();
		break;
	case C_AudioPlayer:
		return new AudioPlayer();
		break;
	case C_Paddle:
		return new Paddle();
		break;
	case C_Brick:
		return new Brick();
		break;
	case C_Ball:
		return new Ball();
		break;
	}
	return NULL;
}

void SceneManager::BuildScene(std::string xmlFilename) {
	tinyxml2::XMLDocument doc;
	auto error = doc.LoadFile(xmlFilename.c_str());
	GameObjectManager::GetInstance()->EmptyRoot();

	tinyxml2::XMLElement* levelParent = doc.FirstChildElement("Level");
	tinyxml2::XMLNode* gChild;

	for (gChild = levelParent->FirstChild(); gChild != 0; gChild = gChild->NextSibling()) {
		AddGameObject(gChild, NULL);
	}
}

void SceneManager::AddGameObject(tinyxml2::XMLNode* node, GameObject* parent) {
	tinyxml2::XMLElement* elem = node->ToElement();

	std::string objName(elem->Attribute("name"));

	GameObject* obj = new GameObject(objName);
	GameObjectManager::GetInstance()->AddGameObject(obj, parent);

	tinyxml2::XMLElement* componentParent = node->FirstChildElement("Components");
	tinyxml2::XMLNode* cChild;

	if (componentParent) {
		for (cChild = componentParent->FirstChild(); cChild != 0; cChild = cChild->NextSibling()) {
			AddComponent(obj, cChild->ToElement());
		}
	}

	tinyxml2::XMLElement* childrenElem = node->FirstChildElement("Children");
	tinyxml2::XMLNode* oChild;

	if (childrenElem) {
		for (oChild = childrenElem->FirstChild(); oChild != 0; oChild = oChild->NextSibling()) {
			AddGameObject(oChild, obj);
		}
	}
}

void SceneManager::AddComponent(GameObject* obj, tinyxml2::XMLElement* elem) {
	std::string eStr = elem->Name();
	if (eStr == "Transform") {
		tinyxml2::XMLElement* p = elem->FirstChildElement("Position");
		tinyxml2::XMLElement* r = elem->FirstChildElement("Rotation");
		tinyxml2::XMLElement* s = elem->FirstChildElement("Scale");

		obj->Translate(sf::Vector2f(p->FloatAttribute("x"), p->FloatAttribute("y")));
		obj->Rotate(r->FloatAttribute("y"));
		obj->Scale(sf::Vector2f(s->FloatAttribute("x"), s->FloatAttribute("y")));
	}
	else if (eStr == "SpriteRenderer") {
		tinyxml2::XMLElement* sp = elem->FirstChildElement("Sprite");
		SpriteRenderer* c_sp = new SpriteRenderer();

		std::string shortFilename = sp->Attribute("filename");
		c_sp->SetSpriteFromFile(assetRoot + shortFilename);

		obj->AddComponent(c_sp);
	}
	else if (eStr == "Rigidbody") {
		PhysicsRBody* rb = new PhysicsRBody();
		rb->mass = elem->FloatAttribute("mass");
		rb->bounciness = elem->FloatAttribute("bounciness");
		rb->obeysGravity = elem->BoolAttribute("obeysGravity");
		rb->canCollide = elem->BoolAttribute("canCollide");

		obj->AddComponent(rb);
	}
	else if (eStr == "AudioPlayer") {
		AudioPlayer* ap = new AudioPlayer();

		obj->AddComponent(ap);
	}
	else if (eStr == "Paddle") {
		Paddle* pad = new Paddle();
		pad->speed = elem->FloatAttribute("speed");

		obj->AddComponent(pad);
	}
	else if (eStr == "Brick") {
		Brick* brk = new Brick();
		obj->AddComponent(brk);
	}
	else if (eStr == "Ball") {
		Ball* bal = new Ball();
		bal->speed = elem->FloatAttribute("speed");

		obj->AddComponent(bal);
	}
}