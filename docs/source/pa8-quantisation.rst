PA8 - Quantisation in Machine Learning
======================================

Assignment Details
^^^^^^^^^^^^^^^^^^

Quantisation is one of the project assignments that you can choose for PA8 as your final project assignment.
Please read the document carefully and fill in the required code sections. Your code needs to run in DSMLP or QIDK in order to receive points.

Quantisation
^^^^^^^^^^^^

Quantisation is the process of mapping a large set of values to a smaller discrete set of values.
In essence, it involves reducing the numerical precision of data while preserving its essential characteristics.
Quantisation is widely used in many fields. One notable example is in signal processing, where the infinite range of analog voltages are converted into discrete integer values.
For example, a common ADC (Analog-to-Digital Converter) converts from ±5V analog signal to a 16 bit digital integer representation.
This means all possible infinite values between :math:`+5.0` and :math:`-5.0V` are represented by integers between ``-32768`` and ``+32767`` (±2^15). This allows us store analog real world information in digital devices.

Quantisation in Machine Learning
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Quantisation in the context of Machine Learning is very similar to Quantisation in the case of DSP (Digital Signal Processing). In this case, the data's precision is reduced from one form to another.
For example, a common quantisation strategy is to represent ``FP32`` (32-bit Floating Point) numbers using ``INT16`` (16-bit Integer) numbers. Using this quantisation strategy, we can effectively reduce the computation and storage costs by a factor of 2x.
