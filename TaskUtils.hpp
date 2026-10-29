#pragma once

#include <vector>
#include <functional>
#include "Task.hpp"

class TaskUtils {
public:
    static std::vector<Task> filter(
        const std::vector<Task>& tasks,
        const std::function<bool(const Task&)>& predicate
    ); 
};