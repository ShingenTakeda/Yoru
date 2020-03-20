#pragma once
#define RUNNING_LINUX
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

#ifdef RUNNING_LINUX
#include <unistd.h>
#include <dirent.h>
inline std::string GetWorkingDirectory()
{
    char cwd [1026];
    if(!getcwd(cwd , sizeof(cwd)))
    {
        return "";
    }

    return std::string(cwd) + std::string("/");
}

std::vector<std::pair<std::string, bool>> GetFileList(const std::string& l_directory,
const std::string& l_search = "*", bool l_directories = false)
{
    std::vector<std::pair<std::string, bool>> files;

    DIR* dpdf;
    dpdf = opendir(l_directory.c_str());
    if(!dpdf)
    {
        return files;
    }

    if(l_search.empty())
    {
        return files;
    }

    std::string search = l_search;
	if (search[0] == '*') { search.erase(search.begin()); }
	if (search[search.length() - 1] == '*') { search.erase(search.end()); }
	struct dirent *epdf;
	while (epdf = readdir(dpdf))
    {
		std::string name = epdf->d_name;
		if (epdf->d_type == DT_DIR && !l_directories) { continue; }
		if (l_search != "*.*") 
        {
			if (name.length() < search.length()) { continue; }
			if (search[0] == '.') 
            {
				if (name.compare(name.length() - search.length(), search.length(), search) != 0) { continue; }
			} 
            else if (name.find(search) == std::string::npos) { continue; }
		}

		files.emplace_back(name, (epdf->d_type == DT_DIR));
	}
		closedir(dpdf);
		return files;
}

#elif defined RUNNING_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <window.h>
#include <Shlwapi.h>
inline std::string GetWorkingDirectory()
{
    HMODULE hModule = GetModuleHandle(nullptr);
    if(!hmodule)
    {
        return "";
    }

    char path[256];
    GetModuleFileName(hModule, path, sizeof(path));
    PathRemoveFileSpec(path);

    return std::string(path) + "\\";
}

inline std::vector< std::pair <std::string, bool>> GetFileList(const std::string& l_directory,
const std::string& l_search = ".", bool l_directories = false)
{
    std::vector< std::pair <std::string, bool>> files;
    if(l_search.empty())
    {
        return files;
    }

    std::string path = l_directory + l_search;
    WIN32_FIND_DATA data;
    HANDLE found = FindFirstFile(path.c_str(), &data);
    if(found == INVALID_HANDLE_VALUE)
    {
        return files;
    }
    do
    {
        if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || l_directories) 
        {
				files.emplace_back(std::make_pair(
					std::string(data.cFileName),
					((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
				));
        }
    } while (FindNextFile(found, &data));
    FindClose(found);

    return files;
}

#endif
inline void ReadQuotedString(std::stringstream& l_stream, std::string& l_string)
{
	l_stream >> l_string;
	if (l_string.at(0) == '"') 
    {
		while (l_string.at(l_string.length() - 1) != '"' || !l_stream.eof())
        {
			std::string str;
			l_stream >> str;
			l_string.append(" " + str);
		}
	}
		l_string.erase(std::remove(l_string.begin(), l_string.end(), '"'), l_string.end());
}

template<class T>
inline T Interpolate(float tBegin, float tEnd, const T& begin_val, const T& end_val, float tX) 
{
	return static_cast<T>((((end_val - begin_val) / (tEnd - tBegin)) * (tX - tBegin)) + begin_val);
}

namespace Yoru
{
    template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}