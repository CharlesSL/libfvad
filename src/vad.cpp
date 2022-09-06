#include <cstdlib>
#include "vad.h"
#include "iostream"
#include <cmath>

using namespace std;
using namespace chrono;

void *init_vad(int mode, int sample_rate, int num_processes, bool verbose) {
    auto *pool = new BS::thread_pool(num_processes);
    Fvad *fvad = fvad_new();
    fvad_set_mode(fvad, mode);
    fvad_set_sample_rate(fvad, sample_rate);
    Vad *vad = new Vad(sample_rate, mode, pool, verbose);
    return vad;
}

void free_vad(void *vad_p) {
    delete (Vad*)vad_p;
}

vector<bool> process_vad_loop(Vad *vad, const int16_t *samples, int num_frames) {
    Fvad *fvad = fvad_new();
    fvad_set_mode(fvad, vad->mode);
    fvad_set_sample_rate(fvad, vad->sample_rate);
    vector<bool> results;
    for (int i = 0; i < num_frames; ++i) {
        results.emplace_back(fvad_process(fvad, samples + (i * vad->vad_frame_length), vad->vad_frame_length));
    }
    fvad_free(fvad);
    return results;
}

vector<bool> process_vad(void *vad_p, const char *samples, int len) {
    Vad *vad = static_cast<Vad *>(vad_p);
    vector<future<vector<bool>>> futures;
    int vad_frame_length = vad->vad_frame_length;
    int total_num_frames = floor((double) len / vad_frame_length);
    auto *samples_short = (short *) samples;

    // allocate task to multi threads
    auto t1 = high_resolution_clock::now();
    int num_frames_per_thread = ceil((double) total_num_frames / vad->pool->get_thread_count());
    for (int i = 0; i < total_num_frames; i += num_frames_per_thread) {
        futures.emplace_back(vad->pool->submit(process_vad_loop, vad,  samples_short + (i * vad_frame_length), min(num_frames_per_thread, total_num_frames - i)));
    }
    auto t2 = high_resolution_clock::now();

    // waiting for task finish
    vector<bool> results;
    for (auto &future: futures) {
        auto r = future.get();
        for (auto result: r) {
            results.emplace_back(result);
        }
    }
    auto t3 = high_resolution_clock::now();
    if (vad->verbose)
        cout << "total_num_frames=" << total_num_frames
             << ", submit_task cost_ms=" << duration_cast<milliseconds>(t2 - t1).count()
             << ", finish_task cost_ms=" << duration_cast<milliseconds>(t3 - t2).count()
             << endl;
    return results;
}
