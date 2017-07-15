#include "GuiWindow.h"
#include "ui/UIWidget.h"

namespace RioGame
{

	GuiWindow::GuiWindow()
	{
	}

	void GuiWindow::init(::RioEngine::ui::Widget* window)
	{
		this->window = window;
		init();
	}

	void GuiWindow::setIsVisible(bool val)
	{
		this->window->setVisible(val);
	}

	bool GuiWindow::getIsVisible() const
	{
		return this->window->isVisible();
	}
} // namespace RioGame
