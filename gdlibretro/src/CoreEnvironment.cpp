#include "RetroHost.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <cstdarg> // Required for va_start and va_end

// Logging function for the core
void core_log(enum retro_log_level level, const char *fmt, ...)
{
    char buffer[4096] = {0};
    static const char *levelstr[] = {"DEBUG", "INFO", "WARN", "ERROR"};
    va_list va;

    va_start(va, fmt);
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wformat-nonliteral"
        vsnprintf(buffer, sizeof(buffer), fmt, va);
    #pragma clang diagnostic pop
    va_end(va);

    godot::UtilityFunctions::print("[RetroHost Loaded CORE][" +
                                    godot::String(levelstr[level - 1]) + "] " + buffer);
}

// Retrieves a core variable
bool RetroHost::get_variable(retro_variable *variable)
{
    if (!this->core_variables[variable->key].IsDefined())
    {
        godot::UtilityFunctions::printerr("[RetroHost] Core variable ", variable->key, " not defined");
        return false;
    }

    auto var_value = core_variables[variable->key].as<std::string>();
    if (var_value.empty())
    {
        godot::UtilityFunctions::printerr("[RetroHost] Core variable ", variable->key, " was empty ", var_value.c_str());
        return false;
    }

    const std::string::size_type size = var_value.size();
    char *buffer = new char[size + 1];
    memcpy(buffer, var_value.c_str(), size + 1);

    this->please_free_me_str.push_back(buffer);

    variable->value = buffer;
    return true;
}

// Helper function to split strings
std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

// Handles various core environment commands
bool RetroHost::core_environment(unsigned command, void *data){

    godot::UtilityFunctions::print("[RetroHost] core_environment called with command: ", command);

    switch (command)
    {
        case RETRO_ENVIRONMENT_GET_LOG_INTERFACE:
        {
            godot::UtilityFunctions::print("[RetroHost] RETRO_ENVIRONMENT_GET_LOG_INTERFACE called.");
            struct retro_log_callback *cb = (struct retro_log_callback *)data;
            cb->log = core_log;
        }
        break;

        case RETRO_ENVIRONMENT_GET_CAN_DUPE:
        {
            godot::UtilityFunctions::print("[RetroHost] Core can dupe set.");
            bool *b = (bool *)data;
            *b = true;
        }
        break;

        case RETRO_ENVIRONMENT_GET_VARIABLE:
        {
            auto var = (retro_variable *)data;
            godot::UtilityFunctions::print("[RetroHost] RETRO_ENVIRONMENT_GET_VARIABLE called for key: ", var->key);
            return this->get_variable(var);
        }
        break;

        case RETRO_ENVIRONMENT_SET_VARIABLES:
        {
            auto variables = (const struct retro_variable *)data;
            while (variables->key)
            {
                if (!this->core_variables[variables->key].IsDefined())
                {
                    std::string value = variables->value;
                    auto possible_values_str = split(value, ";")[1].erase(0, 1);
                    auto possible_values = split(possible_values_str, "|");
                    this->core_variables[variables->key] = possible_values[0];

                    godot::UtilityFunctions::print("[RetroHost] Core variable ", variables->key, 
                        " was not present in the config file, now set to the first possible value: ", 
                        possible_values[0].c_str());
                }
                variables++;
            }
        }
        break;

        case RETRO_ENVIRONMENT_GET_VFS_INTERFACE:
        {
            auto vfs_interface = (struct retro_vfs_interface_info *)data;
            godot::UtilityFunctions::print("[RetroHost] Core requested VFS interface");
            if (vfs_interface->required_interface_version > this->vfs.supported_interface_version)
            {
                godot::UtilityFunctions::printerr("[RetroHost] Core requested VFS interface v",
                                                  vfs_interface->required_interface_version, 
                                                  " we only support up to v", 
                                                  this->vfs.supported_interface_version);
                return false;
            }
            vfs_interface->iface = &this->vfs.vfs_interface;
            return true;
        }
        break;

        case RETRO_ENVIRONMENT_SET_PIXEL_FORMAT:
        {
            const enum retro_pixel_format *fmt = (enum retro_pixel_format *)data;
            if (*fmt > RETRO_PIXEL_FORMAT_RGB565)
            {
                return false;
            }

            godot::UtilityFunctions::print("[RetroHost] Core setting pixel format");
            return this->core_video_set_pixel_format(*fmt);
        }
        break;

        case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY:
        case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY:
        case RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY:
        case RETRO_ENVIRONMENT_GET_LIBRETRO_PATH:
        {
            godot::UtilityFunctions::print("[RetroHost] Core requested path");
            *(const char **)data = this->cwd.utf8().get_data();
            return true;
        }

        case RETRO_ENVIRONMENT_SHUTDOWN:
        {
            godot::UtilityFunctions::print("[RetroHost] Core shutdown requested");
            break;
        }

        default:
        {
            godot::UtilityFunctions::print("[RetroHost] Command ", command, " not handled explicitly.");
            return false;
        }
    }

    return true;
}
