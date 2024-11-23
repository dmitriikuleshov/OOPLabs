#pragma once
#include "config.hpp"
#include "npc.hpp"
#include <filesystem>

class Battle {
  private:
    std::shared_ptr<INpcConfig> config;

  public:
    Battle(const std::string &config_file_path) {
        config = ConfigHandler::create_config(config_file_path);
    };
};