#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <string>
#include <stdexcept>

namespace Menu {
	class MenuItem
	{
	public:
		virtual void visit() = 0;

	};

	class Button : public MenuItem
	{
	public:
		explicit Button(std::string text)
			: _text(std::move(text))
		{}

		void visit() override;

		bool getStatus() const
		{
			return _handled;
		}

		void setHandleStatus()
		{
			_handled = true;
		}
	private:
		bool _handled = true;
		std::string _text;
	};

	class BeginItem : public MenuItem
	{
	public:
		explicit BeginItem(std::string text)
			: _text(std::move(text))
		{}

		void visit() override;
	private:
		std::string _text;
	};

	class EndItem : public MenuItem
	{
	public:
		void visit() override;
	};

	class Slider : public MenuItem
	{
	public:
		explicit Slider(std::string name, float min, float max, float def_value = 0)
			: _text(std::move(name)), _min(min), _max(max), _sliderValue(def_value)
		{
			if (_min >= _max)
			{
				throw std::runtime_error("Not valid slider range!");
			}
		}

		void visit() override;

		float getSliderValue() const
		{
			return _sliderValue / (_max - _min);
		}
	private:
		float _min;
		float _max;
		float _sliderValue;
		std::string _text;
	};
}
#endif MENU_ITEM_HPP