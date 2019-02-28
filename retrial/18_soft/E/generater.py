import random
import sys
from pathlib import Path
import os
n = 1500000
max = 10**9
path = Path(sys.argv[0]).parent
with open(os.path.join(path, 'cases/case2.txt'), 'w') as file:
    i = 0
    while i < n:
        file.write(f"{int(random.random()*max)}\n")
        i += 1
