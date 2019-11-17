#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 150000;

class ProblemSpec : public BaseProblemSpec{
    protected:
        int N;
        vector<int> A, B, C;
        long long ans;
    
    void InputFormat(){
        LINE(N);
        LINE(A % SIZE(N));
        LINE(B % SIZE(N));
        LINE(C % SIZE(N));
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
        CONS(eachElementBetween(A, 1, 5));
        CONS(eachElementBetween(B, 1, 5));
        CONS(eachElementBetween(C, 1, 5));
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
            CASE(N = 3, A ={1, 3, 3}, B = {1, 1, 1}, C = {1, 2, 3});
            CASE(N = 7, 
            A ={3,3,4,1,3,4,4},
            B ={4,2,5,1,5,5,4},
            C ={5,5,1,3,4,4,4});

            CASE(N = 3,
            randomArrayMaks(N, A),
            randomArrayMaks(N, B),
            randomArrayMaks(N, C));
            for (int i = 0; i < 4; i++){
                CASE(N = 3,
                randomArray(N, A),
                randomArray(N, B),
                randomArray(N, C));
            }

            CASE(N = 100,
            randomArrayMaks(N, A),
            randomArrayMaks(N, B),
            randomArrayMaks(N, C));

            for (int i = 0; i < 9; i++){
                CASE(N = rnd.nextInt(3, 100),
                randomArray(N, A),
                randomArray(N, B), 
                randomArray(N, C));
            }

            CASE(N = 2000,
            randomArrayMaks(N, A),
            randomArrayMaks(N, B),
            randomArrayMaks(N, C));

            for (int i = 0; i < 10; i++){
                CASE(N = rnd.nextInt(3, 2000),
                randomArray(N, A),
                randomArray(N, B), 
                randomArray(N, C));
            }

            CASE(N=MAXN,
            randomArrayMaks(N, A),
            randomArrayMaks(N, B),
            randomArrayMaks(N, C));

            for (int i = 0; i < 20; i++){
                CASE(N = rnd.nextInt(3, MAXN),
                randomArray(N, A),
                randomArray(N, B), 
                randomArray(N, C));
            }
        }

    private:
        void randomArray(int N, vector<int> & a){
            a.clear();
            for (int i = 0; i < N; i++){
                a.push_back(rnd.nextInt(1, 5));
            }
        }
        void randomArrayMaks(int N, vector<int> &a){
            a.clear();
            for (int i = 0; i < N; i++){
                a.push_back(5);
            }
        }
};
