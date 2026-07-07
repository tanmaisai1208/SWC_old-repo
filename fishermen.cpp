#define _CRT_SECURE_NO_WARNINGS 
#include<iostream> 
using namespace std; 
#define MAX 3 

int fishspot[100]; // fishing spots 
int gate[MAX]; // position of gates 
int fishermen[MAX]; // no of fishermen at each gate 
int N; // total no of fishing spots 
int visited[MAX]; // occupied fishing spots 
int Answer; // result 

// To unmark spots occupied by fishermen of gate# index 
class GFG 
{ 
public : 
void reset_fishspot(int index) 
{ 
	int i; 
	for (i = 1; i <= N; i++) 
		if (fishspot[i] == index + 1) 
			fishspot[i] = 0; 
} 

// Calculate minimum distance while 
// allotting spots to fishermen of gate# index. 
// Returns number of positions possible 
// with minimum disance. 
// pos1, pos2 is used to return positions 
int calculate_distance(int index, int*pos1, 
					int *pos2, int *score) 
{ 
	int i, sum = 0, left_min = 999999, 
					right_min = 999999, 
					left, right, npos = 0; 
	*pos1 = *pos2 = *score = 0; 

	left = right = gate[index]; 

	// Allot spots to all fishermen except 
	// last based on minimum distance 
	for (i = 1; i < fishermen[index]; i++) 
	{ 
		if (fishspot[gate[index]] == 0) 
		{ 
			sum++; 
			fishspot[gate[index]] = index + 1; 
		} 
		else
		{ 
			left_min = right_min = 999999; 

			while ((left > 0) && (fishspot[left] > 0)) 
				left--; 

			while ((right <= N) && 
				(fishspot[right] > 0)) 
				right++; 

			if ((left > 0) && (fishspot[left] == 0)) 
				left_min = gate[index] - left + 1; 

			if ((right <= N) && (fishspot[right] == 0)) 
				right_min = right - gate[index] + 1; 

			if (right_min == left_min) 
			{ 
				// Place 2 fishermen, if avaiable 
				if ((fishermen[index] - i - 1) > 1) 
				{ 
					fishspot[left] = fishspot[right] = index + 1; 
					sum += (2 * left_min); 
					i++; 

					// If all fishermen are alloted spots 
					if (i == fishermen[index]) 
					{ 
						npos = 1; 
						*score = sum; 
						return npos; 
					} 
				} 
				else
				{ 
					sum += left_min; 
					fishspot[left] = index + 1; 
				} 
			} 
			else if (left_min < right_min) 
			{ 
				sum += left_min; 
				fishspot[left] = index + 1; 
			} 
			else if (right_min < left_min) 
			{ 
				sum += right_min; 
				fishspot[right] = index + 1; 
			} 
		} 
	} 

	left_min = right_min = 99999; 

	// Allot spot to last fishermen 
	while ((left > 0) && (fishspot[left] > 0)) 
		left--; 

	if ((left > 0) && (fishspot[left] == 0)) 
		left_min = gate[index] - left + 1; 

	while ((right <= N) && (fishspot[right] > 0)) 
		right++; 

	if ((right <= N) && (fishspot[right] == 0)) 
		right_min = right - gate[index] + 1; 

	if ((sum + left_min) == (sum + right_min)) 
	{ 
		npos = 2; 
		*pos1 = left; 
		*pos2 = right; 
		*score = sum + left_min; 
	} 
	else if ((sum + left_min) > 
			(sum + right_min)) 
	{ 
		npos = 1; 
		*score = sum + right_min; 
		fishspot[right] = index + 1; 
	} 
	else if ((sum + left_min) < 
			(sum + right_min)) 
	{ 
		npos = 1; 
		*score = sum + left_min; 
		fishspot[left] = index + 1; 
	} 
	return npos; 
} 

// Solve is used to select next gate 
// and generate all combinations. 
void solve(int index, int sum, int count) 
{ 
	int npos, pos1, pos2, score, i; 

	visited[index] = 1; 

	if (sum > Answer) 
		return; 

	npos = calculate_distance(index, &pos1, 
							&pos2, &score); 
	sum += score; 

	if (count == MAX) 
	{ 
		if (Answer > sum) 
			Answer = sum; 

		return; 
	} 

	if (npos == 1) 
	{ 
		for (i = 0; i < MAX; i++) 
		{ 
			if (visited[i] == 0) 
			{ 
				solve(i, sum, count + 1); 
				visited[i] = 0; 
				reset_fishspot(i); 
			} 
		} 
	} 
	
	else if (npos == 2) 
	{ 
		fishspot[pos1] = index + 1; 
		for (i = 0; i < MAX; i++) 
		{ 
			if (visited[i] == 0) 
			{ 
				solve(i, sum, count + 1); 
				visited[i] = 0; 
				reset_fishspot(i); 
			} 
		} 

		fishspot[pos1] = 0; 
		fishspot[pos2] = index + 1; 
		for (i = 0; i < MAX; i++) 
		{ 
			if (visited[i] == 0) 
			{ 
				solve(i, sum, count + 1); 
				visited[i] = 0; 
				reset_fishspot(i); 
			} 
		} 
		fishspot[pos2] = 0; 
	} 
} 
}; 

