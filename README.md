# PmergeMe - Ford-Johnson Merge-Insertion Sort Algorithm

A C++ implementation of the Ford-Johnson algorithm (merge-insertion sort) using both `std::vector` and `std::list` containers with Jacobsthal sequence optimization.

> **⭐ 100% C++98 Compliant**
> 
> Advanced sorting algorithm with dual container implementations and performance comparison

## 📋 Description

**PmergeMe** implements the **Ford-Johnson algorithm**, a hybrid sorting technique that combines merge and insertion sort with the **Jacobsthal sequence** for optimal insertion ordering. The program sorts integers using both vector and list containers and compares their performance.

### Core Features ✅
- **Ford-Johnson Algorithm** - Merge-insertion sort with Jacobsthal optimization
- **Dual Containers** - std::vector and std::list implementations
- **Jacobsthal Sequence** - J(n) = J(n-1) + 2*J(n-2) for optimal insertion order
- **Pair-based Sorting** - Groups elements into pairs, recursively sorts maxima
- **Binary Insertion** - Uses std::lower_bound for vector version
- **Performance Comparison** - Measures and displays timing for both containers
- **C++98 Standard** - No modern C++ features

## 🚀 Compilation & Usage

```bash
make                    # Compile
./pmergeme 3 2 5 1 4   # Sort integers
```

**Input:** Space-separated positive integers (max 2147483647)
**Output:** Sorted sequence with timing for both containers

## 🧠 The Ford-Johnson Algorithm

### Overview

The algorithm achieves O(n log n) complexity through a clever strategy:
1. **Pair Creation** - Group elements into pairs (a, b) where a ≤ b
2. **Recursive Sort** - Sort the "b" elements (maxima)
3. **Binary Insertion** - Insert "a" elements using binary search with Jacobsthal ordering

### Jacobsthal Sequence

**Definition:** J(n) = J(n-1) + 2*J(n-2)
- J(0) = 0, J(1) = 1, J(2) = 1, J(3) = 3, J(4) = 5, J(5) = 11, J(6) = 21...

**Purpose:** Determines insertion order to minimize comparisons
- Inserts at positions J(k), then between J(k-1) and J(k)
- Guarantees O(n log n) worst-case complexity

### Example Execution

```
Input: [3, 2, 5, 1, 4]

Step 1: Create pairs
Pairs: (3,2) (5,1) (4)
→ Max heap per pair: {3,2}, {5,1}, {4}

Step 2: Sort pairs by maximum
Pairs after sort: {3,2}, {4}, {5,1}
Sorted maxima: [2, 4, 5]

Step 3: Extract stragglers
Remaining (minima): [3, 1]

Step 4: Binary insertion with Jacobsthal order
Insert using Jacobsthal positions: [1, 3, 5] → binary insert 1, then 3
Result: [1, 2, 3, 4, 5]
```

## 📚 Implementation Details

### Pair-Based Structure

Each pair stored as `std::priority_queue<int>` (max-heap):
```
Pair (3, 2) → priority_queue with top() = 3 (maximum)
Pair (5, 1) → priority_queue with top() = 5
```

**Advantages:**
- Max element easily accessible via top()
- Straightforward comparison for sorting pairs
- Natural way to track both elements

### Vector vs List Implementations

**Vector Version (PmergeMe_vector.cpp):**
- Uses `std::vector<priority_queue<int>>`
- Binary search with `std::lower_bound` for insertion
- Cache-friendly, faster for small-medium sizes
- Time: O(n log n), Space: O(n)

**List Version (PmergeMe_list.cpp):**
- Uses `std::list<priority_queue<int>>`
- Manual traversal for insertion
- Better for very large datasets
- Time: O(n log n), Space: O(n)

### Jacobsthal Insertion Order

The sequence determines which elements to insert first:
```cpp
std::vector<size_t> generateJacobsthalSequence(size_t n)
{
    // Generate: 1, 3, 5, 11, 21, 43, ...
    // Insert at these indices for optimal comparison count
}
```

This order minimizes the total number of comparisons needed.

## 📁 Project Structure

