#pragma once
#include <string>

class Tileset {

public:
	Tileset();
	~Tileset();

	int getFirstgid() { return _firstgid; }
	void setFirstgid(int firstGid) { _firstgid = firstGid; }

	int getColumns() { return _numColumns; }
	void setColumns(int columns) { _numColumns = columns; }

	int getRows() { return _numRows; }
	void setFiles(int rows) { _numRows = rows; }

	std::string getSourceTsx() { return _sourceTsx; }
	void setSourceTsx(const char* sourceTsx) { _sourceTsx = sourceTsx; }

	std::string getSourceImage() { return _sourceImage; }
	void setSourceImage(const char* sourceImage) { _sourceImage = sourceImage; }

	int getIdRscManager() { return _idRscMngPlayer; }
	void setIdRscManager(int id) { _idRscMngPlayer = id; }


private:
	int _firstgid; // firstgrid number where each tileset starts(ex: tileset1 = 1-15, tileset2 = 16-50)
	int _numColumns; // according to tileset size
	int _numRows; // according to tileset size
	std::string _sourceTsx; // associated graphic file TSX
	std::string _sourceImage; // path of image
	int _idRscMngPlayer; // id of the graph in our ResourceManager
};

