/*
 * Buffer.h
 *
 *  Created on: 27.02.2015
 *      Author: Caspar
 */

#ifndef CORE_BUFFER_H_
#define CORE_BUFFER_H_

#include <boost/core/noncopyable.hpp>
#include <cassert>
#include <mutex>

template<class Container>
class ReadView;
template<class Container>
class WriteView;

template<class Container>
class Buffer {
public:
	const ReadView<Container>& ReadAccess();
	WriteView<Container>& WriteAccess();

private:
	Container stored_data;
	std::mutex data_mutex;
};

template<class Container>
class View: public boost::noncopyable {
public:
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;

	const_iterator cbegin();
	const_iterator cend();
	size_t size();
	bool empty();

protected:
	View(Container* buffer_cont) :
			data(buffer_cont) {
		assert(buffer_cont); //There is no usecase for a null pointer.
	}
	Container* data;
private:
	std::lock_guard<std::mutex> lock;
};

template<class Container>
class ReadView: View<Container> {
public:
	ReadView(Container* buffer_cont) :
			View<Container>(buffer_cont) {
	}
private:
};

template<class Container>
class WriteView: public View<Container> {
public:
	using iterator = typename View<Container>::iterator;
	using const_iterator = typename View<Container>::const_iterator;

	WriteView(Container* buffer_cont) :
			View<Container>(buffer_cont) {
	}

	iterator begin();
	iterator end();
private:
};

template<class Container>
inline const ReadView<Container>& Buffer<Container>::ReadAccess() {
	return ReadView<Container>(&stored_data);
}

template<class Container>
inline WriteView<Container>& Buffer<Container>::WriteAccess() {
	return WriteView<Container>(&stored_data);
}

template<class Container>
inline typename View<Container>::const_iterator View<Container>::cbegin() {
	return data->cbegin();
}

template<class Container>
inline typename View<Container>::const_iterator View<Container>::cend() {
	return data->cend();
}

template<class Container>
inline size_t View<Container>::size() {
	return data->size();
}

template<class Container>
inline bool View<Container>::empty() {
	return data->empty();
}

template<class Container>
inline typename WriteView<Container>::iterator WriteView<Container>::begin() {
	return this->data->begin();
}

template<class Container>
inline typename WriteView<Container>::iterator WriteView<Container>::end() {
	return this->data->end();
}

#endif /* CORE_BUFFER_H_ */
