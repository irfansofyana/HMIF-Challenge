#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

typedef long long LL;

const int MAXN = 500005;
const int MAXB = 1e6;

class ProblemSpec : public BaseProblemSpec{
    protected:
        int N;
        vector<int> arr;
        LL ans;
    
    void InputFormat(){
        LINE(N);
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
            for (int i = 0; i < 4; ++i){
                CASE(
                    N = rnd.nextInt(1, 1*MAXN/5),
                    randomArrayRange(N, arr, 1, 1*MAXB/5);
                );
            }
            for (int i = 0; i < 4; ++i){
                CASE(
                    N = rnd.nextInt(1*MAXN/5+1, 2*MAXN/5),
                    randomArrayRange(N, arr, 1*MAXB/5+1, 2*MAXB/5)
                );
            }

            for (int i = 0; i < 5; ++i){
                CASE(
                    N = rnd.nextInt(2*MAXN/5+1, 3*MAXN/5),
                    randomArrayRange(N, arr, 2*MAXB/5+1, 3*MAXB/5)
                );
            }

            for (int i = 0; i < 7; ++i){
                CASE(
                    N = rnd.nextInt(3*MAXN/5+1, 4*MAXN/5),
                    randomArrayRange(N, arr, 3*MAXB/5+1, 4*MAXB/5)
                );
            }

            for (int i = 0; i < 10; ++i){
                CASE(
                    N = rnd.nextInt(4*MAXN/5+1, 5*MAXN/5),
                    randomArrayRange(N, arr, 4*MAXB/5+1, 5*MAXB/5)
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
        void randomArrayRange(int N, vector<int> & a, int lo, int hi){
            a.clear();
            for (int i = 0; i < N; i++){
                a.push_back(rnd.nextInt(lo, hi));
            }
        }
};