#pragma once
#include <string>
#include <DirectXMath.h>
#include <vector>

#include <DirectXTex.h>

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

struct Node
{
	//���O
	std::string name;
	//���[�J���X�P�[��
	DirectX::XMVECTOR scaling = { 1,1,1,0 };
	//���[�J����]�p
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	//���[�J���ړ�
	DirectX::XMVECTOR translation = { 0,0,01 };
	//���[�J���ό`�s��
	DirectX::XMMATRIX transform;
	//�O���[�o���ό`�s��
	DirectX::XMMATRIX glodalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
};

class Model
{
private:	//�G�C���A�X
	template <class T> using ComPtr =
		Microsoft::WRL::ComPtr<T>;
	//DirextX::�ȗ�
	using XMFOLAT2 = DirectX::XMFLOAT2;
	using XMFOLAT3 = DirectX::XMFLOAT3;
	using XMFOLAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImg = DirectX::ScratchImage;

public:
	//�t�����h�N���X
	friend class FbxLoader;

	//�o�b�t�@����
	void CreateBuffers(ID3D12Device* device);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���f����
	std::string name;
	//�m�[�h�z��
	std::vector<Node>nodes;
	//�A���r�G���g�W��
	DirectX::XMFLOAT3 ambient = { 1,1,1 };
	//�f�B�t�[�Y�W��
	DirectX::XMFLOAT3 diffuse = { 1,1,1 };
	//�e�N�X�`�����^�f�[�^
	DirectX::TexMetadata metadata = {};
	//�e�N�X�`���C���[�W
	DirectX::ScratchImage scratchImg = {};
	
public: //�T�u�N���X
	//���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos; //zyz���W
		DirectX::XMFLOAT3 normal; //�@���x�N�g��
		DirectX::XMFLOAT2 uv; //uv���W
	};
	//���b�V�������m�[�h
	Node* meshNode = nullptr;
	//���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;

	//std::���ȗ�
	using string = std::string;
	template <class T> using vextor =
	std::vector<T>;

	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//���f���̕ό`�s�񏊓�
	const XMMATRIX& GetModelTransform() { return meshNode->glodalTransform; }
};