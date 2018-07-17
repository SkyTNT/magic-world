#pragma once
#define _USE_MATH_DEFINES

#include <functional>

void commitMainThreadTask(std::function<void()> _task);
