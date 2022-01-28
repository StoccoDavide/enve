.. rst-class:: emphasize-children

.. rst-class:: html-toggle

..
  ****
  ENVE
  ****

====================================================
A library for real-time tire/road contact evaluation
====================================================

`Github repository <https://github.com/StoccoDavide/enve>`__

Installation
------------

MATLAB
~~~~~~

Download the toolbox and install as usual. Run ``CompileENVElib`` on MATLAB Command Window to
compile the ``MEX`` of the library.

C++
~~~

Download the library

.. code:: sh

   git clone git@github.com:StoccoDavide/enve.git —recurse-submodules

if you forget ``—recurse-submodules`` you must load the submdules `ACME <https://github.com/StoccoDavide/acme>`__
and `Utils <https://github.com/ebertolazzi/Utils>`__ next.
To compile the library you can use ``cmake``

.. code:: sh

   mkdir build
   cd build
   cmake ..
   make

or ``rake``

.. code:: sh

   rake build       # on MacOS/Linux/Windows
   rake build_osx   # on Mac
   rake build_linux # on Linux
   rake build_win   # on Windows

using ``rake`` you have the library and headers in the following tree

.. code:: text

   `-- lib
       |-- include
       |   |-- enve_flat.hh
       |   |-- enve_hyperellipse.hh
       |   |-- enve_mesh.hh
       |   |-- enve_points.hh
       |   |-- enve_polynom.hh
       |   |-- enve_rib.hh
       |   |-- enve_shape.hh
       |   |-- enve_shell.hh
       |   |-- enve_triangleground.hh
       |   `-- enve.hh
       |-- lib
       |   `-- libenve_OSTYPE_static.a
       `-- dll
           `-- libenve_OSTYPE.dylib

where OSTYPE can be ``linux``, ``osx``, ``mingw_x64``, ``win_x64``

Index
-----

.. toctree::
   :maxdepth: 2

   intro.rst   
   examples.rst   
   api-cpp/root.rst
   api-matlab/root.rst


Authors C++/MATLAB MEX
----------------------

- | **Davide Stocco**
  | Department of Industrial Engineering
  | University of Trento
  | davide.stocco@unitn.it

- | **Enrico Bertolazzi**
  | Department of Industrial Engineering
  | University of Trento
  | enrico.bertolazzi@unitn.it

Authors SIMULINK S-Function
---------------------------

- | **Matteo Larcher**
  | Department of Industrial Engineering
  | University of Trento
  | matteo.larcher@unitn.it

- | **Davide Stocco**
  | Department of Industrial Engineering
  | University of Trento
  | davide.stocco@unitn.it

License
-------

.. literalinclude:: ../../LICENSE.txt
   :language: none