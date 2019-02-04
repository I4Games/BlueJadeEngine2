#ifndef BLUEJADE_BASECOMPONENT
#define BLUEJADE_BASECOMPONENT

class GameObject;
enum ComponentType;

class BaseComponent {
public:
	GameObject* GetGameObject();
	void SetGameObject(GameObject* gameObject);

	virtual void Update(float msec) = 0;
	virtual ComponentType GetComponentType() = 0;

protected:
	GameObject* gameObject;
};

#endif