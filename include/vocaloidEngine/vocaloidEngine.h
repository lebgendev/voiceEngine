#include "sounds.h"
#include <fstream>

#ifndef VOCALOIDENGINE_h
#define VOCALOIDENGINE_h

class SineOscillator {
    float frequency, amplitude, angle= 0.0f;
    int bitDepth = 16, sampleRate = 44100;

    int maxAmplitude;
    int preSize = 0;

    std::ofstream outputFile;

    public:

    SineOscillator(float f, float a);

    float processConsonant(Frequencies &sound);

    float processVowel(Frequencies &sound);
    
    void byteTransformFileWrite(int val, int size);

    void initWAV(std::string filename = "waveform.wav");

    void initWAVHeaders();

    void generateVowel(float duration, Frequencies &sound);

    void generateConsonant(Frequencies &sound);

    void finalizeWAV();

    void closeWAV();

    void resetFrequencies(Frequencies &sound);
    
};

#endif