// Driver Code 
int main() 
{ 	
	N = 10; // total no of fishing spots 
	
	// position of gates(1-based indexing) 
	gate[0] = 4; 
	gate[1] = 6; 
	gate[2] = 10; 
	
	//no of fishermen at each gate 
	fishermen[0] = 5; //gate1 
	fishermen[1] = 2; //gate 2 
	fishermen[2] = 2; //gate 3 

	for (i = 1; i <= N; i++) 
		fishspot[i] = 0; 

	Answer = 999999; 

	for (i = 0; i < MAX; i++) 
	{ 
		g.solve(i, 0, 1); 
		visited[i] = 0; 
		g.reset_fishspot(i); 
	} 

	cout << Answer << endl; 

	return 0; 
} 
// This code is contributed by SoM15242 


// Function to reset fishing spots occupied by a specific gate
void reset_fishspot(int gate_index) {
    for (int i = 0; i < N; i++) {
        if (fishspot[i] == gate_index + 1) {
            fishspot[i] = 0;
        }
    }
}

// Function to calculate the minimum distance for assigning fishermen from a gate
// Returns the number of positions possible for the last fisherman (1 or 2)
// Updates pos1, pos2, and score accordingly
int calculate_distance(int gate_index, int& pos1, int& pos2, int& score) {
    int sum = 0;
    int left = gate_positions[gate_index] - 1; // Convert to 0-based index
    int right = gate_positions[gate_index] - 1;
    int fishermen = fishermen_count[gate_index];
    int npos = 0;

    // Assign spots to all fishermen except the last one
    for (int i = 0; i < fishermen - 1; i++) {
        int left_min = INT_MAX, right_min = INT_MAX;

        // Find the leftmost available spot
        while (left >= 0 && fishspot[left] != 0) {
            left--;
        }
        if (left >= 0) {
            left_min = gate_positions[gate_index] - (left + 1); // Convert back to 1-based
        }

        // Find the rightmost available spot
        while (right < N && fishspot[right] != 0) {
            right++;
        }
        if (right < N) {
            right_min = (right + 1) - gate_positions[gate_index]; // Convert back to 1-based
        }

        // Choose the spot with the minimum distance
        if (left_min == right_min && left_min != INT_MAX) {
            // Place two fishermen if possible
            if (fishermen - i - 1 > 1) {
                fishspot[left] = gate_index + 1;
                fishspot[right] = gate_index + 1;
                sum += 2 * left_min;
                i++; // Skip the next iteration
            } else {
                sum += left_min;
                fishspot[left] = gate_index + 1;
            }
        } else if (left_min < right_min && left_min != INT_MAX) {
            sum += left_min;
            fishspot[left] = gate_index + 1;
        } else if (right_min < left_min && right_min != INT_MAX) {
            sum += right_min;
            fishspot[right] = gate_index + 1;
        }
    }

    // Assign the last fisherman
    int left_min = INT_MAX, right_min = INT_MAX;
    while (left >= 0 && fishspot[left] != 0) {
        left--;
    }
    if (left >= 0) {
        left_min = gate_positions[gate_index] - (left + 1); // Convert back to 1-based
    }
    while (right < N && fishspot[right] != 0) {
        right++;
    }
    if (right < N) {
        right_min = (right + 1) - gate_positions[gate_index]; // Convert back to 1-based
    }

    if (left_min == right_min && left_min != INT_MAX) {
        npos = 2;
        pos1 = left;
        pos2 = right;
        score = sum + left_min;
    } else if (left_min < right_min && left_min != INT_MAX) {
        npos = 1;
        score = sum + left_min;
        fishspot[left] = gate_index + 1;
    } else if (right_min < left_min && right_min != INT_MAX) {
        npos = 1;
        score = sum + right_min;
        fishspot[right] =Your code is a solution to a **Dynamic Programming and Backtracking** problem related to **optimizing the placement of fishermen at fishing spots** to minimize the total distance traveled. Here's a detailed explanation of the problem and how your code works:

---

### **Problem Statement (Inferred from the Solution):**

You are given:
- A line of **N fishing spots** numbered from 1 to N.
- **Three gates** located at specific positions on the line.
- Each gate has a certain number of fishermen who need to be assigned to fishing spots.

**Objective:**
Assign the fishermen from each gate to the fishing spots such that:
1. Each fishing spot can be occupied by only one fisherman.
2. The total distance traveled by all fishermen (sum of distances from their respective gates to their assigned spots) is minimized.

---

### **Key Components of Your Solution:**

1. **Data Structures:**
   - `fishspot[]`: Tracks which gate's fishermen occupy each fishing spot.
   - `gate[]`: Stores the positions of the gates.
   - `fishermen[]`: Stores the number of fishermen at each gate.
   - `visited[]`: Tracks which gates have been processed.
   - `Answer`: Stores the minimum total distance.

2. **Functions:**
   - `reset_fishspot(index)`: Resets the fishing spots occupied by the fishermen from a specific gate.
   - `calculate_distance(index, pos1, pos2, score)`: Calculates the minimum distance for assigning fishermen from a gate to fishing spots. It also returns the positions (`pos1`, `pos2`) where the last fisherman can be placed if there are multiple options.
   - `solve(index, sum, count)`: Uses backtracking to explore all possible combinations of assigning fishermen from different gates to minimize the total distance.

3. **Algorithm:**
   - The solution uses **backtracking** to try all possible combinations of assigning fishermen from different gates.
   - For each gate, it calculates the minimum distance for placing its fishermen and recursively explores the next gate.
   - The `Answer` is updated whenever a better (smaller) total distance is found.

---

### **Example Scenario (Based on Your Code):**

- **Input:**
  - `N = 10` (fishing spots from 1 to 10).
  - Gates at positions: `gate[0] = 4`, `gate[1] = 6`, `gate[2] = 10`.
  - Fishermen at each gate: `fishermen[0] = 5`, `fishermen[1] = 2`, `fishermen[2] = 2`.

- **Output:**
  The code calculates the minimum total distance for assigning all fishermen to fishing spots and prints the result (`Answer`).

---

### **How Your Code Works:**

1. **Initialization:**
   - The fishing spots array (`fishspot[]`) is initialized to `0`, indicating no fishermen are assigned.
   - The `visited[]` array tracks which gates have been processed.

2. **Backtracking (`solve` function):**
   - For each gate, the code calculates the minimum distance for assigning its fishermen to fishing spots.
   - It explores all possible combinations of assigning fishermen from different gates and updates the `Answer` whenever a better solution is found.

3. **Distance Calculation (`calculate_distance` function):**
   - The function assigns fishermen to fishing spots starting from the gate position and moving outward (left and right).
   - It ensures that each fishing spot is occupied by only one fisherman.
   - If there are multiple options for placing the last fisherman, it considers both possibilities and explores both paths in the backtracking.

4. **Pruning:**
   - The code stops exploring a branch if the current accumulated distance already exceeds the best answer found (`Answer`).
