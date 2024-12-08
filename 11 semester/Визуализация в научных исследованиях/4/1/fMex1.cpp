#include <cmath>
#include "mex.hpp"
#include "mexAdapter.hpp"
#define  PI  3.1415926535897932

class MexFunction : public matlab::mex::Function {
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) override {
        checkArguments(outputs, inputs);

        double xb = inputs[0][0];
        double xe = inputs[1][0];
        int N = static_cast<int>(inputs[2][0]);
        double yb = inputs[3][0];
        double ye = inputs[4][0];
        int M = static_cast<int>(inputs[5][0]);
        double x1 = inputs[6][0];
        double y1 = inputs[7][0];
        double I1 = inputs[8][0];
        double f1 = inputs[9][0];

        matlab::data::ArrayFactory factory;

        // Создание выходных массивов
        matlab::data::TypedArray<double> x = factory.createArray<double>({1, static_cast<size_t>(N)});
        matlab::data::TypedArray<double> y = factory.createArray<double>({1, static_cast<size_t>(M)});
        matlab::data::TypedArray<double> z = factory.createArray<double>({static_cast<size_t>(N), static_cast<size_t>(M)});

        Field(xb, xe, N, yb, ye, M, x1, y1, I1, f1, x, y, z);

        outputs[0] = std::move(x);
        outputs[1] = std::move(y);
        outputs[2] = std::move(z);
    }

private:
    void checkArguments(matlab::mex::ArgumentList& outputs, matlab::mex::ArgumentList& inputs) {
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        matlab::data::ArrayFactory factory;
        if (inputs.size() != 10) {
            matlabPtr->feval(u"error",
                0,
                std::vector<matlab::data::Array>({ factory.createScalar("Ten inputs required: xb, xe, N, yb, ye, M, x1, y1, I1, f1.") }));
        }

        if (outputs.size() != 3) {
            matlabPtr->feval(u"error",
                0,
                std::vector<matlab::data::Array>({ factory.createScalar("Three outputs required: x, y, z.") }));
        }
    }

    void Field(double xb, double xe, int N, double yb, double ye, int M,
               double x1, double y1, double I1, double f1,
               matlab::data::TypedArray<double>& x,
               matlab::data::TypedArray<double>& y,
               matlab::data::TypedArray<double>& z) {
        double lam = 2;
        double r0 = lam / 4;
        double k = 2 * PI / lam;

        double dx = (xe - xb) / (N - 1);
        double dy = (ye - yb) / (M - 1);

        for (int i = 0; i < N; ++i) {
            x[i] = xb + dx * i;
        }
        for (int j = 0; j < M; ++j) {
            y[j] = yb + dy * j;
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                double r1 = std::sqrt((x[i] - x1) * (x[i] - x1) + (y[j] - y1) * (y[j] - y1));
                double c1;

                if (r1 < r0) {
                    c1 = I1 / r0;
                } else {
                    c1 = -I1 / r1 * ((1 / (k * r1)) * std::cos(k * r1 + f1) + 
                                     (1 - 1 / (k * r1) / (k * r1)) * std::sin(k * r1 + f1));
                }

                z[i][j] = c1;
            }
        }
    }
};
