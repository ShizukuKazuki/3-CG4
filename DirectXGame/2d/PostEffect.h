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
    //シーン描画前処理
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
    //シーン描画後処理
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
    //パイプライ生成
    void CreateGraphicsPipelineState();
protected:  // メンバ変数
    // テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff;
    // SRV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descHeapSRV;
    // 深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    // RTV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descHeapRTV;
    // DSV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descHeapDSV;
    //グラフィックパイプライン
    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;

protected: // 静的メンバ変数
    // 画面クリアカラー
    static const float clearColor[4];

};

