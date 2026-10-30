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

void TaskUtils::forEach(
        std::vector<Task>& tasks,
        const std::function<void(Task&)>& op
) 
{
    for (auto& task : tasks) {
        op(task);
    }
}

void TaskUtils::sort(
        std::vector<Task>& tasks,
        const std::function<bool(const Task&, const Task&)>& lessThan
) {
    for (int i = 0; i < tasks.size(); ++i) {
        int bestIndex = i;
        for (int j = i + 1; j < tasks.size(); ++j) {
            if (lessThan(tasks[j], tasks[bestIndex])) {
                bestIndex = j;
            }
        }
        if (bestIndex != i) {
            std::swap(tasks[i], tasks[bestIndex]);
        }
    }
}