#include "ThreadPool.h"
#include<functional>
using namespace std;

ThreadPool::ThreadPool(int min, int max) : m_maxThread(max), m_minThread(min), m_stop(false), m_idleThread(min), m_curThread(min)
{
    // 创建管理者
    m_manager = new thread(&ThreadPool::manager, this);

    // 创建工作线程
    for (int i = 0; i < min; i++)
    {
        thread t(&ThreadPool::worker, this);
        m_workers[t.get_id()] =  move(t);
    }
}

void ThreadPool::AddTask(function<void(void)> task)
{
    {
        // 线程同步
        lock_guard<mutex> locker(m_queueMutex); // 加锁，locker被析构的时候解锁
        m_tasks.emplace(task);                  // 队列任务里加入任务
    }

    // 唤醒
    m_condition.notify_one();
}

void ThreadPool::manager()
{
    while (!m_stop.load())
    {
        this_thread::sleep_for(chrono::seconds(3));
        int idel = m_idleThread.load();
        int cur = m_curThread.load();

        // 空闲线程太多就销毁，空闲线程不够就创建
        if (idel > cur / 2 && cur > m_minThread)
        {
            m_exitThread.store(2);
            m_condition.notify_all();
            lock_guard<mutex> lck(m_idsMutex);
            // 销毁线程
            for (auto id : m_ids)
            {
                auto it = m_workers.find(id);
                if (it != m_workers.end())
                {
                    (*it).second.join(); // 销毁
                    m_workers.erase(it);
                }
            }
            m_ids.clear();
        }
        else if (idel == 0 && cur < m_maxThread)
        {
            thread t(&ThreadPool::worker, this);
            m_workers[t.get_id()] =  move(t);
            m_curThread++;
            m_idleThread++;
        }
    }
}

void ThreadPool::worker()
{
    while (!m_stop.load()) // 线程池未关闭的时候就一直循环
    {
        std::function<void(void)> task = nullptr;
        {
            unique_lock<mutex> locker(m_queueMutex);
            while (m_tasks.empty() && !m_stop) // 任务队列空
            {
                m_condition.wait(locker); // 锁的控制权交给wait
                if (m_exitThread.load() > 0)
                {
                    m_curThread--;
                    m_exitThread--;
                    // 线程退出
                    lock_guard<mutex> lck(m_idsMutex);
                    m_ids.emplace_back(this_thread::get_id());
                    return;
                }
            }

            // 取任务
            if (!m_tasks.empty())
            {
                task = move(m_tasks.front());
                m_tasks.pop();
            }
        }

        // 执行任务
        if (task)
        {
            m_idleThread--; // 空弦线程--;
            task();
            m_idleThread++;
        }
    }
}
