#pragma once

#include "App.hh"
#include "utils/Logger.hh"
#include "utils/Instrumentor.hh"

int main(int argc, char** argv)
{
    GE::utils::Logger::init();

    GE_PROFILE_BEGIN("App startup", "AppStartupTrace.json");
    GE::Uptr<GE::App> app{GE::createApp()};
    GE_PROFILE_END();

    GE_PROFILE_BEGIN("App::run", "AppRuntimeTrace.json");
    app->run();
    GE_PROFILE_END();

    GE_PROFILE_BEGIN("App Shutdown", "AppShutdownTrace.json");
    app.reset();
    GE_PROFILE_END();
}