#include <iostream>
#include <string>
using namespace std;

template <class T>
class MyArray {
    T* arr;
    int sz;
    int cap;

    void resize() {
        cap = cap * 2 + 1;
        T* newArr = new T[cap];
        for (int i = 0; i < sz; i++) {
        	newArr[i] = arr[i];
		}
        delete[] arr;
        arr = newArr;
    }
public:
    MyArray() { arr = new T[4]; sz = 0; cap = 4; }
    MyArray(const MyArray& o) {
        cap = o.cap; sz = o.sz;
        arr = new T[cap];
        for (int i = 0; i < sz; i++) {
        	arr[i] = o.arr[i];
		}
    }
    MyArray& operator=(const MyArray& o) {
        if (this != &o) {
            delete[] arr;
            cap = o.cap; sz = o.sz;
            arr = new T[cap];
            for (int i = 0; i < sz; i++) {
            	arr[i] = o.arr[i];
			}
        }
        return *this;
    }
    ~MyArray() { delete[] arr; }

    void push_back(T val) {
        if (sz == cap) resize();
        arr[sz++] = val;
    }
    T& operator[](int i) {
	 return arr[i]; 
	 }
    const T& operator[](int i) const { 
	return arr[i]; 
	}
    int size() const { 
	return sz; 
	}
    bool empty() const {
	 return sz == 0; 
	 }

    void removeAt(int i) {
        if (i < 0 || i >= sz) return;
        for (int j = i; j < sz - 1; j++) {
        	arr[j] = arr[j + 1];
		}
        sz--;
    }
};

class MyStack {
    MyArray<string> arr;
public:
    void push(string val) {
	 arr.push_back(val); 
	 }
    string top() { 
        if (arr.empty()) return "";
        return arr[arr.size() - 1]; 
    }
    void pop() {
	 if (!arr.empty()) arr.removeAt(arr.size() - 1); 
	 }
    bool empty() {
	 return arr.empty(); 
	}
};

class MyQueue {
    MyArray<string> arr;
    int front;
public:
    MyQueue() { front = 0; }
    void push(string val) { arr.push_back(val); }
    string frontVal() { 
        if (empty()) return "";
        return arr[front]; 
    }
    void pop() { 
        if (!empty()) front++; 
        if (empty()) {
            // Reset queue when empty
            front = 0;
            
        }
    }
    bool empty() { return front >= arr.size(); }
};
class IntQueue {
    int* arr;
    int head, tail, cap;
public:
    IntQueue() { cap = 64; arr = new int[cap]; head = tail = 0; }
    ~IntQueue() { delete[] arr; }
    void push(int v) {
        if (tail == cap) { 
		// resize
            int* newArr = new int[cap * 2];
            int j = 0;
            for (int i = head; i < tail; i++) newArr[j++] = arr[i];
            delete[] arr; 
            arr = newArr; 
            cap *= 2;
            head = 0; 
            tail = j;
        }
        arr[tail++] = v;
    }
    int frontVal() { return arr[head]; }
    void pop() { head++; }
    bool empty() { return head == tail; }
};

// Dijkstra
struct PairInt { int dist, node; };

class MinHeap {
    PairInt* arr;
    int sz, cap;

    void swap(PairInt& a, PairInt& b) { PairInt t = a; a = b; b = t; }

