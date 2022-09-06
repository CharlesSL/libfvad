
#include <vector>
#include "../test/fvad.h"
#include "BS_thread_pool.hpp"
using namespace std;
class Vad {
public:
    Vad(int sample_rate,int mode, BS::thread_pool *pool, bool verbose) :
            sample_rate(sample_rate),mode(mode),vad_frame_length(sample_rate / 1000 * 20),pool(pool),verbose(verbose) {}

    ~Vad() = default;

    BS::thread_pool *pool;
    int sample_rate;
    int mode;
    int vad_frame_length;
    bool verbose;
};

void *init_vad(int mode, int sample_rates, int num_processes, bool verbose= false);

vector<bool> process_vad(void *vad_p,  const char *samples, int len);

void free_vad(void *vad_p);
