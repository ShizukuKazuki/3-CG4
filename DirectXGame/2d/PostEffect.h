#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    //コントラクタ
    PostEffect();

    //描画コマンドの発行
    void Draw(ID3D12GraphicsCommandList* cmdList);
    //初期化
    void Initialize();
protected:  // メンバ変数
    // テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff;
    // SRV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descHeapSRV;

};

