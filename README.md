# Sparse Array Implementation using Doubly Linked List

## Overview
A C++ implementation of a memory-efficient sparse array using a doubly linked list. Stores only non-zero elements while maintaining array semantics. Ideal for handling large arrays with predominantly zero/default values.

## Features
- **Sparse Storage**: Only stores non-zero elements
- **Array Operations**:
  - Set/get values by index
  - Add two sparse arrays (element-wise)
  - Full array print with implicit zeros
  - Compact non-zero elements print
- **Efficient Insertion**: Maintains sorted indices for O(n) operations
- **Memory Safe**: Automatic memory cleanup
- **Bidirectional Traversal**: Doubly linked list structure

## Usage
```
// Create sparse array of length 100
ArrayLinkedList arr(100);

// Set values
arr.set_value(5, 10);  // Set index 10 to 5
arr.set_value(3, 42);

// Get values
cout << arr.get_value(10); // Returns 5
cout << arr.get_value(5);  // Returns 0

// Create second array
ArrayLinkedList arr2(100);
arr2.set_value(7, 10);
arr2.set_value(2, 30);

// Add arrays
arr.add(arr2);

// Print
arr.print_array();        // 0 0 0...5+7=12 at 10...2 at 30... 
arr.print_array_nonzero();// 12 3 2 (at indices 10, 42, 30)
```

## Key Methods
#### Methods	                      Description
- `set_value(int data, int index)`	Stores value at index
- `get_value(int index)`	          Retrieves value (0 if not set)
- `print_array()`	                  Prints full array with zeros
- `print_array_nonzero()`	          Prints only stored values
- `add(ArrayLinkedList& other)`	    Element-wise addition

## Example
Input:
```
ArrayLinkedList a(10), b(10);
a.set_value(3, 2);
a.set_value(5, 5);
b.set_value(4, 2);
b.set_value(7, 8);

a.add(b);
a.print_array();
```
Output:
```
0 0 7 0 0 5 0 0 7 0
```

## Implementation Details
- Doubly Linked List: Enables efficient forward/backward traversal
- Sorted Indices: Maintains index order for fast lookups
- Automatic Merging: `add()` combines values at same indices
- Memory Management: Destructor cleans up all nodes

## Notes
- Fixed array length set at construction
- Zero-based indexing
- Default value is 0 for unset indices
- Indices beyond array length are invalid
- Optimized for sparse data scenarios
