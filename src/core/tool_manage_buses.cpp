#include "tool_manage_buses.hpp"
#include "core_board.hpp"
#include "core_schematic.hpp"
#include "core_frame.hpp"
#include <iostream>

namespace horizon {

ToolManageBuses::ToolManageBuses(Core *c, ToolID tid) : ToolBase(c, tid)
{
}

bool ToolManageBuses::can_begin()
{
    switch (tool_id) {
    case ToolID::MANAGE_BUSES:
    case ToolID::ANNOTATE:
    case ToolID::MANAGE_NET_CLASSES:
    case ToolID::EDIT_SCHEMATIC_PROPERTIES:
    case ToolID::MANAGE_POWER_NETS:
    case ToolID::TOGGLE_GROUP_TAG_VISIBLE:
        return core.c;

    case ToolID::EDIT_STACKUP:
        return core.b;

    case ToolID::EDIT_FRAME_PROPERTIES:
        return core.f;

    default:
        return false;
    }
}

ToolResponse ToolManageBuses::begin(const ToolArgs &args)
{
    bool r = false;

    if (tool_id == ToolID::MANAGE_BUSES) {
        auto sch = core.c->get_schematic();
        r = imp->dialogs.manage_buses(sch->block);
    }
    else if (tool_id == ToolID::ANNOTATE) {
        auto sch = core.c->get_schematic();
        r = imp->dialogs.annotate(sch);
    }
    else if (tool_id == ToolID::MANAGE_NET_CLASSES) {
        auto sch = core.c->get_schematic();
        r = imp->dialogs.manage_net_classes(sch->block);
    }
    else if (tool_id == ToolID::EDIT_SCHEMATIC_PROPERTIES) {
        r = imp->dialogs.edit_schematic_properties(core.c->get_schematic(), core.c->m_pool);
    }
    else if (tool_id == ToolID::EDIT_STACKUP) {
        r = imp->dialogs.edit_stackup(core.b);
    }
    else if (tool_id == ToolID::MANAGE_POWER_NETS) {
        r = imp->dialogs.manage_power_nets(core.c->get_block());
    }
    else if (tool_id == ToolID::EDIT_FRAME_PROPERTIES) {
        r = imp->dialogs.edit_frame_properties(core.f->get_frame());
    }
    else if (tool_id == ToolID::TOGGLE_GROUP_TAG_VISIBLE) {
        auto sch = core.c->get_schematic();
        sch->group_tag_visible = !sch->group_tag_visible;
        r = true;
    }
    if (r) {
        core.r->commit();
    }
    else {
        core.r->revert();
    }
    return ToolResponse::end();
}
ToolResponse ToolManageBuses::update(const ToolArgs &args)
{
    return ToolResponse();
}
} // namespace horizon
