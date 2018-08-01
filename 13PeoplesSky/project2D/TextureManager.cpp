#include "TextureManager.h"

// initialise the instance to nullptr so we know it hasn't been created
TextureManager* TextureManager::m_instance = nullptr;

TextureManager::TextureManager() { }

TextureManager::~TextureManager()
{
	// delete all the textures
	for (auto pair : m_textures)
		delete pair.second;
	// and all the fonts
	for (auto pair : m_fonts)
		delete pair.second;
}

TextureManager* TextureManager::GetInstance()
{
	return m_instance;
}

void TextureManager::Create()
{
	// we never want to create more than one!
	if (m_instance)
		return;

	m_instance = new TextureManager();
}

void TextureManager::Destroy()
{
	delete m_instance;
	m_instance = nullptr;
}

// grabs a texture based on a file name by checking if it already exists in
// the map, and if not it creates it and stores it
aie::Texture* TextureManager::LoadTexture(std::string fileName)
{
	// auto here so I don't have to type out the whole iterator type
	auto foundTexture = m_textures.find(fileName);

	// check if the texture exists
	if (foundTexture == m_textures.end())
	{
		// texture doesn't exist, let's create it
		m_textures[fileName] = new aie::Texture(fileName.c_str());
	}

	// texture SHOULD exist in the map now!
	return m_textures[fileName];
}

aie::Font* TextureManager::LoadFont(std::string fileName, 
	unsigned short fontSize)
{
	// stick the font size onto the end of the file name as the key
	std::string key = fileName + std::to_string(fontSize);

	auto foundFont = m_fonts.find(key);

	// check if the font exists
	if (foundFont == m_fonts.end())
	{
		// font doesn't exist! let's create it
		m_fonts[key] = new aie::Font(fileName.c_str(), fontSize);
	}

	// font should exist!
	return m_fonts[key];
}
