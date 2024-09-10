#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

class SolutionToMergeIntervals {
public:
	static void printToMergeIntervals(vector<vector<int>>& result, vector<int>& interval)
	{
		for (int i = 0; i < result.size(); ++i) {
			cout << "[" << result[i][0] << "," << result[i][1] << "],";
		}
		cout << "      interval: [" << interval[0] << "," << interval[1] << "]" << endl;
	}
	static vector<vector<int>> merge(vector<vector<int>>& intervals) {
		int length = intervals.size();
		if (length == 1) return intervals;

		vector<vector<int>> result;

		int min = intervals[0][0];
		int max = intervals[0][1];
		for (int i = 1; i < length; ++i) {
			if (intervals[i][0] < min) min = intervals[i][0];
			if (intervals[i][1] > max) max = intervals[i][1];
		}
		result.push_back({ min, max });
		int temp = 0;
		for (int i = 0; i < length; ++i) {
			int j = 0;
			printToMergeIntervals(result, intervals[i]);
			if (intervals[i][0] == intervals[i][1]) {
				int value = intervals[i][0];
				while (j < result.size() && !(value >= result[j][0] && value <= result[j][1]))
					++j;
				if (j == result.size()) continue;
				if (value == result[j][0]) {
					if (result[j][0] == result[j][1]) {
						result.erase(result.begin() + j);
						if (result.size() == 0) {
							result.push_back({ min,max });
							return result;
						}
					}
					else ++result[j][0];
				}
				else if (value == result[j][1]) {
					if (result[j][0] == result[j][1]) {
						result.erase(result.begin() + j);
						if (result.size() == 0) {
							result.push_back({ min,max });
							return result;
						}
					}
					else --result[j][1];
				}
				else {
					temp = result[j][1];
					result[j][1] = value - 1;
					result.insert(result.begin() + j + 1, { value + 1, temp });
				}
			}
			else {
				while (j < result.size() &&
					(intervals[i][0] >= result[j][1] || intervals[i][1] <= result[j][0]))
					++j;

				if (intervals[i][0] < result[j][0] && intervals[i][1] >= result[j][1]) {
					result.erase(result.begin() + j);
					if (result.size() == 0) {
						result.push_back({ min,max });
						return result;
					}
				}

				else if (intervals[i][0] > result[j][0] && intervals[i][1] < result[j][1]) {
					temp = result[j][1];
					result[j][1] = intervals[i][0];
					result.insert(result.begin() + j + 1, { intervals[i][1], temp });
				}
				else if (intervals[i][0] >= result[j][0]) {
					temp = 0;
					if (intervals[i][0] > result[j][0]) {
						result[j][1] = intervals[i][0];
						temp = 1;
					}
					while (j + temp < result.size() && intervals[i][1] >= result[j + temp][1]) {
						cout << "j = " << j << ",		temp = " << temp << endl;
						result.erase(result.begin() + j + temp);
						if (result.size() == 0) {
							result.push_back({ min,max });
							return result;
						}
					}
					if (j + temp < result.size() && intervals[i][1] > result[j + temp][0])
						result[j + temp][0] = intervals[i][1];
				}
				else if (intervals[i][1] == result[j][1]) {
					result.erase(result.begin() + j);
					if (result.size() == 0) {
						result.push_back({ min,max });
						return result;
					}
				}
				else
					result[j][0] = intervals[i][1];
				printToMergeIntervals(result, intervals[i]);
			}
		}
		cout << "here" << endl;
		for (int i = 0; i < result.size(); ++i) {
			if (result[i][0] == result[i][1]) {
				result[i][0] = min;
				// if (i == result.size() - 1) {
				// 	result[i][1] = max;
				// 	return result;
				// }
				if (i == result.size() - 1)
					min = result[i][1];
				else
					min = result[i][1] + 1;
				--result[i][1];
			}
			else {
				temp = result[i][1];
				result[i][1] = result[i][0];
				result[i][0] = min;
				min = temp;
			}
			printToMergeIntervals(result, intervals[0]);
		}
		if (min <= max)
			result.push_back({ min, max });
		return result;
	}
};


class Solution {
public:
	void print(pair<char, vector<pair<int, int>>> const& vectorOfPositions) {
		cout << "Number:: " << vectorOfPositions.first << "  ";
		for (auto const& x : vectorOfPositions.second)
			cout << "i = " << x.first << ",    j = " << x.second << ";     ";
		cout << endl;
	}


	bool isInSquare(map<int, int>& row_cols, pair<int, int> const& position)
	{
		int div_I = position.first / 3;
		int div_J = position.second / 3;
		for (int i = 3 * div_I; i < 3 * (1 + div_I); ++i) {
			for (int j = 3 * div_J; j < 3 * (1 + div_J); ++j) {
				if (i == position.first or j == position.second) continue;
				if (row_cols.count(i) && row_cols[i] == j)
					return true;
			}
		}
		return false;
	}


	bool isOkey(vector<pair<int, int>> const& vectorOfPositions) {
		map<int, int> row_cols;
		unordered_set<int> cols;
		for (auto const position : vectorOfPositions) {
			if (row_cols.count(position.first) || cols.count(position.second))
				return false;
			if (isInSquare(row_cols, position)) return false;

			row_cols[position.first] = position.second;
			cols.insert(position.second);
		}
		return true;
	}


	bool isValidSudoku(vector<vector<char>>& board) {
		map<char, vector<pair<int, int>>> number_positions;
		int sideLength = board.size();
		for (int i = 0; i < sideLength; ++i) {
			for (int j = 0; j < sideLength; ++j) {
				if (board[i][j] == '.') continue;
				if (!number_positions.count(board[i][j]))
					number_positions[board[i][j]] = {};
				number_positions[board[i][j]].push_back({ i,j });
			}
		}
		for (auto const& element : number_positions) {
			if (!isOkey(element.second)) return false;
		}
		return true;
	}
};

int main() {
	//vector<vector<int>> data(5);
	//data[0] = { 2,3 };
	//data[1] = { 5,5 };
	//data[2] = { 2,2 };
	//data[3] = { 3,4 };
	//data[4] = { 3,4 };
	//vector<int> foo = { 0,0 };

	//vector<vector<int>> result = SolutionToMergeIntervals::merge(data);
	//cout << "result::" << endl;
	//printToMergeIntervals(result, foo);


	vector<vector<char>> board;	Solution s;
	board.push_back({ '8', '3', '.', '.', '7', '.', '.', '.', '.' });
	board.push_back({ '6', '.', '.', '1', '9', '5', '.', '.', '.' });
	board.push_back({ '.', '9', '8', '.', '.', '.', '.', '6', '.' });
	board.push_back({ '8', '.', '.', '.', '6', '.', '.', '.', '3' });
	board.push_back({ '4', '.', '.', '8', '.', '3', '.', '.', '1' });
	board.push_back({ '7', '.', '.', '.', '2', '.', '.', '.', '6' });
	board.push_back({ '.', '6', '.', '.', '.', '.', '2', '8', '.' });
	board.push_back({ '.', '.', '.', '4', '1', '9', '.', '.', '5' });
	board.push_back({ '.', '.', '.', '.', '8', '.', '.', '7', '9' });

	cout << "result::" << s.isValidSudoku(board) << endl;

	return 0;
}