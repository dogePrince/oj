import sys
import os
import subprocess
import re
import shutil
import argparse
from colorama import init, Fore, Back, Style
init(autoreset=True)


class Project:
    def __init__(self, src, name='', out='', _type='c', _args=None):
        self._out = ''

        self.exec = None
        self.platform = None
        self.name = name
        self.src = src
        self.type = _type
        self.out = out
        self.args = _args

        self.set_platform()

    def create(self):
        if os.path.exists(self.src):
            os.makedirs(self.src, exist_ok=True)
            main_file = os.path.join(self.src, self.name)
            if os.path.exists(main_file):
                if self.type == 'c':
                    src = os.path.normpath('templates/temp.c')
                    dst = os.path.join(self.src, self.name+'.c')
                elif self.type == 'cpp':
                    src = os.path.normpath('templates/temp.cpp')
                    dst = os.path.join(self.src, self.name+'.cpp')
                else:
                    raise Exception(Fore.RED + "Unknown source type.")
                shutil.copyfile(src, dst)

    def set_platform(self):
        pattern = re.compile("^win", re.I)
        sys_result = pattern.match(sys.platform)
        if sys_result is not None:
            self.platform = "win"
        else:
            self.platform = "unix"

    def get_src_to_string(self):
        result = ''
        files = os.listdir(self.src)
        pattern = re.compile(rf'.+?\.{self.type}$')
        for file in files:
            if pattern.match(file):
                result += os.path.join(self.src, file) + ' '
        return result

    def build(self):
        if not os.path.exists(self.src) or not os.listdir(self.src):
            print(Fore.RED + "source code doesn't exists")
            return False

        src = self.get_src_to_string()
        dst = self.exec

        if not os.path.exists(self.out):
            os.makedirs(self.out, exist_ok=True)

        if self.type == "c":
            cmd = f"gcc {src} -o {dst}"
        elif self.type == "cpp":
            cmd = f"g++ {src} -o {dst}"
        else:
            print(Fore.RED + "Unknown source type.")
            return False
        try:
            subprocess.check_output(cmd, shell=True)
            return True
        except Exception as exc:
            print(Fore.RED + exc.output.decode('utf-8'))
            return False

    def run(self, _args=None, debug=False):
        if not os.path.exists(self.exec):
            raise Exception(Fore.RED + "You should build firstly.")
        else:
            cmd = []
            if debug:
                cmd.append('gdb')
            cmd.append(self.exec)
            if _args:
                cmd.extend(_args)
            elif type(self.args) is list:
                cmd.extend(self.args)
            subprocess.call(cmd)
            self.args = _args

    def delete(self):
        if os.path.exists(self.exec):
            os.remove(self.exec)
        if os.path.exists(self.out) and not os.listdir(self.out):
            os.rmdir(self.out)
        if os.path.exists(self.src):
            shutil.rmtree(self.src)

    @property
    def src(self):
        return self._src

    @src.setter
    def src(self, src):
        if not src:
            print(Fore.RED + 'src should be a not empty string')
        else:
            self._src = src
            if not self.name:
                self.name = os.path.basename(os.path.normpath(src))

    @property
    def out(self):
        return self._out

    @out.setter
    def out(self, out):
        if not out:
            self._out = os.path.join(self.src, 'debug')
        else:
            self._out = out
        self.exec = os.path.join(self.out, self.name)

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        if name:
            self._name = name
            self.exec = os.path.join(self.out, self.name)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='get_cc_test', description='quick build a project')
    parser.add_argument('src', help='source path')
    parser.add_argument('--name', default='', help='project name')
    parser.add_argument('--type', choices=['c', 'cpp'], default='c', help='project type')
    parser.add_argument('--out', default='', help='binary file path')
    parser.add_argument('--actions', nargs='+', choices=['build', 'run', 'debug', 'delete'], default=['build', 'run'], help='actions you can do')
    parser.add_argument('--args', nargs='+', default=None, help='arguments for project')

    args = parser.parse_args()
    P = Project(args.src, name=args.name, out=args.out, _type=args.type, _args=args.args)

    if 'delete' in args.actions:
        P.delete()
        exit(0)

    if 'build' in args.actions:
        if not P.build():
            exit(1)

    if 'run' in args.actions:
        P.run()
    elif 'debug' in args.actions:
        P.run(debug=True)
