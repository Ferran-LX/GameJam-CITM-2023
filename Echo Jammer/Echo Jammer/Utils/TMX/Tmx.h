#pragma once
#include<iostream>
#include<fstream>
#include <vector>

#include "tinyxml2.h"
#include "Layer.h"
#include "Tileset.h"



class Tmx {

public:
	void Init();

private:
	void LoadTmx();
	void GetAttributes();
	void GetTilesets();
	Tileset GetinformationAdditionalTileset(const char* sourceTempo, Tileset tilesetTempo);
	void GetLayers();
	int SearchTileset(int tileToPaint);
	std::string TransformDataToString();

	int _width;
	int _heigth;
	int _tileWidth;
	int _tileHeight;
	std::vector<Layer> _layers;
	std::vector<Tileset> _tilesets;
	tinyxml2::XMLDocument _tmx;
	tinyxml2::XMLElement* _map;
};