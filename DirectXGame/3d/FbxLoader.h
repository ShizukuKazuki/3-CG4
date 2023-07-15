#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>

#include <string>

#include"Model.h"

class FbxLoader
{
private: // エイリアス
	using string = std::string;

public: //定数
	// モデル格納ルートパス
	static const string baseDirectory;

	// テクスチャがない場合の標準テクスチャファイル名
	static const string defaultTextureFileName;

public:

	/// シングルトンインスタンスの取得
	static FbxLoader* GetInstance();
	/// 初期化
	void Initialize(ID3D12Device* device);
	// 後始末
	void Finalize();
	// ファイルからFBXモデル読込
	Model* LoadModelFromFile(const string& modelName);
	// 再帰的にノート構成を解析 
	void ParseNodeRecursive
	(Model* model, FbxNode* fbxNode, Node* parent = nullptr);
	//メッシュ読み込み
	void ParseMesh(Model* model, FbxNode* fbxNode);

	// 頂点座標読み取り
	void ParseMeshVertices(Model* model, FbxMesh* fbxMesh);
	// 面情報読み取り
	void ParseMeshFaces(Model* model, FbxMesh* fbxMesh);
	// マテリアル読み取り
	void ParseMaterial(Model* model, FbxNode* fbxNode);
	// テクスチャ読み取り
	void LoadTexture(Model* model, const std::string& fullpath);
	//スキニング情報を読み取り
	void ParseSkin(Model* model, FbxMesh* fbxMesh);
	//FBXの行列をXMMATRIXに変換
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);



	// ディレクトリを含んだファイルパスからファイル名を抽出する
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
	// D3D12デバイス
	ID3D12Device* device = nullptr;
	// FBXマネジャー
	FbxManager* fbxManager = nullptr;
	// FBXインポータ
	FbxImporter* fbxImporter = nullptr;
};
