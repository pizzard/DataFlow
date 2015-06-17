/*
 * Thread.h
 *
 *  Created on: 15.04.2015
 *      Author: Caspar
 */

#ifndef CORE_THREAD_H_
#define CORE_THREAD_H_

#include <thread>
#include <vector>

enum rate
{
	fast = 10,
	slow = 100,
	very_slow = 500,
};


class Thread {

public:
	Thread();
	virtual ~Thread();

private:
};

class ThreadManager {
public:

private:
	using ThreadPool = std::vector<std::thread>;


};

#endif /* CORE_THREAD_H_ */
