/*
 * functional.h
 *
 *  Created on: 08.04.2015
 *      Author: Caspar
 */

#ifndef CORE_FUNCTIONAL_H_
#define CORE_FUNCTIONAL_H_
#include <algorithm>
#include <vector>

#include "master_traits.h"

template<class Function>
struct copy_map {
	copy_map(Function f) :
			fun(f), result_container() {
	}
	typedef typename utils::function_traits<Function>::result_type base_t;
	typedef typename std::vector<base_t> result_type;

	template<class ForwardRange>
	auto operator()(const ForwardRange&& in) {
		result_container.clear();
		std::transform(begin(in), end(in), back_inserter(result_container),
				fun);
		return result_container;
	}

private:
	Function fun;
	result_type result_container; //ToDo reevaluate choice of vector
};

template<class Function>
struct in_place_map {
	in_place_map(Function f) :
			fun(f) {
	}

	template<class ForwardRange>
	auto operator()(ForwardRange&& in) {
		auto end = std::transform(begin(in), end(in), in.begin(), fun);
		return std::make_pair(in.begin(), end); //todo the pair is not a real range
	}

private:
	Function fun;
};

template<class Function>
static auto map(const Function& f) {
	return copy_map<Function>(f);
}

template<class OutputType, class Pred>
class filter {
	filter(Pred p) :
			predicate(p) {

	}

	typedef OutputType result_type;

	template<class ForwardRange>
	auto operator()(const ForwardRange&& in) {
		auto it = std::copy_if(begin(in), end(in), result_cont.begin(),
				predicate);
		result_cont.resize(std::distance(result_cont.begin(), it));
		return result_cont;
	}

	Pred predicate;
	OutputType result_cont;

};

template<class T, class BinaryOperation>
class foldl {
	foldl(BinaryOperation op, T init) :
			binop(op), initial_value(init) {

	}

	typedef T result_value;

	template<class ForwardRange>
	auto operator()(const ForwardRange&& in) {
		return std::accumulate(begin(in), end(in), initial_value, binop);
	}

private:
	BinaryOperation binop;
	const T initial_value;
};

template<class T, class BinaryOperation>
class foldr {
	foldr(BinaryOperation op, T init) :
			binop(op), initial_value(init) {

	}

	typedef T result_value;

	template<class ForwardRange>
	auto operator()(const ForwardRange&& in) {
		return std::accumulate(rbegin(in), rend(in), initial_value, binop);
	}

private:
	BinaryOperation binop;
	const T initial_value;
};

#endif /* CORE_FUNCTIONAL_H_ */
