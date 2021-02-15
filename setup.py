import os
import re
from setuptools import setup,Extension

setup(name='extend-cpython',
      version="0.0.1",
      description='extend-cpython',
      author="Neeky",
      author_email="neeky@live.com",
      maintainer='Neeky',
      maintainer_email='neeky@live.com',
      python_requires='>=3.6.*',
      ext_modules = [Extension('plugins/maths',["src/maths.cpp"])],
      classifiers=[
          'Development Status :: 4 - Beta',
          'Intended Audience :: Developers',
          'Operating System :: POSIX',
          'Operating System :: MacOS :: MacOS X',
          'Programming Language :: Python :: 3.6',
          'Programming Language :: Python :: 3.7',
          'Programming Language :: Python :: 3.8']
      )