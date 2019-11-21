#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

typedef long long LL;

const int MAXN = 10005;
const int MAXB = 1e9;

class ProblemSpec : public BaseProblemSpec{
    protected:
        int N, M;
        vector<int> arr;
        LL ans;
    
    void InputFormat(){
        LINE(N, M);
        LINE(arr % SIZE(N));
    }

    void OutputFormat(){
        LINE(ans);
    }

    void GradingConfig(){
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints(){
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= M && M <= min(N, 50));
        CONS(eachElementBetween(arr, 1, MAXB));
    }

    private: 
        bool eachElementBetween(const vector<int> & a, int lo, int hi){
            for (int i = 0; i < (int)a.size(); i++){
                if (a[i] < lo || a[i] > hi) return false;
            }
            return true;
        }
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
    protected:
        void TestCases(){
            CASE(
                N = 5,
                M = 2,
                arr = {7, 2, 5, 10, 8});
            for (int i = 0; i < 10; ++i){
                CASE(
                    N = rnd.nextInt(1, 2000),
                    M = rnd.nextInt(1, min(N, 50)),
                    randomArray(N, arr));
            }
            CASE(
                N = MAXN,
                M = 50,
                randomArray(N, arr)   
            );
            for (int i = 0; i < 15; ++i){
                CASE(
                    N = rnd.nextInt(1, MAXN),
                    M = rnd.nextInt(1, min(N, 50)),
                    randomArray(N, arr)
                );
            }
        }
    private: 
        void randomArray(int N, vector<int> & a){
            a.clear();
            for (int i = 0; i < N; i++){
                a.push_back(rnd.nextInt(1, MAXB));
            }
        }
};