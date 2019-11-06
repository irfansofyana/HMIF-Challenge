#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

typedef long long LL;

const int MAXN = 100005;
const int MAXB = 1e9;

class ProblemSpec : public BaseProblemSpec{
    protected:
        int N, M;
        vector<vector<LL> > dp;
        vector<LL> arr;
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

        }
    private: 

};