# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# Path to the directory containing the C/C++ source files
cpp_source_dir = '../../src'

# Add the directory to the Python path so autodoc can find the source files
import os
import sys

sys.path.insert(0, os.path.abspath(cpp_source_dir))

# NOTE: You may want to change this to the path containing your breathe installation
sys.path.append("../ext/breathe")

# Configuration for autodoc to generate documentation from the C/C++ source files
autodoc_default_flags = ['members', 'undoc-members']



# -- Project information -----------------------------------------------------

project = 'CSE 160 - Introduction to Parallel Computing'
copyright = '2024, UCSD-CSE160'
author = 'UCSD-CSE160'

# The full version, including alpha/beta/rc tags
release = '0.0.1'


# -- General configuration ---------------------------------------------------
html_use_index=False

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.imgmath',
    'sphinx.ext.todo',
    'breathe'
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# -- Options for Breathe output ----------------------------------------------

# NOTE: Relative path might not work, try your system's absolute path
breathe_projects = {'CSE 160 - Introduction to Parallel Computing' : '../doxyxml' }

breathe_default_project = "CSE 160 - Introduction to Parallel Computing"
