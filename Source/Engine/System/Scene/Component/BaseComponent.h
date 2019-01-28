#ifndef BLUEJADE_BASECOMPONENT
#define BLUEJADE_BASECOMPONENT

class GameObject;

class BaseComponent {
public:
	GameObject* GetGameObject();
	void SetGameObject(GameObject* gameObject);

	virtual void Update(float msec) = 0;

protected:
	GameObject* gameObject;
};

#endif