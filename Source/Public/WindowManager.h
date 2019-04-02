#pragma once

struct GLFWwindow;

namespace Engine
{
	class WindowManager
	{
	public:
		explicit WindowManager() = default;
		bool TryCreate();
		void Clear() const;
		void SwapAndPoll() const;
		bool IsCloseRequested() const;
		void Destroy();
	private:
		//TODO: Replace with smart pointer
		GLFWwindow* m_Window = nullptr;
	};
}