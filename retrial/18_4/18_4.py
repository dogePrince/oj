import sys

class P:
    def __init__(self, parent):
        self.parent = parent
        self.count = 0

def add(people):
    people.count += 1
    if people.parent is not None:
        add(people.parent)

p_set = []
for x in input().strip().split(' '):
    value = int(x)
    p_set.append(P(value))

for p in p_set:
    if p.parent == 0:
        p.parent = None
    else:
        p.parent = p_set[p.parent-1]
    add(p)

for p in p_set:
    sys.stdout.write(str(p.count)+' ')
sys.stdout.flush()
