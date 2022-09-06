# libfvad: voice activity detection (VAD) library #
[![Build Status](https://travis-ci.org/dpirch/libfvad.svg?branch=master)](https://travis-ci.org/dpirch/libfvad)

this is a fork of [libfvad](https://github.com/dpirch/libfvad.git), with multi threads support and [pybind11](https://github.com/pybind/pybind11.git) integrated
## Support multi process
using [thread pool](https://github.com/bshoshany/thread-pool.git) to accelerate inference

## Support pybind11
build as a shared library using in python, more convenient in python-build ASR system

## Building
```
cmake . -B ./build
make
```

## Usage
- python example is in test/test_vad.py
- only support 16bit pcm, use 20ms as a frame, return True/False for each frame
- move vad_cpp_XXX.so to python_library_path to support global importing
```
import vad_cpp as vad
v=vad.init_vad(3, 16000, 12, False) # init, params: vad_mode, sample_rate, num_processes, verbose
results=vad.process_vad(v,pcm,pcm_len) # do vad, params: vad instance, pcm_data(16bit), pcm_length
vad.free_vad(v) # free memory
```