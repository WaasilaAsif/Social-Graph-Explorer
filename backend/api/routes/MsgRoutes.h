#pragma once
#include "MsgAPI.h"
#include <crow.h>

class MsgRoutes {
public:
    MsgRoutes(MsgAPI* api);
    void registerRoutes(crow::SimpleApp& app);

private:
    MsgAPI* msgApi;
};
