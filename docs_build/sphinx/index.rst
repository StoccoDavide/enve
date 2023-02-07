.. rst-class:: emphasize-children

.. rst-class:: html-toggle

==============================================
Real-Time Tire/Road Contact Evaluation Library
==============================================


.. image:: https://img.shields.io/badge/Github-enve-D95319.svg
  :target: https://github.com/stoccodavide/enve

.. image:: https://img.shields.io/badge/Version-4.0.0-D95319.svg
  :target: https://github.com/stoccodavide/enve

.. image:: https://img.shields.io/badge/Release-4.0.0-D95319.svg
  :target: https://github.com/stoccodavide/enve

.. image:: https://img.shields.io/badge/License-BSD3-D95319.svg
  :target: https://opensource.org/licenses/BSD-3-Clause


ENVE is a library for real-time tire/road contact evaluation. It is written in
C++11 with a MATLAB MEX interface and a SIMULINK S-Function interface. The
library is designed to be used in real-time applications, such as vehicle
dynamics simulation and control. The library is based on the ACME library, which
is a C++11 library for simple 3D geometry processing.

Installation
------------

C++
~~~

Download the library using git:

.. code:: sh

   git clone git@github.com:StoccoDavide/enve.git —recurse-submodules

Notice that if you forget ``—recurse-submodules`` you must download the submdule
`ACME <https://github.com/StoccoDavide/acme>`__ next. To compile the library you
can use ``cmake``:

.. code:: sh

   mkdir build
   cd build
   cmake ..
   make

or ``rake``:

.. code:: sh

   rake build_submodules
   rake build # or simply 'rake'

The compiled library and headers are stores as follows:

.. code:: text

   `-- lib
       |-- include
       |   |-- enve.hh
       |   |-- enve_sfun_interface.hh
       |   |-- enve_sfun_types.hh
       |   `-- enve
       |       |-- flat.hxx
       |       |-- mesh.hxx
       |       |-- output.hxx
       |       |-- rib.hxx
       |       |-- shape.hxx
       |       |-- shell.hxx
       |       `-- triangleground.hxx
       |-- lib
       |   `-- libenve_OSTYPE_static.a
       `-- dll
           `-- libenve_OSTYPE.dylib

where OSTYPE can be ``linux``, ``osx``, ``mingw_x64``, ``win_x64`` depending
on your OS.

MATLAB MEX
~~~~~~~~~~

Download the toolbox and install the toobox as usual. Run ``CompileENVElib_CMake``
on MATLAB Command Window to compile the MATLAB MEX library with ``cmake``.

SIMULINK S-Function
~~~~~~~~~~~~~~~~~~~

Compile the C++ library as explained above. Then, run ``CompileENVEsfun`` on
MATLAB Command Window to compile the SIMULINK S-Function.

Index
-----

.. toctree::
   :maxdepth: 2

   Manual_Introduction.rst
   Manual_Usage.rst
   api-cpp/root.rst
   api-matlab/root.rst


Authors C++/MATLAB MEX
----------------------

| **Davide Stocco**
| Department of Industrial Engineering
| University of Trento
| davide.stocco@unitn.it

| **Enrico Bertolazzi**
| Department of Industrial Engineering
| University of Trento
| enrico.bertolazzi@unitn.it

Authors SIMULINK S-Function
---------------------------

| **Matteo Larcher**
| Department of Industrial Engineering
| University of Trento
| matteo.larcher@unitn.it

| **Davide Stocco**
| Department of Industrial Engineering
| University of Trento
| davide.stocco@unitn.it

License
-------

.. literalinclude:: ../LICENSE.txt
   :language: none