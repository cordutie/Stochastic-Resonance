/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

using namespace c74::min;

class timedom : public object<timedom>, public vector_operator<> {
public:
    MIN_DESCRIPTION{ "Stochastic Resonance based algorithm applied designed to be used in the time domain." };
    MIN_TAGS{ "" };
    MIN_AUTHOR{ "Esteban Gutierrez" };
    MIN_RELATED{ "" };

    inlet<>  input_1{ this, "(signal) input signal", "signal" };
    inlet<>  input_2{ this, "(list) alpha, Theta, sigma and Amount of Iterations in that order" };
    outlet<> output_1{ this, "(signal) output signal", "signal" };

    attribute<number> alpha{ this, "Attenuation factor", 1.0 };
    attribute<number> Theta{ this, "Threshold factor", 1.0 };
    attribute<number> sigma{ this, "Noise factor", 1.0 };
    attribute<number> N{ this, "Iterations", 8 };


    message<> list{ this, "list", "alpha, Theta and sigma in that order",
    MIN_FUNCTION {
        alpha = args[0];
        Theta = args[1];
        sigma = args[2];
        N = args[3];
        return {};
        }
    };

    message<> bang{ this, "bang", "Print the parameters.",
        MIN_FUNCTION {
            int M = static_cast<int>(N);
            if (M < 1) { M = 1; }
            cout << "alpha = " << alpha << endl;
            cout << "Theta = " << Theta << endl;
            cout << "sigma = " << sigma << endl;
            cout << "M     = " << M << endl;
        return {};
        }
    };

    void operator()(audio_bundle input, audio_bundle output) {
        auto          in_1 = input.samples(0);
        auto          out_1 = output.samples(0);

        float eta;
        float result = 0;
        float result_temp = 0;
        float signal_temp = 0;
        int M = static_cast<int>(N);
        if (M < 1) { M = 1; }

        std::normal_distribution<float> d(0, 1);

        for (auto i = 0; i < input.frame_count(); ++i) {
            result = 0;
            result_temp = 0;

            //signal is attenuated
            in_1[i] = in_1[i] * alpha;

            for (auto j = 0; j < M; j++) {
                //Noise is made
                eta = d(gen) * sigma;

                //Noise is added
                signal_temp = in_1[i] + eta;

                //Threshold is applied
                if (signal_temp > Theta || signal_temp < -Theta) {
                    result_temp = signal_temp;
                }
                else {
                    result_temp = 0;
                }
                result = result + result_temp;
            }

            // average of results is computed 
            out_1[i] = (1.0 / M) * result;
        }
    }
};

MIN_EXTERNAL(timedom);