    void heapifyUp(int i) {
        while (i > 0 && arr[(i-1)/2].dist > arr[i].dist) {
            swap(arr[(i-1)/2], arr[i]);
            i = (i-1)/2;
        }
    }
    void heapifyDown(int i) {
        while (true) {
            int smallest = i, l = 2*i+1, r = 2*i+2;
            if (l < sz && arr[l].dist < arr[smallest].dist) smallest = l;
            if (r < sz && arr[r].dist < arr[smallest].dist) smallest = r;
            if (smallest == i) break;
            swap(arr[i], arr[smallest]);
            i = smallest;
        }
    }
public:
    MinHeap() { cap = 64; arr = new PairInt[cap]; sz = 0; }
    ~MinHeap() { delete[] arr; }
    void push(int dist, int node) {
        if (sz == cap) {
            PairInt* newArr = new PairInt[cap*2];
            for (int i = 0; i < sz; i++) newArr[i] = arr[i];
            delete[] arr; arr = newArr; cap *= 2;
        }
        arr[sz++] = {dist, node};
        heapifyUp(sz-1);
    }
    PairInt top() { return arr[0]; }
    void pop() { arr[0] = arr[--sz]; heapifyDown(0); }
    bool empty() { return sz == 0; }
};

class User {
public:
    string name;
    int id;
    MyArray<string> posts;
    MyArray<int> friends;

    User() { name = ""; id = -1; }
    User(string n, int i) { 
	name = n; id = i; 
	}

    void display() const {
        cout << name << " (ID: " << id << ")" << endl;
    }

    bool operator==(const User& u) const {
	
	
	 return id == u.id; 
	 }

    friend ostream& operator<<(ostream& os, const User& u) {
        os << u.name << " (" << u.id << ")";
        return os;
    }
};

struct IntNode {
    int data;
    IntNode* next;
    IntNode(int d) : data(d), next(nullptr) {}
};

class IntLinkedList {
    IntNode* head;
public:
    IntLinkedList() {
	 head = nullptr; 
	 }
    ~IntLinkedList() {
        while (head) {
		 IntNode* t = head;
		  head = head->next;
		   delete t; 
		   }
    }
    void insert(int val) {
        IntNode* n = new IntNode(val);
        n->next = head; head = n;
    }
    bool search(int val) {
        IntNode* t = head;
        while (t) { if (t->data == val) return true; t = t->next; }
        return false;
    }
};

class HashTable {
    IntLinkedList table[10];
    int hashFunc(int id) {
	 return (id < 0 ? -id : id) % 10; 
	 }
public:
    void insert(int id) {
	 table[hashFunc(id)].insert(id); 
	 }
    bool search(int id) {
	 return table[hashFunc(id)].search(id); 
	 }
};

struct BSTNode {
    User data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(User u) : data(u), left(nullptr), right(nullptr) {}
};

class BST {
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, User u) {
        if (!node){
        	 return new BSTNode(u);
		}
        if (u.id < node->data.id) {
        	node->left = insertHelper(node->left, u);
		}
        else if (u.id > node->data.id) {
        	node->right = insertHelper(node->right, u);
		}
        return node;
    }

    BSTNode* searchHelper(BSTNode* node, int id) {
        if (!node || node->data.id == id){
        	 return node;
		}
        if (id < node->data.id){
        	 return searchHelper(node->left, id);
		}
        return searchHelper(node->right, id);
    }

    void inorder(BSTNode* node) {
        if (!node) {
        	return;
		}
        inorder(node->left);
        node->data.display();
        inorder(node->right);
    }

    void destroy(BSTNode* node) {
        if (!node) {
        	return;
		}
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() { 
	root = nullptr; 
	}
    ~BST() {
	 destroy(root); 
	 }

    void insert(User u) {
	 root = insertHelper(root, u); 
	 }

    User search(int id) {
        BSTNode* r = searchHelper(root, id);
        if (r) return r->data;
        return User("", -1);
    }

    void display() { inorder(root); }
};

const int MAX_USERS = 100;
const int INF = 999999;

class Graph {
    int adj[MAX_USERS][MAX_USERS];
    int nodeIds[MAX_USERS];
    int nodeIdCount;

    int getIndex(int id) {
        for (int i = 0; i < nodeIdCount; i++)
            if (nodeIds[i] == id) return i;
        return -1;
    }

