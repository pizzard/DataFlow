/*
 * Trigger.h
 *
 *  Created on: 15.04.2015
 *      Author: Caspar
 */

#ifndef CORE_TRIGGER_H_
#define CORE_TRIGGER_H_
#include <vector>
#include <functional>
#include <atomic>

class Trigger {
public:
	Trigger(const int rate);
	virtual ~Trigger();

	void Run() {
		for (std::function<void(void)>& job : workload) {
			job();
		}
	}

private:
	const int cycle_rate; ///< Cycle rate of this trigger in multiples of the atomic trigger rate. invariant: cycle_rate > 0
	std::vector<std::function<void(void)>> workload; ///< all elements will be called every time the Trigger runs;
	std::atomic<bool> running;

};

class TriggerManager {
public:

private:
	std::vector<std::weak_ptr<Trigger>> triggers; //Todo weak_ptr really the best way to handle potential deletion of triggers?

};

#endif /* CORE_TRIGGER_H_ */
