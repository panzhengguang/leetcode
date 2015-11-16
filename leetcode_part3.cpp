#include"header.h"
using namespace std;
namespace panzg_leetcode
{
	class Solution
	{
	public:
		/*Spiral Matrix*/
		vector<int> spiralOrder(vector<vector<int>>& matrix)
		{
			vector<int> result;
			if (matrix.empty())
				return result;
			int beginX = 0, endX = matrix[0].size() - 1;
			int beginY = 0, endY = matrix.size() - 1;
			while (true)
			{
				//上
				for (int j = beginX; j <= endX; ++j)
					result.push_back(matrix[beginY][j]);
				if (++beginY > endY)
					break;
				//右
				for (int i = beginY; i <= endY; ++i)
					result.push_back(matrix[i][endX]);
				if (beginX > --endX)
					break;
				//下
				for (int j = endX; j >= beginX; --j)
					result.push_back(matrix[endY][j]);
				if (--endY < beginY)
					break;
				//左
				for (int i = endY; i >= beginY; --i)
					result.push_back(matrix[i][beginX]);
				if (++beginX > endX)
					break;
			}
			return result;
		}
		/*Spiral Matrix 2*/
		vector<vector<int>> generateMatrix(int n)
		{
			vector<vector<int>> matrix(n, vector<int>(n));
			int begin = 0, end = n - 1;
			int num = 1;
			while (begin < end)
			{
				for (int i = begin; i < end; ++i)
					matrix[begin][i] = num++;
				for (int i = begin; i < end; ++i)
					matrix[i][end] = num++;
				for (int j = end; j > begin; --j)
					matrix[end][j] = num++;
				for (int i = end; i > begin; --i)
					matrix[i][begin] = num++;
				++begin;
				--end;
			}
			if (begin == end) matrix[begin][begin] = num;
			return matrix;
		}
		/*ZigZag Conversion 数学规律*/
		string convert(string s, int numRows)
		{
			if (numRows <= 1 || s.size() <= 1)
				return s;
			string result;
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0, index = i; index < s.size(); j++, index = (2 * numRows - 2) * j + i)
				{
					result.append(1, s[index]); // 垂直元素
					if (i == 0 || i == numRows - 1)
						continue; // 斜对角元素
					if (index + (numRows - i - 1) * 2 < s.size())
						result.append(1, s[index + (numRows - i - 1) * 2]);
				}
			}
			return result;
		}
		/*Divide Two Integers*/
		//int divide(int dividend, int divisor)
		//{
		//	if (!divisor) return INT_MAX;
		//	if (divisor == 1) return dividend;
		//	if (divisor == -1){
		//		if (dividend == INT_MIN) { return INT_MAX; }
		//		else { return -dividend; }
		//	}

		//	bool s1 = dividend < 0;
		//	bool s2 = divisor < 0;

		//	unsigned int nom = s1 ? -dividend : dividend;
		//	unsigned int den = s2 ? -divisor : divisor;

		//	unsigned int rem = 0;
		//	unsigned int quot = 0;

		//	for (int i = 31; i >= 0; --i){
		//		rem <<= 1;
		//		rem |= (nom >> i) & 1;
		//		if (rem >= den){
		//			rem -= den;
		//			quot |= (1 << i);
		//		}
		//	}

		//	return s1^s2 ? -quot : quot;
		//}
		// LeetCode, Text Justification
		// 时间复杂度 O(n)，空间复杂度 O(1)
		vector<string> fullJustify(vector<string> &words, int L)
		{
			vector<string> result;
			const int n = words.size();
			int begin = 0, len = 0; // 当前行的起点，当前长度
			for (int i = 0; i < n; ++i) {
				if (len + words[i].size() + (i - begin) > L)
				{
					result.push_back(connect(words, begin, i - 1, len, L, false));
					begin = i;
					len = 0;
				}
				len += words[i].size();
			}
			// 最后一行不足 L
			result.push_back(connect(words, begin, n - 1, len, L, true));
			return result;
		}
		/**
		* @brief 将 words[begin, end] 连成一行
		* @param[in] words 单词列表
		* @param[in] begin 开始
		* @param[in] end 结束
		* @param[in] len words[begin, end] 所有单词加起来的长度
		* @param[in] L 题目规定的一行长度
		* @param[in] is_last 是否是最后一行
		* @return 对齐后的当前行
		*/
		string connect(vector<string> &words, int begin, int end, int len, int L, bool is_last)
		{
			string s;
			int n = end - begin + 1;
			for (int i = 0; i < n; ++i)
			{
				s += words[begin + i];
				addSpaces(s, i, n - 1, L - len, is_last);
			}
			if (s.size() < L) s.append(L - s.size(), ' ');
			return s;
		}
		/**
		* @brief 添加空格.
		* @param[inout]s 一行
		* @param[in] i 当前空隙的序号
		* @param[in] n 空隙总数
		* @param[in] L 总共需要添加的空额数
		* @param[in] is_last 是否是最后一行
		* @return 无
		*/
		void addSpaces(string &s, int i, int n, int L, bool is_last)
		{
			if (n < 1 || i > n - 1) return;
			int spaces = is_last ? 1 : (L / n + (i < (L % n) ? 1 : 0));
			s.append(spaces, ' ');
		}
		//LeetCode, Max Points on a Line
		// 暴力枚举法，以边为中心，时间复杂度 O(n^3)，空间复杂度 O(1)
		int maxPoints(vector<Point>& points)
		{
			if (points.size() < 3)
				return points.size();
			int result = 0;

			for (int i = 0; i < points.size() - 1; i++)
			{
				for (int j = i + 1; j < points.size(); j++)
				{
					int sign = 0;
					int a, b, c;
					if (points[i].x == points[j].x)
						sign = 1;
					else
					{
						a = points[j].x - points[i].x;
						b = points[j].y - points[i].y;
						c = a*points[i].y - b*points[i].x;
					}
					int count = 0;
					for (int k = 0; k < points.size(); k++)
					{
						if ((0 == sign && a*points[k].y == c + b*points[k].x) ||
							(1 == sign && points[k].x == points[j].x))
							count++;
					}
					if (count > result)
						result = count;
				}
			}
			return result;
		}

		/*
		该方法的核心是将原问题转变成一个寻找第k小数的问题（假设两个原序列升序排列），这样中位数实际上是第(m+n)/2小的数。所以只要解决了第k小数的问题，原问题也得以解决。

		首先假设数组A和B的元素个数都大于k/2，我们比较A[k/2-1]和B[k/2-1]两个元素，这两个元素分别表示A的第k/2小的元素和B的第k/2小的元素。这两个元素比较共有三种情况：>、<和=。如果A[k/2-1]<B[k/2-1]，这表示A[0]到A[k/2-1]的元素都在A和B合并之后的前k小的元素中。换句话说，A[k/2-1]不可能大于两数组合并之后的第k小值，所以我们可以将其抛弃。

		证明也很简单，可以采用反证法。假设A[k/2-1]大于合并之后的第k小值，我们不妨假定其为第（k+1）小值。由于A[k/2-1]小于B[k/2-1]，所以B[k/2-1]至少是第（k+2）小值。但实际上，在A中至多存在k/2-1个元素小于A[k/2-1]，B中也至多存在k/2-1个元素小于A[k/2-1]，所以小于A[k/2-1]的元素个数至多有k/2+ k/2-2，小于k，这与A[k/2-1]是第（k+1）的数矛盾。

		当A[k/2-1]>B[k/2-1]时存在类似的结论。

		当A[k/2-1]=B[k/2-1]时，我们已经找到了第k小的数，也即这个相等的元素，我们将其记为m。由于在A和B中分别有k/2-1个元素小于m，所以m即是第k小的数。(这里可能有人会有疑问，如果k为奇数，则m不是中位数。这里是进行了理想化考虑，在实际代码中略有不同，是先求k/2，然后利用k-k/2获得另一个数。)

		通过上面的分析，我们即可以采用递归的方式实现寻找第k小的数。此外我们还需要考虑几个边界条件：

		如果A或者B为空，则直接返回B[k-1]或者A[k-1]；
		如果k为1，我们只需要返回A[0]和B[0]中的较小值；
		如果A[k/2-1]=B[k/2-1]，返回其中一个；
		*/
		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
		{
			int k = nums1.size() + nums2.size();
			//偶数
			if (k % 2 == 0)
				return (
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2) +
				findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1)
				) / 2;
			//奇数
			else
				return findKthSortedArrays(nums1.begin(), nums1.size(), nums2.begin(), nums2.size(), k / 2 + 1);
		}
		double findKthSortedArrays(vector<int>::const_iterator nums1, int m, vector<int>::const_iterator nums2, int n, int k)
		{
			if (m > n)
				return findKthSortedArrays(nums2, n, nums1, m, k);
			//边界条件
			if (m == 0)
				return *(nums2 + k - 1);
			//返回第1小的值，即min(num[0],num1[0])
			if (k == 1)
				return min(*nums1, *nums2);

			//下面是判断B[k-1]和A[k-1]关系；
			int mk = min(m, k / 2);
			int nk = k - mk;
			//如果A[k/2-1]=B[k/2-1]，返回其中一个；
			if (*(nums1 + mk - 1) == *(nums2 + nk - 1))
				return *(nums1 + mk - 1);
			//当A[k/2-1] < B[k/2-1],删除A[0，k/2-1]
			else if (*(nums1 + mk - 1) < *(nums2 + nk - 1))
				return findKthSortedArrays(nums1 + mk, m - mk, nums2, n, k - mk);
			//当A[k/2-1] > B[k/2-1],删除B[0，k/2-1]
			else
				return findKthSortedArrays(nums1, m, nums2 + nk, n - nk, k - nk);
		}
		/*Swap Nodes in Pairs*/
		ListNode* swapPairs(ListNode* head)
		{
			if (head == nullptr || head->next == nullptr)
				return head;
			ListNode my_head(-1);
			my_head.next = head;
			ListNode * pre = head, *cur = head->next, *last = &my_head;
			while (1)
			{
				last->next = cur;
				pre->next = cur->next;
				cur->next = pre;
				if (!(pre->next && pre->next->next))
					break;
				else
				{
					last = pre;
					pre = pre->next;
					cur = pre->next;
				}
			}
			return my_head.next;
		}
		/*Reverse Nodes in k-Group 使用栈进行保存*/
		ListNode* reverseKGroup(ListNode* head, int k)
		{
			stack<ListNode*> stack_node;
			int flag = 0; //判断是否是整个链表的第一个节点
			ListNode * last_node = nullptr;  //记录最后一个节点
			ListNode * my_head = nullptr; //记录首节点，进行返回
			ListNode * temp = nullptr; //临时节点
			int count = 0; //计数器，入栈一个count++
			while (head)
			{
				//压入k个节点
				while (head && count < k)
				{
					stack_node.push(head);
					head = head->next;
					count++;
				}
				//如果个数足够
				if (count == k)
				{
					for (int i = 0; i < k; i++)
					{
						temp = stack_node.top();
						if (!flag) //第一个节点，需要赋值给my_head
						{
							flag = 1;
							my_head = temp;
						}
						if (last_node != nullptr)  //链到尾部
						{
							last_node->next = temp;
						}
						last_node = temp;
						stack_node.pop();
					}
					last_node->next = nullptr;
					count = 0;
				}
				//尾部个数不够
				else
				{
					for (int i = 0; i < count; i++)
					{
						temp = stack_node.top();
						stack_node.pop();
					}
					if (!flag) //第一个节点，需要赋值给my_head
					{
						flag = 1;
						my_head = temp;
					}
					if (last_node != nullptr)  //链到尾部
					{
						last_node->next = temp;
					}
				}
			}
			return my_head;
		}
		/*First Missing Positive 时间复杂度和空间复杂度都是o(n)，不符合要求*/
		int firstMissingPositive(vector<int>& nums)
		{
			unordered_map<int, bool> m_map;
			for (int i = 0; i < nums.size(); i++)
			{
				m_map[nums[i]] = true;
			}
			int index = 1;
			for (int i = 0; i < nums.size(); i++)
			{
				auto res = m_map.find(index);
				if (res == m_map.end())
				{
					return index;
				}
				else
					index++;
			}
			return index;
		}
		/*first missing positive 空间复杂度为常数
		思路：可以把数组中的元素放入“合适”的位置时，例如将1放在0位置上，2放在1位置上。。。，最后遍历数组，如果某个位置上的数不合适，则返回该位置上“合适”的数，
		*/
		int firstMissingPositive_v2(vector<int> &nums)
		{
			int size = nums.size();
			if (size == 0) return 1;
			for (int i = 1; i <= size; i++)
			{
				//将元素放入合适的位置
				while (nums[i - 1] != i)
				{
					if (nums[i - 1]<0 || nums[i - 1]>size || nums[i - 1] == nums[nums[i - 1] - 1])
					{
						break;
					}
					int temp = nums[i - 1];
					nums[i - 1] = nums[temp - 1];
					nums[temp - 1] = temp;
				}
			}
			for (int i = 1; i <= size; i++)
			{
				if (nums[i - 1] != i)
					return i;
			}
			return size + 1;
		}
		/*Plus One 将数组代表的整数加1*/
		vector<int> plusOne(vector<int>& digits)
		{
			int flag = 0;
			for (auto iter = digits.rbegin(); iter != digits.rend(); iter++)
			{
				int temp = (*iter + flag);
				if (iter == digits.rbegin())
				{
					temp += 1;
				}
				flag = temp / 10;
				*iter = temp % 10;
			}
			if (flag > 0)
				digits.insert(digits.begin(), flag);
			return digits;
		}
		/*Search in Rotated Sorted Array II*/
		bool search(vector<int>& nums, int target)
		{
			auto res = find(nums.begin(), nums.end(), target);
			if (res == nums.end())
				return false;
			else
				return true;
		}
		/*Symmetric Tree 递归*/
		bool isSymmetric(TreeNode* root)
		{
			if (root == nullptr)
				return true;
			else
				return isSymmetric_helper(root->left, root->right);
		}
		bool isSymmetric_helper(TreeNode* left, TreeNode* right)
		{
			if (left == nullptr && right == nullptr)
				return true;
			if (left == nullptr || right == nullptr)
				return false;
			return left->val == right->val && isSymmetric_helper(left->left, right->right)
				&& isSymmetric_helper(left->right, right->left);
		}
		/*Maximum Depth of Binary Tree 递归*/
		int maxDepth(TreeNode* root)
		{
			return maxDepth_helper(root, 0);
		}
		int maxDepth_helper(TreeNode* root, int depth)
		{
			if (root == nullptr)
				return depth;
			else
				return max(maxDepth_helper(root->left, depth + 1), maxDepth_helper(root->right, depth + 1));
		}
		/*Longest Consecutive Sequence 偷懒不符合O(n)要求*/
		int longestConsecutive_v1(vector<int>& nums)
		{
			sort(nums.begin(), nums.end());
			int count = 1;
			int result = 1;
			for (size_t i = 1; i < nums.size(); i++)
			{
				if (nums[i] == nums[i - 1] + 1)
					count++;
				else if (nums[i] == nums[i - 1])
				{
					continue;
				}
				else
				{
					result = max(result, count);
					count = 1;
				}
			}
			return max(result, count);
		}
		/*Longest Consecutive Sequence,用unordered_set，O(n)*/
		int longestConsecutive(vector<int>& nums)
		{
			int len = 0, candidate, val;
			unordered_set<int> set(nums.begin(), nums.end());
			while (!set.empty())
			{
				val = *set.begin();
				set.erase(val);
				candidate = 1;
				//处理比val大的数
				for (int i = val + 1; set.find(i) != set.end(); ++i)
				{
					set.erase(i);
					candidate++;
				}
				//处理比val小的数
				for (int i = val - 1; set.find(i) != set.end(); --i)
				{
					set.erase(i);
					candidate++;
				}
				len = max(len, candidate);
			}
			return len;
		}
		/*Copy List with Random Pointer 使用unordered_map,时间复杂度、空间复杂度都为O(N)*/
		RandomListNode *copyRandomList(RandomListNode *head)
		{
			unordered_map<RandomListNode*, RandomListNode*> result;
			RandomListNode* m_head = head;
			while (m_head != nullptr)
			{
				RandomListNode * node = new RandomListNode(m_head->label);
				result[m_head] = node;
				m_head = m_head->next;
			}
			m_head = head;
			while (m_head)
			{
				if (m_head->next != nullptr)
					result[m_head]->next = result[m_head->next];
				if (m_head->random != nullptr)
					result[m_head]->random = result[m_head->random];
				m_head = m_head->next;
			}
			return result[head];
		}
		/*Reverse Words in a String 用栈*/
		void reverseWords(string &s)
		{
			stack<string> st;
			st = reverseWords_helper(s, " ");
			s.clear();
			while (!st.empty())
			{
				string str = st.top();
				if (str != "")
					s += (str + " ");
				st.pop();
			}
			if (s.size() > 1)
				s.erase(s.size() - 1);
		}
		/*Reverse Words in a String 局部翻转，然后整体翻转*/
		void reverseWords_v2(string &s)
		{
			reverseWords_v2_remove_space(s);
			if (s[0] == ' ')
				s.erase(0, 1);
			if (s == "") return;
			int prev = 0;
			if (s[s.size() - 1] != ' ')
				s += " ";
			for (int i = 1; i < s.size(); i++)
			{
				if (s[i] != ' '&& s[i - 1] == ' ')
					prev = i;
				else if (s[i] == ' ')
					reverseWords_v2_helper(s, prev, i - 1);
			}
			if (s[s.size() - 1] == ' ')
				s.erase(s.size() - 1);
			reverseWords_v2_helper(s, 0, s.size() - 1);
		}
		void reverseWords_v2_helper(string& s, int start, int end)
		{
			while (start < end)
			{
				char temp = s[start];
				s[start] = s[end];
				s[end] = temp;
				start++;
				end--;
			}
		}
		void reverseWords_v2_remove_space(string& s)
		{
			int i = 1;
			while (i < s.size())
			{
				if (s[i - 1] == ' '&&s[i] == ' ')
					s.erase(i, 1);
				else
					i++;
			}
		}
		/*字符串分割函数，结果存储在stack中*/
		stack<std::string> reverseWords_helper(std::string str, std::string pattern)
		{
			std::string::size_type pos;
			std::stack<std::string> result;
			str += pattern;//扩展字符串以方便操作
			int size = str.size();
			for (int i = 0; i < size; i++)
			{
				pos = str.find(pattern, i);
				if (pos < size)
				{
					std::string s = str.substr(i, pos - i);
					result.push(s);
					i = pos + pattern.size() - 1;
				}
			}
			return result;
		}
		/*Linked List Cycle,判断链表是否有环,经典快慢指针问题*/
		bool hasCycle(ListNode *head)
		{
			ListNode* fast = head;
			ListNode* slow = head;
			while (fast)
			{
				if (fast->next)
					fast = fast->next->next;
				else
					return false;
				slow = slow->next;
				if (fast == slow)
					return true;
			}
			return false;
		}
		/*Linked List Cycle 2，找环的起点，经典快慢指针问题*/
		ListNode *detectCycle(ListNode *head)
		{
			if (!head) return 0;

			ListNode *fast = head, *slow = head;
			if (fast->next && fast->next->next)
			{
				do
				{
					fast = fast->next->next;
					slow = slow->next;
				} while (fast != slow && fast->next && fast->next->next);

				// the point is when two pointers meet, the distance from the position 
				// to the entry is equal to the distance from head to the entry

				if (fast == slow)
				{
					for (fast = head; fast != slow; fast = fast->next, slow = slow->next);
					return fast;
				}
			}
			return 0;
		}
		/*Reorder List 用栈或者数组记录位置，空间复杂度有点高*/
		void reorderList(ListNode* head)
		{
			ListNode *my_head = head;
			vector<ListNode*> node_vec; //记录指针
			while (my_head)
			{
				node_vec.push_back(my_head);
				my_head = my_head->next;
			}
			int length = node_vec.size();
			int i = 0, j = length - 1;
			ListNode *m_head = new ListNode(-1);
			m_head->next = head;
			ListNode *cur = m_head;
			while (i < j)  //交替链接
			{
				cur->next = node_vec[i];
				cur = cur->next;
				i++;
				cur->next = node_vec[j];
				cur = cur->next;
				j--;
			}
			if (i == j)
			{
				cur->next = node_vec[i];
				cur->next->next = nullptr;
			}
			else
				cur->next = nullptr;
		}
		class Entry
		{
		public:
			int key;
			int value;
			Entry(int key, int value) :key(key), value(value){};
		};
		class LRUCache
		{
		public:
			int capacity, currentSize;
			unordered_map < int, list<Entry*>::iterator> hash;
			list<Entry*> lru; // front is the lastest
		public:
			LRUCache(int capacity) :capacity(capacity), currentSize(0)
			{

			}
			int get(int key)
			{
				Entry *entry = nullptr;
				auto it = hash.find(key);
				if (it == hash.end())
					return -1;
				else
				{
					//让it指向的元素移动到lru链表的首部
					lru.splice(lru.begin(), lru, it->second);
					return (*(it->second))->value;
				}
			}
			void set(int key, int value)
			{
				Entry *entry = nullptr;
				auto it = hash.find(key);
				if (it == hash.end()) //不存在key
				{
					entry = new Entry(key, value);
					if (currentSize >= capacity) //空间用尽，删除首部元素
					{
						hash.erase(lru.back()->key);
						delete lru.back();
						lru.pop_back();
					}
					else
						currentSize++;
					lru.push_front(entry);
					hash[key] = lru.begin();
				}
				else
				{
					(*(it->second))->value = value;
					lru.splice(lru.begin(), lru, it->second); //移动到首部
				}
			}
		};
		/*Maximum Product Subarray 直接两层循环，超时*/
		int maxProduct(vector<int>& nums)
		{
			int length = nums.size();
			int result = INT_MIN;
			for (int i = 0; i < length; i++)
			{
				int temp = 1;
				for (int j = i; j < length; j++)
				{
					temp *= nums[j];
					result = max(result, temp);
				}
			}
			return result;
		}
		/*
		动态规划，当前状态包含三种情况：
		1. current maxValue * A[i]  if A[i]>0
		2. current minValue * A[i]  if A[i]<0
		3. A[i]
		所以代码中需要记录当前最小值和当前最大值两个值
		*/
		int maxProduct_dp(vector<int>& nums)
		{
			int length = nums.size();
			if (length <= 0) return 0;
			if (length == 1) return nums[0];
			int curMax = nums[0];
			int curMin = nums[0];
			int result = nums[0];
			for (int i = 1; i < length; i++)
			{
				int temp_max = nums[i] * curMax;
				int temp_min = nums[i] * curMin;
				curMax = max(max(temp_max, temp_min), nums[i]);
				curMin = min(min(temp_max, temp_min), nums[i]);
				result = max(result, curMax);
			}
			return result;
		}
		/*Find Minimum in Rotated Sorted Array 二分法*/
		int findMin(vector<int>& nums)
		{
			//也可以一行代码搞定，直接 return *(min_element(nums.begin(),nums.end()));
			int begin = 0, end = nums.size() - 1;
			if (end == 0) return nums[0];
			if (nums[end] > nums[0]) return nums[0];
			while (begin < end)
			{
				if (begin == end - 1)
					return min(nums[begin], nums[end]);
				int mid = (begin + end) / 2;
				if (nums[mid] < nums[begin])
					end = mid;
				else
					begin = mid;
			}
		}
		/*Find Minimum in Rotated Sorted Array 2 二分法*/
		int findMin2(vector<int>& nums)
		{
			int n = nums.size();
			if (n == 0) return 0;

			int l = 0, r = n - 1;
			while (l <= r)
			{
				if (l == r) return nums[r];
				int mid = (l + r) / 2;

				while (nums[mid] == nums[l] && l<mid) l++;
				while (nums[mid] == nums[r] && r>mid) r--;

				if (nums[mid] > nums[r])
					l = mid + 1;
				else
					r = mid;
			}
		}
		/*Intersection of Two Linked Lists，找两个链表的交点 用Map空间复杂度高*/
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
		{
			unordered_map<ListNode*, int> m_map;
			ListNode *head_a = headA, *head_b = headB;
			while (head_a)
			{
				m_map[head_a] = 1;
				head_a = head_a->next;
			}
			while (head_b)
			{
				auto res = m_map.find(head_b);
				if (res != m_map.end())
					return head_b;
				else
					m_map[head_b] = 1;
				head_b = head_b->next;
			}
			return nullptr;
		}
		/*时间复杂度O(N)，空间复杂度O(1)*/
		ListNode *getIntersectionNode_v2(ListNode *headA, ListNode *headB)
		{
			ListNode *head_a = headA, *head_b = headB;
			int lengthA = 0, lengthB = 0;
			while (head_a)
			{
				lengthA++;
				head_a = head_a->next;
			}
			while (head_b)
			{
				lengthB++;
				head_b = head_b->next;
			}
			int diff = abs(lengthA - lengthB); //计算两个链表的长短之差
			int flag = lengthA < lengthB ? 1 : 0;
			while (diff--)
			{
				if (flag)
					headB = headB->next;
				else
					headA = headA->next;
			}
			while (headA && headB)
			{
				if (headA == headB)
					return headA;
				else
				{
					headA = headA->next;
					headB = headB->next;
				}
			}
			return nullptr;
		}
		/*Find Peak Element*/
		int findPeakElement(vector<int>& nums)
		{
			int length = nums.size();
			if (length == 1 || nums[0] > nums[1])
				return 0;
			int i = 0;
			for (i = 1; i < length - 1; i++)
			{
				if (nums[i] > nums[i + 1] && nums[i] > nums[i - 1])
					return i;
			}
			if (nums[i - 1] < nums[i])
				return i;
		}
		/*Compare Version Numbers*/
		int compareVersion(string version1, string version2)
		{
			int i = 0;
			int j = 0;
			int n1 = version1.size();
			int n2 = version2.size();

			int num1 = 0;
			int num2 = 0;
			while (i < n1 || j < n2)
			{
				while (i < n1 && version1[i] != '.'){
					num1 = num1 * 10 + (version1[i] - '0');
					i++;
				}

				while (j<n2 && version2[j] != '.'){
					num2 = num2 * 10 + (version2[j] - '0');;
					j++;
				}

				if (num1>num2) return 1;
				else if (num1 < num2) return -1;

				num1 = 0;
				num2 = 0;
				i++;
				j++;
			}

			return 0;
		}
		/*Maximum gap*/
		int maximumGap(vector<int>& nums)
		{
			sort(nums.begin(), nums.end());
			int max_value = 0;
			for (int i = 1; i < nums.size(); i++)
			{
				max_value = max(max_value, nums[i] - nums[i - 1]);
			}
			return max_value;
		}
		//桶排序
		int maximumGap_v2(vector<int> &nums)
		{
			int n = nums.size();
			if (n < 2) return 0;
			int maxE = *max_element(nums.begin(), nums.end());
			int minE = *min_element(nums.begin(), nums.end());

			int len = maxE - minE;
			if (len <= 1) return len;
			vector<int> buck_max(n, INT_MIN);
			vector<int> buck_min(n, INT_MAX);

			for (int i = 0; i < n; i++)
			{
				// note the divide and multiply order and the double cast
				// it's used to avoid the overflow and underflow during calculation
				int index = (double)(nums[i] - minE) / len * (n - 1);
				buck_max[index] = max(buck_max[index], nums[i]);
				buck_min[index] = min(buck_min[index], nums[i]);
			}

			int gap = 0, pre = buck_max[0];
			for (int i = 1; i < n; i++)
			{
				if (buck_max[i] == INT_MIN) continue;
				gap = max(gap, buck_min[i] - pre);
				pre = buck_max[i];
			}
			return gap;
		}
		/*Excel Sheet Column Title*/
		string convertToTitle(int n)
		{
			string res;
			while (n >= 1)
			{
				res = (char)('A' + (n - 1) % 26) + res;
				n = (n - 1) / 26;
			}
			return res;
		}
		/*Majority Element O(N)时间，O(N)空间*/
		int majorityElement(vector<int>& nums)
		{
			unordered_map<int, int> count;
			int length = nums.size();
			for (int i = 0; i < length;i++)
			{
				auto res = count.find(nums[i]);
				if (res == count.end())
					count[nums[i]] = 1;
				else
					count[nums[i]]++;
				if (count[nums[i]] > length / 2)
					return nums[i];
			}
		}
		/*Moore's voting algorithm 常数空间复杂度*/
		int majorityElement_v2(vector<int>& nums)
		{
			int curValue=0, curCount = 0;
			for (int i = 0; i < nums.size();i++)
			{
				if (curCount == 0)
				{
					curCount = 1;
					curValue = nums[i];
				}
				else if (curValue == nums[i])
					curCount++;
				else
					curCount--;
			}
			return curValue;
		}
		/*Majority Element II，，遍历*/
		vector<int> majorityElement2(vector<int>& nums)
		{
			vector<int> result;
			if (nums.size() == 0) return result;
			sort(nums.begin(), nums.end());
			int count = 0, curVal = nums[0];
			for (int i = 0; i < nums.size(); i++)
			{
				if (nums[i] == curVal) count++;
				else
				{
					curVal = nums[i];
					count = 1;
				}
				if (count > nums.size() / 3 && (result.size() == 0 || result[result.size() - 1] != curVal))
					result.push_back(curVal);
			}
			return result;
		}
		/*投票算法*/
		vector<int> majorityElement2_v2(vector<int>& nums) {
			vector<int> v;
			int size = nums.size();
			int n1 = 0, n2 = 0, cn1 = 0, cn2 = 0;
			for (int i = 0; i < size; i++)
			{
				if (nums[i] == n1)
				{
					cn1++;
				}
				else if (nums[i] == n2)
				{
					cn2++;
				}
				else if (cn1 == 0)
				{
					n1 = nums[i];
					cn1 = 1;
				}
				else if (cn2 == 0)
				{
					n2 = nums[i];
					cn2 = 1;
				}
				else
				{
					cn1--;
					cn2--;
				}
			}
			if (cn2 == 0 && size > 0)//用来解决[0 0]的情况
				n2 = nums[0] - 1;
			cn1 = 0;
			cn2 = 0;
			for (int i = 0; i<size; i++)
			{
				if (nums[i] == n1)
					cn1++;
				if (nums[i] == n2) 
					cn2++;
			}
			if (cn1>size / 3)
				v.push_back(n1);
			if (cn2 > size / 3)
				v.push_back(n2);
			return v;
		}
		/*Min Stack*/
		class MinStack
		{
		public:
			//int1记录当前节点的值，int2记录到当前节点的最小值
			stack<pair<int, int>> st;
			void push(int x)
			{
				int min_value;
				if (st.empty())
					min_value = x;
				else
					min_value = st.top().second < x ? st.top().second : x;
				pair<int, int> p(x, min_value);
				st.push(p);
			}

			void pop()
			{
				st.pop();
			}

			int top()
			{
				return st.top().first;
			}

			int getMin()
			{
				return st.top().second;
			}
		};
		/*Excel Sheet Column Number*/
		int titleToNumber(string s)
		{
			int length = s.size();
			int result = 0;
			for (int i = 0; i < length;i++)
			{
				result = 26*result+s[i]-'A'+1;
			}
			return result;
		}
		/*Factorial Trailing Zeroes 
		n!后缀0的个数 = n!质因子中5的个数 = floor(n/5) + floor(n/25) + floor(n/125) + ....
		*/
		int trailingZeroes(int n)
		{
			int res = 0;
			while (n)
			{
				res += n / 5;
				n /= 5;
			}
			return res;
		}
		long long jiesheng(int n)
		{
			long long  count = 1;
			for (int i = 1; i <= n;i++)
			{
				count *= i;
			}
			return count;
		}
		/*Rotate Array 分成前后两端分别旋转*/
		void rotate(vector<int>& nums, int k)
		{
			int length = nums.size();
			if (k == length) //直接返回
			{
				return;
			}
			else if (k > length) //取余
				k %= length;
			rotate_helper(nums, 0, length-k-1);
			rotate_helper(nums, length-k, length - 1);
			rotate_helper(nums, 0, length - 1);
		}
		void rotate_helper(vector<int> &nums,int start,int end)
		{
			while (start<end)
			{
				int temp = nums[start];
				nums[start] = nums[end];
				nums[end] = temp;
				start++;
				end--;
			}
		}
	};
}
int main()
{
	panzg_leetcode::Solution sol;
	ListNode node1(1);
	ListNode node2(2);
	ListNode node3(3);
	ListNode node4(4);
	ListNode node5(5);
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
//	node4.next = &node5;
	vector<vector<int>> vec(1, vector<int>(2, 3));
	vector<int> nums = { 1,2};

	//sol.reorderList(&node1);
	//ListNode *p = &node1;
	//while (p)
	//{
	//	cout << p->val << endl;
	//	p = p->next;
	//}

	sol.rotate(nums, 3);
	for each (auto var in nums)
	{
		cout << var << " ";
	}


	system("pause");
}