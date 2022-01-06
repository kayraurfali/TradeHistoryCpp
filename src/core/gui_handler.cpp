#include "gui_handler.h"

namespace trade_history
{
    gui_handler &gui_handler::instance_ = gui_handler::create();
    int gui_handler::s_componentCounter = 0;

    gui_handler &gui_handler::instance()
    {
        return instance_;
    }

    entity_id gui_handler::create_new_entity_id(entity_index index, entity_version version)
    {
        return (entity_id(index) << 32) | entity_id(version);
    }

    entity_id gui_handler::add_new_entity()
    {
        if (!free_entities.empty())
        {
            entity_index index = free_entities.top();
            free_entities.pop();
            entity_id new_id = create_new_entity_id(index, get_entity_version(entities[index].id));
            entities[index].id = new_id;
            entities_size++;
            
            return new_id;
        }
        if (entities_size < MAX_ENTITIES)
        {
            entity_id new_id = create_new_entity_id(entity_index(entities_size), 0);
            entities[entities_size] = {new_id, component_mask()};
            entities_size++;

            return new_id;
        }

        return INVALID_ENTITY;
    }

    bool gui_handler::destroy_entity(entity_id id)
    {
        if (!is_entity_valid(id)) return false; // if entity is already deleted
        entity_id new_id = create_new_entity_id(entity_index(-1), get_entity_version(id) + 1);
        entities[get_entity_index(id)].id = new_id;
        entities[get_entity_index(id)].mask.reset();
        free_entities.push(get_entity_index(id));
        return true;
    }

    entity_index gui_handler::get_entity_index(entity_id id)
    {
        return id >> 32;
    }

    entity_version gui_handler::get_entity_version(entity_id id)
    {
        return (entity_version)id; //discard first 32 bits
    }

    bool gui_handler::is_entity_valid(entity_id id)
    {
        return get_entity_index(id) != entity_index(-1);
    }

    void gui_handler::update()
    {}

    void gui_handler::render()
    {
        for (int i = 0; i < component_pool_size; i++)
        {
            for (int j = 0; j < entities_size; j++)
            {
                entity_id id = entities[j].id;
                if (!is_entity_valid(id)) continue;
                entity_index index = get_entity_index(id);

                component_pools[i].get(index);
            }
        }
    }

    gui_handler::gui_handler() : component_pool_size(0), entities_size(0)
    {}
}