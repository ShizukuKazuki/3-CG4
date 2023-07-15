#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    //�R���g���N�^
    PostEffect();

    //�`��R�}���h�̔��s
    void Draw(ID3D12GraphicsCommandList* cmdList);
    //������
    void Initialize();
    //�V�[���`��O����
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
    //�V�[���`��㏈��
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
    //�p�C�v���C����
    void CreateGraphicsPipelineState();
protected:  // �����o�ϐ�
    // �e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff;
    // SRV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap>descHeapSRV;
    // �[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    // RTV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap>descHeapRTV;
    // DSV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap>descHeapDSV;
    //�O���t�B�b�N�p�C�v���C��
    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;

protected: // �ÓI�����o�ϐ�
    // ��ʃN���A�J���[
    static const float clearColor[4];

};

