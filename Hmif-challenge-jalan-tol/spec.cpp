//by : irfan sofyana
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 100000
#define MAXQ 100000
#define MAXW 1000000000

typedef long long LL;

class ProblemSpec : public BaseProblemSpec{
    protected:
        //list of variables 
        int N, Q;
        vector<int> U, V, W;
        vector<int> L, R;
        vector<LL> ans;

        void InputFormat(){
            LINE(N, Q);
            LINES(U, V, W) % SIZE(N-1);
            LINES(L, R) % SIZE(Q);
        }

        void OutputFormat(){
            LINES(ans) % SIZE(Q);
        }

        void GradingConfig(){
            TimeLimit(2);
            MemoryLimit(64);
        }

        void Constraints(){
            CONS(1 <= N && N <= MAXN);
            CONS(1 <= Q && Q <= MAXQ);
            CONS(eachElementBetween(U, 1, N));
            CONS(eachElementBetween(V, 1, N));
            CONS(eachElementBetween(W, 1, MAXW));
            CONS(isMakeTree(N, U, V));
            CONS(eachElementBetween(L, 1, MAXW));
            CONS(eachElementBetween(R, 1, MAXW));
            CONS(isValidLR(L, R));
        }

    private:
        bool eachElementBetween(const vector<int> &X, int lo, int hi){
            for (int i = 0; i < X.size(); i++){
                if (X[i] < lo || X[i] > hi) return false;
            }
            return true;
        }

        bool isValidLR(const vector<int> &L, const vector<int> &R){
            for (int i = 0; i < (int)L.size(); i++){
                if (L[i] > R[i]) return false;
            }
            return true;
        }

        void DFS(vector<bool> &visited,const vector<vector<int> > &adj, int node,int parent, bool &ret){
            visited[node] = true;
            for (int i = 0; i < adj[node].size(); i++){
                int nxt = adj[node][i];
                if (visited[nxt]) {
                    if (nxt != parent) {
                        ret = false;
                        return;   
                    }
                }else{
                    DFS(visited, adj, nxt, node, ret);
                }
            }
        }

        bool isAllVisited(int N,vector<bool> &visited){
            for (int i = 1; i <= N ; i++){
                if (visited[i] == false) return false;
            }
            return true;
        }

        bool isMakeTree(int N, const vector<int> &a,const vector<int> &b){
            vector<bool> visited(N+1);
            vector<vector<int> > adj(N+1);
            for(int i = 0; i < N-1; i++){
                adj[a[i]].push_back(b[i]);
                adj[b[i]].push_back(a[i]);
            }
            bool ret = true;
            fill(visited.begin(), visited.end(), false);
            DFS(visited, adj, 1, 0, ret);
            return isAllVisited(N, visited) && ret;
        }

        bool isMakeStarTree(int N, const vector<int> &a, const vector<int> &b){
            bool isTree = isMakeStarTree(N, a, b);
            vector<vector<int> > adj(N-1);
            for (int i = 0; i < N-1; i++){
                adj[a[i]].push_back(b[i]);
                adj[b[i]].push_back(a[i]);
            }
            int cnt = 0;
            for (int i = 1; i <= N; i++){
                if ((int)adj[i].size() > 1) cnt++;
            }
            return (cnt==1 && isTree);
        }

};

class TestSpec : public BaseTestSpec <ProblemSpec>{
    protected:
        void BeforeTestCase(){
            U.clear();
            V.clear();
            W.clear();
            L.clear();
            R.clear();
            ans.clear();
        }

        void TestCases(){
            for (int i = 0; i < 3; i++){
                CASE(N = rnd.nextInt(1, 1000), 
                    Q = rnd.nextInt(1, 1000), 
                    RandomTree(N, U, V),
                    RandomWeight(N, W, 100001, 1000000000);
                    RandomQuery(Q, 1, 100000, L, R));
            }
            for (int i = 0; i < 6; i++){
                CASE(N = rnd.nextInt(1, 1000), 
                    Q = rnd.nextInt(1, 1000), 
                    RandomTree(N, U, V),
                    RandomWeight(N, W, 100001, 1000000000);
                    RandomQuery(Q, 1, 1000000000, L, R));
            }
            for (int i = 0; i < 7; i++){
                CASE(N = rnd.nextInt(1, 1000),
                        Q = rnd.nextInt(1, 1000),
                        RandomTree(N, U, V),
                        RandomWeight(N, W, 1, 100000),
                        RandomQuery(Q, 1, 1000000000, L, R));
            }
            for (int i = 0; i < 10; i++){
                CASE(N = rnd.nextInt(1, 1000),
                        Q = rnd.nextInt(1, 1000),
                        RandomStarTree(N, U, V),
                        RandomWeight(N, W, 1, 1000000000),
                        RandomQuery(Q, 1, 1000000000, L, R));
            }
            for (int i = 0; i < 10; i++){
                CASE(N = rnd.nextInt(1, 100000),
                    Q = rnd.nextInt(1, 100000),
                    RandomStarTree(N, U, V),
                    RandomWeight(N, W, 1, 100000),
                    RandomQuery(Q, 1, 1000000, L, R));
            }   
        }
        
    private:
        void renumber(int N, vector<int> &a, vector<int> &b){
            vector<int> p;
            for (int i = 1; i <= N; i++)
                p.push_back(i);
            rnd.shuffle(p.begin(), p.end());
            for (int i = 0 ; i < (int)a.size(); i++){
                a[i] = p[a[i]-1];
                b[i] = p[b[i]-1];
            }
        }
        void RandomTree(int N, vector<int> &a, vector<int> &b){
            a.clear(); b.clear();
            for (int i = 2; i <= N; i++){
                a.push_back(i);
                b.push_back(rnd.nextInt(1,i-1));
            }
            renumber(N, a, b);
        }
        void RandomQuery(int Q,int lo,int hi, vector<int> &l, vector<int> &r){
            l.clear(); r.clear();
            for (int i = 0; i < Q; i++){
                int b1 = rnd.nextInt(lo, hi);
                int b2 = rnd.nextInt(b1, hi);
                l.push_back(b1);
                r.push_back(b2);
            }
        }
        void RandomStarTree(int N, vector<int> &a, vector<int> &b){
            a.clear(); b.clear();
            int center = rnd.nextInt(1, N);
            for (int i = 1; i <= N; i++){
                if (i != center){
                    int t = rnd.nextInt(1, 2);
                    if (t == 1) {
                        a.push_back(i);
                        b.push_back(center);
                    }else {
                        a.push_back(center);
                        b.push_back(i);
                    }
                }

            }
        }
        void RandomWeight(int N, vector<int> & W, int lo, int hi){
            W.clear();
            for (int i = 0; i < N-1; i++){
                W.push_back(rnd.nextInt(lo, hi));
            }
        }
};
