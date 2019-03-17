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


class Project:
    # src: root path of project
    # debug: debug path
    # type: project type
    # args: args for run project
    # cases: paths of test cases
    def __init__(self, src, debug='', _type='cpp', _args=[], cases=None):
        self.name = None
        self.exec = None
        self.platform = None
        self.set_platform()

        self.type = _type
        self.args = _args
        self.src = src
        self.debug = debug
        self.cases = cases

    # create project if it not exists
    def create(self):
        if not os.path.exists(self.src):
            # create project folder
            os.makedirs(self.src, exist_ok=True)

            # copy template file to project folder
            project_file = os.path.join(self.src, self.name + '.' + self.type)
            template_file = os.path.join("templates", "template." + self.type)
            if not os.path.exists(template_file):
                raise Exception(Fore.RED + "Unknown source type.")
            shutil.copyfile(template_file, project_file)

            # create cases folder
            case_dir = os.path.join(self.src, "cases")
            os.makedirs(case_dir, exist_ok=True)
            with open(os.path.join(case_dir, "case1"), 'w'): pass

            # create debug folder
            os.makedirs(self.debug, exist_ok=True)

    # delete project
    def delete(self):
        if os.path.exists(self.debug):
            shutil.rmtree(self.debug)
        if os.path.exists(self.src):
            shutil.rmtree(self.src)

    # set platform
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

    def read_case(self):
        if self.cases is None:
            return None

        file_set = []
        for path in self.cases:
            if os.path.isfile(path):
                file_set.append(path)
            if os.path.isdir(path):
                for root, dirs, files in os.walk(path, topdown=False):
                    for file in files:
                        file_set.append(os.path.join(root, file))

        return file_set

    def build(self):
        src = self.get_src_to_string()
        if not src:
            raise Exception(Fore.RED + "source code doesn't exists")

        if not os.path.exists(self.debug):
            os.makedirs(self.debug, exist_ok=True)

        # build project
        if self.type == "c":
            cmd = f"gcc {src} -o {self.exec}"
        elif self.type == "cpp":
            cmd = f"g++ {src} -o {self.exec}"
        else:
            raise Exception(Fore.RED + "Unknown source type.")
        try:
            subprocess.check_output(cmd, shell=True)
        except Exception as exc:
            print(exc.output.decode('utf-8'))
            raise Exception('Build Error!')

    def run(self, debug=False):
        if not os.path.exists(self.exec):
            raise Exception(Fore.RED + 'You should build firstly.')

        cmd = [self.exec]
        cmd.extend(self.args)

        case_set = self.read_case()
        if not case_set:
            subprocess.call(cmd)
            return

        total_count = 0
        passed_count = 0
        failed_count = 0
        other_count = 0
        for case in case_set:
            total_count += 1
            print(Fore.GREEN + f'case {total_count}:')
            print(f'path: {case}')

            file_name = os.path.basename(os.path.normpath(case))
            out_file_name = os.path.join(self.src, 'debug', f'{file_name}_out.txt')

            start_time = datetime.datetime.utcnow()
            with open(case, 'r') as file_in, \
                 open(out_file_name, 'w') as file_out:
                p = Popen(cmd, stdout=file_out, stdin=file_in, stderr=sys.stderr, encoding='utf8')
                file_out.flush()
            p.wait()
            p.kill()
            end_time = datetime.datetime.utcnow()

            print(Fore.CYAN + f'start:\t{start_time}\nend:\t{end_time}\nduring:\t{(end_time-start_time).total_seconds()}\n')
            compare_result = self.compare(case, out_file_name)
            if compare_result == 'passed':
                print('status: ' + Fore.GREEN + 'passed\n')
                passed_count += 1
            elif compare_result == 'failed':
                print('status: ' + Fore.RED + 'failed\n')
                failed_count += 1
            else:
                other_count +=1
        print(Fore.MAGENTA + f'total:  {total_count}\npassed: {passed_count}\nfailed: {failed_count}\nother:  {other_count}')

    def compare(self, case, output):
        with open(case, 'r') as case_file, \
             open(output, 'r') as output_file:
            splitor = '#'*6
            content1 = case_file.read()
            if splitor in content1:
                content1 = content1.split('#'*6)[1].strip()
                content2 = output_file.read().strip()
                if content1 == content2:
                    return 'passed'
                else:
                    return 'failed'
            else:
                return 'noExpect'

    @property
    def src(self):
        return self._src

    @src.setter
    def src(self, src):
        if not src:
            print(Fore.RED + 'src should be a not empty string')
        else:
            self._src = src
            self.name = os.path.basename(os.path.normpath(src))

    @property
    def debug(self):
        return self._debug

    @debug.setter
    def debug(self, debug):
        if not debug:
            self._debug = os.path.join(self.src, 'debug')
        else:
            self._debug = debug
        self.exec = os.path.join(self.debug, self.name)
        if self.platform == 'win':
            self.exec += '.exe'

    @property
    def cases(self):
        return self._cases

    @cases.setter
    def cases(self, cases):
        if cases is None:
            self._cases = None
        elif cases == []:
            self._cases = [os.path.join(self.src, 'cases')]
        else:
            self._cases = cases

if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='get_cc_test', description='quick build a project')
    parser.add_argument('src', help='source path')
    parser.add_argument('--type', choices=['c', 'cpp'], default='cpp', help='project type')
    parser.add_argument('--out', default='', help='folder for output file')

    parser.add_argument('--build', action='store_true', help='build project')
    parser.add_argument('--run', nargs='*', default=None, help='run project (support run with args)')
    parser.add_argument('--debug', action='store_true', help='debug project')
    parser.add_argument('--delete', action='store_true', help='delete project')
    parser.add_argument('--create', action='store_true', help='create a project')

    parser.add_argument('--cases', nargs='*', default=None, help='paths of cases')

    args = parser.parse_args()

    P = Project(args.src, debug=args.out, _type=args.type, _args=args.run, cases=args.cases)

    if not (args.build or args.run is not None or args.debug or args.delete or args.create):
        P.args = []
        P.build()
        P.run()
    else:
        if args.build and not (args.delete or args.create):
            P.build()
        if args.run is not None and not (args.debug or args.delete or args.create):
            P.run()
        elif args.debug and not (args.run is not None or args.delete or args.create):
            P.run(debug=True)
        elif args.delete and not (args.run is not None or args.debug or args.create):
            P.delete()
        elif args.create and not (args.run is not None or args.debug or args.delete):
            P.create()
