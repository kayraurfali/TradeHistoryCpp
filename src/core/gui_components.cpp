#include "gui_components.h"

namespace trade_history
{
	u32 rectangle::component_id = s_component_id_counter++;
	u32 circle::component_id = s_component_id_counter++;
	u32 style::component_id = s_component_id_counter++;
	u32 clickable::component_id = s_component_id_counter++;
}