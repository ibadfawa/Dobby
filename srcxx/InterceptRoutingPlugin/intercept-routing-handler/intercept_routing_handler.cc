
#include "hookzz_internal.h"

#include "logging/logging.h"

#include "intercept_routing_handler.h"
#include "MultiThreadSupport/ThreadSupport.h"

// Closure bridge branch here unitily, then  common_bridge_handler will dispatch to other handler.
void intercept_routing_common_bridge_handler(RegisterContext *reg_ctx, ClosureTrampolineEntry *entry) {
  DLOG("[*] catch common bridge handler, carry data: %p, carry handler: %p\n",
       ((HookEntry *)entry->carry_data)->target_address, entry->carry_handler);
  USER_CODE_CALL UserCodeCall = (USER_CODE_CALL)entry->carry_handler;
  UserCodeCall(reg_ctx, entry);
  return;
}
