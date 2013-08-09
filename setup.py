#! coding: utf-8
from setuptools import find_packages
from setuptools import setup


setup(
    name = 'DAMIS',
    version = '0.1',
    url = 'http://damis.lt',
    license = 'aGPL',
    description = 'Data Analysis and Mining Infrastructure for Scientists',
    maintainer = u'Informatikos mokslų centras',
    maintainer_email = 'info@InScience.lt',
    packages=find_packages('src'),
    package_dir={'': 'src'},
    install_requires=[]
)
