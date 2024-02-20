#pragma once
#include <Windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
class Input
{
 public:
	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	//
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//
	void Update();

	/// <summary>
	///	キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号(DIK_0等)</param>
	/// <returns></returns>
	bool PushKey(BYTE keyNumber);
 private:
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8>keyboard;

	BYTE key[256] = {};

};

