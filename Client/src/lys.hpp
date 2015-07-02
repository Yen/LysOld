#pragma once

// General Macros

#define LYS_STRINGIFY(s) #s
#define LYS_PAUSE system("pause")

// Logging System

#include <string>

std::string lysDateTime(const std::string &format);

#include <stdio.h>

#define LYS_LOGBASE(title, out, ...) printf("%s || " title ": " out "\n", lysDateTime("[%x] <%X>").data(), __VA_ARGS__);

#define LYS_LOG(out, ...) LYS_LOGBASE("Log", out, __VA_ARGS__);
#define LYS_LOG_ERR(out, ...) LYS_LOGBASE("Error", out, __VA_ARGS__);
#define LYS_LOG_FAITAL(out, ...) LYS_LOGBASE("Faital", out, __VA_ARGS__);
#define LYS_LOG_APP(out, ...) LYS_LOGBASE("Application", out, __VA_ARGS__);