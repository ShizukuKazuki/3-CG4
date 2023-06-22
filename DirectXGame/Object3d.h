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
private:	//エイリアス
	template <class T> using ComPtr =
		Microsoft::WRL::ComPtr<T>;
	//DirextX::省略
	using XMFOLAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFOLAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //静的メンバ関数
	//setter
	static void SetDevice(ID3D12Device* device) { Object3d::device = device; }
	static void SetCamera(Camera* camera) { Object3d::camera = camera; }
	//グラフィックパイプラインの生成
	static void CreateGraphicsPipeline();
private:
	//デバイス
	static ID3D12Device* device;
	//カメラ
	static Camera* camera;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインテートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
public: //サブクラス
	//定数バッファ用データ構造体
	struct ConstBuffDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
public: //メンバ関数
	void Initialize();
protected: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
};

