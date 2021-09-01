#include "ResourceManagers.h"
#include "GameObject/Shader.h"
#include "GameObject/Texture.h"
#include "GameObject/Model.h"
#include "GameObject/Camera.h"
#include "GameObject/Font.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/Sprite3D.h"
#include "GameObject/Text.h"


ResourceManagers::ResourceManagers()
{
	std::string dataPath = "..\\Data\\";
	m_ShaderPath = dataPath + "Shaders\\";
	m_ModelPath = dataPath + "Models\\"; 
	m_TexturePath = dataPath + "Textures\\";
	m_FontPath = dataPath + "Fonts\\";
	m_SongPath = dataPath + "Sounds\\";
}

ResourceManagers::~ResourceManagers()
{
}

void ResourceManagers::AddShader(const std::string& name)
{
	auto it = m_MapShader.find(name);
	if (it != m_MapShader.end())
	{
		return;
	}

	std::shared_ptr<Shader>  shaders;
	shaders = std::make_shared<Shader>();
	std::string vs = m_ShaderPath + name + ".vs";
	std::string fs = m_ShaderPath + name + ".fs";

	shaders->Init(vs, fs);

	m_MapShader.insert(std::pair<std::string, std::shared_ptr<Shader>>(name, shaders));

}

void ResourceManagers::AddModel(const std::string& name)
{
	auto it = m_MapModels.find(name);
	if (it != m_MapModels.end())
	{
		return;
	}
	std::string path = m_ModelPath + name;
	std::shared_ptr<Model> model = std::make_shared<Model>(path, NFG);
	m_MapModels.insert(std::pair<std::string, std::shared_ptr<Model>>(name, model));
}

void ResourceManagers::AddTexture(const std::string& name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end())
	{
		return;
	}
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::string file = m_TexturePath + name;
	texture->Init(file.c_str(), GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	m_MapTexture.insert(std::pair<std::string, std::shared_ptr<Texture>>(name, texture));
}

void ResourceManagers::AddFont(const std::string& name)
{
	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end())
	{
		return;
	}
	std::string path = m_FontPath + name;
	std::shared_ptr<Font> font = std::make_shared<Font>(path);
	m_MapFont.insert(std::pair<std::string, std::shared_ptr<Font>>(name, font));
}

void ResourceManagers::AddSong(const std::string& name)
{
	auto it = m_MapSong.find(name);
	if (it != m_MapSong.end())
	{
		return;
	}
	std::string path = m_SongPath + name;
	std::shared_ptr<Song> song = std::make_shared<Song>(path);
	m_MapSong.insert(std::pair<std::string, std::shared_ptr<Song>>(name, song));
}

void ResourceManagers::RemoveShader(const std::string& name)
{
	m_MapShader.erase(name);
}

void ResourceManagers::RemoveModel(const std::string& name)
{
	m_MapModels.erase(name);
}

void ResourceManagers::RemoveTexture(const std::string& name)
{
	m_MapTexture.erase(name);
}

void ResourceManagers::RemoveFont(const std::string& name)
{
	m_MapFont.erase(name);
}

void ResourceManagers::RemoveSong(const std::string& name)
{
	m_MapSong.erase(name);
}

std::shared_ptr<Shader> ResourceManagers::GetShader(const std::string& name)
{
	auto it = m_MapShader.find(name);
	if (it != m_MapShader.end())
	{
		return it->second;
	}

	std::shared_ptr<Shader>  shaders;
	shaders = std::make_shared<Shader>();
	std::string vs = m_ShaderPath + name + ".vs";
	std::string fs = m_ShaderPath + name + ".fs";

	shaders->Init(vs, fs);

	m_MapShader.insert(std::pair<std::string, std::shared_ptr<Shader>>(name, shaders));

	return shaders;
}

std::shared_ptr<Texture> ResourceManagers::GetTexture(const std::string& name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end())
	{
		return it->second;
	}
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	std::string file = m_TexturePath + name;
	texture->Init(file.c_str(), GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	m_MapTexture.insert(std::pair<std::string, std::shared_ptr<Texture>>(name, texture));
	return texture;
}

std::shared_ptr<Model> ResourceManagers::GetModel(const std::string& name)
{
	auto it = m_MapModels.find(name);
	if (it != m_MapModels.end())
	{
		return it->second;
	}
	std::string path = m_ModelPath + name;
	std::shared_ptr<Model> model = std::make_shared<Model>(path, NFG);
	m_MapModels.insert(std::pair<std::string, std::shared_ptr<Model>>(name, model));

	return model;
}

std::shared_ptr<Font> ResourceManagers::GetFont(const std::string& name)
{
	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end())
	{
		return it->second;
	}
	std::string path = m_FontPath + name;
	std::shared_ptr<Font> font = std::make_shared<Font>(path);
	m_MapFont.insert(std::pair<std::string, std::shared_ptr<Font>>(name, font));
	return font;
}

std::shared_ptr<Song> ResourceManagers::GetSong(const std::string& name)
{
	auto it = m_MapSong.find(name);
	if (it != m_MapSong.end())
	{
		return it->second;
	}
	std::string path = m_SongPath + name;
	std::shared_ptr<Song> song = std::make_shared<Song>(path);
	m_MapSong.insert(std::pair<std::string, std::shared_ptr<Song>>(name, song));
	return song;
}

std::vector<std::shared_ptr<Song>> ResourceManagers::GetLibrary()
{
	std::vector<std::shared_ptr<Song>> listSong;
	std::string path = m_SongPath + "Library.txt";
	std::ifstream fin;
	fin.open(path);
	if (fin.is_open()) {
		std::string line;
		while (std::getline(fin, line))
		{
			std::shared_ptr<Song> song = GetSong(line);
			listSong.push_back(song);
		}
		fin.close();
	}
	return listSong;
}
