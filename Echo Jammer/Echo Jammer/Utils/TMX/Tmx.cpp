#include "Tmx.h"

void Tmx::Init(){
	LoadTmx();
}

void Tmx::LoadTmx()
{
	// Open file and check	
	if (_tmx.LoadFile("../_Assets/Images/Granja.tmx") != tinyxml2::XML_SUCCESS)	
		std::cout << "Load TMX file (Granja.tmx) ->" << _tmx.ErrorStr();
	else
		std::cout << "Load TMX file (Granja.tmx) ->OK" << std::endl;

	std::cout << "-------------------------------------------------------------------" << std::endl;

	GetAttributes();
	GetTilesets();
	GetLayers();
}

void Tmx::GetAttributes()
{
	// Get and set attributes: <map>	
	_map = _tmx.FirstChildElement("map");
	int widthTempo = -1, heightTempo = -1, tileWidthTempo = -1, tileHeightTempo = -1;

	/// Get attributes of <map>
	_map->QueryAttribute("width", &widthTempo);
	_map->QueryAttribute("height", &heightTempo);
	_map->QueryAttribute("tilewidth", &tileWidthTempo);
	_map->QueryAttribute("tileheight", &tileHeightTempo);

	/// Set attributes of <map>
	_width = widthTempo * tileWidthTempo;
	_heigth = heightTempo * tileHeightTempo;
	_tileWidth = tileWidthTempo;
	_tileHeight = tileHeightTempo;
}

void Tmx::GetTilesets()
{
	// Get and set the different tilesets: <map> -> <tileset>* n
	tinyxml2::XMLElement* tileset = _map->FirstChildElement("tileset");
	for (tinyxml2::XMLElement* tileset = _map->FirstChildElement("tileset"); tileset != NULL; tileset = tileset->NextSiblingElement("tileset"))
	{
		Tileset tilesetTempo;
		int firstGidTempo = -1;
		const char* sourceTempo;

		/// Get attributes of actual tileset
		tileset->QueryAttribute("firstgid", &firstGidTempo);
		sourceTempo = tileset->Attribute("source");
		tilesetTempo = GetinformationAdditionalTileset(sourceTempo, tilesetTempo);

		/// Set attributes of actual tileset
		tilesetTempo.setFirstgid(firstGidTempo);
		tilesetTempo.setSourceTsx(sourceTempo);

		// Upload the tileset to the resourceManager
	//	tilesetTempo.setIdRscManager(_rscManager->loadAndGetGraphicID(tilesetTempo.getSourceImage().c_str()));

		/// Add tileset in the vector
		_tilesets.push_back(tilesetTempo);
	}
}

Tileset Tmx::GetinformationAdditionalTileset(const char* sourceTempo, Tileset tilesetTempo)
{
	// Get the fields: numColumns and image path
	int numColumns = -1;
	int numFiles = -1;
	int tileCount = -1;
	std::string pathTsx = "Resources/Images/Tmx/";
	std::string pathImage = "Resources/Images/";
	pathTsx += sourceTempo;

	tinyxml2::XMLDocument _tmxTemp;

	if (_tmxTemp.LoadFile(pathTsx.c_str()) != tinyxml2::XML_SUCCESS)
		std::cout << "Load TSX file (" << pathTsx.c_str() << ") ->" << _tmxTemp.ErrorStr();
	else
		std::cout << "Load TSX file (" << pathTsx.c_str() << ") ->OK " << std::endl;

	std::cout << "-------------------------------------------------------------------" << std::endl;

	tinyxml2::XMLElement* tileset = _tmxTemp.FirstChildElement("tileset");
	tileset->QueryAttribute("columns", &numColumns);
	tileset->QueryAttribute("tilecount", &tileCount);
	numFiles = tileCount / numColumns;

	tinyxml2::XMLElement* image = tileset->FirstChildElement("image");
	std::string pathImageToBeTreated = image->Attribute("source");
	pathImage += pathImageToBeTreated.replace(0, 3, "");

	tilesetTempo.setSourceTsx(pathTsx.c_str());
	tilesetTempo.setSourceImage(pathImage.c_str());
	tilesetTempo.setColumns(numColumns);
	tilesetTempo.setFiles(numFiles);

	return tilesetTempo;
}

