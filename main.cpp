#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

#include "Task.hpp"
#include "TaskUtils.hpp"

int main() {
    const std::vector<std::string> names {
        "Spec Rev", "Parser", "Roadmap",
        "Fix CI", "UI Proto", "Metrics",
        "Sec Audit", "DB Mig", "Docs"
    };
    const std::vector<int> priorities{ 6, 9, 7, 8, 5, 6, 9, 8, 4 };
    const std::vector<double> times { 1.0, 5.5, 2.5, 1.2, 3.0, 2.0, 4.0, 6.0, 1.5 };
    const std::vector<std::string> depts {
        "Product", "Engineering", "Product",
        "Engineering", "Design", "Data",
        "Security", "Engineering", "Product"
    };
    
    std::vector<int> idx(names.size());
    for (int i = 0; i < idx.size(); ++i) idx[i] = i;
    
    std::vector<Task> tasks(idx.size());

    std::cout << "== All ==" << std::endl;
    std::transform(idx.begin(), idx.end(), tasks.begin(), [&](int i) {
        return Task(names[i], priorities[i], times[i], depts[i]);
    });
    for (const auto& t : tasks) {
        t.print();
    }

    std::cout << std::endl << "== Eng >2h ==" << std::endl;

    double shortThreshold = 1.5;
    int newlyDoneCount = 0;
    std::cout << std::endl << "== Short Tasks Done ==" << std::endl;



    std::cout << std::endl << "== Priority ↓ ==" << std::endl;

    std::cout << std::endl << "== Renamed [HOT] ==" << std::endl;

    std::cout << std::endl << "== Summary ==" << std::endl;

    const std::string projectName = "Apollo";
    std::cout << std::endl << "== Project tag ==" << std::endl;

    int batchId = 42;
    std::cout << std::endl << "== First 3 (batch) ==" << std::endl;

    return 0;
}