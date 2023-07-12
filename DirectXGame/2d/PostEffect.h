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
protected:  // �����o�ϐ�
    // �e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff;
    // SRV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap>descHeapSRV;

};

