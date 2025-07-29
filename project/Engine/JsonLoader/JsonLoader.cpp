#include "JsonLoader.h"
#include <cassert>
#include "Logger.h"
#include "kMath.h"

using namespace Logger;

JsonLoader* JsonLoader::instance = nullptr;

JsonLoader* JsonLoader::GetInstance() {
    if (instance == nullptr)
    {
        instance = new JsonLoader;
    }
    return instance;
}

void JsonLoader::Finalize() {
    delete instance;
    instance = nullptr;
}

void JsonLoader::Initialize() {

}

const LevelData JsonLoader::LoadJsonTransform(const std::string& directoryPath, const std::string& fileName)
{
    LevelData lvData;

    Transform tl = { {0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f,0.0f} };
    JsonData data;
    data.transform = tl;
    data.file_name = "null";
    data.name = "null";
    data.type = "null";
    lvData.datas["null"] = data;
    lvData.name = "null";

    // 連結してファイルパスを得る
    const std::string fullpath = directoryPath + "/" + fileName;

    // ファイルストリーム
    std::ifstream file;

    // ファイルを開く
    file.open(fullpath);
    // ファイルオープン失敗をチェック
    if (file.fail())
    {
        Log("ファイルの展開に失敗しました\nファイルパスが正しい確認してください\n");
        return lvData;
    }

    // JSON文字列から解凍したデータ
    nlohmann::json deserialized;

    // 解凍
    file >> deserialized;

    // 正しいレベルデータファイルかチェック
    if (!deserialized.is_object())
    {
        Log("正しいレベルデータファイルではありません\nBlockPoint is_object\n");
        return lvData;
    }
    if (!deserialized.contains("name"))
    {
        Log("正しいレベルデータファイルではありません\nBlockPoint contains\n");
        return lvData;
    }
    if (!deserialized["name"].is_string())
    {
        Log("正しいレベルデータファイルではありません\nBlockPoint is_string\n");
        return lvData;
    }

    // "name"を文字列として取得
    std::string name = deserialized["name"].get<std::string>();
    // 正しいレベルデータファイルかチェック
    if (name.compare("scene") != 0)
    {
        Log("正しいレベルデータファイルではありません\nBlockPoint compare\n");
        return lvData;
    }

    // レベルデータ格納用インスタンスを生成
    LevelData levelData;

    // "name"を文字列として取得
    levelData.name = deserialized["name"].get<std::string>();
    if (levelData.name != "scene")
    {
        Log("シーンではない");
        return lvData;
    }

    // "object"の全オブジェクトを走査
    for (nlohmann::json& object : deserialized["objects"])
    {
        if (!object.contains("type"))
        {
            Log("objectにtypeが存在しません\n");
            return lvData;
        }

        // 種別を取得
        //std::string type = object["type"].get<std::string>();

        if (object["type"].get<std::string>() == "MESH" || object["type"].get<std::string>() == "CAMERA")
        {
            // // 同じ名前なら後ろに数字を追加する
            //if (levelData.datas.contains(object["file_name"].get<std::string>()))
            //{
            //    for (size_t i = 0; i < levelData.datas.size(); i++)
            //    {
            //        std::string num = "_0" + std::to_string(i);
            //        if (!levelData.datas.contains(object["file_name"].get<std::string>() + num))
            //        {
            //            jsonData = levelData.datas[object["file_name"].get<std::string>() + num];
            //            break;
            //        }
            //    }
            //}
            // 1個分の要素の準備
            JsonData& jsonData = levelData.datas[object["file_name"].get<std::string>()];

            jsonData.type = object["type"].get<std::string>(); // "type"
            jsonData.name = object["name"].get<std::string>(); // "name"

            // transformのパラメータ読み込み
            nlohmann::json& transform = object["transform"];
            // 平行移動 "translation"
            jsonData.transform.translate.x = (float)transform["translation"][0];
            jsonData.transform.translate.y = (float)transform["translation"][2];
            jsonData.transform.translate.z = (float)transform["translation"][1];
            if (object["type"].get<std::string>() == "MESH")
            {
                // 回転角 "rotation"
                jsonData.transform.rotate.x = -SwapRadian((float)transform["rotation"][0]);
                jsonData.transform.rotate.y = -SwapRadian((float)transform["rotation"][2]);
                jsonData.transform.rotate.z = -SwapRadian((float)transform["rotation"][1]);
            }
            else if (object["type"].get<std::string>() == "CAMERA")
            {
                // 回転角 "rotation"
                jsonData.transform.rotate.x = SwapRadian(90.0f) - SwapRadian((float)transform["rotation"][0]);
                jsonData.transform.rotate.y = -SwapRadian((float)transform["rotation"][2]);
                jsonData.transform.rotate.z = -SwapRadian((float)transform["rotation"][1]);
            }
            // 拡大縮小 "scaling"
            jsonData.transform.scale.x = (float)transform["scaling"][0];
            jsonData.transform.scale.y = (float)transform["scaling"][1];
            jsonData.transform.scale.z = (float)transform["scaling"][2];

            // "file_name"
            if (object.contains("file_name"))
            {
                jsonData.file_name = object["file_name"].get<std::string>();
            }

            if (object.contains("children"))
            {
                for (nlohmann::json& children : object["children"])
                {
                    // transformのパラメータ読み込み
                    nlohmann::json& childTransform = children["transform"];
                    // 平行移動 "translation"
                    Transform transformchild;
                    JsonData data;
                    transformchild.translate.x = (float)childTransform["translation"][0];
                    transformchild.translate.y = (float)childTransform["translation"][1];
                    transformchild.translate.z = (float)childTransform["translation"][2];
                    // 回転角 "rotation"
                    transformchild.rotate.x = -(float)childTransform["rotation"][0];
                    transformchild.rotate.y = -(float)childTransform["rotation"][1];
                    transformchild.rotate.z = -(float)childTransform["rotation"][2];
                    // 拡大縮小 "scaling"
                    transformchild.scale.x = (float)childTransform["scaling"][0];
                    transformchild.scale.y = (float)childTransform["scaling"][1];
                    transformchild.scale.z = (float)childTransform["scaling"][2];
                    
                    data.transform = transformchild;
                    data.file_name = children["file_name"].get<std::string>();
                    data.name = children["name"].get<std::string>();
                    data.type = children["type"].get<std::string>();
                    
                }
            }
        }

    }
    return levelData;
}
