/*
 * Operator.h
 *
 *  Created on: 28.02.2015
 *      Author: Caspar
 */

#ifndef CORE_OPERATOR_H_
#define CORE_OPERATOR_H_

#include <boost/signals2.hpp>
#include <functional>
#include <iostream>

#include "Connection.h"
#include "traits.h"

template<class T>
class InputPort {
public:
	//ToDo decide what to do, when Port is not connected
	T operator()() {
		return target_function();
	}

	template<class S>
	void connect(const S& source) {
		target_function = source;
	}

private:
	std::function<T(void)> target_function;
};

template<class T>
class OutputPort {
public:
	//ToDo what does this really need to do?
};

class Operator {
public:
	Operator() = default;

	InputPort<int> in;

	void Trigger() {
		std::cout << "OperatorPrint: " << in() << "\n";
	}

private:
};

template<class result_t, class receiver_t,
		class signal_t = boost::signals2::signal<result_t()>>
boost::signals2::connection Connect(boost::signals2::signal<result_t()>& sig,
		receiver_t& receiver) {
	return sig.connect(receiver);
}

template<class result_t, class sender_t>
	void Connect(const sender_t& sender, InputPort<result_t>& receiver) {
		receiver.connect(sender);
}

template<class sender_t, class receiver_t>
typename connection_trait<sender_t, receiver_t>::type Connect_impl(
		const sender_t& sender, const receiver_t& receiver) {
	return typename connection_trait<sender_t, receiver_t>::type { sender,
			receiver };
}

// This connection takes ownership of both sender and receiver
template<class sender_t, class receiver_t>
auto Connect(const sender_t& sender, const receiver_t& receiver){
	return Connect_impl(sender, receiver);
}

template<class sink_t, class source_t>
auto operator >>(const source_t& source, const sink_t& sink) {
	return Connect(source, sink);
}

template<class result_t, class source_t>
void operator >>(const source_t& source, InputPort<result_t>& sink) {
	Connect(source, sink);
}

#endif /* CORE_OPERATOR_H_ */
