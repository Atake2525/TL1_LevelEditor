#include "Text.h"
#include "WinApp.h"
#include <d3d12.h>

void Text::Initialize() {
	LoadFont();
}

void Text::LoadFont() {
	// �t�H���g�n���h���̐���
	LOGFONT lf = {
		fontSize, 0, 0, 0, fonrWeight, 0, 0, 0,
		SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
		(WCHAR)"MS P����"
	};
	HFONT hFont = CreateFontIndirectW(&lf);

	// ���݂̃E�B���h�E�T�C�Y�ɓK�p
	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyPhOutline�֐��̓G���[�g�Ȃ�
	HDC hdc = GetDC(WinApp::GetInstance()->GetHwnd());
	//HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// �t�H���g�r�b�g�}�b�v�擾
	const wchar_t* c = L"S";
	UINT code = (UINT)*c;
	const int gradFlag = GGO_GRAY4_BITMAP;
	// �K���̍ő�l
	int grad = 0;
	switch (gradFlag)
	{
	case GGO_GRAY2_BITMAP:
		grad = 4;
		break;
	case GGO_GRAY4_BITMAP:
		grad = 16;
		break;
	case GGO_GRAY8_BITMAP:
		grad = 64;
		break;
	}


	GetTextMetrics(hdc, &tm);

	CONST MAT2 mat = { {0,1}, {0,0}, {0,0}, {0,1} };
	DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);
	BYTE* pMono = new BYTE[size];
	GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, pMono, &mat);
}

void Text::EntryTexture() {
	// �t�H���g�̕��ƍ���
	int fontWidth = gm.gmCellIncX;
	int fontHeight = tm.tmHeight;

	// �t�H���g���������ރe�N�X�`������
	D3D12_RESOURCE_DESC fontTextureDesc;
	ZeroMemory(&fontTextureDesc, sizeof(fontTextureDesc));
	fontTextureDesc.Width = fontWidth;
	fontTextureDesc.Height = fontHeight;
	fontTextureDesc.MipLevels = 1;
	fontTextureDesc.ArraySize = 1;
	fontTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	fontTextureDesc.SampleDesc.Count = 1;
	fontTextureDesc.SampleDesc.Quality = 0;
	fontTextureDesc.Usage = D3D11_USAGE_DYNAMIC;
	fontTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	fontTextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	fontTextureDesc.MiscFlags = 0;
	ID3D11Texture2D* fontTexture = 0;
}

void Text::Update() {

}

void Text::Draw() {

}