void Tmx::GetLayers()
{
	// Get and set the differents layers: <map> -> <layer>* n
	tinyxml2::XMLElement* layer = _map->FirstChildElement("layer");
	for (tinyxml2::XMLElement* layer = _map->FirstChildElement("layer"); layer != NULL; layer = layer->NextSiblingElement("layer"))
	{
		Layer layerTempo;

		int idTempo = -1;
		int widthTempo = -1;
		int heightTempo = -1;
		const char* nameTempo;
		std::string dirtyData;

		/// Get the different attributes
		layer->QueryAttribute("id", &idTempo);
		layer->QueryAttribute("width", &widthTempo);
		layer->QueryAttribute("height", &heightTempo);
		nameTempo = layer->Attribute("name");

		/// Save them in a Layer
		layerTempo.setId(idTempo);
		layerTempo.setWidth(widthTempo);
		layerTempo.setHeight(heightTempo);
		layerTempo.setName(nameTempo);

		/// Get dirty data
		tinyxml2::XMLElement* data = layer->FirstChildElement("data");
		dirtyData = data->GetText();

		/// Initialize two-dimensional vector "dataContent" (vector of vectors<int>) (width=X, height=Y)
		std::vector<std::vector<int>>dataContent;
		int actualWidthLayer = layerTempo.getWidth();
		int actualHeigthLayer = layerTempo.getHeight();
		for (int x = 0; x < actualWidthLayer; x++)
		{
			std::vector<int>vectorTemp;
			dataContent.push_back(vectorTemp);
		}

		/// Convert "dirtyData" of the current layer and save in a vector(without commas or line breaks)
		int sizeData = dirtyData.size();
		int initPointer = 0;
		int finalPointer = 0;
		std::vector<int>vectorCleanData;

		for (int i = 0; i < sizeData; i++)
		{
			if (dirtyData[i] == ',')
			{
				finalPointer = i - 1;
				std::string strTempo = dirtyData.substr(initPointer, finalPointer);
				vectorCleanData.push_back(stoi(strTempo));
				initPointer = i + 1;
			}
			else if (dirtyData[i] == '\n')
			{
				initPointer = i + 1;
			}
			else if (i == sizeData - 2)
			{
				std::string strTempo = dirtyData.substr(initPointer, i);
				vectorCleanData.push_back(stoi(strTempo));
			}
		}

		/// Write the clean data in the vector of vectors<int>"contingutData" by doing a pushback() for 
		/// the whole row X and then increment Y to make a new row of pushbacks().

		int pointerCleanVector = 0;
		for (int y = 0; y < actualHeigthLayer; y++)
		{
			for (int x = 0; x < actualWidthLayer; x++)
			{
				dataContent[x].push_back(vectorCleanData[pointerCleanVector]);
				pointerCleanVector++;
			}
		}

		/// Assign Data in the object Layer
		layerTempo.data = dataContent;

		/// Save each layer in a vector of layers
		_layers.push_back(layerTempo);
	}
}

int Tmx::SearchTileset(int tileOfDraw)
{
	int whichTileset = -1;
	bool found = false;
	int count = 0;
	int tilesetSize = _tilesets.size();

	if (tileOfDraw > 0)
	{
		while (!found)
		{
			if (count + 1 == tilesetSize) {
				found = true;
				whichTileset = tilesetSize - 1;
			}
			else if (tileOfDraw < _tilesets.at(count + 1).getFirstgid()) {
				found = true;
				whichTileset = count;
			}
			else
				count++;
		}
	}

	return whichTileset;
}


std::string Tmx::TransformDataToString()
{
	std::string resultDATA = "";

	int widthLayer = _layers.at(0).getWidth();
	int heigthLayer = _layers.at(0).getHeight();

	for (int y = 0; y < widthLayer; y++)
	{
		for (int x = 0; x < heigthLayer; x++)
		{
			resultDATA += std::to_string(_layers.at(0).data[x][y]);
			if (y == widthLayer - 1 && x == heigthLayer - 1)
				resultDATA += "";
			else
				resultDATA += ",";
		}
		resultDATA += "\n";
	}

	return resultDATA;
}

