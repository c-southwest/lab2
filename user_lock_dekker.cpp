#include "user_locks.hpp"
#include <iostream>
#include <stdio.h>

#define READ_MEMORY_ORDER std::memory_order_acquire
#define WRITE_MEMORY_ORDER std::memory_order_release

user_lock_dekker::user_lock_dekker()
    : user_lock() {
    m_flag[0] = m_flag[1] = false;
    m_turn = false;
    m_flag_a[0].store(0);
    m_flag_a[1].store(0);
    m_turn_a.store(0);
}

const std::memory_order mo = std::memory_order_relaxed;   // strange, use mo program will be correct.

void user_lock_dekker::lock(int thread_id) {
    // TODO: Implement the lock acquire part of the Dekker algorithm here
    m_flag_a[thread_id].store(true, WRITE_MEMORY_ORDER);// = true;
    std::atomic_thread_fence(std::memory_order_seq_cst);
    int j = thread_id == 1 ? 0 : 1;
    while(m_flag_a[j].load(READ_MEMORY_ORDER) == true){
        if(m_turn_a.load(READ_MEMORY_ORDER) != thread_id){
            m_flag_a[thread_id].store(false, WRITE_MEMORY_ORDER);// = false;
            while(m_turn_a.load(READ_MEMORY_ORDER) != thread_id){
            }
            m_flag_a[thread_id].store(true, WRITE_MEMORY_ORDER);// = true;
            std::atomic_thread_fence(std::memory_order_seq_cst);
        }
    }
    // printf("thread %d get the lock, turn:%d, flag[0]=%d, flag[1]=%d\n",
    // thread_id, m_turn_a.load(),  m_flag_a[0].load(), m_flag_a[1].load());

    //printf("thread %d try to get lock\n", thread_id);
    // m_flag[thread_id] = true;
    // int j = thread_id == 1 ? 0 : 1;
    // int c = 0;
    // while (m_flag[j] == true) {
    //     if (m_turn != thread_id) {
    //         m_flag[thread_id] = false;
    //         int count = 0;
    //         while (m_turn != thread_id) {
    //             printf(
    //                 "thread %d inner while, turn:%d, flag[0]=%d, flag[1]=%d\n",
    //                 thread_id, m_turn, m_flag[0], m_flag[1]);
    //             count++;
    //             if (count >= 40) {

    //                 printf("Finished thread %d inner while, turn:%d, "
    //                        "flag[0]=%d, flag[1]=%d\n",
    //                        thread_id, m_turn, m_flag[0], m_flag[1]);
    //                 exit(0);
    //             }
    //         }
    //         m_flag[thread_id] = true;
    //     }
    //     printf("thread %d outer while, turn:%d, flag[0]=%d, flag[1]=%d\n",
    //            thread_id, m_turn, m_flag[0], m_flag[1]);
    //     if (c >= 40) {
    //         printf("Finished thread %d inner while, turn:%d, flag[0]=%d, "
    //                "flag[1]=%d\n",
    //                thread_id, m_turn, m_flag[0], m_flag[1]);
    //         exit(0);
    //     }
    // }
    // printf("thread %d get the lock, turn:%d, flag[0]=%d, flag[1]=%d\n",
    // thread_id, m_turn,  m_flag[0], m_flag[1]);
}

void user_lock_dekker::unlock(int thread_id) {
    // TODO: Implement the lock release part of the Dekker algorithm here
    int j = thread_id == 1 ? 0 : 1;
    m_turn_a.store(j, WRITE_MEMORY_ORDER);// = j;
    m_flag_a[thread_id].store(false, WRITE_MEMORY_ORDER);// = false;
}
