#include "Stdafx.h"
#include "AssetIter.h"

vector<string> split(const string& s, const char d) {
    vector<string> result;
    stringstream ss(s);
    string temp;

    while (getline(ss, temp, d)) {
        result.push_back(temp);
    }
    return result;
}

string replace_all(const string& s, const string& p, const string& r) {
    string result = s;
    size_t pos = 0;
    size_t offset = 0;
    while ((pos = result.find(p, offset)) != string::npos) {
        result.replace(result.begin() + pos, result.begin() + pos + p.size(), r);
        offset = pos + r.size();
    }

    return result;
}

bool AssetIter::Next(string& id, string& value)
{
    if (asset && iter != asset->end()) {
        string temp = *iter++;
        vector<string> pair = split(temp, '=');
        if (pair.size() >= 2 && pair[0].length() != 0 && pair[1].length() != 0) {
            id = pair[0];
            value = pair[1];
            return true;
        }
    }
    return false;
}

AssetParser::~AssetParser()
{
    asset_map::iterator iter(assets.begin());
    while (iter != assets.end()) {
        delete iter++->second;
    }
    assets.clear();
}

bool AssetParser::LoadAssetPackFile(string filename)
{
    if (!ValidateAssetPackFile(filename))
        return false;

    ifstream file(filename.c_str());
    string str;
    while (getline(file, str)) {
        str = replace_all(str, "\t", "");
        str = replace_all(str, " ", "");

        if (str.length() == 0)
            continue;

        if (str.at(0) == '[' && str.at(str.length() - 1) == ']') {
            str = replace_all(str, "[", "");
            str = replace_all(str, "]", "");

            if (!IsTypeExsits(str))
                InsertNewAssetType(str);

            string value;
            vector<string>* assetVec = GetAssetVector(str);
            while (getline(file, value)) {
                value = replace_all(value, "\t", "");
                value = replace_all(value, " ", "");
                if (value.empty() || value.size() < 3)
                    continue;
                else if (value.at(0) == '[' && value.at(1) == '/' && value.at(value.length() - 1 == ']') {

                }
            }

        }
    }
    return false;
}

bool AssetParser::IsTypeExsits(string type)
{
    return false;
}

AssetIter AssetParser::GetAsset(string type)
{
    return AssetIter();
}

bool AssetParser::ValidateFileExists(string filename)
{
    return false;
}

bool AssetParser::ValidateAssetPackFile(string filename)
{
    return false;
}

void AssetParser::InsertNewAssetType(string type)
{
}

vector<string*> AssetParser::GetAssetVector(string type)
{
    return vector<string*>();
}
