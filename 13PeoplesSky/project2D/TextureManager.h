#pragma once

#include <map>
#include <string>
#include "Texture.h"

class TextureManager
{
public:
	//----------------------------------------------
	// GetInstance
	//----------------------------------------------
	// Grabs the singleton instance of the texture manager
	// Used like this:
	//		TextureManager* textureMan = TextureManager::GetInstance();
	//		aie::Texture* texture = textureMan->LoadTexture("./images/img.png");
	// returns a pointer to the TextureManager instance
	// Can be nullptr if Create hasn't been called yet
	static TextureManager* GetInstance();

	//----------------------------------------------
	// Create
	//----------------------------------------------
	// Creates an instance of the texture manager to be accessed anywhere
	// Should be called once at the start of the program
	static void Create();

	//----------------------------------------------
	// Destroy
	//----------------------------------------------
	// Destroys the instance of the texture manager created in Create
	// Should be called once at the END of the program
	static void Destroy();

	//----------------------------------------------
	// LoadTexture
	//----------------------------------------------
	// Gets a texture fom a filename
	// If the texture has been loaded previously, it returns a pointer to that,
	// and if the texture has not been loaded, it creates it and stores it
	//
	// e.g. 
	//	aie::Texture* shipTexture = textureManager->LoadTexture("./ship.png");
	//
	// fileName: Name of the file in relation to the /bin/ directory
	// returns a pointer to an aie::Texture containing the image
	// DON'T destroy the texture returned by this - it is handled by this class!
	aie::Texture* LoadTexture(std::string fileName);

private:
	TextureManager();
	~TextureManager();

	// instance that GetInstance returns
	static TextureManager* m_instance;

	// map containing all the textures
	std::map<std::string, aie::Texture*> m_textures;
};