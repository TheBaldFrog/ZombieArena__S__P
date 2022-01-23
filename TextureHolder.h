#pragma once

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
public:
	TextureHolder();
	static Texture& GetTexture(string const& filename);
private:
	// map that holds related pairs of String and Texture
	map<string, Texture> m_Texture;

	// for Singleton
	static TextureHolder* m_s_Instance;
};