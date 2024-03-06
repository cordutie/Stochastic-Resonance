/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"
#include <random>
#include <cmath>

std::random_device rd;
std::mt19937 gen(rd());

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

float C_curve(float f) {
    float f_r = 1000.0f;
    float f_L = pow(10.0f, 1.5f);
    float f_H = pow(10.0f, 3.9f);
    float f_A = pow(10.0f, 2.45f);
    float D = sqrt(0.5f);

    float b = (1.0f / (1.0f - D)) * (pow(f_r, 2) + (f_L * f_H) * (f_L * f_H) / (f_r * f_r) - D * (f_L * f_L + f_H * f_H));
    float c = f_L * f_L * f_H * f_H;

    float f_1 = sqrt((-b - sqrt(b * b - 4 * c)) / 2);
    float f_4 = sqrt((-b + sqrt(b * b - 4 * c)) / 2);

    return (f_4 * f_4 * f * f) / ((f * f + f_1 * f_1) * (f * f + f_4 * f_4));
}

class freqdom : public object<freqdom>, public vector_operator<> {
public:
    MIN_DESCRIPTION{ "Stochastic Resonance based algorithm applied designed to be used in the frequency domain." };
    MIN_TAGS{ "" };
    MIN_AUTHOR{ "Esteban Gutierrez" };
    MIN_RELATED{ "" };

    inlet<>  input_1{ this, "(signal) input magnitude spectrum signal", "signal" };
    inlet<>  input_2{ this, "(signal) input phase spectrum signal", "signal" };
    inlet<>  input_3{ this, "(list) alpha, Theta, sigma and Amount of Iterations in that order" };
    outlet<> output_1{ this, "(signal) output magnitude spectrum signal", "signal" };
    outlet<> output_2{ this, "(signal) output phase spectrum signal", "signal" };
    //outlet<> output_3{ this, "(signal) threshold function", "signal" };

    attribute<number> alpha{ this, "Attenuation factor", 1.0 };
    attribute<number> sigma{ this, "Noise factor", 1.0 };
    attribute<number> N{ this, "Iterations", 8 };
    attribute<number> sr{ this, "Sampling rate", 44100 };
    attribute<number> Theta_1{ this, "Line left parameter", 0 };
    attribute<number> Theta_2{ this, "Line right parameter", 0 };

    message<> list{ this, "list", "alpha, Theta and sigma in that order",
    MIN_FUNCTION {
        alpha = args[0];
        sigma = args[1];
        N = args[2];
        sr = args[3];
        Theta_1 = args[4];
        Theta_2 = args[5];
        return {};
        }
    };

    message<> bang{ this, "bang", "Print the parameters.",
        MIN_FUNCTION {
            int M = static_cast<int>(N);
            if (M < 1) { M = 1; }
            int fs = static_cast<int>(sr);
            if (fs != 44100 && fs != 48000 && fs != 88200 && fs != 96000) { fs = 44100; }
            cout << "alpha = " << alpha << endl;
            cout << "sigma = " << sigma << endl;
            cout << "M = " << M << endl;
            cout << "Sampling rate = " << fs << endl;
            cout << "Line left parameter = " << Theta_1 << endl;
            cout << "Line right parameter = " << Theta_2 << endl;
        return {};
        }
    };

    void operator()(audio_bundle input, audio_bundle output) {
        auto          in_1 = input.samples(0);
        auto          in_2 = input.samples(1);
        auto          out_1 = output.samples(0);
        auto          out_2 = output.samples(1);
        //auto          out_3 = output.samples(2);

        float bin_freq = 0;
        float eta;
        float result = 0;
        float result_temp = 0;
        float signal_temp = 0;
        int M = static_cast<int>(N);
        if (M < 1) { M = 1; }
        int fs = static_cast<int>(sr);
        if (fs != 44100 && fs != 48000 && fs != 88200 && fs != 96000) { fs = 44100; }

        std::normal_distribution<float> d(0, 1);

        //passthrough in the phase
        for (auto i = 0; i < input.frame_count(); ++i) {
            out_2[i] = in_2[i];
        }

        for (auto i = 0; i < input.frame_count(); ++i) {
            result = 0;
            result_temp = 0;

            //freq of the bin is computed
            bin_freq = bin_to_freq(i, fs, input.frame_count());

            //threshold function is plotted
            //out_3[i] = threshold_function(bin_freq, Theta_1, Theta_2);

            //signal is normalized according to Max/MSP non normalized fft
            in_1[i] = (2.0 / input.frame_count()) * in_1[i];

            //signal is attenuated
            in_1[i] = in_1[i] * alpha;

            for (auto j = 0; j < M; j++) {
                //Noise is made
                eta = d(gen) * sigma * C_curve(bin_freq);

                //Noise is added
                signal_temp = in_1[i] + eta;

                //Threshold is applied
                if (signal_temp > threshold_function(bin_freq, Theta_1, Theta_2)) {
                    result_temp = signal_temp;
                }
                else {
                    result_temp = 0;
                }
                result = result + result_temp;
            }

            // average of results is computed 
            out_1[i] = (1.0 / M) * result;

            // result normalized according to max fft
            out_1[i] = (input.frame_count() / 2.) * result;
        }
    }
};

MIN_EXTERNAL(freqdom);