#include "ButtonView.h"
#include "Font.h"
#include "MenuView.h"
#include "Menus.h"

namespace sns
{
	void MenuView::Draw( Menu const& model, Font const& font, Surface& render_target )noexcept
	{
		std::visit( [ & ]( auto const& menu )
		{
			using type = std::decay_t<decltype( menu )>;
			for( auto const& button : type::buttons )
			{
				ButtonView::Draw( button, font, render_target );
			}
		}, model.variant );
	}
}
