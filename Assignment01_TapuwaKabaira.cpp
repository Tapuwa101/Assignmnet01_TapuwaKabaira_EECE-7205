#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

// PROBLEM 1: Merge Overlapping Intervals


vector<vector<int>> mergeIntervals(vector<vector<int>> intervals)
{
    vector<vector<int>> merged;

    if (intervals.empty())
    {
        return merged;
    }

    sort(intervals.begin(), intervals.end());

    vector<int> current = intervals[0];

    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] <= current[1])
        {
            current[1] = max(current[1], intervals[i][1]);
        }
        else
        {
            merged.push_back(current);
            current = intervals[i];
        }
    }

    merged.push_back(current);

    return merged;
}

// PROBLEM 2A: Counting Sort for 0, 1, and 2

void countingSort012(vector<int>& values)
{
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;

    for (int value : values)
    {
        if (value == 0)
        {
            count0++;
        }
        else if (value == 1)
        {
            count1++;
        }
        else
        {
            count2++;
        }
    }

    int index = 0;

    for (int i = 0; i < count0; i++)
    {
        values[index] = 0;
        index++;
    }

    for (int i = 0; i < count1; i++)
    {
        values[index] = 1;
        index++;
    }

    for (int i = 0; i < count2; i++)
    {
        values[index] = 2;
        index++;
    }
}

// PROBLEM 2B: Dutch National Flag

