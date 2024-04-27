# Interval Heap
This C++ code is for an Interval Heap.
An interval heap is a binary heap in which each node contains two elements (except the last node). It is a
completebinary tree in which:
1. The left element is less than or equal to the right element.
2. Both the elements define a closed interval.
3. Interval represented by any node except the root is a sub-interval of the parent node.
4. Elements on the left hand side define a min heap.
5. Elements on the right hand side define a max heap.
# Compiler
This was built and tested on Visual Studio 2022.
