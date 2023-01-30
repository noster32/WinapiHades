#pragma once

typedef map<string, vector<string>*> asset_map;

class AssetIter
{
private:
	vector<string>* asset;
	vector<string>::iterator iter;

public:
	AssetIter() : asset(NULL) { }
	AssetIter(vector<string>* _asset) : asset(_asset), iter(_asset->begin()) { }
	bool Next(string& id, string& value);
};

class AssetParser
{
public:
	enum AssetType {
		TYPE_FILE,
		TYPE_TEXT,
		TYPE_NUMBER
	};
private:
	asset_map assets;
public:
	static AssetParser& GetInstance() {
		static AssetParser instance;
		return instance;
	}
	~AssetParser();
	bool LoadAssetPackFile(string filename);
	bool IsTypeExsits(string type);
	AssetIter GetAsset(string type);

protected:
	bool ValidateFileExists(string filename);
	bool ValidateAssetPackFile(string filename);
	void InsertNewAssetType(string type);
	vector<string*> GetAssetVector(string type);

private:
	AssetParser();
};

