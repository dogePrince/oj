import sys
import os
import subprocess
import re
from colorama import init, Fore, Back, Style

# def get_platform():
#     platform = sys.platform
#     pattern = re.compile("^win", re.I)
#     sys_result = pattern.match("win32")
#     if sys_result is not None:
#         return "win"
#     else:
#         return "unix"

class QuickRun():
    valid_settings = {  # config_name: is_a_value_required
                   "-debug": False,
                   "-o": True,
                   "-compare": False
               }

    parent = None
    project = None
    type = None
    exec = None
    setting = {}
    cmd_args = []

    def __init__(self, parent, project, *args=None, *settings=None):
        self.parent = parent
        self.project = project  # user specify a project name
        if "." in project:
            self.project = project.split(".")[0]
            self.type = project.split(".")[1]
        else:
            self.project = project
            self.type = "c"

        if args is not None:
            self.cmd_args = args
        if args is not None:
            self.setting = settings

    def build(self, *settings=None):
        if settings is None:
            settings = self.settings
        debug_path = setting.get["-o"]
        if debug_path is None:
            debug_path = "debug"  # path where gcc(g++) output

        if not os.path.exists(debug_path):
            os.mkdir(debug_path)

        src = os.path.join(self.parent, self.project, f"{self.project}.{self.type}")
        out = os.path.join(debug_path, self.project)

        if self.type == "c":
            cmd = f"gcc {src} -o {out}"
        else if self.type == "cpp":
            cmd = f"g++ {src} -o {out}_cpp"
        else:
            raise Fore.RED + "Unknown source type."
        result = {}
        try:
            subprocess.check_output(cmd, shell=True)
            result["exec"] = out
            result["info"] = "build success!"
            self.exec = out
        except Exception as exc:
            result["info"] = exc.output.decode('utf-8')
        return result

    def run(self, args=None):
        if args is None:
            args = self.args
        if self.exec is None:
            raise Fore.RED + "You should build firstly."
        cmd = [self.exec]
        if args is not None:
            cmd.extend(args)
        subprocess.call(cmd)

    def debug(self, args=None):
        if args is None:
            args = self.args
        cmd = ["gdb", self.exec]
        if args != None:
            cmd.extend(args)
        subprocess.call(cmd)

    def fast_run(self, *args=None, *settings=None):
        if settings is None:
            settings = self.settings
        result = build(settings)
        exec = result.get("exec")
        if exec is not None:
            print(Fore.GREEN + result["info"])
            if not setting.get["-debug"]:
                run(exec, args=args)
            else:
                debug(exec, args=args)
        else:
            print(result["info"])


def read_setting(self, args):
    index = 0
    while index < len(args):
        required = self.valid_settings.get(args[index])
        if required is None:
            print(Fore.RED + f'Invalid config key "{args[index]}"')
            return 1
        else if required:
            if index+1 >= len(args):
                print(Fore.RED + f'You should give a value to key "{args[index]}"')
                return 1
            self.setting[args[index]] = args[index+1]
            index += 2
        else:
            self.setting[args[index]] = True
            index += 1
    print(Fore.GREEN + 'Conplete to read settings.')
    return 0

def fast_run(path, pro, args=None, to_debug=False):
    result = build(path, pro)
    exec = result.get("exec")
    if exec is not None:
        print(Fore.GREEN + result["info"])
        if not to_debug:
            run(exec, args=args)
        else:
            debug(exec, args=args)
    else:
        print(result["info"])

if __name__ == '__main__':
    init(autoreset=True)
    arg_len = len(sys.argv)
    if arg_len == 1:
        print(Fore.RED + "A project name is needed!")
        exit(1)
    path = sys.argv[0]
    project = sys.argv[1]  # user specify a project name
    parent = os.path.abspath(os.path.join(path, os.pardir))

    args = []
    setting = {}
    if arg_len > 2:
        index = 2
        while index < arg_len:
            if sys.argv[index].startswith("-"):
                break;
            else:
                args.append(sys.argv[index])
                index += 1
        while index in range(index, arg_len):
            if sys.argv[index] in valid_settings:



    fast_run(parent, project, args=args, to_debug=to_debug)
