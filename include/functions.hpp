#include <cmath>
#include <vector>
#include <functional>

float f1(float x, float y);
float f2(float x, float y);
float f3(float x, float y);
float f4(float x, float y);
float f5(float x, float y);
float f6(float x, float y);
float f7(float x, float y);
float f8(float x, float y);
float f9(float x, float y);
float f10(float x, float y);
float f11(float x, float y);
float f12(float x, float y);

class Functions{
    public:
        Functions();
        ~Functions();
        std::vector<std::function<float(float, float)>> functions;
        std::function<float(float, float)> getFunction(int i);

    private:
        void initFunctions();

};




