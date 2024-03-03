#include "atomic_counters.hpp"

atomic_counter_lock::atomic_counter_lock()
    : atomic_counter()
    , m_value(0)
    , m_lock() {
}

int atomic_counter_lock::increment() {
    // TODO: Add locks here
    m_lock.lock();
    int prev_value = m_value;
    m_value = m_value + 1;
    m_lock.unlock();
    return prev_value;
}

int atomic_counter_lock::decrement() {
    // TODO: Add locks here
    m_lock.lock();
    int prev_value = m_value;
    m_value = m_value - 1;
    m_lock.unlock();
    return prev_value;
}

void atomic_counter_lock::set(int value) {
    // TODO: Add locks here
    m_lock.lock();
    m_value = value;
    m_lock.unlock();
}

int atomic_counter_lock::get() {
    // TODO: Add locks here
    m_lock.lock();
    int v = m_value;
    m_lock.unlock();
    return v;
}
