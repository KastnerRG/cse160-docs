# Documentation for cse160-opencl

This folder contains the documentation for the "cse160-opencl" project. The documentation is written using reStructuredText (RST) format and is built using Sphinx.

## Getting Started

Follow these steps to create the documentation for cse160-opencl:

### Prerequisites

Make sure you have the following software installed:

- Python: Sphinx requires Python to be installed on your system. You can download Python from the [official website](https://www.python.org/downloads/).

### Installation

1. Clone the repository to your local machine:

    ```bash
    git clone git@github.com:KastnerRG/cse160-docs.git
    ```

2. Navigate to the `docs` directory:

    ```bash
    cd cse160-docs/docs
    ```

3. Install Sphinx and any necessary dependencies using pip:

    ```bash
    pip install sphinx
    ```

### Writing Documentation

1. Write your documentation using reStructuredText (RST) format. You can create new RST files or modify existing ones in this directory.

2. Follow the [Sphinx documentation](https://www.sphinx-doc.org/en/master/) for guidance on structuring your documentation, adding content, and using features like cross-references, code blocks, and images.

### Building Documentation

1. Once you've written or modified the documentation, you can build it using Sphinx.

2. From the `docs` directory, run the following command:

    ```bash
    make html
    ```

3. Sphinx will generate HTML files for your documentation in the `build/html` directory.

### Viewing Documentation

You can view the generated HTML documentation by opening the corresponding HTML files in a web browser. Alternatively, you can serve the documentation locally using a web server.

The latest documentation is being hosted [here](https://docs-cse160.readthedocs.io/en/latest/)

### Helpful Comments for Breate & Doxygen

- Documentation root path: root/docs
- Breathe Path: root/ext/breathe
- Doxygen XML Output: root/doxyxml

### Setting up Doxygen

- You might want to change the absolute paths in `docs/source/conf.py` and `docs/doxygen/Doxyfile`. You just need to change the prefix path from the given sample path.

- If you want doxygen to consider private class members as well, search for the `EXTRACT_PRIVATE` field in the Doxyfile and switch it to `YES`.
