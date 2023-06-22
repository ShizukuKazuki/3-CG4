#include "Object3d.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

using namespace Microsoft::WRL;

ComPtr<ID3D12RootSignature> rootsignature;
ComPtr<ID3D12PipelineState> pipelinestate;
//静的メンバ関数の実体
ID3D12Device* Object3d::device = nullptr;
Camera* Object3d::camera = nullptr;

void Object3d::Initialize()
{
	HRESULT result;
	//定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBuffDataTransform) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform));
}
void Object3d::CreateGraphicsPipeline()
{

}