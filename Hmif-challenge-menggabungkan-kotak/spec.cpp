#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

typedef long long LL;

const int MAXN = 400;
const int MAXB = 1e9;

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
                    N = rnd.nextInt(1, 100),
                    randomArrayRange(arr, N, 1, 10000));
            }
            for (int i = 0; i < 4; ++i){
                CASE(
                    N = rnd.nextInt(101, 200),
                    randomArrayRange(arr, N, 10001, 1000000); 
                );
            }
            for (int i = 0; i < 4; ++i){
                CASE(
                    N = rnd.nextInt(201, 300),
                    randomArrayRange(arr, N, 1000001, 1000000000); 
                );
            }
            for (int i = 0; i < 4; ++i){
                CASE(
                    N = rnd.nextInt(301, 400),
                    randomArrayRange(arr, N, 1, 1000000000); 
                );
            }
            for (int i = 0; i < 4; ++i){
                CASE(
                    N = rnd.nextInt(1, 400),
                    randomArrayRange(arr, N, 1, 1000000000); 
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
        void randomArrayRange(vector<int> & a, int N, int lo, int hi){
            a.clear();
            for (int i = 0; i < N; ++i){
                a.push_back(rnd.nextInt(lo, hi));
            }
        }
};