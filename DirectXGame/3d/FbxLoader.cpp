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

void FbxLoader::ParseNodeRecursive(Model* model, FbxNode* fbxNode)
{
    //ノード名を取得
    string name = fbxNode->GetName();
    //モデルにノードを追加（Todo）
    //FBXノードの情報を解析しノードに追加（Todo）
    //FBXノードのメッシュ情報を解析（Todo）

    //子ノードに対して再起呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++)
    {
        ParseNodeRecursive(model, fbxNode->GetChild(i));
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
    //ルートノードから順に解析しモデルに流し込む
    ParseNodeRecursive(model, fbxScene->GetRootNode());
    //FBXシーン解放
    fbxScene->Destroy();

}