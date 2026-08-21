# Simple C++ Voice Engine

A lightweight, header-only voice synthesis engine implemented in pure C++ that simulates audio waveforms and formant filters.

## Features

- **Waveform Synthesis:** Generates raw audio data (e.g., sawtooth waves).
- **Formant Filtering:** Implements biquad formant filters to simulate vowel sounds.
- **WAV Export:** Built-in capability to write uncompressed 16-bit WAV files.
- **Zero Dependencies:** Pure C++ implementation with no external audio libraries.

## Getting Started

### Prerequisites

- A C++17 compatible compiler (e.g., GCC, Clang, or MSVC).

### Compilation

You can compile the example generator directly using your preferred compiler:

```bash
g++ main.cpp include/voiceEngine/*.cpp -o main.exe -I./include
./voice_engine