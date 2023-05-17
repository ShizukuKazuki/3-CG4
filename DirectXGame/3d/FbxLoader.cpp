#include "FbxLoader.h"
#include <cassert>

//静的メンバ変数の実態
const std::string FbxLoader::baseDirecotory =
"Resources/";

using namespace DirectX;

FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device)
{
    //再初期化チェック
    assert(fbxManager == nullptr);
    //引数からメンバ関数に代入
    this->device = device;
    //FBXマネージャー生成
    fbxManager = FbxManager::Create();
    //FBXマネージャーの入出力設定
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);
    //FBXインポーター生成
    fbxInporter = FbxImporter::Create(fbxManager, "");
}

void FbxLoader::Finalize()
{
    //各種FBXインスタンスの破棄
    fbxInporter->Destroy();
    fbxManager->Destroy();
}

void FbxLoader::ParseNodeRecursive(Model* model, FbxNode* fbxNode, Node* parent)
{
    //ノード名を取得
    string name = fbxNode->GetName();
    //モデルにノードを追加（Todo）
    //FBXノードの情報を解析しノードに追加（Todo）
    //FBXノードのメッシュ情報を解析（Todo）
    
    //モデルにノードを追加
    model->nodes.emplace_back();
    Node& node = model->nodes.back();
    //ノード名を取得
    node.name = fbxNode->GetName();

    //FBXノードのローカル移動情報
    FbxDouble3 rotaion = fbxNode->LclRotation.Get();
    FbxDouble3 scalin = fbxNode->LclScaling.Get();
    FbxDouble3 translation = fbxNode->LclTranslation.Get();

    //形式変換して代入
    node.rotation = { (float)rotaion[0],(float)rotaion[1],(float)rotaion[2],0.0f };
    //回転角をDegree（度）からラジアンに変換
    node.rotation.m128_f32[0] = XMConvertToRadians(node.rotation.m128_f32[0]);
    node.rotation.m128_f32[1] = XMConvertToRadians(node.rotation.m128_f32[1]);
    node.rotation.m128_f32[2] = XMConvertToRadians(node.rotation.m128_f32[2]);

    //スケール、回転、平行移動行列の計算
    XMMATRIX matScling, matRotation, matTranslation;
    matScling = XMMatrixScalingFromVector(node.scaling);
    matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation);
    matTranslation = XMMatrixTranslationFromVector(node.translation);

    //ローカル変形行列の計算
    node.transform = XMMatrixIdentity();

    //グローバル変形行列の計算
    node.glodalTransform = node.transform;
    if (parent)
    {
        node.parent = parent;
        //親の変形を計算
        node.glodalTransform *= parent->glodalTransform;
    }

    //子ノードに対して再起呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++)
    {
        ParseNodeRecursive(model, fbxNode->GetChild(i),&node);
    }

}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
    //モデルと同じ名前のファルダから読み込む
    const string deirectoryPath = baseDirecotory
        + modelName + "/";
    //拡張子.fbxを付加
    const string fileName = modelName + ".fbx";
    //連結してフルパスを得る
    const string fullpath = deirectoryPath + fileName;

    //ファイル名を指定しFBXファイルを読み込む
    if (!fbxInporter->Initialize(fullpath.c_str(), -1, fbxManager->GetIOSettings()))
    {
        assert(0);
    }

    //シーン生成
    FbxScene* fbxScene =
    FbxScene::Create(fbxManager, "fbxScene");
    //ファイルからロードしたFBXファイル情報をシーンインポート
    fbxInporter->Import(fbxScene);

    //モデル生成
    Model* model = new Model();
    model->name = modelName;
    //FBXノードの数を取得
    int nodeCount = fbxScene->GetNodeCount();
    model->nodes.reserve(nodeCount);
    //ルートノードから順に解析しモデルに流し込む
    ParseNodeRecursive(model, fbxScene->GetRootNode());
    //FBXシーン解放
    fbxScene->Destroy();

}