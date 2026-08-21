#include "sounds.h"
#include <fstream>
#include <cstdint>

#ifndef VOICEENGINE_h
#define VOICEENGINE_h

class SineOscillator {
    float frequency, amplitude, angle= 0.0f;
    int bitDepth = 16, sampleRate = 44100;

    int maxAmplitude;
    int preSize = 0;

    std::ofstream outputFile;

    public:

    SineOscillator(float f, float a);

    float processVoicelessConsonant(Frequencies &sound);

    float processVowel(Frequencies &sound);
    
    void byteTransformFileWrite(int val, int size);

    void initWAV(std::string filename = "waveform.wav");

    void initWAVHeaders();

    void generateVowel(float duration, Frequencies &sound);

    void generateVoicelessConsonant(Frequencies &sound);

    void generateVoicedConsonant(Frequencies &sound);

    void finalizeWAV();

    void closeWAV();

    void resetFrequencies(Frequencies &sound);
    
};

#endif