#ifndef  MAP_INC
#define  MAP_INC

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "expat.h"
#include "globalVar.h"
#include "ResourcesManager.h"
#include "Tiles/Tile.h"
#include "Tiles/Ground.h"
#include "Tiles/Coin.h"
#include "Tiles/DefaultTile.h"
#include "Objects/Object.h"
#include "Objects/Finish.h"
#include "Trace.h"
#include "csv.h"
#include "List.h"
#include "File.h"
#include "SDL2/SDL_image.h"
#include "Datas.h"

typedef struct
{
	File* file;

	List* tileDatas;
	uint32_t spacingX;
	uint32_t spacingY;
	uint32_t tileSizeX;
	uint32_t tileSizeY;

	int32_t startX;
	int32_t startY;
}StaticFile;

typedef struct
{
	XML_Parser parser;

	uint32_t nbCasesX;
	uint32_t nbCasesY;

	uint32_t caseSizeX;
	uint32_t caseSizeY;

	List* files;
	List* staticFiles;
	List* staticTraces;
	List* dynamicFiles;
	List* objects;
}Map;

/* The xml format file are like this :
 * <map>
 *	<Window numberCase="axb" tileSize="axb" title="title"/>
 *
 *	<Files>
 *	 <Static file="path" spacing="axb" tileSize="axb">
 *	  <StaticTile name="name" type="type"/>
 *	 </Static>
 *	 <Dynamic file="path"> //Used for animation
 *	  <DynamicEntity name="name">
 *	   <DynamicTile name="name" pos="axb" size="axb" type="type"/>
 *	  </DynamicEntity>
 *	 </Dynamic>
 *	</Files>
 *
 *  <Objects name="name" numberCases = "axb" tileSize="axb" type="type">
 *   <ObjectsColumn fileID="fileID" tileID="tileID"/>
 *  </Objects>
 *
 *  <Traces>
 *   <StaticTrace name="name" shift="axb" size="axb">
 *    <Column fileID="fileID" tileID="tileID" objectID="objectID"/>
 *   </StaticTraces>
 *   <DynamicTrace name="name">
 *    <DynamicTile animName="name" animeTime="time" fileID="fileID" origin="axb" position="axb" tileID="tileID"/>
 *    <StaticTile fileID="fileID" tileID="tileID" position="axb"/>
 *   </DynamicTrace>
 *  </Traces>
 * </map> 
 *
 * each fileID et tileID are represented in csv format for StaticTrace. It earns us some time process and file spaces
 * axb = coordX . coordY
 * */

Map* Map_create(const char* filePath);

void parseFile(const char* name, const char** attrs);
void parseObject(const char* name, const char** attrs);
void parseTrace(const char* name, const char** attrs);

void startElement(void *map, const char* name, const char** attrs);
void startElementFiles(void *map, const char* name, const char** attrs);
void startElementObjects(void *map, const char* name, const char** attrs);
void startElementTraces(void *map, const char* name, const char** attrs);
void endElement(void *map, const char* name);

void getXYFromStr(const char* str, uint32_t* x, uint32_t* y);

void Map_draw(Map* self, Window* window);
SDL_Rect Map_getRect(Map* self);

Tile* Map_getTileInfo(Map* self, int32_t x, int32_t y);
bool  Map_isOutside(Map* self, int32_t x, int32_t y);

void  Map_destroy(Map* map);

StaticFile*  StaticFile_create(File* file, uint32_t tileSizeX, uint32_t tileSizeY, uint32_t spacingX, uint32_t spacingY);
List* StaticFile_getTiles(StaticFile* self);
Tile* StaticFile_createTile(StaticFile* self, int32_t tileID, bool def);
void  StaticFile_destroy(StaticFile* self);

extern uint32_t XML_depth;
extern uint32_t XML_NthColumn;

#endif
