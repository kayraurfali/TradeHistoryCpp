#pragma once

#include <bitset>

#include <util/types.h>
#include <core/component_pool.h>
#include <stack>

namespace trade_history
{
	using entity_id = u64;
	using entity_index = u32;
	using entity_version = u32;
	using component_mask = std::bitset<MAX_COMPONENTS>;

	class gui_handler
	{
		static gui_handler &create()
		{
			static gui_handler t;
			return t;
		}
		struct entity
		{
			entity_id id;
			component_mask mask;
		};

		entity_id create_new_entity_id(entity_index index, entity_version version);
	public:
		static gui_handler &instance();

		template<typename T>
		int get_component_id()
		{
			static int s_componentId = s_componentCounter++;
			return s_componentId;
		}

		template<typename T>
		T *assign_component_to_entity(entity_id id)
		{
			int component_id = get_component_id<T>();
			entity_index index = get_entity_index(id);
			
			if (component_pool_size >= MAX_COMPONENTS)
			{
				printf("Maximum component size for an entity has been reached");
				return nullptr;
			}
			if (entities[index].mask.test(component_id)) 
			{
				printf("Entity already has a component like this.\n");
				return nullptr; // if component already exists, return;
			}
			if (component_pools[component_id].is_empty()) // New component, make a new pool
			{
				component_pools[component_id] = component_pool(sizeof(T));
				component_pool_size++;
			}

			T *pComponent = static_cast<T *>(component_pools[component_id].get(index));

			// Set the bit for this component to true and return the created component
			entities[index].mask.set(component_id);
			return pComponent;
		}

		template<typename T>
		T *get_component_in_entity(entity_id id)
		{
			int component_id = get_component_id<T>();
			entity_index index = get_entity_index(id);

			if (!entities[index].mask.test(component_id))
				return nullptr;

			T *pComponent = static_cast<T *>(component_pools[component_id].get(index));
			return pComponent;
		}

		template<typename T>
		bool remove_component_in_entity(entity_id id)
		{
			entity_index index = get_entity_index(id);

			if (entities[index].id != id)
				return false;

			int component_id = get_component_id<T>();
			if (!entities[index].mask.test(component_id))
			{
				printf("Entity does not have that kind of a component.");
				return false;
			}
			
			component_pools[component_id].delete_at(index);
			entities[index].mask.reset(component_id);

			return true;
		}

		entity_id add_new_entity();
		bool destroy_entity(entity_id id);
		entity_index get_entity_index(entity_id id);
		entity_version get_entity_version(entity_id id);
		bool is_entity_valid(entity_id id);

		void update();
		void render();
	private:
		gui_handler();
		static int s_componentCounter;

		entity entities[MAX_ENTITIES];
		u32 entities_size;
		std::stack<entity_index> free_entities;

		component_pool component_pools[MAX_COMPONENTS];
		u32 component_pool_size;

		static gui_handler &instance_;
	};

#define INVALID_ENTITY create_new_entity_id(entity_index(-1), 0);
}