#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 100000;

class ProblemSpec : public BaseProblemSpec{
    protected:
        int N, K;
        vector<int> ans;

    void InputFormat(){
        LINE(N, K);
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
        CONS(0 <= K && K < N);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>{
    protected: 
        void TestCases(){
            CASE(N = 5, K = 3);
            CASE(N = 7, K = 4);
            CASE(N = 94, K = 47);
            CASE(N = 98280, K = 84);
            for (int i = 0; i < 10; ++i){
                CASE(N = rnd.nextInt(1, 2000), K = rnd.nextInt(0, N-1));
            }
            for (int i = 0; i < 10; ++i){
                CASE(N = rnd.nextInt(2001, MAXN), K = rnd.nextInt(0,50));
            }
            for (int i = 0; i < 5; ++i){
                CASE(N = rnd.nextInt(10000, MAXN), K = rnd.nextInt(0, 1));
            }
        }
};