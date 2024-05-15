#pragma once
#include <string>
#include <vector>

namespace Mordred
{
	class Vulkan_Server
	{
	public:
		Vulkan_Server(const std::string);
		~Vulkan_Server();

	private:
		static std::vector<char> readFile(const std::string& filepath);

		void initPipeline();
	};

	Vulkan_Server::Vulkan_Server()
	{
	}

	Vulkan_Server::~Vulkan_Server()
	{
	}


}