import sys
from pathlib import Path
import os

path = Path(sys.argv[0]).parent
with open(os.path.join(path, 'cases/case_base.txt'), 'r') as file:
    i = 0
    while i < 15:
        with open(os.path.join(path, f'cases/case_{i}.txt'), 'w') as f2:
            f2.write('100000\n')

            j = 0
            while j < 100000:
                line = file.readline()
                f2.write(line)
                j += 1

        i+=1
