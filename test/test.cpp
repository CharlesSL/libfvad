//
// Created by Charles on 2022/9/1.
//
#include "vad.h"
#include "iostream"

int main(int argc, char** argv) {
    Vad *vad= init_vad(3,16000,12);
    vector<int16_t> samples(640001203) ;
    for (int i = 0; i < 640001203; ++i) {
        samples.emplace_back(i);
    }
    std::cout<< "starting"<<"\n";
    vector<bool> results= process_vad(vad, samples);
    std::cout<< results.size()<<"\n";
    free_vad(vad);
}