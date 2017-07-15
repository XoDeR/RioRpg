#pragma once

namespace RioEngine
{
	namespace ui
	{
		class Widget;
	}
}

namespace RioGame
{
	// Abstract class that custom Gui windows inherit from, prevents unnecessary rewriting of common functions 
	// (like visibility setting and window assignment on init)
	class GuiWindow
	{
	protected:
		// Root window
		::RioEngine::ui::Widget* window = nullptr;
	public:
		GuiWindow();
		virtual ~GuiWindow() = default;
		// Initializes the window variable and calls the protected init function
		void init(::RioEngine::ui::Widget*);
		virtual void setIsVisible(bool);
		bool getIsVisible() const;
	protected:
		// Specific init function for each inheriting class
		virtual void init() = 0;
	};
} // namespace RioGame