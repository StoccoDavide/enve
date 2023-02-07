The Library
===========

**What is ENVE?**

The ENVE library is a free software written in C++ (standard C++11) under the
BSD 3-clause license. Its main purpose is to describe through very simple
geometric entities ground surfaces and tires (modeled as rigid shells), and to
analyze the contact between them. More specifically, the surface (which can
represent a road or a generic terrain) is described as a triangular mesh, while
the tire is representesd through a series of stacked disks (also called ribs).
The intersection of the geometric entities that make up the road and tire allows
us to analyze the shape of the road surface near the contact interface.

**What does ENVE mean?**

ENVE is an abbreviation (more or less fanciful) of ENveloping method for wheeled
VEhicles.

**What does ENVE do?**

ENVE is software specifically developed to locally evaluate the contact between
a triangular surface and a series of stacked disks (called ribs). It is
specifically designed to serve the automotive field simulation.

**How fast is ENVE?**

ENVE can work with a Real-Time Factor (RTF) bigger than 20 (average result
calculated on a mesh with 25k+ triangles, tire consisting of 10 ribs, refresh
rate of 1kHz and based on 28k samples [3]).

**Can I use ENVE on MATLAB environment?**

Yes. ENVE is provided with both a MATLAB MEX wrapper and a SIMULINK S-Function.

**Need more information?**

Write to one of the authors, we will be happy to answer all your questions!


Third Party Libraries
---------------------

We rely on the migthy `Eigen3 <https://eigen.tuxfamily.org>`__ linear algebra
template library, and on the `ACME <https://github.com/StoccoDavide/acme>`__
3D geometry library.


Maintenance and Compatibility
-----------------------------

Library has been tested on Linux, MacOS and Windows.
If you have questions regarding the library or you want to report a bug,
please open an `issue <https://github.com/StoccoDavide/enve/issues/new>`__
at GitHub. If your request would contain confidential information, please send
us an email.

References
----------

1.  *Davide Stocco*,
    **Real-Time Computation of Tire/Road Contact using Tailored Algorithms**,
    2020, Master Thesis (*in Italian*),
    `PDF <https://github.com/StoccoDavide/MasterThesis/blob/master/thesis.pdf>`__.

2.  *Davide Stocco and Enerico Bertolazzi*,
    **Acme: A small 3D geometry library**,
    SoftwareX 16 (2021): 100845,
    DOI `10.1016/j.softx.2021.100845 <https://doi.org/10.1016/j.softx.2021.100845>`__.

3.  *Davide Stocco, Matteo Larcher and Enerico Bertolazzi*,
    **A Novel Approach for Real-Time Tire/Ground Contact Modeling**,
    Journal XX (202X): XX,
    DOI `XXX <https://doi.org/XXX>`__.
