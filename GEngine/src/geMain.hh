#pragma once

#include "App.hh"
#include "utils/Logger.hh"

int main(int argc, char** argv)
{
    GE::utils::Logger::init();

    ENGINE_LOG_INFO("Engine Logger Initialized");
    LOG_INFO("Client Logger Initialized");

    GE::Uptr<GE::App> app{GE::createApp()};
    app->run();
}