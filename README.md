# Task Manager

Every day at LambdaDesk, a fresh list of tasks arrives from Product, Engineering, Design, and more teams. Your job is to turn this list into helpful views: what’s urgent, what’s quick to finish, and what needs attention next. Instead of writing many separate loops, you’ll write small functions right where you need them—C++ lambda functions.

You’ll add a tiny helper class that can run functions over a list of `Task`s. Then you’ll use lambdas to build and print the list, filter items, sort them, rename them, and make quick summaries. Along the way you’ll practice different capture modes (by value and by reference), generic lambdas, and even lambdas that remember a little bit of state.
## Construct Tasks with a Transform

1. Let’s start by turning the raw inputs into real `Task` objects. In `main.cpp`, under the `== All ==` print statement, use `std::transform()` to fill the `tasks` vector from the indices in `idx`. Provide a lambda that takes an `int i`, captures the source arrays `names`, `priorities`, `times`, and `depts` by reference, and returns a `Task` constructed from `names[i]`, `priorities[i]`, `times[i]`, and `depts[i]` using the `Task` constructor.

2. Now let’s make sure the initial list looks correct. Loop over `tasks` and for each `task`, call the member function `task.print()`.

## Filter with Lambdas

3. It’s time to give the code a clear way to build focused views. In `TaskUtils.hpp`, declare a public and static function named `filter()` that returns `std::vector<Task>` and takes two parameters: a `const std::vector<Task>&` named `tasks` and a `const std::function<bool(const Task&)>&` named `predicate()`. Keep the function body empty for now.

4. Now let’s connect the declaration to its implementation. In `TaskUtils.cpp`, start the `filter()` definition by writing the full function signature that matches the declaration in the header and opening the function body.

5. Let’s keep filtering efficient as lists grow. Inside `filter()`, create a local `std::vector<Task> result` to hold the filtered tasks.

6. Now let’s decide which tasks stay in the view. Write a loop that iterates over all the tasks in the input vector as `const auto& task`. Inside the loop, call the predicate with `predicate(task)` and store the boolean in a local variable named `keep`. If `keep` is `true`, push the current `task` into `result` using `result.push_back(task)`. After the loop finishes, return `result`.

7. Finally, let’s create a simple engineering-focused view. In `main.cpp`, after the `== Eng >2h ==` print statement, create a new `auto` variable named `engLong` to store the result of calling `TaskUtils::filter()` with `tasks` and a lambda that accepts a `const Task& task`, captures needed variables implicitly by reference, and returns `true` only when `task.getDepartment()` is `"Engineering"` and `task.getEstimatedTimeHours()` is greater than `2.0`. Then, for each `const auto& task` in `engLong`, call `task.print()`.

## Act with Lambdas

8. Let’s enable batch updates across tasks. In `TaskUtils.hpp`, declare a public and static function named `forEach()` that returns `void` and takes two parameters: a `std::vector<Task>&` named `tasks` and a `const std::function<void(Task&)>&` named `op()`.

9. Now let’s start applying batch actions to tasks. In `TaskUtils.cpp`, start the `forEach()` definition by writing the full function signature that matches the header and opening the function body. Keep the function body empty for now.

10. Next, let’s allow the user to apply the function to each task. Inside `forEach()`, write a loop `for (auto& task : tasks)` so that each element can be modified in place via a non-`const` reference. Inside the loop body, call the provided operation with `op(task)`. Do not add any other logic here—the `op()` lambda decides what action to take on each `task`.

11. Let’s finish by clearing quick tasks from the list. In `main.cpp`, after the `== Short Tasks Done ==` print statement, call `TaskUtils::forEach()` with `tasks` and a lambda that captures `shortThreshold` and `newlyDoneCount` by reference, marks any task whose time is less than or equal to `shortThreshold` as done using `task.getEstimatedTimeHours()`, `task.isDone()`, and `task.setDone(true)`, and increments `newlyDoneCount` each time a task is completed. Afterward, print:

```
Marked <X> short tasks done
```

Where `X` is the updated count stored in `newlyDoneCount`.
## Sort with Lambdas

12. Let’s show important work first. In `TaskUtils.hpp`, declare a public and static function named `sort()` that returns `void` and takes a `std::vector<Task>&` named `tasks` and a `const std::function<bool(const Task&, const Task&)>&` named `lessThan()`.

13. We should keep ordering logic flexible. In `TaskUtils.cpp`, start the `sort()` definition by writing a function whose signature exactly matches the declaration you just added in the header. You will implement a selection sort that orders the vector using the provided comparator `lessThan()`. Keep the function body empty for now.

14. It’s time to mark the position of the best candidate for the front of the remaining unsorted range. Inside `sort()`, write a `for` loop that starts at integer index `i = 0` and runs while `i < tasks.size()`. At the start of each outer iteration, set an integer `bestIndex = i`.

15. Let’s compare the remaining items to find the minimum value. Write an inner loop inside the `for` loop with integer `j` starting at `i + 1` and running while `j < tasks.size()`. Each time `lessThan(tasks[j], tasks[bestIndex])` returns `true`, update `bestIndex = j`.

16. Now let’s place the lowest value in position. After the inner loop finishes, check if `bestIndex != i`. If so, swap `tasks[i]` and `tasks[bestIndex]` using `std::swap(tasks[i], tasks[bestIndex])`.