    int ensureNode(int id) {
        int idx = getIndex(id);
        if (idx == -1) {
            idx = nodeIdCount;
            nodeIds[nodeIdCount++] = id;
        }
        return idx;
    }

public:
    Graph() {
        nodeIdCount = 0;
        for (int i = 0; i < MAX_USERS; i++)
            for (int j = 0; j < MAX_USERS; j++)
                adj[i][j] = 0;
    }

    void addEdge(int u, int v) {
        int ui = ensureNode(u);
        int vi = ensureNode(v);
        adj[ui][vi] = 1;
        adj[vi][ui] = 1;
    }

    MyArray<int> bfsSuggestions(int startId) {
        MyArray<int> suggestions;
        bool visited[MAX_USERS] = {false};
        IntQueue q;

        int startIdx = getIndex(startId);
        if (startIdx == -1) return suggestions;

        visited[startIdx] = true;
        q.push(startIdx);

        while (!q.empty()) {
            int cur = q.frontVal(); q.pop();
            for (int i = 0; i < nodeIdCount; i++) {
                if (adj[cur][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                    suggestions.push_back(nodeIds[i]);
                }
            }
        }
        return suggestions;
    }

    void dfsHelper(int idx, bool* visited) {
        visited[idx] = true;
        cout << "User " << nodeIds[idx] << " -> ";
        for (int i = 0; i < nodeIdCount; i++) {
            if (adj[idx][i] && !visited[i])
                dfsHelper(i, visited);
        }
    }

    void dfs(int startId) {
        bool visited[MAX_USERS] = {false};
        int idx = getIndex(startId);
        if (idx == -1) { cout << "User not in graph!" << endl; return; }
        cout << "DFS Traversal: ";
        dfsHelper(idx, visited);
        cout << "END" << endl;
    }

    MyArray<int> dijkstra(int startId, int endId) {
        MyArray<int> path;
        int startIdx = getIndex(startId);
        int endIdx = getIndex(endId);
        if (startIdx == -1 || endIdx == -1) {
        	return path;
		}

        int dist[MAX_USERS], prev[MAX_USERS];
        bool visited[MAX_USERS] = {false};
        for (int i = 0; i < MAX_USERS; i++) { 
		dist[i] = INF; prev[i] = -1;
		}
        dist[startIdx] = 0;

        MinHeap pq;
        pq.push(0, startIdx);

        while (!pq.empty()) {
            PairInt top = pq.top(); pq.pop();
            int cur = top.node;
            if (visited[cur]) continue;
            visited[cur] = true;
            if (cur == endIdx) break;

            for (int i = 0; i < nodeIdCount; i++) {
                if (adj[cur][i] && !visited[i]) {
                    int newDist = dist[cur] + 1;
                    if (newDist < dist[i]) {
                        dist[i] = newDist;
                        prev[i] = cur;
                        pq.push(newDist, i);
                    }
                }
            }
        }

        if (dist[endIdx] == INF) return path;

        MyArray<int> reversed;
        int cur = endIdx;
        while (cur != startIdx) {
            reversed.push_back(nodeIds[cur]);
            cur = prev[cur];
        }
        reversed.push_back(nodeIds[startIdx]);

        for (int i = reversed.size() - 1; i >= 0; i--)
            path.push_back(reversed[i]);

        return path;
    }
};

class SocialNetwork {
    User users[MAX_USERS];
    int userCount;
    Graph socialGraph;
    BST userBST;
    HashTable userHash;
    MyStack undoStack;
    MyQueue notifQueue;
    int nextId;

    void clearInputBuffer() {
        cin.clear();
        while (cin.get() != '\n');  // Clear the entire line
    }

    int linearSearch(int id) {
        for (int i = 0; i < userCount; i++)
            if (users[i].id == id){
            	 return i;
			}
        return -1;
    }

    int binarySearch(int id) {
        int left = 0, right = userCount - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (users[mid].id == id){
            	 return mid;
			}
            else if (users[mid].id < id){
            	 left = mid + 1;
			}
            else {
            	right = mid - 1;
			}
        }
        return -1;
    }

