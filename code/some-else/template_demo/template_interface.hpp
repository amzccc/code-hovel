/*********************************************************************************
 * @file		template_interface.hpp
 * @brief		
 * @author		cheng wentao
 * @version		v1.0.0
 * @date		2024-08-06 21:05
 **********************************************************************************/
#ifndef TEMPLATE_INTERFACE_H__
#define TEMPLATE_INTERFACE_H__

#include "template_inner.hpp"

template<Kind K, Voice V, Leg L>
struct Selection : public inner::SelectInner<K, V, L> {
    void property() {
        inner::SelectInner<K, V, L>::property();
    }
};

#endif // !template_interface.hpp