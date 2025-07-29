#include <Windows.h>

#pragma once


// �Q�l����
// https://hakase0274.hatenablog.com/entry/2018/11/17/170918#%E3%83%95%E3%82%A9%E3%83%B3%E3%83%88%E8%AA%AD%E3%81%BF%E8%BE%BC%E3%81%BF

class Text
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	///  �t�H���g�ǂݍ���
	/// </summary>
	void LoadFont();

	/// <summary>
	/// �e�N�X�`����������
	/// </summary>
	void EntryTexture();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	// �t�H���g�n���h���̐���
	int fontSize = 64;

	int fonrWeight = 1000;

	TEXTMETRIC tm;

	GLYPHMETRICS gm;

};

