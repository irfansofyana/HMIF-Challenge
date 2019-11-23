//by : irfan sofyana
#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

#define MAXN 2000
#define MAXK 100000000

typedef long long LL;

class ProblemSpec : public BaseProblemSpec{
    protected:
        //list of variables 
        int N, K;
        vector<int> arr;
        vector<int> ans;

        void InputFormat(){
            LINE(N, K);
            LINE(arr % SIZE(N));
        }

        void OutputFormat(){
            LINE(ans % SIZE(N));
        }

        void GradingConfig(){
            TimeLimit(1);
            MemoryLimit(256);
        }

        void Constraints(){
            CONS(1 <= N && N <= MAXN);
            CONS(0 <= K && K <= MAXK);
            CONS(eachElementBetween(arr, 1, MAXK));
        }

    private:
        bool eachElementBetween(const vector<int> &X, int lo, int hi){
            for (int i = 0; i < X.size(); i++){
                if (X[i] < lo || X[i] > hi) return false;
            }
            return true;
        }
};

class TestSpec : public BaseTestSpec <ProblemSpec>{
    protected:
        void TestCases(){
            for (int i = 0; i < 3; ++i){
                CASE(
                    N = rnd.nextInt(1, 1*MAXN/4),
                    K = rnd.nextInt(0, 1*MAXK/4),
                    randomArrayRange(arr, N, 1, MAXK) 
                );
            }

            for (int i = 0; i < 5; ++i){
                CASE(
                    N = rnd.nextInt(1*MAXN/4 + 1, 2*MAXN/4),
                    K = rnd.nextInt(1*MAXK/4 + 1, 2*MAXK/4),
                    randomArrayRange(arr, N, 1*MAXN/3, MAXK)
                );
            }

            for (int i = 0; i < 10; ++i){
                CASE(
                    N = rnd.nextInt(2*MAXN/4+1, 3*MAXN/4+1),
                    K = rnd.nextInt(2*MAXK/4+1, 3*MAXK/4),
                    randomArrayRange(arr, N, 2*MAXN/3, MAXK)
                );
            }

            for (int i = 0; i < 10; ++i){
                CASE(
                    N = rnd.nextInt(3*MAXN/4+1, 4*MAXN/4),
                    K = rnd.nextInt(3*MAXK/4+1, 4*MAXK/4),
                    randomArrayRange(arr, N, MAXK/1000, MAXK);
                );
            }
            CASE(
                N = MAXN,
                K = MAXK,
                randomArrayRange(arr,N, MAXK, MAXK);
            );
        }
        
    private:
        void randomArray(int N, vector<int> & a){
            a.clear();
            for (int i = 0; i < N; i++){
                a.push_back(rnd.nextInt(1, MAXK));
            }
        }
        void randomArrayRange(vector<int> & a, int N, int lo, int hi){
            a.clear();
            for (int i = 0; i < N; ++i){
                a.push_back(rnd.nextInt(lo, hi));
            }
        }
};
