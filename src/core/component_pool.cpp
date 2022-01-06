#include "component_pool.h"
#include <cstdlib>
#include <core/gui_components.h>

namespace trade_history
{
    component_pool::component_pool() : 
        element_size(0), component_array(nullptr), component_id(u32(-1))
    {}

    component_pool::component_pool(u64 element_size, u32 component_id) : 
        element_size(element_size), component_id(component_id)
    {
        component_array = (i8 *)malloc(MAX_ENTITIES * element_size);
    }

    component_pool::~component_pool()
    {
        if (component_array != nullptr) free(component_array);
    }

    void *component_pool::get(u32 index)
    {
        return (void *)(component_array + index * element_size);
    }

    bool component_pool::delete_at(u32 index)
    {
        memset(get(index), 0, element_size);
        return true;
    }
    bool component_pool::is_empty()
    {
        return component_array == nullptr;
    }

    u32 component_pool::get_component_id()
    {
        return component_id;
    }
    
    component_pool &component_pool::operator=(component_pool &&other)
    {
        if (&other == this) return *this;

        element_size = other.element_size;
        component_array = other.component_array;
        
        other.component_array = nullptr;

        return *this;
    }
}
