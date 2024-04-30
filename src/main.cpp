#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <fstream>

#include "../include/point.hpp"
#include "../include/rec.hpp"

#include "../include/func.hpp"

using namespace std;

class Tree {
private:
    struct Node {
        Node* left = nullptr; Node* right = nullptr;
        int start = 0, finish = 0, mod = 0;
    };

    struct Event {
        bool operator<(const Event& other) const {
            if (start == other.start) {
                if (end == other.end) {
                    return query < other.query;
                }
                return end < other.end;
            }
            return start < other.start;
        }

        int start, end;
        int query;
    };

    vector<Node*> arr_tree;

    Node* NewNode(int count, int d = 1) {
        if (count == 1) {
            Node* t = new Node;
            t->start = t->finish = d;
            return t;
        }

        int mid = (count + 1) / 2;
        Node* left = NewNode(mid, d);
        Node* right = NewNode(count - mid, d + mid);

        Node* node = new Node;
        node->left = left;
        node->right = right;
        node->start = d;
        node->finish = d + count - 1;

        return node;
    }

    Node* Copy(Node* node) {
        Node* copy = new Node;
        copy->left = node->left;
        copy->right = node->right;
        copy->start = node->start;
        copy->finish = node->finish;
        copy->mod = node->mod;
        return copy;
    }

    void query(Node* parent, Node* root, int start, int end, int number, bool fl) {
        if (end <= root->start || root->finish < start) {
            return;
        }
        Node* current = root;
        if (fl || parent != nullptr) {
            Node *copy = Copy(root);
            if (parent == nullptr) {
                arr_tree.push_back(copy);
            } else {
                if (parent->left == root) {
                    parent->left = copy;
                } else {
                    parent->right = copy;
                }
            }
            current = copy;
        }

        if ((start <= current->start && current->start < end) && (start <= current->finish && current->finish < end)) {
            current->mod += number;
        } else {
            query(current, current->left, start, end, number, fl);
            query(current, current->right, start, end, number, fl);
        }
    }

    int find(int x, int y, int count) {
        if (0 < x && 0 < y && y <= count) {
            Node* root = arr_tree[x];
            int mods = 0;
            while (root->left != nullptr) {
                mods += root->mod;
                if (root->left->start <= y && y <= root->left->finish) {
                    root = root->left;
                } else {
                    root = root->right;
                }
            }
            mods += root->mod;
            return mods;
        }
        return 0;
    }

public:
    void Result(vector<Rectangle> &rectangles, vector<Point> &points) {
        if (rectangles.empty()) {
            for (int i = 0; i < points.size(); ++i) {
//                cout << 0 << " ";
            }
            return;
        }

        set<int> x, y;
        for (auto& rectangle : rectangles) {
            x.insert(rectangle.getLeftPoint().getX()); x.insert(rectangle.getRightPoint().getX());
            y.insert(rectangle.getLeftPoint().getY()); y.insert(rectangle.getRightPoint().getY());
        }

        vector<int> uniqX(x.cbegin(), x.cend());
        vector<int> uniqY(y.cbegin(), y.cend());

        vector<pair<int, Event>> events;
        for (auto& rectangle : rectangles) {
            pair<int, Event> event;
            event.first = distance(uniqX.begin(), upper_bound(uniqX.begin(), uniqX.end(), rectangle.getLeftPoint().getX()));
            event.second.query = 1;
            event.second.start = distance(uniqY.begin(), upper_bound(uniqY.begin(), uniqY.end(), rectangle.getLeftPoint().getY()));
            event.second.end = distance(uniqY.begin(), upper_bound(uniqY.begin(), uniqY.end(), rectangle.getRightPoint().getY()));
            events.push_back(event);

            event.first = distance(uniqX.begin(), upper_bound(uniqX.begin(), uniqX.end(), rectangle.getRightPoint().getX()));
            event.second.query = -1;
            events.push_back(event);
        }

        sort(events.begin(), events.end());

        int count = y.size() - 1;

        Node* root = NewNode(count);

        arr_tree.reserve(x.size() + 1);
        arr_tree.push_back(root);

        for (auto& event : events) {
            if (event.first != (arr_tree.size() - 1)) {
                query(nullptr, arr_tree[arr_tree.size() - 1], event.second.start, event.second.end, event.second.query, true);
            } else {
                query(nullptr, arr_tree[arr_tree.size() - 1], event.second.start, event.second.end, event.second.query, false);
            }
        }

        for (auto& point : points) {
            int x_coord = distance(uniqX.begin(), upper_bound(uniqX.begin(), uniqX.end(), point.getX()));
            int y_coord = distance(uniqY.begin(), upper_bound(uniqY.begin(), uniqY.end(), point.getY()));
            int res = find(x_coord, y_coord, count);
//            cout << res << " ";
        }
    }
};

std::vector<Point> GeneratePoints(int number, int range) {
    const int X_PRIME = 65537;
    const int Y_PRIME = 7919;
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, range);

    for (int i = 0; i < number; i++) {
        int x = (X_PRIME * i) % range;
        int y = (Y_PRIME * i) % range;
        points.push_back(Point(x, y));
    }
    return points;
}


vector<Rectangle> GenerateRecs(int count){
    vector<Rectangle> rectangles;

    for (int i = 0; i < count; i++) {
        rectangles.push_back(Rectangle(Point(10 * i, 10 * i), Point(10 * (2 * count - i), 10 * (2 * count - i))));
    }
    return rectangles;
}

int main(){
    std::ofstream file("output.txt", std::ios::app);

    file << "m,n," <<"BruteForce," << "Map," << "PersistentTree" << "\n";

    for (int m = 250; m < 3000; m += 250) {
        auto n = m * m;

        file << m << "," << n << ",";

        vector<Rectangle> recs = GenerateRecs(m);
        vector<Point> points = GeneratePoints(n, recs.size() * 2);

        {
            auto start = chrono::steady_clock::now();
            BruteForceTime(recs, points);
            cout << "\n";
            auto finish = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = finish - start;
            file << elapsed_seconds.count() << ",";
        }

        {
            auto start = chrono::steady_clock::now();
            vector<vector<int>> map = BuildMap(recs);
            MapTime(map, points);
            auto finish = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = finish - start;
            file << elapsed_seconds.count() << ",";
        }

        {
            Tree tree;
            auto start = chrono::steady_clock::now();
            tree.Result(recs, points);
            auto finish = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = finish - start;
            file << elapsed_seconds.count() << "\n";
        }
    }
//    {
//        auto start = chrono::steady_clock::now();
//        BruteForceTime(recs, points);
//        cout << "\n";
//        auto finish = chrono::steady_clock::now();
//        chrono::duration<double> elapsed_seconds = finish - start;
//        file << elapsed_seconds.count() << ",";
//    }
//
//    {
//        auto start = chrono::steady_clock::now();
//        vector<vector<int>> map = BuildMap(recs);
//        MapTime(map, points);
//        auto finish = chrono::steady_clock::now();
//        chrono::duration<double> elapsed_seconds = finish - start;
//        file << elapsed_seconds.count() << ",";
//    }
//
//    {
//        Tree tree;
//        auto start = chrono::steady_clock::now();
//        tree.Result(recs, points);
//        auto finish = chrono::steady_clock::now();
//        chrono::duration<double> elapsed_seconds = finish - start;
//        file << elapsed_seconds.count() << "," << "\n";
//    }


    return 0;
}