```
PmergeMe/
├── Makefile                      # Build configuration
├── README.md                     # This file
│
├── includes/
│   └── PmergeMe.hpp             # Main class header
│
└── srcs/
    ├── main.cpp                 # Entry point
    ├── PmergeMe.cpp             # Main orchestration
    ├── PmergeMe_vector.cpp      # Vector-based implementation
    ├── PmergeMe_list.cpp        # List-based implementation
    └── PmergeMe_parse.cpp       # Input parsing & validation
```

## 🧪 Test Cases

```bash
# Single element
./pmergeme 42
# Output: 42

# Already sorted
./pmergeme 1 2 3 4 5
# Output: 1 2 3 4 5

# Reverse sorted
./pmergeme 5 4 3 2 1
# Output: 1 2 3 4 5

# Random order
./pmergeme 3 2 5 1 4
# Output: 1 2 3 4 5

# Large dataset
./pmergeme $(shuf -i 1-1000 -n 1000 | tr '\n' ' ')
# Compares performance of vector vs list
```

## 🔧 How It Works Step-by-Step

**1. Parsing & Validation**
- Accept space-separated integers
- Validate range (0 to INT_MAX)
- Detect duplicates, errors

**2. Create Pairs (Vector Version)**
```
Input: [3, 2, 5, 1, 4]
→ Pairs: {(3,2), (5,1), (4)}  // Last pair has one element if odd
```

**3. Sort Pair Maxima**
```
Extract maxima: [3, 5, 4]
→ Sort them: [3, 4, 5]
→ Pairs reordered: {(3,2), (4), (5,1)}
```

**4. Insert Minima with Jacobsthal**
```
Minima to insert: [2, 1]
Jacobsthal sequence: [1, 3, 5, 11, ...]
→ Insert 1 at position 1 (binary search in [3, 4, 5])
→ Insert 2 at position determined by Jacobsthal
→ Result: [1, 2, 3, 4, 5]
```

**5. Measure Timing**
- Record time for vector version
- Record time for list version
- Display both with sorted sequence

## 📊 Technical Specs

| Aspect | Details |
|--------|---------|
| **Algorithm** | Ford-Johnson (merge-insertion) |
| **Time Complexity** | O(n log n) worst-case |
| **Space Complexity** | O(n) |
| **Containers** | std::vector and std::list |
| **Input Range** | 0 to 2,147,483,647 |
| **Compilation** | `-Wall -Wextra -Werror -std=c++98` |

## 🎓 Educational Value

This project demonstrates:

✅ **Advanced Sorting** - Ford-Johnson algorithm, Jacobsthal sequence
✅ **Container Traits** - Vector (cache-friendly) vs List (flexible insertion)
✅ **Binary Search** - std::lower_bound for optimal insertion
✅ **Recursive Algorithms** - Merge-sort style pair splitting
✅ **Priority Queues** - Max-heap for pair management
✅ **Input Validation** - Range checking, error handling
✅ **Performance Analysis** - Timing comparisons between implementations
✅ **STL Mastery** - Complex use of vectors, lists, queues, algorithms
✅ **C++98 Templates** - Priority queue template specialization
✅ **Algorithm Optimization** - Jacobsthal sequence for minimal comparisons

## 🚀 Performance Notes

- **Vector faster** than list for typical input sizes (better cache locality)
- **Ford-Johnson optimal** for comparison-heavy scenarios
- **Worst-case:** O(n log n) guaranteed (unlike QuickSort)
- **Best-case:** O(n) when input nearly sorted

## 📝 Key Algorithm Insights

**Why Jacobsthal?**
- Standard binary insertion = O(n² log n) comparisons
- Ford-Johnson = O(n log n) comparisons
- Jacobsthal sequence = optimal insertion order

**Pair-based approach:**
- Reduces comparison count by sorting maxima first
- Stragglers handled separately
- Minima binary-inserted in optimal Jacobsthal order

## 👤 Author

[@itaharbo91](https://github.com/itaharbo91)

---

**GitHub Description**: Implementation of Ford-Johnson merge-insertion sort in C++98 with dual std::vector and std::list containers. Features Jacobsthal sequence optimization achieving O(n log n) worst-case complexity with performance comparison between vector and list implementations.