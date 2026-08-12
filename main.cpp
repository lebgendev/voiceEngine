#include <iostream>
#include <cmath>
#include <fstream>

typedef struct{
    float f1;
    float f2;
    float f3;
    float f1_x1 = 0, f1_x2 = 0, f1_y1 = 0, f1_y2 = 0;
    float f2_x1 = 0, f2_x2 = 0, f2_y1 = 0, f2_y2 = 0;
    float f3_x1 = 0, f3_x2 = 0, f3_y1 = 0, f3_y2 = 0;
} Frequencies;

Frequencies i_sound = {240.0, 2400.0, 3000.0};
Frequencies ah_sound = {730.0, 1090.0, 2440.0};


// float applyBiquadFilter(float sample, float frequency, float f1, float f2){
    
// }

float applyBiquadFilter(float sample, float targetFreq, int sampleRate, float& x1, float& x2, float& y1, float& y2) {
    float omega = 2.0f * M_PI * targetFreq / (float)sampleRate;
    float alpha = sin(omega) / 20.0f;
    
    float b0 = alpha;
    float b1 = 0.0f;
    float b2 = -alpha;
    float a0 = 1.0f + alpha;
    float a1 = -2.0f * cos(omega);
    float a2 = 1.0f - alpha;

    b0 /= a0; b1 /= a0; b2 /= a0;
    a1 /= a0; a2 /= a0;

    float y0 = b0 * sample + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;

    x2 = x1;
    x1 = sample;
    y2 = y1;
    y1 = y0;

    return y0; 
}

void resetFrequencies(Frequencies &sound){
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
}

class SineOscillator {
    float frequency, amplitude, angle = 0.0f;
    int bitDepth = 16, sampleRate = 44100;

    int maxAmplitude;
    int preSize = 0;

    std::ofstream outputFile;

    public:

    SineOscillator(float f, float a) : frequency(f), amplitude(a) {
        maxAmplitude = pow(2, bitDepth-1) - 1;
    }

    float process(){
        auto sample = 2.0f * angle - 1.0f;
        angle += frequency / (float)sampleRate;

        if (angle >= 1.0f) {
            angle -= 1.0f;
        }


        float formant1_out = applyBiquadFilter(sample, i_sound.f1, sampleRate, i_sound.f1_x1, i_sound.f1_x2, i_sound.f1_y1, i_sound.f1_y2);
        float formant2_out = applyBiquadFilter(sample, i_sound.f2, sampleRate, i_sound.f2_x1, i_sound.f2_x2, i_sound.f2_y1, i_sound.f2_y2);
        float formant3_out = applyBiquadFilter(sample, i_sound.f3, sampleRate, i_sound.f3_x1, i_sound.f3_x2, i_sound.f3_y1, i_sound.f3_y2);

        float vowelSample =
            1.0f * formant1_out +
            0.6f * formant2_out +
            0.3f * formant3_out;

        return vowelSample;
    }
    
    void byteTransformFileWrite(int val, int size){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        outputFile.write(reinterpret_cast<char*>(&val), size);
    }

    void initWAV(std::string filename = "waveform.wav"){
        this->outputFile.open(filename, std::ios::binary);
    }

    void initWAVHeaders(){

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

    void generateWAV(int duration = 1){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        for(int i = 0; i < sampleRate*duration; i++){
            auto sample = process();
            short intSample = static_cast<short>(sample*maxAmplitude);
            outputFile.write(reinterpret_cast<char*> (&intSample), 2);
        }
        resetFrequencies(i_sound);
    }

    void finalizeWAV(){
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

    void closeWAV(){
        if(!outputFile){
            std::cerr << "Output File is missing.\n";
            return;
        }
        if(!outputFile.is_open()){
            std::cerr << "Output File isn't open.\n";
        }
        outputFile.close();
    }
    
    
};





int main(){
    int duration = 2;
    SineOscillator osc(880.0, 0.5);

    osc.initWAV();
    osc.initWAVHeaders();
    osc.generateWAV(3);
    osc.finalizeWAV();
    osc.closeWAV();

    return 0;
}