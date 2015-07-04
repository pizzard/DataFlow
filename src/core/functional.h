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
static auto map(const Function&& f) {
	return copy_map<Function>(f);
}

template<class OutputType, class Pred>
struct copy_filter {
	copy_filter(Pred p) :
			predicate(p), result_container() {

	}

	//ToDo should be able to get this through a metafunction from lhs of connection
	typedef std::vector<OutputType> result_type;

	template<class ForwardRange>
	auto operator()(const ForwardRange&& in) {
		result_container.resize(in.size());
		auto it = std::copy_if(begin(in), end(in), result_container.begin(),
				predicate);
		result_container.resize(std::distance(result_container.begin(), it));
		return result_container;
	}

private:
	Pred predicate;
	result_type result_container;
};

template<class OutputType, class Pred>
static auto filter(const Pred&& p) {
	return copy_filter<OutputType, Pred>(p);
}

template<class T, class BinaryOperation>
struct foldl_t {
	foldl_t(BinaryOperation op, T init) :
			binop(op), initial_value(init) {

	}

	typedef T result_type;

	template<class ForwardRange>
	auto operator()(const ForwardRange&& in) {
		return std::accumulate(begin(in), end(in), initial_value, binop);
	}

private:
	BinaryOperation binop;
	const T initial_value;
};

template<class T, class BinaryOperation>
static auto fold(BinaryOperation op, T init) {
	return foldl_t<T, BinaryOperation>(op, init);
}


#endif /* CORE_FUNCTIONAL_H_ */
