% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
%                                                                     %
% The ENVE project                                                    %
%                                                                     %
% Copyright (c) 2020, Davide Stocco, Matteo Larcher and Enrico        %
% Bertolazzi.                                                         %
%                                                                     %
% The ENVE project and its components are supplied under the terms of %
% the open source BSD 2-Clause License. The contents of the ENVE      %
% project and its components may not be copied or disclosed except in %
% accordance with the terms of the BSD 2-Clause License.              %
%                                                                     %
% URL: https://opensource.org/licenses/BSD-2-Clause                   %
%                                                                     %
%    Davide Stocco                                                    %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: davide.stocco@unitn.it                                   %
%                                                                     %
%    Matteo Larcher                                                   %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: matteo.larcher@unitn.it                                  %
%                                                                     %
%    Enrico Bertolazzi                                                %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: enrico.bertolazzi@unitn.it                               %
%                                                                     %
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

% oldPath = getenv('PATH');
% newPath = strcat(oldPath, pathsep, 'path-to-cmake');
% setenv('PATH', newPath);
% ! cmake --version'

clc;
clear all;

build_utils    = false;
build_acme     = false;
build_enve     = false;
block_generate = true;

addpath('./include_sfun');
addpath('./src_sfun');

disp('----------------- ENVE SIMULATOR 1 S-FUNCTION ------------------');

%% Compile C++ libraries

Simulink.importExternalCTypes('./include_sfun/sfun_types.h');

if ismac
  dyn_ext = '.dylib';
elseif ispc
  dyn_ext = '.dll';
elseif isunix
  dyn_ext = '.so';
else
  disp('Platform not supported');
  return;
end

if build_utils
  disp('Building UTILS library...');
  cd ./../../submodules/acme/submodules/Utils
  if ismac
    ! rake clean
    ! rake build_osx
  elseif ispc
    ! rake clean
    ! rake build_windows
  elseif isunix
    ! rake clean
    ! rake build_linux
  end
  cd ./../../../../sfun/Simulator1
  disp('Done');
end

if build_acme
  disp('Building ACME library...');
  cd ./../../submodules/acme
  if ismac
    ! rake clean
    ! rake build_osx
  elseif ispc
    ! rake clean
    ! rake build_windows
  elseif isunix
    ! rake clean
    ! rake build_linux
  end
  cd ./../../sfun/Simulator1
  disp('Done');
end

if build_enve
  disp('Building ENVE library...');
  cd ./../..
  if ismac
    ! rake clean
    ! rake build_osx
  elseif ispc
    ! rake clean
    ! rake build_windows
  elseif isunix
    ! rake clean
    ! rake build_linux
  end
  cd ./sfun/Simulator1
  disp('Done');
end

%% ENVE S-Function interface

disp('Building S-FUNCTION...');

def = legacy_code('initialize');
def.SFunctionName    = 'ENVEsfun_Simulator1';
def.Options.language = 'C';

lib_dir = '/usr/local/lib';
if (~contains(getenv('LD_RUN_PATH'), lib_dir))
  setenv('LD_RUN_PATH', [getenv('LD_RUN_PATH') ':' lib_dir]);
end

def.IncPaths    = {'../../lib/include'};
def.HeaderFiles = {'sfun_types.h', 'sfun_interface.h'};

def.LibPaths = {lib_dir};
if ismac
  lib_name = ['../../lib/dll/libenve_osx', dyn_ext];
elseif ispc
  disp('Fill information!');
  return;
elseif isunix
  lib_name = [lib_dir, '/libenve_linux', dyn_ext];
else
  disp('Platform not supported');
  return;
end
def.HostLibFiles = {lib_name};

%% Functions interface

def.StartFcnSpec = [ 'void sfun_init(', ...
                     'double p1[1], ',  ... % Ribs number
                     'double p2[1], ',  ... % Shell radius on x axis (m)
                     'double p3[1], ',  ... % Shell curve degree for x axis
                     'double p4[1], ',  ... % Shell radius on y axis (m)
                     'double p5[1], ',  ... % Shell curve degree for y axis
                     'double p6[1], ',  ... % Shell half width on y axis (m)
                     'double p7[1], ',  ... % Flat ground surface height (m)
                     'double p8[1]) ',  ... % Flat ground surface friction scaling coefficient (-)
                   ];

def.OutputFcnSpec = [ 'void sfun_out(', ...
                      'shellsRF      u1[1], ',  ... % Input bus containing the shell reference frame
                      'groundContact y1[1], ',  ... % Output bus containing the contact point reference frame
                      'double        p9[1], ',  ... % method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
                      'double        p10[1]) ', ... % flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat
                    ];

def.TerminateFcnSpec = 'void sfun_end()';

%% Create MEX

disp('Building MATLAB mex...');
if isfile(lib_name)
  legacy_code('generate_for_sim',def);
  legacy_code('sfcn_cmex_generate', def);
  legacy_code('sfcn_tlc_generate', def);
  legacy_code('sfcn_makecfg_generate', def);
  legacy_code('compile', def, {} );
  if block_generate
      legacy_code('slblock_generate', def, def.SFunctionName);
  end
else
  disp('ENVE is not installed, cannot create MATLAB mex.');
end
disp('Done');

disp('----------------------------- DONE -----------------------------');
