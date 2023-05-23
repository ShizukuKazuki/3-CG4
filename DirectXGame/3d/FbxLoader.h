#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>

#include<string>
#include "Model.h"
class FbxLoader
{
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	 /// <summary>
	/// 初期化
	/// </summary>
	static FbxLoader* GetInstance();

	void Initialize(ID3D12Device* device);

	void Finalize();

	void ParseNodeRecursive(Model* model, FbxNode* fbxNode,Node*parent = nullptr);
	//メッシュ読み取り
	void ParseMesh(Model* model, FbxNode* fbxNode);
	//頂点座標読み取り
	void ParseMeshVertices(Model* model, FbxMesh* fbxMesh);
	//面情報読み取り
	void ParseMeshFaces(Model* model, FbxMesh* fbxNode);
	//マテリアル読み取り
	void ParseMaterial(Model* model, FbxNode* fbxNode);
	//テクスチャ読み込み
	void LoadTexture(Model* model, const std::string& fullpath);
	
	//ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);

	

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;
	//D3D12デバイス
	ID3D12Device* device = nullptr;
	//FBXマネージャー
	FbxManager* fbxManager = nullptr;
	//FBXインポーター
	FbxImporter* fbxInporter = nullptr;

	using string = std::string;

	//テクスチャがない場合の標準テクスチャ名
	static const string defaultTextureFileName;

public:	//定数
		//モデル格納ルートパス
	static const string baseDirecotory;
	//ファイルからFBXモデル読込
	void LoadModelFromFile(const string& modelName);
};