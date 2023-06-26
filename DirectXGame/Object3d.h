#pragma once

#include"Model.h"
#include"Camera.h"

#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<DirectXMath.h>
#include<string>

class Object3d
{
private:	//�G�C���A�X
	template <class T> using ComPtr =
		Microsoft::WRL::ComPtr<T>;
	//DirextX::�ȗ�
	using XMFOLAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFOLAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	//xyz�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	//���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	//���[�J�����[���h���W�s��
	XMMATRIX matWorld;
	//���f��
	Model* model = nullptr;


public: //�ÓI�����o�֐�
	//setter
	static void SetDevice(ID3D12Device* device) { Object3d::device = device; }
	static void SetCamera(Camera* camera) { Object3d::camera = camera; }
	//�O���t�B�b�N�p�C�v���C���̐���
	static void CreateGraphicsPipeline();
private:
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����
	static Camera* camera;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
public: //�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBuffDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
public: //�����o�֐�
	void Initialize();
	//���t���[������
	void Updata();
	//���f���̃Z�b�g
	void SetModel(Model* model) { this->model = model;}
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
protected: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
};