17. It’s time to rank our tasks by priority for a clear top list. In `main.cpp`, after the `== Priority ↓ ==` print statement, call `TaskUtils::sort()` on `tasks` with a comparator lambda that orders by descending priority so higher priorities appear first. Name the lambda parameters `a` and `b`, both of type `const Task&`, and return `true` when `a.getPriority()` is greater than `b.getPriority()`.

18. Let’s confirm that the order looks right. Still in `main.cpp`, iterate the sorted `tasks` to print each item by calling the `print()` method on each task.

## Apply with Lambdas

19. Now let’s allow different views of the data without changing the data itself. In `TaskUtils.hpp`, declare a public and static function named `apply()` that returns `std::vector<Task>` and takes a `const std::vector<Task>&` named `tasks` and a `const std::function<Task(const Task&)>&` named `transformer()`.

20. Let’s start by building the new list of tasks step by step. In `TaskUtils.cpp`, start the `apply()` definition by writing a function whose signature exactly matches the declaration you just added in the header. Inside `apply()`, create a local vector named `result` to hold transformed tasks. Keep the rest of the function body empty for now.

21. Now let’s apply the chosen transformation to each task. Still in the `apply()` function, write a loop that iterates over the input vector by `const` reference as `const auto& task`. For each `task`, call `transformer(task)` to obtain a new `Task` and push that returned value into `result`. After the loop, return `result`.

22. Let’s highlight high-priority tasks. In `main.cpp`, after the `== Renamed [HOT] ==` print statement, declare a vector named `renamed` and initialize it with the result of calling `TaskUtils::apply()` on `tasks` and a stateless lambda that takes a `const Task& task` and returns a new `Task` whose name is prefixed with `"[HOT] "` when `task.getPriority()` is at least `8`. Preserve the original fields by using `task.getName()` (with the prefix when applicable), `task.getPriority()`, `task.getEstimatedTimeHours()`, `task.getDepartment()`, and `task.isDone()`.

23. Finally, iterate the `renamed` vector and, for each `const auto& task`, call `task.print()` to display the updated tasks.

## Generic Lambdas and Captures

24. Let’s give the team a quick snapshot of progress. In `main.cpp`, after the `== Summary ==` print statement, write a generic `summarize()` lambda that takes a `const auto& list`, which is a vector of tasks. Inside, count the total number of tasks, count how many are done using `task.isDone()`, and sum the estimated hours as a `double` using `task.getEstimatedTimeHours()`).

25. It’s time to share the headline numbers clearly. Still in the `summarize()` lambda, use the numbers you calculated to print:

```
Summary: <N> tasks, <D> done, total est. time = <H>h
```

For example:

```
Summary: 10 tasks, 3 done, total est. time = 4h
```

Then, call `summarize(tasks)`.

26. Now let’s link each printed task to its project name. In `main.cpp`, under the print statement for `== Project tag ==`, define a lambda named `showWithProject()` that takes a `const Task& task` and captures `projectName` by value. It should print this project name and then call `task.print()`.

27. Let’s apply the project tag consistently. Write a `for` loop over `tasks` that calls `showWithProject(task)` each iteration.

28. Now let’s track completion as you scan the list. Define a lambda named `countDone()` that takes a `const Task& task`, captures `doneCount` by reference, and increments `doneCount` when `task.isDone()` is `true`. Loop over `tasks`, call `countDone(task)` for each, and then print `Done: <Y>` where `Y` is the final value of `doneCount`.

29. Finally, let’s watch for items that may need attention soon. Define a lambda named `countAbove()` that captures `priorityThreshold` by value and `flaggedCount` by reference, and increments `flaggedCount` when `task.getPriority()` is greater than `7`. Loop over `tasks` with this lambda, then print:

```
Flagged > 7: <result>
```

## Stateful Closures and Init-Captures

30. And now let’s label output for export batches. In `main.cpp`, under the print statement for `== First 3 (batch) ==`, define a lambda named `showWithBatch()` that takes a `const Task& task` and uses an init-capture to build and capture a `std::string` named `msg` with the value `"Batch-"` followed by `std::to_string(batchId)`. The lambda should print the captured `msg`, a space, two colons, another space, and then the task using `task.print()`. For example, if `batchId` is `42`, the output lines should look like:

```
Batch-42 :: Task{name='Parser', priority=9, time=5.50h, dept='Engineering', done=no}
Batch-42 :: Task{name='Sec Audit', priority=9, time=4.00h, dept='Security', done=no}
Batch-42 :: Task{name='Fix CI', priority=8, time=1.20h, dept='Engineering', done=yes}
```

31. Finally, invoke `showWithBatch(task)` for the first three tasks, or fewer if the list has fewer than three items.

## Congrats!

32. Great work! You used lambdas to build, filter, sort, transform, and summarize tasks. You also practiced captures, generic lambdas, and stateful lambdas. LambdaDesk can now slice and label task queues with clear, compact code.

Want to try more?

- Add a tie-breaker to your sort: if two tasks have the same priority, order them by `estimatedTimeHours` (shorter first).
- Print a short report by department. Count tasks per department with a lambda and print lines like `Engineering: 3`.
- Write a transformer that appends the priority to each name, e.g., `"Parser (P9)"`.
- Make a small factory function `makePrefixer(std::string tag)` that returns a lambda capturing `tag`, then use it to tag tasks with different project names.
