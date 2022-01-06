#pragma once

#include <util/types.h>
#include <cstddef>

#define MAX_ENTITIES 128
#define MAX_COMPONENTS 16

namespace trade_history
{
	class component_pool
	{
	public:
		component_pool();
		component_pool(u64 element_size, u32 component_id);
		
		~component_pool();

		void *get(u32 index);
		bool delete_at(u32 index);
		
		bool is_empty();
		u32 get_component_id();

		component_pool &operator=(component_pool &&other);
	private:
		u32 component_id;

		i8 *component_array;
		u64 element_size;
	};
}

