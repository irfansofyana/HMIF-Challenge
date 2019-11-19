#include <tcframe/spec.hpp>
#include <assert.h>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    string header;
    int N, M, C;
    vector<int> A, B;
    vector<int> V, W;
    int Q;
    vector<int> op;
    vector<vector<int> > data;
    vector<int> ans;

    void InputFormat() {
        // LINE(header);
        LINE(N, M, C);
        LINE(W % SIZE(N));
        LINE(V % SIZE(N));
        LINES(A, B) % SIZE(M);
        LINE(Q);
        LINES(op, data) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100000);
        CONS(N-1 <= M && M <= ((int) min(100000LL, (1LL*(long long) N*(N-1)))));
        CONS(1 <= C && C <= N);
        CONS(A.size() == B.size());
        CONS(A.size() == M);
        CONS(eachElementBetween(A, 1, N));
        CONS(eachElementBetween(B, 1, N));
        CONS(isConnected(N, A, B));
        CONS(noSelfLoop(A, B));
        CONS(eachElementBetween(W, 1, C));
        CONS(eachElementBetween(V, 1, 1000000000));
        CONS(1 <= Q && Q <= 100000);
        CONS(eachElementBetween(op, 1, 2));
        CONS(eachQuery(op, data, N, 1000000000));
    }

    // void Subtask1() {
    //     Points(3);

    //     CONS(N == 8);
    // }

    // void Subtask2() {
    //     Points(6);

    //     CONS(N == 10);
    // }

    // void Subtask3() {
    //     Points(16);

    //     CONS(1 <= Q && Q <= 2000);
    //     CONS(eachElementBetween(op, 1, 1));
    // }

    // void Subtask4() {
    //     Points(20);

    //     CONS(1 <= N && N <= 2000);
    //     CONS(1 <= Q && Q <= 2000);
    // }

    // void Subtask5() {
    //     Points(55);

    //     // no additional constraints
    // }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (int x : v)
            if (x < lo || x > hi)
                return false;
        return true;
    }

    bool noSelfLoop(const vector<int>& u, const vector<int>& v) {
        for (int i = 0; i < u.size(); i++)
            if (u[i] == v[i])
                return false;
        return true;
    }

    bool isConnected(int n, const vector<int>& u, const vector<int>& v) {
        vector<bool> isVisited(n);
        vector<vector<int>> adj(n);
        for (int i = 0; i < u.size(); i++) {
            adj[u[i]-1].push_back(v[i]-1);
            adj[v[i]-1].push_back(u[i]-1);
        }
        int numNodesVisited = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            if (isVisited[now]) {
                continue;
            }
            isVisited[now] = true;
            ++numNodesVisited;
            for (int v : adj[now]) {
                q.push(v);
            }
        }
        return numNodesVisited == n;
    }

    bool eachQuery(const vector<int>& op, const vector<vector<int> >& data, int maxn, int maxv) {
        for (int i=0; i<op.size(); i++) {
            int opt = op[i];
            if (opt == 1) {
                if (data[i].size() != 1) return false;
                if (data[i][0] < 1 || data[i][0] > maxn) return false;
            } else if (opt == 2) {
                if (data[i].size() != 2) return false;
                if (data[i][0] < 1 || data[i][0] > maxn) return false;
                if (data[i][1] < 1 || data[i][1] > maxv) return false;
            } else {
                return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void BeforeTestCase() {
        A.clear();
        B.clear();
        V.clear();
        W.clear();
        op.clear();
        for (int i=0; i<data.size(); i++) data[i].clear();
        data.clear();
    }

    void TestCases(){
        //0
        CASE(N = 5, M = 4, C = 2, Q = 4, generateSubtask0(A, B, W, V, op, data)); //0
        //1
        CASE(N = 8, M = 10, C = 2, Q = 6, generateSubtask1(A, B, W, V, op, data)); //1
        //2
        CASE(N = 10, M = 15, C = 3, Q = 8, generateSubtask2(A, B, W, V, op, data)); //2
        //4
        
        //2 poin / tc
        CASE(N = 316,    M = 99540,  C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        // CASE(N = 316,    M = 99540,  C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        
        //2 poin
        CASE(N = 2000,   M = 100000, C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 2000,   M = 100000, C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 2000,   M = 100000, C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 2000,   M = 100000, C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        // CASE(N = 2000,   M = 100000, C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
        
        //2 poin
        CASE(N = 316,    M = 99540,  C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
       
       //5
        CASE(N = 316,    M = 99540,  C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        // CASE(N = 316,    M = 99540,  C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 316,    M = 99540,  C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        // CASE(N = 316,    M = 99540,  C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 100000, M = 100000, C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 100000, M = 100000, C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 100000, M = 100000, C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        CASE(N = 100000, M = 100000, C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        // CASE(N = 100000, M = 100000, C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
        //3
        CASE(N = 100000, M = 100000, C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 100000, M = 100000, C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 100000, M = 100000, C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 100000, M = 100000, C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
        CASE(N = 100000, M = 100000, C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    }

    // void SampleTestCase1() {
    //     Subtasks({4, 5});
    //     Input({
    //         "0...45",
    //         "5 4 2",
    //         "1 2 2 2 2",
    //         "1 2 3 4 5",
    //         "1 2",
    //         "2 3",
    //         "3 4",
    //         "4 5",
    //         "4",
    //         "1 1",
    //         "1 2",
    //         "2 3 6",
    //         "1 2"
    //     });
    //     Output({
    //         "1",
    //         "5",
    //         "6"
    //     });
    // }

    // void TestGroup1() {
    //     Subtasks({1, 4, 5});
    //     CASE(
    //         header=".1..45",
    //         N = 8, M = 10, C = 2, Q = 6,
    //         generateSubtask1(A, B, W, V, op, data));
    // }

    // void TestGroup2() {
    //     Subtasks({2, 4, 5});
    //     CASE(
    //         header="..2.45",
    //         N = 10, M = 15, C = 3, Q = 8,
    //         generateSubtask2(A, B, W, V, op, data));
    // }

    // void TestGroup3() {
    //     Subtasks({3, 5});
    //     CASE(header="...3.5", N = 100000, M = 100000, C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...3.5", N = 100000, M = 100000, C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...3.5", N = 100000, M = 100000, C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...3.5", N = 100000, M = 100000, C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...3.5", N = 100000, M = 100000, C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    // }

    // void TestGroup4() {
    //     Subtasks({3, 4, 5});
    //     CASE(header="...345", N = 316,    M = 99540,  C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...345", N = 316,    M = 99540,  C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...345", N = 316,    M = 99540,  C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...345", N = 316,    M = 99540,  C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    //     CASE(header="...345", N = 316,    M = 99540,  C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 1, N, 1000000000));
    // }

    // void TestGroup5() {
    //     Subtasks({4, 5});
    //     CASE(header="....45", N = 316,    M = 99540,  C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 316,    M = 99540,  C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 316,    M = 99540,  C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 316,    M = 99540,  C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 316,    M = 99540,  C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 2000,   M = 100000, C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 2000,   M = 100000, C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 2000,   M = 100000, C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 2000,   M = 100000, C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header="....45", N = 2000,   M = 100000, C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 2000,   randomQuery(op, data, Q, 2, N, 1000000000));
    // }

    // void TestGroup6() {
    //     Subtasks({5});
    //     CASE(header=".....5", N = 316,    M = 99540,  C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 316,    M = 99540,  C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 316,    M = 99540,  C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 316,    M = 99540,  C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 316,    M = 99540,  C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 100000, M = 100000, C = 1,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 100000, M = 100000, C = 1*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 100000, M = 100000, C = 2*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 100000, M = 100000, C = 3*N/4, randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    //     CASE(header=".....5", N = 100000, M = 100000, C = N,     randomGraph(N, M, A, B), randomArray(V, N, 1, 1000000000), randomArray(W, N, 1, C), Q = 100000, randomQuery(op, data, Q, 2, N, 1000000000));
    // }

private:
    void generateSubtask0(vector<int>& u, vector<int>& v, vector<int>& a, vector<int>& b, vector<int>& op, vector<vector<int> >& data) {
        int arr_u[] = {1, 2, 3, 4};
        int arr_v[] = {2, 3, 4, 5};

        u.insert(u.begin(), arr_u, arr_u + 4);
        v.insert(v.begin(), arr_v, arr_v + 4);

        int arr_a[] = {1, 2, 2, 2, 2};
        int arr_b[] = {1, 2, 3, 4, 5};

        a.insert(a.begin(), arr_a, arr_a + 5);
        b.insert(b.begin(), arr_b, arr_b + 5);
        
        int arr_op[] = {1, 1, 2, 1};

        op.insert(op.begin(), arr_op, arr_op + 4);
        
        vector<int> temp;
        temp.clear(); temp.push_back(1); data.push_back(temp);
        temp.clear(); temp.push_back(2); data.push_back(temp);
        temp.clear(); temp.push_back(3); temp.push_back(6); data.push_back(temp);
        temp.clear(); temp.push_back(2); data.push_back(temp);

    }

    void generateSubtask1(vector<int>& u, vector<int>& v, vector<int>& a, vector<int>& b, vector<int>& op, vector<vector<int> >& data) {
        int arr_u[] = {1, 4, 8, 1, 2, 2, 8, 6, 1, 3};
        int arr_v[] = {7, 8, 7, 5, 3, 7, 5, 5, 2, 8};

        u.insert(u.begin(), arr_u, arr_u + 10);
        v.insert(v.begin(), arr_v, arr_v + 10);

        int arr_a[] = {2, 1, 1, 1, 1, 1, 2, 2};
        int arr_b[] = {3, 6, 10, 20, 3, 3, 7, 8};

        a.insert(a.begin(), arr_a, arr_a + 8);
        b.insert(b.begin(), arr_b, arr_b + 8);
        
        int arr_op[] = {1, 1, 2, 1, 2, 1};

        op.insert(op.begin(), arr_op, arr_op + 6);
        
        vector<int> temp;
        temp.clear(); temp.push_back(2); data.push_back(temp);
        temp.clear(); temp.push_back(6); data.push_back(temp);
        temp.clear(); temp.push_back(4); temp.push_back(15); data.push_back(temp);
        temp.clear(); temp.push_back(7); data.push_back(temp);
        temp.clear(); temp.push_back(8); temp.push_back(7); data.push_back(temp);
        temp.clear(); temp.push_back(1); data.push_back(temp);

    }

    void generateSubtask2(vector<int>& u, vector<int>& v, vector<int>& a, vector<int>& b, vector<int>& op, vector<vector<int> >& data) {
        int arr_u[] = { 3, 1, 1, 3, 2, 9, 5, 6, 8, 4, 2, 10, 4, 7, 8};
        int arr_v[] = {10, 5, 9, 4, 4, 5, 7, 3, 1, 6, 1,  1, 8, 8, 9};

        u.insert(u.begin(), arr_u, arr_u + 15);
        v.insert(v.begin(), arr_v, arr_v + 15);

        int arr_a[] = {3, 2, 1, 2, 1, 2, 1, 2, 3, 1};
        int arr_b[] = {32, 40, 80, 35, 60, 55, 50, 40, 23, 81};

        a.insert(a.begin(), arr_a, arr_a + 10);
        b.insert(b.begin(), arr_b, arr_b + 10);
        
        int arr_op[] = {1, 1, 2, 2, 1, 1, 1, 1};

        op.insert(op.begin(), arr_op, arr_op + 8);
        
        vector<int> temp;
        temp.clear(); temp.push_back(2);  data.push_back(temp);
        temp.clear(); temp.push_back(9);  data.push_back(temp);
        temp.clear(); temp.push_back(10); temp.push_back(75); data.push_back(temp);
        temp.clear(); temp.push_back(6);  temp.push_back(35); data.push_back(temp);
        temp.clear(); temp.push_back(3);  data.push_back(temp);
        temp.clear(); temp.push_back(6);  data.push_back(temp);
        temp.clear(); temp.push_back(7);  data.push_back(temp);
        temp.clear(); temp.push_back(10); data.push_back(temp);

    }

    void randomArray(vector<int>& v, int size, int lo, int hi) {
        for (int i=0; i<size; i++)
            v.push_back(rnd.nextInt(lo, hi));
    }

    void renumber(int n, vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 0; i < n; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < u.size(); i++) {
            u[i] = 1+permutation[u[i]];
            v[i] = 1+permutation[v[i]];
        }
    }

    void randomTree(int n, vector<int>& u, vector<int>& v) {
        for (int i = 1; i < n; i++) {
            u.push_back(i);
            v.push_back(rnd.nextInt(0, i-1));
        }
        renumber(n, u, v);
    }

    void randomGraph(int n, int m, vector<int>& u, vector<int>& v) {
        randomTree(n, u, v);
        while (u.size() < m) {
            int newU = rnd.nextInt(0, N - 2);
            int newV = rnd.nextInt(newU + 1, N - 1);
            u.push_back(newU+1);
            v.push_back(newV+1);
        }
    }

    void randomQuery(vector<int>& op, vector<vector<int> >& data, int size, int maxop, int maxn, int maxx) {
        for (int i=0; i<size; i++) {
            int opt = rnd.nextInt(1, maxop);
            op.push_back(opt);
            vector<int> datat;
            datat.push_back(rnd.nextInt(1, maxn));
            if (opt == 2)
                datat.push_back(rnd.nextInt(1, maxx));
            data.push_back(datat);
        }
    }
};