    void bubbleSort() {
        for (int i = 0; i < userCount - 1; i++)
            for (int j = 0; j < userCount - i - 1; j++)
                if (users[j].id > users[j+1].id) {
                    User tmp = users[j]; users[j] = users[j+1]; users[j+1] = tmp;
                }
        cout << "Users sorted by ID using Bubble Sort!" << endl;
    }

    void insertionSort() {
        for (int i = 1; i < userCount; i++) {
            User key = users[i];
            int j = i - 1;
            while (j >= 0 && users[j].id > key.id) {
                users[j+1] = users[j]; j--;
            }
            users[j+1] = key;
        }
        cout << "Users sorted by ID using Insertion Sort!" << endl;
    }

public:
    SocialNetwork() { userCount = 0; nextId = 1; }

    void createUser() {
        if (userCount >= MAX_USERS) { 
            cout << "Max users reached!" << endl; 
            return; 
        }
        
        clearInputBuffer();
        
        string name;
        cout << "Enter user name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be empty!" << endl;
            return;
        }

        users[userCount] = User(name, nextId);
        userBST.insert(users[userCount]);
        userHash.insert(nextId);
        userCount++;

        string msg = "Created user: " + name;
        undoStack.push(msg);

        string notif = "Welcome " + name + "! You joined the network!";
        notifQueue.push(notif);

        cout << "User created! ID: " << nextId << endl;
        nextId++;
        
