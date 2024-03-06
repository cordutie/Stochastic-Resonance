/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"
//#include <random>
#include <cmath>

//std::random_device rd;
//std::mt19937 gen(rd());

using namespace c74::min;

float window_function(string tipo, int index, int frame_size) {
    float result = 0.;
    if (tipo == "hann" || tipo == "hanning") {
        result = pow(sin(M_PI * index * (1. / frame_size)), 2.);
    }
    else if (tipo == "hamming") {
        result = 0.54 - 0.46 * cos(2. * M_PI * index * (1. / frame_size));
    }
    else {
        result = 1;
    }
    return result;
}


class windowing : public object<windowing>, public vector_operator<> {
public:
    MIN_DESCRIPTION{ "Trying a passthrough." };
    MIN_TAGS{ "test" };
    MIN_AUTHOR{ "Esteban Gutierrez" };
    MIN_RELATED{ "panner~" };

    inlet<>  input_1{ this, "(signal) input signal", "signal" };
    inlet<>  input_2{ this, "(symbol) name of the window to use", "symbol" };
    outlet<> output_1{ this, "(signal) output signal", "signal" };

    // the actual attribute for the message
    attribute<symbol> name{ this, "window_name", "hanning",
        description {
            "Window name. Choose between hann, hamming and rectangular."
        }
    };

    // define an optional argument for setting the message
    argument<symbol> window_name{ this, "window_name", "Window name.",
        MIN_ARGUMENT_FUNCTION {
            name = arg;
        }
    };

    message<> bang{ this, "bang", "Print the parameters.",
        MIN_FUNCTION {
            symbol cacha_2 = name;
            string cacha = cacha_2;
            cout << "window_name = " << cacha << endl;
        return {};
        }
    };

    void operator()(audio_bundle input, audio_bundle output) {
        auto          in = input.samples(0);
        auto          out = output.samples(0);
        symbol cacha_2 = name;
        string cacha = cacha_2;

        for (auto i = 0; i < input.frame_count(); ++i) {
            out[i] = in[i] * window_function(cacha, i, input.frame_count());
        }
    };
};

MIN_EXTERNAL(windowing);
