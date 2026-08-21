#include "vocaloidEngine.h"
#include <iostream>



    SineOscillator::SineOscillator(float f, float a) : frequency(f), amplitude(a) {
        maxAmplitude = pow(2, bitDepth-1) - 1;
    }

    float SineOscillator::processVoicelessConsonant(Frequencies &sound){
        static uint32_t xorshift_state = 2463534242U;
        xorshift_state ^= xorshift_state << 13;
        xorshift_state ^= xorshift_state >> 17;
        xorshift_state ^= xorshift_state << 5;
        float noise = (static_cast<float>(xorshift_state) / 4294967296.0f) * 2.0f - 1.0f;

        float f1_out = applyBiquadFilter(noise, sound.f1, sound.bw1, sampleRate, sound.f1_x1, sound.f1_x2, sound.f1_y1, sound.f1_y2);
        float f2_out = applyBiquadFilter(f1_out, sound.f2, sound.bw2, sampleRate, sound.f2_x1, sound.f2_x2, sound.f2_y1, sound.f2_y2);
        float f3_out = applyBiquadFilter(f2_out, sound.f3, sound.bw3, sampleRate, sound.f3_x1, sound.f3_x2, sound.f3_y1, sound.f3_y2);

        float burst = f3_out*0.25;

        return burst;
    }

    float SineOscillator::processVowel(Frequencies &sound){
        auto sample = 0.0;
        for(int h = 1; h <= 50; h++){
            sample += (1.0f / h) * sin(2.0f * M_PI * h * angle);
        }
        sample *= amplitude;

        angle += frequency / (float)sampleRate;

        if (angle >= 1.0f) angle -= 1.0f;


        float formant1_out = applyBiquadFilter(sample, sound.f1, sound.bw1, sampleRate, sound.f1_x1, sound.f1_x2, sound.f1_y1, sound.f1_y2);
        float formant2_out = applyBiquadFilter(sample, sound.f2, sound.bw2, sampleRate, sound.f2_x1, sound.f2_x2, sound.f2_y1, sound.f2_y2);
        float formant3_out = applyBiquadFilter(sample, sound.f3, sound.bw3, sampleRate, sound.f3_x1, sound.f3_x2, sound.f3_y1, sound.f3_y2);

        float vowelSample =
            1.0f * formant1_out +
            0.6f * formant2_out +
            0.3f * formant3_out;

        vowelSample *= 0.5f;

        if(vowelSample > 1.0f)
            vowelSample = 1.0f;

        if(vowelSample < -1.0f)
            vowelSample = -1.0f;
        return vowelSample;
    }
    
    void SineOscillator::byteTransformFileWrite(int val, int size){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        outputFile.write(reinterpret_cast<char*>(&val), size);
    }

    void SineOscillator::initWAV(std::string filename){
        this->outputFile.open(filename, std::ios::binary | std::ios::trunc);
        std::cout << filename << " initialized";
    }

    void SineOscillator::initWAVHeaders(){

        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }

        //RIFF Chunk
        outputFile << "RIFF";
        outputFile << "----";
        outputFile << "WAVE";

        // File Size cant be more than 32 bit integer limit, just remember that.

        //Format Chunk
        outputFile << "fmt ";
        byteTransformFileWrite(16, 4); // 16 for PCM
        byteTransformFileWrite(1, 2); // Compression Code (PCM uncompressed)
        byteTransformFileWrite(1, 2); // Num of channels. 1: mono / 2: stereo i think
        byteTransformFileWrite(sampleRate, 4); // sample rate

        byteTransformFileWrite(sampleRate*1*bitDepth/8, 4); // byte rate
        byteTransformFileWrite(1*bitDepth/8, 2); // block align / bytes per sample across all channels
        byteTransformFileWrite(bitDepth, 2); // bit depth / bits per sample


        //Data Chunk

        outputFile << "data";
        outputFile << "----";


        
        this->preSize = outputFile.tellp();



    }

    void SineOscillator::generateVowel(float duration, Frequencies &sound){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        for(int i = 0; i < sampleRate*duration; i++){
            auto sample = processVowel(sound);
            short intSample = static_cast<short>(sample*maxAmplitude);
            outputFile.write(reinterpret_cast<char*> (&intSample), 2);
        }
        resetFrequencies(sound);
    }

    void SineOscillator::generateVoicelessConsonant(Frequencies &sound){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        for(int i = 0; i < sampleRate*0.05; i++){
            auto sample = processVoicelessConsonant(sound);
            short intSample = static_cast<short>(sample*maxAmplitude);
            outputFile.write(reinterpret_cast<char*> (&intSample), 2);
        }
        resetFrequencies(sound);
    }

    void SineOscillator::generateVoicedConsonant(Frequencies &sound){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        int length = sampleRate * 0.05;

        for(int i = 0; i < length; i++){
            float t = (float)i / length; 

            float sample1 = processVoicelessConsonant(sound);
            float sample2 = processVowel(sound);

            float sample = sample1 * (1.0f - t) + sample2 * t;

            short intSample = static_cast<short>(sample * maxAmplitude);
            outputFile.write(reinterpret_cast<char*>(&intSample), 2);
        }
        resetFrequencies(sound);
    }

    void SineOscillator::finalizeWAV(){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        if(preSize == 0){
            std::cerr << "No Data assigned to WAV";
            return;
        }
        int postSize = outputFile.tellp();

        outputFile.seekp(preSize - 4);
        byteTransformFileWrite(postSize - preSize, 4);

        outputFile.seekp(4, std::ios::beg);
        byteTransformFileWrite(postSize - 8, 4);
    }

    void SineOscillator::closeWAV(){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        if(!outputFile.is_open()){
            std::cerr << "Output File isn't open.\n";
        }
        outputFile.close();
    }

    void SineOscillator::resetFrequencies(Frequencies &sound){
        sound.f1_x1 = 0;
        sound.f1_x2 = 0;
        sound.f1_y1 = 0;
        sound.f1_y2 = 0;

        sound.f2_x1 = 0;
        sound.f2_x2 = 0;
        sound.f2_y1 = 0;
        sound.f2_y2 = 0;

        sound.f3_x1 = 0;
        sound.f3_x2 = 0;
        sound.f3_y1 = 0;
        sound.f3_y2 = 0;
        angle = 0.0;
    }
    