void dutchNationalFlag(vector<int>& values)
{
    int low = 0;
    int mid = 0;
    int high = values.size() - 1;

    while (mid <= high)
    {
        if (values[mid] == 0)
        {
            swap(values[low], values[mid]);
            low++;
            mid++;
        }
        else if (values[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(values[mid], values[high]);
            high--;
        }
    }
}


// PROBLEM 3: Largest Number


string largestNumber(vector<int> values)
{
    if (values.empty())
    {
        return "";
    }

    vector<string> numbers;

    for (int value : values)
    {
        numbers.push_back(to_string(value));
    }

    sort(numbers.begin(), numbers.end(),
        [](string a, string b)
        {
            return a + b > b + a;
        });

    if (numbers[0] == "0")
    {
        return "0";
    }

    string result = "";

    for (string number : numbers)
    {
        result += number;
    }

    return result;
}

// PROBLEM 4: Group Anagrams

vector<vector<string>> groupAnagrams(vector<string> words)
{
    map<string, vector<string>> groups;

    for (string word : words)
    {
        string key = word;
        sort(key.begin(), key.end());
        groups[key].push_back(word);
    }

    vector<vector<string>> result;

    for (auto group : groups)
    {
        result.push_back(group.second);
    }

    return result;
}

// PROBLEM 5: Meeting Rooms

bool canAttendAllMeetings(vector<vector<int>> meetings)
{
    if (meetings.empty())
    {
        return true;
    }

    sort(meetings.begin(), meetings.end());

    for (int i = 1; i < meetings.size(); i++)
    {
        if (meetings[i][0] < meetings[i - 1][1])
        {
            return false;
        }
    }

    return true;
}

// PROBLEM 6A: K Closest Points Using Sorting

vector<vector<int>> kClosestSorting(vector<vector<int>> points, int k)
{
    sort(points.begin(), points.end(),
        [](vector<int> a, vector<int> b)
        {
            int distanceA = a[0] * a[0] + a[1] * a[1];
            int distanceB = b[0] * b[0] + b[1] * b[1];

            return distanceA < distanceB;
        });

    vector<vector<int>> result;

    for (int i = 0; i < k && i < points.size(); i++)
    {
        result.push_back(points[i]);
    }

    return result;
}

// PROBLEM 6B: K Closest Points Using a Heap

struct Point
{
    int x;
    int y;
    int distance;
};

struct PointCompare
{
    bool operator()(Point a, Point b)
    {
        return a.distance < b.distance;
    }
};

vector<vector<int>> kClosestHeap(vector<vector<int>> points, int k)
{
    priority_queue<Point, vector<Point>, PointCompare> heap;

    for (vector<int> point : points)
    {
        int distance = point[0] * point[0] + point[1] * point[1];

        Point current;
        current.x = point[0];
        current.y = point[1];
        current.distance = distance;

        heap.push(current);

        if (heap.size() > k)
        {
            heap.pop();
        }
    }

    vector<vector<int>> result;

    while (!heap.empty())
    {
        Point current = heap.top();
        heap.pop();

        result.push_back({current.x, current.y});
    }

    return result;
}

// PROBLEM 7: K Most Frequent Values

vector<int> topKFrequent(vector<int> values, int k)
{
    map<int, int> frequency;

    for (int value : values)
    {
        frequency[value]++;
    }

    vector<pair<int, int>> numbers;

    for (auto item : frequency)
    {
        numbers.push_back({item.first, item.second});
    }

    sort(numbers.begin(), numbers.end(),
        [](pair<int, int> a, pair<int, int> b)
        {
            if (a.second != b.second)
            {
                return a.second > b.second;
            }

            return a.first < b.first;
        });

    vector<int> result;

    for (int i = 0; i < k && i < numbers.size(); i++)
    {
        result.push_back(numbers[i].first);
    }

    return result;
}

// PROBLEM 8: Merge K Sorted Arrays

struct Node
{
    int value;
    int arrayIndex;
    int valueIndex;
};

struct NodeCompare
{
    bool operator()(Node a, Node b)
    {
        return a.value > b.value;
    }
};

vector<int> mergeKSortedArrays(vector<vector<int>> arrays)
{
    priority_queue<Node, vector<Node>, NodeCompare> heap;

    for (int i = 0; i < arrays.size(); i++)
    {
        if (!arrays[i].empty())
        {
            Node node;
            node.value = arrays[i][0];
            node.arrayIndex = i;
            node.valueIndex = 0;

            heap.push(node);
        }
    }

    vector<int> result;

    while (!heap.empty())
    {
        Node current = heap.top();
        heap.pop();

        result.push_back(current.value);

        int arrayNumber = current.arrayIndex;
        int nextIndex = current.valueIndex + 1;

        if (nextIndex < arrays[arrayNumber].size())
        {
            Node nextNode;
            nextNode.value = arrays[arrayNumber][nextIndex];
            nextNode.arrayIndex = arrayNumber;
            nextNode.valueIndex = nextIndex;

            heap.push(nextNode);
        }
    }

    return result;
}

// PROBLEM 9: Kth Largest Element

int kthLargest(vector<int> values, int k)
{
    priority_queue<int, vector<int>, greater<int>> heap;

    for (int value : values)
    {
        heap.push(value);

        if (heap.size() > k)
        {
            heap.pop();
        }
    }

    return heap.top();
}

// PROBLEM 10: Count Inversions

long long mergeAndCount(vector<int>& values, int left, int middle, int right)
{
    vector<int> temp;

    int i = left;
    int j = middle + 1;
    long long inversions = 0;

    while (i <= middle && j <= right)
    {
        if (values[i] <= values[j])
        {
            temp.push_back(values[i]);
            i++;
        }
        else
        {
            temp.push_back(values[j]);
            inversions += middle - i + 1;
            j++;
        }
    }

    while (i <= middle)
    {
        temp.push_back(values[i]);
        i++;
    }

    while (j <= right)
    {
        temp.push_back(values[j]);
        j++;
    }

    for (int x = 0; x < temp.size(); x++)
    {
        values[left + x] = temp[x];
    }

    return inversions;
}

long long mergeSortAndCount(vector<int>& values, int left, int right)
{
    if (left >= right)
    {
        return 0;
    }

    int middle = (left + right) / 2;

    long long leftCount =
        mergeSortAndCount(values, left, middle);

    long long rightCount =
        mergeSortAndCount(values, middle + 1, right);

    long long mergeCount =
        mergeAndCount(values, left, middle, right);

    return leftCount + rightCount + mergeCount;
}

long long countInversions(vector<int> values)
{
    if (values.size() < 2)
    {
        return 0;
    }

    return mergeSortAndCount(values, 0, values.size() - 1);
}

// HELPER FUNCTIONS

void printVector(vector<int> values)
{
    cout << "[";

    for (int i = 0; i < values.size(); i++)
    {
        cout << values[i];

        if (i < values.size() - 1)
        {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

void printIntervals(vector<vector<int>> intervals)
{
    cout << "[";

    for (int i = 0; i < intervals.size(); i++)
    {
        cout << "[" << intervals[i][0]
             << ", " << intervals[i][1] << "]";

        if (i < intervals.size() - 1)
        {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

// program used to display a menu that allows the user to choose which problem to run. 

int main()
{
    int choice;

    cout << "==============================" << endl;
    cout << "       ASSIGNMENT #01" << endl;
    cout << "==============================" << endl;

    cout << "1. Merge Overlapping Intervals" << endl;
    cout << "2. Sort 0, 1, and 2" << endl;
    cout << "3. Largest Number" << endl;
    cout << "4. Group Anagrams" << endl;
    cout << "5. Meeting Rooms" << endl;
    cout << "6. K Closest Points" << endl;
    cout << "7. K Most Frequent Values" << endl;
    cout << "8. Merge K Sorted Arrays" << endl;
    cout << "9. Kth Largest Element" << endl;
    cout << "10. Count Inversions" << endl;

    cout << endl;
    cout << "Enter the problem number: ";
    cin >> choice;

    if (choice == 1)
    {
        vector<vector<int>> intervals =
        {
            {1, 3},
            {2, 6},
            {8, 10},
            {9, 12}
        };

        vector<vector<int>> answer = mergeIntervals(intervals);

        cout << "Merged intervals: ";
        printIntervals(answer);
    }

    else if (choice == 2)
    {
        vector<int> values = {2, 0, 2, 1, 1, 0};

        vector<int> counting = values;
        vector<int> dutch = values;

        countingSort012(counting);
        dutchNationalFlag(dutch);

        cout << "Counting solution: ";
        printVector(counting);

        cout << "Dutch National Flag solution: ";
        printVector(dutch);
    }

    else if (choice == 3)
    {
        vector<int> values = {10, 2, 9, 39, 17};

        cout << "Largest number: "
             << largestNumber(values) << endl;
    }

    else if (choice == 4)
    {
        vector<string> words =
        {
            "eat", "tea", "tan", "ate", "nat", "bat"
        };

        vector<vector<string>> answer =
            groupAnagrams(words);

        cout << "Anagram groups:" << endl;

        for (vector<string> group : answer)
        {
            cout << "[ ";

            for (string word : group)
            {
                cout << word << " ";
            }

            cout << "]" << endl;
        }
    }

    else if (choice == 5)
    {
        vector<vector<int>> meetings =
        {
            {0, 30},
            {5, 10},
            {15, 20}
        };

        bool answer = canAttendAllMeetings(meetings);

        cout << "Can attend all meetings: ";

        if (answer)
        {
            cout << "True" << endl;
        }
        else
        {
            cout << "False" << endl;
        }
    }

    else if (choice == 6)
    {
        vector<vector<int>> points =
        {
            {1, 3},
            {-2, 2},
            {5, 8},
            {0, 1}
        };

        int k = 2;

        vector<vector<int>> sortingAnswer =
            kClosestSorting(points, k);

        vector<vector<int>> heapAnswer =
            kClosestHeap(points, k);

        cout << "Sorting solution:" << endl;

        for (vector<int> point : sortingAnswer)
        {
            cout << "[" << point[0]
                 << ", " << point[1] << "] ";
        }

        cout << endl;

        cout << "Heap solution:" << endl;

        for (vector<int> point : heapAnswer)
        {
            cout << "[" << point[0]
                 << ", " << point[1] << "] ";
        }

        cout << endl;
    }

    else if (choice == 7)
    {
        vector<int> values = {1, 1, 1, 2, 2, 3};

        int k = 2;

        vector<int> answer =
            topKFrequent(values, k);

        cout << "Most frequent values: ";
        printVector(answer);
    }

    else if (choice == 8)
    {
        vector<vector<int>> arrays =
        {
            {1, 4, 7},
            {2, 5, 8},
            {3, 6, 9}
        };

        vector<int> answer =
            mergeKSortedArrays(arrays);

        cout << "Merged array: ";
        printVector(answer);
    }

    else if (choice == 9)
    {
        vector<int> values = {3, 2, 1, 5, 6, 4};

        int k = 2;

        cout << "Kth largest value: "
             << kthLargest(values, k) << endl;
    }

    else if (choice == 10)
    {
        vector<int> values = {2, 4, 1, 3, 5};

        cout << "Number of inversions: "
             << countInversions(values) << endl;
    }

    else
    {
        cout << "Invalid problem number." << endl;
    }

    return 0;
}