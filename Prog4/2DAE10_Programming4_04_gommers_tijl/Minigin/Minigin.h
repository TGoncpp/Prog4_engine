#pragma once
#include <string>
#include <functional>

namespace TG
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath, int windowWidth, int windowHeight);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}