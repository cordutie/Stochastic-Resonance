/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"

using namespace c74::min;

float bin_to_freq(int j, float fs, int frame_size) {
    return j * fs * (1.0 / frame_size);
}

float threshold_function(float freq, float a, float b) {
    //makes a line that pass over (1,a) and (10,b)
    //x in such represent the exponent of the freq domain (2^x = freq)
    //then everything is transformed to amplitude for comparison with the signal
    float result;
    if (freq > 100) {
        result = pow(10.0, 0.05 * ((b - a) * (log2(freq) - log2(100.)) * (1. / (log2(22050) - log2(100.))) + a));
    }
    else {
        result = pow(10.0, 0.05 * ((b - a) * (log2(100) - log2(100.)) * (1. / (log2(22050) - log2(100.))) + a));
    }
    return result;
}

class util : public object<util> {
public:
    MIN_DESCRIPTION{ "Function to plot the threshold function in the frequency domain regarding the sr.freqdom object." };
    MIN_TAGS{ "" };
    MIN_AUTHOR{ "Esteban Gutierrez" };
    MIN_RELATED{ "sr.freqdom~" };

    inlet<>  input_1{ this, "(list) alpha, Theta and sigma in that order", "list" };
    outlet<> output_1{ this, "(list) output magnitude spectrum signal", "list" };

    attribute<number> theta_1{ this, "Threshold_1", 0. };
    attribute<number> theta_2{ this, "Threshold_2", 0. };
    attribute<number> signal_vector_size{ this, "signal_vector_size", 1024 };
    attribute<number> sr{ this, "sampling rate", 44100 };


    message<> list{ this, "list", "amplitudes for the threshold line function at 100Hz and 22050Hz in that order.",
    MIN_FUNCTION {
        theta_1 = args[0];
        theta_2 = args[1];
        int svs = static_cast<int>(signal_vector_size);
        int fs = static_cast<int>(sr);
        if (fs != 44100 && fs != 48000 && fs != 88200 && fs != 96000) { fs = 44100; }

        float bin_freq;

        //Threshold function is saved in an array and outputed
        atoms solution(svs);
        for (int i = 0; i < svs; i++) {
            bin_freq = bin_to_freq(i, fs, svs);
            solution[i] = threshold_function(bin_freq, theta_1, theta_2);
        }
        output_1.send(solution);

        return {};
        }
    };

};

MIN_EXTERNAL(util);