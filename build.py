import sys
import os
import shutil
import subprocess
import platform

def compile(build_dir, target_dir, option, license_js, effekseer_core_js, effekseer_src_js, effekseer_js):
    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    os.chdir(build_dir)

    if platform.system() == 'Windows':
        subprocess.check_call(['cmd', '/c', 'emcmake cmake {0} {1}'.format(option, target_dir)])
        subprocess.check_call(['ninja'])
    else:
        subprocess.check_call(['sh', '-c', 'emcmake cmake {0} {1}'.format(option, target_dir)])
        subprocess.check_call(['ninja'])

    outfile_js = open(effekseer_js, 'w')

    with open(license_js) as infile:
        data = infile.read()
        outfile_js.write(data)

    with open(effekseer_core_js) as infile:
        data = infile.read()
        outfile_js.write(data)

    with open(effekseer_src_js) as infile:
        data = infile.read()
        outfile_js.write(data)

    os.chdir('../')

compile('build_wasm',
    '../src/',
    '-G Ninja',
    license_js = os.path.join('..', 'src', 'js', 'license.js'),
    effekseer_core_js = os.path.join('.', 'effekseer.core.js'),
    effekseer_src_js = os.path.join('..', 'src', 'js', 'effekseer.src.js'),
    effekseer_js = os.path.join('..', 'Release', 'effekseer.js'))

shutil.copy('build_wasm/effekseer.core.wasm', 'Release/effekseer.wasm')