#include "TaskUtils.hpp"

std::vector<Task> TaskUtils::filter(
    const std::vector<Task>& tasks,
    const std::function<bool(const Task&)>& predicate
)
{
    std::vector<Task> result;
    for (const auto& task : tasks) {
        if (predicate(task)) {
            result.push_back(task);
        }
    }
    return result;   
}

void forEach(
        std::vector<Task>& tasks,
        const std::function<void(Task&)>& op
) 
{
    for (auto& task : tasks) {
        op(task);
    }
}