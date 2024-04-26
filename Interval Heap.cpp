#include <iostream>
#include <queue>
using namespace std;
class IntervalHeap {
	int hsize;
	int maxsize;
	int** h;
public:
	IntervalHeap(int s = 100) {
		maxsize = s;
		hsize = 0;
		h = new int* [2];
		h[0] = new int[maxsize];	// min heap
		h[1] = new int[maxsize];	// max heap
		for (int i = 0; i < maxsize; i++) {
			h[0][i] = NULL;
			h[1][i] = NULL;
		}
	}
	void intervalchecker() {
		for (int i = 0; i < hsize / 2; i++) {
			if (h[0][i] > h[1][i]) {
				int temp = h[0][i];
				h[0][i] = h[1][i];
				h[1][i] = temp;
				minreheapUp(0, (hsize - 1) / 2);
				maxreheapUp(0, (hsize - 1) / 2);
			}
		}
	}
	void Swap(int*& h, int root, int minchild) {
		int obj = h[root];
		h[root] = h[minchild];
		h[minchild] = obj;
	}
	void minreheapDown(int root, int bottom) {
		int minChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom) {
			if (leftChild == bottom)
				minChild = leftChild;
			else {
				int tempx = h[0][leftChild];
				int tempy = h[0][rightChild];
				if (tempx >= tempy)
					minChild = rightChild;
				else
					minChild = leftChild;
			}
			int temp = h[0][root];
			int temp1 = h[0][minChild];
			if (temp > temp1) {
				Swap(h[0], root, minChild);
				minreheapDown(minChild, bottom);
			}
		}
	}
	void minreheapUp(int root, int bottom) {
		int parent;
		if (bottom > root) {
			parent = (bottom - 1) / 2;
			int temp = h[0][parent];
			int temp1 = h[0][bottom];
			if (temp > temp1) {
				Swap(h[0], parent, bottom);
				minreheapUp(root, parent);
			}
		}
	}
	void maxreheapDown(int root, int bottom) {
		int maxChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom) {
			if (leftChild == bottom)
				maxChild = leftChild;
			else {
				if (h[1][leftChild] <= h[1][rightChild])
					maxChild = rightChild;
				else
					maxChild = leftChild;
			}
			if (h[1][root] < h[1][maxChild]) {
				Swap(h[1], root, maxChild);
				maxreheapDown(maxChild, bottom);
			}
		}
	}
	void maxreheapUp(int root, int bottom) {
		int parent;
		if (bottom > root) {
			parent = (bottom - 1) / 2;
			int temp = h[1][parent];
			int temp1 = h[1][bottom];
			if (temp < temp1) {
				Swap(h[1], parent, bottom);
				maxreheapUp(root, parent);
			}
		}
	}
	void insert(int d) {
		if (hsize % 2 == 0) {
			h[0][hsize / 2] = d;
			minreheapUp(0, hsize / 2);
			hsize++;
		}
		else {
			h[1][(hsize - 1) / 2] = d;
			maxreheapUp(0, (hsize - 1) / 2);
			hsize++;
		}
		intervalchecker();
	}
	void Delete() {
		if (hsize % 2 == 0) {
			h[0][0] = h[0][(hsize / 2) - 1];
			h[1][0] = h[1][((hsize - 1) / 2)];
			minreheapDown(0, hsize / 2);
			maxreheapDown(0, (hsize - 1) / 2);
			hsize -= 2;
			intervalchecker();
		}
		else {
			h[0][0] = h[0][(hsize - 1) / 2];
			h[1][0] = h[1][(hsize / 2) - 1];
			minreheapDown(0, hsize / 2);
			maxreheapDown(0, (hsize - 1) / 2);
			hsize -= 2;
			intervalchecker();
		}
	}
	void update(int val, int d) {
		for (int i = 0; i < hsize / 2; i++) {
			if (h[0][i] == val) {
				h[0][i] = d;
				minreheapDown(i, (hsize - 1) / 2);
				minreheapUp(0, i);
				break;
			}
			else if (h[1][i] == val) {
				h[1][i] = d;
				maxreheapDown(i, (hsize - 1) / 2);
				maxreheapUp(0, i);
				break;
			}
		}
		intervalchecker();
	}
	void display() {
		if (hsize > 0) {
			for (int i = 0; i < hsize / 2; i++) {
				cout << "[" << h[0][i] << "," << h[1][i] << "]" << endl;
			}
			if (hsize % 2 != 0) {
				cout << "[" << h[0][(hsize / 2)] << "]" << endl;
			}
			cout << endl;
		}
	}

	void display2(int index) {
		if (index < maxsize) {
			if (h[0][index] != NULL)
				cout << h[0][index] << "," << h[1][index] << endl;
			display2(index * 2 + 1);
			display2(index * 2 + 2);
		}
		return;
	}
	void display2() {
		display2(0);
	}
};

int main() {
	IntervalHeap obj;
	cout << "Even Numbers to be inserted:" << endl << endl;
	obj.insert(2);
	obj.insert(40);
	obj.insert(3);
	obj.insert(17);
	obj.insert(4);
	obj.insert(30);
	/*obj.insert(4);
	obj.insert(12);
	obj.insert(3);
	obj.insert(11);
	obj.insert(5);
	obj.insert(10);
	obj.insert(6);
	obj.insert(15);
	obj.insert(4);
	obj.insert(10);
	obj.insert(5);
	obj.insert(11);
	obj.insert(5);
	obj.insert(9);
	obj.insert(4);
	obj.insert(7);
	obj.insert(8);
	obj.insert(8);
	obj.insert(7);
	obj.insert(9);*/
	cout << "Interval Heap after INSERT:" << endl;
	obj.display();
	obj.Delete();
	cout << "Interval Heap after DELETE:" << endl;
	obj.display();
	obj.update(17, 77);
	cout << "Interval Heap after UPDATE (17 to 77):" << endl;
	obj.display();
	cout << "Odd Numbers to be inserted:" << endl << endl;
	IntervalHeap obj2(4);
	obj2.insert(2);
	obj2.insert(30);
	obj2.insert(7);
	obj2.insert(6);
	obj2.insert(10);
	/*obj2.insert(44);
	obj2.insert(15);
	obj2.insert(7);
	obj2.insert(9);*/
	cout << "Interval Heap after INSERT:" << endl;
	obj2.display();
	cout << "Interval Heap after DELETE:" << endl;
	obj2.Delete();
	obj2.display();
	obj2.update(17, 77);
	cout << "Interval Heap after UPDATE (17 to 77):" << endl;
	obj2.display();
	return 0;
}