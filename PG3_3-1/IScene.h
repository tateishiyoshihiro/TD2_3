#pragma once
enum SceneType
{
	kTitle,
	kStage,
	kClear,
	kSceneMax
};
class IScene
{
protected:
	static int sceneNo;
	char* keys_;
	char* preKeys_;
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	~IScene();
	int GetSceneNo();
	void SetKeys(char* keys, char* prekyes);
};


