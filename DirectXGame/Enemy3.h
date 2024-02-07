#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include"BaseCharacter.h"
class Enemy3 : public BaseCharacter {

  public:
	///< summary>
	// ������
	///  </summary>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection) override;

	void Reset(const Vector3& pos);

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	WorldTransform worldTransformEnemy_Body_;
	//  ���f��
	Model* model_ = nullptr;
	// 3D���f��
	Model* modelFighterEnemyBody_;
	float enemySpeed_ = -0.054f;

};
