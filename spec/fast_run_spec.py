import mock
from expects import *
import sys
from fast_run import *

with description('common mock') as self:
    with before.each:
        self.print_patcher = mock.patch('builtins.print')
        self.print_mocker = self.print_patcher.start()

    with after.each:
        self.print_patcher.stop()

    with description('Project.__init__'):
        with context('when make a instance of Project'):
            with it('should get a instance of Project'):
                with mock.patch('fast_run.Project.name'), \
                     mock.patch('fast_run.Project.src'), \
                     mock.patch('fast_run.Project.out'), \
                     mock.patch('fast_run.Project.set_platform') as self.set_platform_mocker:
                    p = Project('src/sub/', name='name', out='out', _args=[1, 2])

                    expect(p.exec).to(equal(None))
                    expect(p.platform).to(equal(None))
                    expect(p.src).to(equal('src/sub/'))
                    expect(p.name).to(equal('name'))
                    expect(p.type).to(equal('c'))
                    expect(p.type).to(equal('c'))
                    expect(p.out).to(equal('out'))
                    self.set_platform_mocker.assert_called_once()

    with description('functions in Project'):
        with before.each:
            self.init_patcher = mock.patch('fast_run.Project.__init__', return_value=None)
            self.init_patcher.start()
            self.project = Project()

        with after.each:
            self.init_patcher.stop()

        with description('functions of Project except properties'):
            with before.each:
                self.project_src_patcher = mock.patch('fast_run.Project.src')
                self.project_out_patcher = mock.patch('fast_run.Project.out')
                self.project_name_patcher = mock.patch('fast_run.Project.name')

                self.project_src_patcher.start()
                self.project_out_patcher.start()
                self.project_name_patcher.start()

            with after.each:
                self.project_src_patcher.stop()
                self.project_out_patcher.stop()
                self.project_name_patcher.stop()

            with description('Project.build'):
                with context('when src file not exists'):
                    with it('should raise an exception'):
                        with mock.patch('fast_run.Project.get_src_to_string', return_value=[]):

                            expect(self.project.build()).to(equal(None))
                            self.print_mocker.assert_called_once_with(Fore.RED + "source code doesn't exists")

                with context('when src file exists, type is c'):
                    with it('should build it successfully'):
                        with mock.patch('fast_run.Project.get_src_to_string', return_value='1.c 2.c'), \
                             mock.patch('os.path.exists', return_value=False), \
                             mock.patch('os.makedirs') as self.makedirs_mocker, \
                             mock.patch('subprocess.check_output') as self.check_output_mocker:
                            self.project.exec = 'exec'
                            self.project.out = 'out'
                            self.project.type = 'c'

                            expect(self.project.build()).to(equal('exec'))
                            self.makedirs_mocker.assert_called_once_with('out', exist_ok=True)
                            self.check_output_mocker.assert_called_once_with('gcc 1.c 2.c -o exec', shell=True)

                # with context('when src file exists, type is cpp, but build fail'):
                #     with it('should raise an exception'):
                #         with mock.patch('fast_run.Project.get_src_to_string', return_value='1.cpp 2.cpp'), \
                #              mock.patch('os.path.exists', return_value=True), \
                #              mock.patch('subprocess.check_output', side_effect=Exception(**{'output':'build fail.'})) as self.check_output_mocker:
                #
                #             self.project.exec = 'exec'
                #             self.project.out = 'out'
                #             self.project.type = 'cpp'
                #
                #             expect(self.project.build()).to(equal(None))
                #             self.check_output_mocker.assert_called_once_with('g++ 1.cpp 2.cpp -o exec', stderr=subprocess.STDOUT, shell=True)


            with description('Project.run'):
                with context('when binary file exists, not debug, args are given'):
                    with it('should run the binary file'):
                        with mock.patch('os.path.exists', return_value=True), \
                             mock.patch('subprocess.call') as call_mocker:

                            self.project.args = ['arg0']
                            self.project.exec = 'exec'

                            self.project.run(_args=['arg1', 'arg2'])

                            call_mocker.assert_called_once_with(['exec', 'arg1', 'arg2'])

                with context('when binary file exists, debug, args not given'):
                    with it('should call gdb to debug'):
                        with mock.patch('os.path.exists', return_value=True), \
                             mock.patch('subprocess.call') as call_mocker:

                            self.project.args = ['arg0']
                            self.project.exec = 'exec'

                            self.project.run(debug=True)

                            call_mocker.assert_called_once_with(['gdb', 'exec', 'arg0'])

                with context('when binary file not exists'):
                    with it('should raise an error'):
                        with mock.patch('os.path.exists', return_value=False), \
                             mock.patch('subprocess.call') as call_mocker:

                            self.project.exec = 'exec'

                            expect(lambda: self.project.run()).to(raise_error(Exception, Fore.RED + 'You should build firstly.'))

            with description('Project.delete'):
                with context('when triple True'):
                    with it('should call three functions'):
                        with mock.patch('os.path.exists', return_value=True), \
                             mock.patch('os.listdir', return_value=False), \
                             mock.patch('os.remove') as remove_mocker, \
                             mock.patch('os.rmdir') as rmdir_mocker, \
                             mock.patch('shutil.rmtree') as rmtree_mocker:

                            self.project.out = 'out'
                            self.project.src = 'src'
                            self.project.exec = 'exec'

                            self.project.delete()

                            remove_mocker.assert_called_once_with('exec')
                            rmdir_mocker.assert_called_once_with('out')
                            rmtree_mocker.assert_called_once_with('src')

                with context('when triple False'):
                    with it('should call nothing'):
                        with mock.patch('os.path.exists', return_value=False), \
                             mock.patch('os.listdir', return_value=False), \
                             mock.patch('os.remove') as remove_mocker, \
                             mock.patch('os.rmdir') as rmdir_mocker, \
                             mock.patch('shutil.rmtree') as rmtree_mocker:

                            self.project.out = 'out'
                            self.project.src = 'src'
                            self.project.exec = 'exec'

                            self.project.delete()

                            remove_mocker.assert_not_called()
                            rmdir_mocker.assert_not_called()
                            rmtree_mocker.assert_not_called()

        with description('Project.src'):
            with context('when argument invalid'):
                with it('should raise an error'):
                    self.project.src = None

                    self.print_mocker.assert_called_once_with(Fore.RED + 'src should be a not empty string')

            with context('when argument valid and name is empty'):
                with it('should update the name property'):
                    with mock.patch('fast_run.Project.name'):
                        self.project.name = ''

                        self.project.src = 'src/sub'

                        expect(self.project.src).to(equal('src/sub'))
                        expect(self.project.name).to(equal('sub'))

            with context('when argument valid and name is not empty'):
                with it('should not update the name property'):
                    with mock.patch('fast_run.Project.name'):
                        self.project.name = 'name'

                        self.project.src = 'src/sub'

                        expect(self.project.src).to(equal('src/sub'))
                        expect(self.project.name).to(equal('name'))

        with description('Project.out'):
            with context('when argument is invalid'):
                with it('should generate a default value to out'):
                    with mock.patch('fast_run.Project.name'), \
                         mock.patch('fast_run.Project.src'):
                        self.project.name = 'name'
                        self.project.src = 'src'

                        self.project.out = None

                        expect(self.project.out).to(equal(os.path.join('src', 'debug')))
                        expect(self.project.exec).to(equal(os.path.join('src', 'debug', 'name')))

            with context('when argument is valid'):
                with it('should generate a default value to out'):
                    with mock.patch('fast_run.Project.name'), \
                         mock.patch('fast_run.Project.src'):
                        self.project.name = 'name'

                        self.project.out = 'out'

                        expect(self.project.out).to(equal('out'))
                        expect(self.project.exec).to(equal(os.path.join('out', 'name')))

        with description('Project.name'):
            with context('when eval a value to name'):
                with it('should update values of name and exec'):
                    with mock.patch('fast_run.Project.out'):
                        self.project.out = 'out'
                        self.project.exec = 'exec'
                        self.project._name = 'name'

                        self.project.name = 'new_name'

                        expect(self.project.name).to(equal('new_name'))
                        expect(self.project.exec).to(equal(os.path.join('out', 'new_name')))
