# Собираем модули

from distutils.core import setup
from distutils.extension import Extension

setup(name='csvcalc', version='1.0',
      ext_modules=[Extension('csvcalc', ['pycsvcalc.c'])])