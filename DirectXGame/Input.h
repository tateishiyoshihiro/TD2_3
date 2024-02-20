#pragma once
#include <Windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION 0x0800//DirectInput�̃o�[�W�����w��
#include<dinput.h>
class Input
{
 public:
	//namespace�ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	//
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//
	void Update();

	/// <summary>
	///	�L�[�̉������`�F�b�N
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�(DIK_0��)</param>
	/// <returns></returns>
	bool PushKey(BYTE keyNumber);
 private:
	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8>keyboard;

	BYTE key[256] = {};

};

