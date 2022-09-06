import multiprocessing
import sys
import time
sys.path.append("./build")

import vad_cpp as vad
data=open('./test.pcm','rb').read()
v=vad.init_vad(3, 16000,multiprocessing.cpu_count(),False)
t1=time.time()
for i in range(1000):
    results=vad.process_vad(v,data, len(data)//2)
t2=time.time()

print('consume',t2-t1, "results:",results)