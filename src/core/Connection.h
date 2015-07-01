/*
 * Operator.h
 *
 *  Created on: 23.02.2015
 *      Author: Caspar
 */

#ifndef CORE_CONNECTION_
#define CORE_CONNECTION_

#include <type_traits>

#include "master_traits.h"
#include "traits.h"

template<class sender_t, class receiver_t, class param_type>
struct VoidConnection {
	sender_t sender;
	receiver_t receiver;
	void operator()(const param_type&& p) {
		///execute sender with parameter and execute receiver with result from sender
		receiver(sender(p));
	}
};

// partial  specialization for no parameter
template<class sender_t, class receiver_t>
struct VoidConnection<sender_t, receiver_t, void> {
	sender_t sender;
	receiver_t receiver;
	void operator()() {
		///execute sender and execute receiver with result from sender
		receiver(sender());
	}
};

template<class sender_t, class receiver_t, class receiver_result,
		class param_type>
struct Connection {
	sender_t sender;
	receiver_t receiver;
	receiver_result operator()(const param_type&& p) {
		///execute sender with parameter and execute receiver with result from sender
		return receiver(sender(p));
	}
};

// partial  specialization for no parameter
template<class sender_t, class receiver_t, class receiver_result>
struct Connection<sender_t, receiver_t, receiver_result, void> {
	sender_t sender;
	receiver_t receiver;
	receiver_result operator()() {
		///execute sender and execute receiver with result from sender
		return receiver(sender());
	}
};

template<bool no_arg, class T>
struct ParamType {
};

template<class T>
struct ParamType<true, T> {
	typedef void type;
};

template<class T>
struct ParamType<false, T> {
	typedef typename utils::function_traits<T>
	::template arg<0>::type type;
};

template<class sender_t, class receiver_t>
struct connection_trait {
	static const bool sender_no_arg = utils::function_traits<sender_t>::arity == 0;

	//static_assert(is_callable<sender_t>::value, "Left Hand Side of Connection must be callable");
	//static_assert(is_callable<receiver_t>::value, "Right Hand Side of Connection must be callable");

	typedef typename ParamType<sender_no_arg, sender_t>::type sender_param;
	//typedef typename utils::function_traits<receiver_t>::result_type receiver_result;
	typedef typename result_of<receiver_t>::type receiver_result;

	static const bool result_is_void = std::is_void<receiver_result>::value;
	typedef typename std::conditional<result_is_void,
			VoidConnection<sender_t, receiver_t, sender_param>,
			Connection<sender_t, receiver_t, receiver_result, sender_param>>::type type;
};



#endif /* CORE_CONNECTION_ */
