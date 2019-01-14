import sys
import os
import subprocess

def fast_run(path, platform, num):
    if platform == "win":
        spliter = "\\"
    else:
        spliter = "/"

    if spliter in path:
        parent = os.path.abspath(os.path.join(path, os.pardir))
    else:
        parent = ""

    debug = os.path.join(parent, "debug")
    if not os.path.exists(debug):
        os.mkdir(debug)

    file = "num"+num
    src = os.path.join(parent, file, f"{file}.c")
    out = os.path.join(debug, file)
    cmd = f"gcc {src} -o {out}"

    subprocess.call(cmd, stderr=subprocess.STDOUT, shell=True)

    if platform == "win":
        cmd = f"{out}" + ".exe"
    else:
        cmd = f"{out}"

    subprocess.call(cmd, stderr=subprocess.STDOUT, shell=True)

if __name__ == '__main__':
    path = sys.argv[0]
    num = sys.argv[1]

    # if len(sys.argv) >= 2:
    #     path = sys.argv[0]
    #     num = sys.argv[1]
    #     if len(sys.argv) >= 3:
    #         platform = sys.argv[2]
    #     elif:
    #         platform = "mac"

    fast_run(path, "mac", num)
