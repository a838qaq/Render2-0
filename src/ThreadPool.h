#pragma once
#include <thread>
#include <vector>
#include <atomic>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <map>
#include <future>
#include <memory>

using namespace std;

class NoneCopy
{
public:
    ~NoneCopy() {};

protected:
    NoneCopy() {};

private:
    NoneCopy(const NoneCopy &) = delete;
    NoneCopy &operator=(const NoneCopy &) = delete;
};

class ThreadPool
{
public:
    ThreadPool(int min = 2, int max = thread::hardware_concurrency());
    ~ThreadPool();

    // 添加任务
    void AddTask(std::function<void(void)> task);

    template <typename F, typename... Args>
    auto AddTask(F &&f, Args &&...args) -> future<typename std::result_of<F(Args...)>::type>
    {
        // 异步方法
        using returnType = typename std::result_of<F(Args...)>::type;
        // 添加package_task包装的实例
        auto mytask = make_shared<packaged_task<returnType()>>(bind(std::forward<F>(f), std::forward<Args>(args)...));

        // 得到future
        future<returnType> res = mytask->get_future();

        // 把任务函数添加到队列
        m_queueMutex.lock();
        m_tasks.emplace([mytask]()
                        { (*mytask)(); });
        m_queueMutex.unlock();
        m_condition.notify_one();

        return res;
    }

private:
    void manager();
    void worker();

private:
    thread *m_manager;        // 管理者
    vector<thread::id> m_ids; // 已经退出了任务函数的线程
    map<thread::id, thread> m_workers;

    atomic<int> m_minThread;
    atomic<int> m_maxThread;

    atomic<int> m_curThread;  // 当前
    atomic<int> m_idleThread; // 空闲
    atomic<int> m_exitThread; // 退出

    atomic<bool> m_stop;                  // 线程池开关
    queue<std::function<void()>> m_tasks; // 任务队列
    mutex m_queueMutex;
    mutex m_idsMutex;
    condition_variable m_condition; //  条件变量
};
