# DataFlow
Work in progress library for data flow based programming.

DataFlow is a library for data flow based programming written in C++.
Design goals are to provide a simple and clean interface using modern techniques and idoms of the C++ language in its current iteration.

DataFlow tries to be highly generic with a certain bias to applications in signal processing.

At the moment the existing implementation is very minimal and highly unstable.

Dependencies:
C++ Standard Library and several boost libraries.


ToDos:
- finish and fix support for collections and higher order functions on collections.
- Add scheduler and support for repeated tasks.
- Add support for events.
- Add Multiplexing and Demultiplexing of connections.
- Add convinient support for threadsafe dynamic connecting and deconnecting of function blocks.
- Exchange the current very much adhoc tests for proper test framework.
