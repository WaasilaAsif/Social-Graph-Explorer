#pragma once
#include "MsgAPI.h"
#include "../../libs/crow/crow_all.h"

class MsgRoutes {
public:
    MsgRoutes(MsgAPI* api);
    void registerRoutes(crow::SimpleApp& app);

private:
    MsgAPI* msgApi;
};
