#pragma once

struct GLFWwindow;

namespace Engine
{
	class WindowManager
	{
	public:
		explicit WindowManager() = default;
		bool Create();
		void Clear() const;
		void SwapAndPoll() const;
		bool IsCloseRequested() const;
		void Destroy();
		GLFWwindow* GetWindow() const { return m_Window; }
	private:
		//TODO: Replace with smart pointer
		GLFWwindow* m_Window = nullptr;
	};
}