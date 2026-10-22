// Z Midna Guard
//
// Problem: in the Twilit Essentials Boss Rush, pressing Z still calls Midna even though Z is
// meant to be an item slot and Midna has her own button (L or D-Pad Left).
//
// Fix: post-hook daAlink_c::midnaTalkTrigger(). The vanilla function returns true when the
// Z button was pressed this frame (mItemTrigger & BTN_Z), unless a custom Midna bind is set.
// If the call was triggered by Z, we turn the result back into false. A call triggered by
// Midna's own button does not set BTN_Z, so it is left alone.
//
// Z items themselves are untouched: we never modify mItemTrigger, only the Midna result.

#include "global.h"
#include "d/actor/d_a_alink.h"

#include "mods/service.hpp"
#include "mods/svc/hook.h"
#include "mods/svc/hook.hpp"
#include "mods/svc/log.h"

DEFINE_MOD();
IMPORT_SERVICE(HookService, svc_hook);
IMPORT_SERVICE(LogService, svc_log);

DEFINE_HOOK(&daAlink_c::midnaTalkTrigger, MidnaTalkTrigger);

static void on_midna_talk_trigger_post(ModContext*, void* args, void* retval, void*) {
    if (args == nullptr || retval == nullptr) {
        return;
    }

    BOOL& result = *static_cast<BOOL*>(retval);
    if (!result) {
        return;
    }

    const daAlink_c* link = mods::arg<const daAlink_c*>(args, 0);
    if (link == nullptr) {
        return;
    }

    // Only cancel calls that came from the Z button.
    if (link->mItemTrigger & daAlink_c::BTN_Z) {
        result = FALSE;
    }
}

extern "C" {

MOD_EXPORT ModResult mod_initialize(ModError* error) {
    const ModResult result = mods::hook::add_post<MidnaTalkTrigger>(on_midna_talk_trigger_post);
    if (result != MOD_OK) {
        return mods::set_error(error, result, "failed to hook daAlink_c::midnaTalkTrigger");
    }
    svc_log->info(mod_ctx, "Z Midna Guard active: Z no longer calls Midna");
    return MOD_OK;
}

MOD_EXPORT ModResult mod_update(ModError*) {
    return MOD_OK;
}

MOD_EXPORT ModResult mod_shutdown(ModError*) {
    return MOD_OK;
}
}
