#pragma once

#include "App.hh"
#include "Logger.hh"

int main(int argc, char** argv)
{
    GE::Logger::init();

    ENGINE_LOG_INFO("Engine Logger Initialized");
    LOG_INFO("Client Logger Initialized");

    auto* app = GE::createApp();
    app->run();
    delete app;
}