        clearInputBuffer();
    }

    void addFriend() {
        int userId, friendId;
        cout << "Enter your user ID: "; 
        
        if (!(cin >> userId)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }
        
        cout << "Enter friend's user ID: "; 
        if (!(cin >> friendId)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }

        if (userId == friendId) {
            cout << "You cannot add yourself as a friend!" << endl;
            clearInputBuffer();
            return;
        }

        int ui = linearSearch(userId);
        int fi = linearSearch(friendId);
        
        if (ui == -1) { 
            cout << "Your user ID not found!" << endl; 
            clearInputBuffer();
            return; 
        }
        if (fi == -1) { 
            cout << "Friend's user ID not found!" << endl; 
            clearInputBuffer();
            return; 
        }

        for (int i = 0; i < users[ui].friends.size(); i++) {
            if (users[ui].friends[i] == friendId) { 
                cout << "Already friends!" << endl; 
                clearInputBuffer();
                return; 
            }
        }

        users[ui].friends.push_back(friendId);
        users[fi].friends.push_back(userId);
        socialGraph.addEdge(userId, friendId);

        string msg = "Added friend: " + to_string(userId) + " <-> " + to_string(friendId);
        undoStack.push(msg);

        string notif = "User " + to_string(friendId) + " is now your friend!";
        notifQueue.push(notif);

        cout << "Friend added!" << endl;
        clearInputBuffer();
    }

    void postContent() {
        int userId;
        cout << "Enter your user ID: "; 
        if (!(cin >> userId)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }
        
        int idx = linearSearch(userId);
        if (idx == -1) { 
            cout << "User not found!" << endl; 
            clearInputBuffer();
            return; 
        }

        clearInputBuffer();
        string content;
        cout << "Enter your post: ";
        getline(cin, content);

        if (content.empty()) {
            cout << "Post cannot be empty!" << endl;
            return;
        }

        users[idx].posts.push_back(content);

        undoStack.push("Posted: " + content);
        notifQueue.push("You posted: " + content);

        cout << "Post added!" << endl;
    }

    void viewFeed() {
        int userId;
        cout << "Enter your user ID: "; 
        if (!(cin >> userId)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }
        
        int idx = linearSearch(userId);
        if (idx == -1) { 
            cout << "User not found!" << endl; 
            clearInputBuffer();
            return; 
        }

        cout << "\n=== FEED ===" << endl;
        cout << "Your posts:" << endl;
        if (users[idx].posts.empty()) {
            cout << "  No posts yet." << endl;
        } else {
            for (int i = 0; i < users[idx].posts.size(); i++)
                cout << i + 1 << ". " << users[idx].posts[i] << endl;
        }

        cout << "\nFriends' posts:" << endl;
        if (users[idx].friends.empty()) {
            cout << "  No friends yet." << endl;
        } else {
            for (int i = 0; i < users[idx].friends.size(); i++) {
                int fi = linearSearch(users[idx].friends[i]);
                if (fi != -1) {
                    cout << "\nFrom " << users[fi].name << ":" << endl;
                    if (users[fi].posts.empty()) {
                        cout << "  No posts yet." << endl;
                    } else {
                        for (int j = 0; j < users[fi].posts.size(); j++)
                            cout << "  - " << users[fi].posts[j] << endl;
                    }
                }
            }
        }
        clearInputBuffer();
    }

    void suggestFriends() {
        int userId;
        cout << "Enter your user ID: "; 
        if (!(cin >> userId)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }
        
        int idx = linearSearch(userId);
        if (idx == -1) { 
            cout << "User not found!" << endl; 
            clearInputBuffer();
            return; 
        }

        MyArray<int> suggestions = socialGraph.bfsSuggestions(userId);

        cout << "\nFriend Suggestions:" << endl;
        bool found = false;
        for (int i = 0; i < suggestions.size(); i++) {
            int sug = suggestions[i];
            if (sug == userId) continue;
            
            bool isFriend = false;
            for (int j = 0; j < users[idx].friends.size(); j++) {
                if (users[idx].friends[j] == sug) { 
                    isFriend = true; 
                    break; 
                }
            }
            
            if (!isFriend) {
                int si = linearSearch(sug);
                if (si != -1) { 
                    cout << "- " << users[si].name << " (ID: " << sug << ")" << endl; 
                    found = true; 
                }
            }
        }
        if (!found) cout << "No suggestions found." << endl;
        clearInputBuffer();
    }

    void shortestPath() {
        int start, end;
        cout << "Enter start user ID: "; 
        if (!(cin >> start)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }
        
        cout << "Enter end user ID: "; 
        if (!(cin >> end)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }

        MyArray<int> path = socialGraph.dijkstra(start, end);
        if (path.size() == 0) { 
            cout << "No path found!" << endl; 
            clearInputBuffer();
            return; 
        }

        cout << "Shortest path: ";
        for (int i = 0; i < path.size(); i++) {
            int pi = linearSearch(path[i]);
            if (pi != -1) cout << users[pi].name;
            else cout << "User " << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\nPath length: " << path.size() - 1 << " connections" << endl;
        clearInputBuffer();
    }

    void undo() {
        if (undoStack.empty()) { 
            cout << "Nothing to undo!" << endl; 
            return; 
        }
        cout << "Undone: " << undoStack.top() << endl;
        undoStack.pop();
    }

    void showNotifications() {
        cout << "\n=== NOTIFICATIONS ===" << endl;
        if (notifQueue.empty()) { 
            cout << "No notifications." << endl; 
            return; 
        }
        int count = 0;
        while (!notifQueue.empty() && count < 20) {
            cout << "- " << notifQueue.frontVal() << endl;
            notifQueue.pop();
            count++;
        }
        if (!notifQueue.empty()) {
            cout << "... and more notifications." << endl;
        }
    }

    void displayUsers() {
        cout << "\n=== ALL USERS (" << userCount << ") ===" << endl;
        if (userCount == 0) {
            cout << "No users yet." << endl;
            return;
        }
        
        for (int i = 0; i < userCount; i++) {
            users[i].display();
            cout << "  Friends: ";
            if (users[i].friends.empty()) {
                cout << "None";
            } else {
                for (int j = 0; j < users[i].friends.size(); j++) {
                    int fi = linearSearch(users[i].friends[j]);
                    if (fi != -1) cout << users[fi].name << " ";
                }
            }
            cout << endl;
        }
    }

    void searchUser() {
        int id;
        cout << "Enter user ID: "; 
        if (!(cin >> id)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }

        cout << "\nLinear Search: ";
        int li = linearSearch(id);
        if (li != -1) users[li].display(); else cout << "Not found!" << endl;

        bubbleSort();

        cout << "Binary Search: ";
        int bi = binarySearch(id);
        if (bi != -1) users[bi].display(); else cout << "Not found!" << endl;

        cout << "BST Search: ";
        User bu = userBST.search(id);
        if (bu.id != -1) bu.display(); else cout << "Not found!" << endl;

        cout << "Hash Table Search: ";
        if (userHash.search(id)) cout << "User found in hash table!" << endl;
        else cout << "Not found!" << endl;
        
        clearInputBuffer();
    }

    void dfsTraversal() {
        int start;
        cout << "Enter starting user ID: "; 
        if (!(cin >> start)) {
            cout << "Invalid ID!" << endl;
            clearInputBuffer();
            return;
        }
        socialGraph.dfs(start);
        clearInputBuffer();
    }

    void sortUsersMenu() {
        cout << "\n=== SORTING ===" << endl;
        cout << "1. Bubble Sort" << endl;
        cout << "2. Insertion Sort" << endl;
        cout << "Enter choice: ";
        int c; 
        if (!(cin >> c)) {
            cout << "Invalid choice!" << endl;
            clearInputBuffer();
            return;
        }
        
        if (c == 1) bubbleSort();
        else if (c == 2) insertionSort();
        else { 
            cout << "Invalid!" << endl; 
            clearInputBuffer();
            return; 
        }
        
        cout << "\nSorted Users:" << endl;
        for (int i = 0; i < userCount; i++) users[i].display();
        clearInputBuffer();
    }

    void showMenu() {
        cout << "\n========================================" << endl;
        cout << "   SMART SOCIAL NETWORK ANALYZER" << endl;
        cout << "========================================" << endl;
        cout << "1.  Create User" << endl;
        cout << "2.  Add Friend" << endl;
        cout << "3.  Post Content" << endl;
        cout << "4.  View Feed" << endl;
        cout << "5.  Suggest Friends (BFS)" << endl;
        cout << "6.  Shortest Path (Dijkstra)" << endl;
        cout << "7.  Undo Last Action" << endl;
        cout << "8.  Show Notifications" << endl;
        cout << "9.  Display All Users" << endl;
        cout << "10. Search User (All Methods)" << endl;
        cout << "11. DFS Traversal" << endl;
        cout << "12. Sort Users" << endl;
        cout << "13. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
    }
};

int main() {
    SocialNetwork network;
    int choice;

    cout << "========================================" << endl;
    cout << "  WELCOME TO SMART SOCIAL NETWORK" << endl;
    cout << "========================================" << endl;

    do {
        network.showMenu();
        
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            while (cin.get() != '\n');  // Clear the buffer
            continue;
        }
        
        // Clear any remaining characters in buffer
        while (cin.get() != '\n');

        switch (choice) {
            case 1:  network.createUser();      break;
            case 2:  network.addFriend();       break;
            case 3:  network.postContent();     break;
            case 4:  network.viewFeed();        break;
            case 5:  network.suggestFriends();  break;
            case 6:  network.shortestPath();    break;
            case 7:  network.undo();            break;
            case 8:  network.showNotifications(); break;
            case 9:  network.displayUsers();    break;
            case 10: network.searchUser();      break;
            case 11: network.dfsTraversal();    break;
            case 12: network.sortUsersMenu();   break;
            case 13:
                cout << "\nGoodbye! Thanks for using Smart Social Network!" << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1-13." << endl;
        }
    } while (choice != 13);

    return 0;
}
