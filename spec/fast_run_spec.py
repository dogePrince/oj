import mock
from expects import *
import sys
from fast_run import *

with description('comment mock') as self:
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
                    self.set_platform_mocker.asser_called_once()

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

            with description('Project.run'):
                with context('when binary file exists, not debug and '):
                    with it('should call three functions'):
                        with mock.patch('os.path.exists', return_value=True), \
                             mock.patch('subprocess.call') as call_mocker:

                            self.project.out = 'out'
                            self.project.src = 'src'
                            self.project.exec = 'exec'

                            self.project.delete()

                            remove_mocker.asser_called_once_with('exec')
                            rmdir_mocker.asser_called_once_with('out')
                            rmtree_mocker.asser_called_once_with('src')

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

                            remove_mocker.asser_called_once_with('exec')
                            rmdir_mocker.asser_called_once_with('out')
                            rmtree_mocker.asser_called_once_with('src')

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

                            remove_mocker.asser_not_called()
                            rmdir_mocker.asser_not_called()
                            rmtree_mocker.asser_not_called()

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
            with context('when argument is invalid'):
                with it('should do nothing'):
                    with mock.patch('fast_run.Project.out'):
                        self.project.exec = 'exec'
                        self.project._name = 'name'

                        self.project.name = ''

                        expect(self.project.name).to(equal('name'))
                        expect(self.project.exec).to(equal('exec'))

            with context('when argument is valid'):
                with it('should update values of name and exec'):
                    with mock.patch('fast_run.Project.out'):
                        self.project.out = 'out'
                        self.project.exec = 'exec'
                        self.project._name = 'name'

                        self.project.name = 'new_name'

                        expect(self.project.name).to(equal('new_name'))
                        expect(self.project.exec).to(equal(os.path.join('out', 'new_name')))
