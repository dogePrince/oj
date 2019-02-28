import sys
import os
import subprocess
import re
import shutil
import argparse
import datetime
from colorama import init, Fore, Back, Style
from subprocess import Popen, PIPE, STDOUT
init(autoreset=True)

def read_case(paths):
    if paths is None:
        return None

    file_set = []
    for path in paths:
        if os.path.isfile(path):
            file_set.append(path)
        if os.path.isdir(path):
            for root, dirs, files in os.walk(path, topdown=False):
                for file in files:
                    file_set.append(os.path.join(root, file))

    return file_set


class Project:
    def __init__(self, src, name='', out='', _type='cpp', _args=[], _input=None):
        self._out = ''

        self.name = name
        self.exec = None
        self.platform = None
        self.type = _type
        self.args = _args

        self.src = src
        self.out = out
        self.input = _input

        self.set_platform()

    def create(self):
        if not os.path.exists(self.src):
            os.makedirs(self.src, exist_ok=True)
            main_file = os.path.join(self.src, self.name)
            if not os.path.exists(main_file):
                if self.type == 'c':
                    src = os.path.normpath('templates/temp.c')
                    dst = os.path.join(self.src, self.name+'.c')
                elif self.type == 'cpp':
                    src = os.path.normpath('templates/temp.cpp')
                    dst = os.path.join(self.src, self.name+'.cpp')
                else:
                    raise Exception(Fore.RED + "Unknown source type.")
                shutil.copyfile(src, dst)

            case_dir = f'{self.src}/cases'
            os.makedirs(case_dir, exist_ok=True)
            with open(f'{case_dir}/case1.txt', 'w'): pass

            os.makedirs(f'{self.src}/output', exist_ok=True)


    def set_platform(self):
        pattern = re.compile("^win", re.I)
        sys_result = pattern.match(sys.platform)
        if sys_result is not None:
            self.platform = "win"
        else:
            self.platform = "unix"

    def get_src_to_string(self):
        result = ''
        if os.path.exists(self.src):
            files = os.listdir(self.src)
            pattern = re.compile(rf'.+?\.{self.type}$')
            for file in files:
                if pattern.match(file):
                    result += os.path.join(self.src, file) + ' '
            return result
        else:
            raise Exception('source path not exists.')

    def build(self):
        src = self.get_src_to_string()

        if not src:
            print(Fore.RED + "source code doesn't exists")
            return None

        if not os.path.exists(self.out):
            os.makedirs(self.out, exist_ok=True)

        if self.type == "c":
            cmd = f"gcc {src} -o {self.exec}"
        elif self.type == "cpp":
            cmd = f"g++ {src} -o {self.exec}"
        else:
            print(Fore.RED + "Unknown source type.")
            return None
        try:
            subprocess.check_output(cmd, shell=True)
            return self.exec
        except Exception as exc:
            print(exc.output.decode('utf-8'))
            return None

    def run(self, debug=False):
        if not os.path.exists(self.exec):
            raise Exception(Fore.RED + 'You should build firstly.')
        else:
            cmd = []
            if debug:
                cmd.append('gdb')
            cmd.append(self.exec)
            cmd.extend(self.args)

            case_set = read_case(self.input)

            if case_set and not debug:
                count = 0
                for case in case_set:
                    count += 1
                    file_name = os.path.basename(os.path.normpath(case))
                    print(Fore.GREEN + f'case {count}: ({file_name})')
                    # print(case.strip())
                    t1 = datetime.datetime.utcnow()

                    with open(case, 'r') as file_in, \
                         open(os.path.join(self.src, f'output/{file_name}_out.txt'), 'w') as file_out:
                        p = Popen(cmd, stdout=file_out, stdin=file_in, stderr=sys.stderr, encoding='utf8')

                        file_out.flush()

                    p.wait()
                    p.kill()

                    # print(Fore.MAGENTA + 'result:')
                    # print(out)
                    t2 = datetime.datetime.utcnow()
                    print(Fore.CYAN + f'start:\t{t1}\nend:\t{t2}\nduring:\t{(t2-t1).total_seconds()}\n')
            else:
                subprocess.call(cmd)

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
    def input(self):
        return self._input

    @input.setter
    def input(self, input):
        if input is None:
            self._input = None
        elif input == []:
            self._input = [os.path.join(self.src, 'cases')]
        else:
            self._input = input

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        self._name = name
        self.exec = os.path.join(self.out, self.name)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='get_cc_test', description='quick build a project')
    parser.add_argument('src', help='source path')
    parser.add_argument('--name', default='', help='project name')
    parser.add_argument('--type', choices=['c', 'cpp'], default='cpp', help='project type')
    parser.add_argument('--out', default='', help='binary file path')

    parser.add_argument('--build', action='store_true', help='build project')
    parser.add_argument('--run', nargs='*', default=None, help='run project')
    parser.add_argument('--debug', action='store_true', help='debug project')
    parser.add_argument('--delete', action='store_true', help='delete project')
    parser.add_argument('--create', action='store_true', help='create a project')

    parser.add_argument('--input', nargs='*', default=None, help='path of input file')

    args = parser.parse_args()

    P = Project(args.src, name=args.name, out=args.out, _type=args.type, _args=args.run, _input=args.input)

    if not (args.build or args.run is not None or args.debug or args.delete or args.create):
        P.args = []
        P.build()
        P.run()
    else:
        if args.build:
            if args.delete or args.create:
                exit(1)
            P.build()
        if args.run is not None and not (args.debug or args.delete or args.create):
            P.run()
        elif args.debug and not (args.run is not None or args.delete or args.create):
            P.run(debug=True)
        elif args.delete and not (args.run is not None or args.debug or args.create):
            P.delete()
        elif args.create and not (args.run is not None or args.debug or args.delete):
            P.create()
