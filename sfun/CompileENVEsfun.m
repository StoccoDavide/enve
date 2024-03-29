% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
%                                                                     %
% This file is part of the ENVE project.                              %
%                                                                     %
% Copyright (c) 2020, Davide Stocco, Matteo Larcher and Enrico        %
% Bertolazzi.                                                         %
%                                                                     %
% The ENVE project and its components are supplied under the terms of %
% the open source BSD 3-Clause License. The contents of the ENVE      %
% project and its components may not be copied or disclosed except in %
% accordance with the terms of the BSD 3-Clause License.              %
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
% newPath = strcat(oldPath, pathsep, '/usr/local/bin');
% setenv('PATH', newPath);
% ! cmake --version

clc;
clear all;

build_submodules = false;
build_enve       = false;
block_generate   = true;

addpath('./include_sfun');
addpath('./src_sfun');

disp('----------------- ENVE SIMULATOR S-FUNCTION ------------------');

%% Compile C++ libraries

Simulink.importExternalCTypes('./include_sfun/enve_sfun_types.h');

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

if build_submodules
  disp('Building SUBMODULES...');
  cd ./..
  ! rake build_submodules
  cd ./sfun
  disp('Done');
end

if build_enve
  cd ./..
  ! rake
  cd ./sfun
  disp('Done');
end

%% ENVE S-Function interface

disp('Building S-FUNCTION...');

def = legacy_code('initialize');
def.SFunctionName    = 'ENVEsfun';
def.Options.language = 'C';

lib_dir = '/usr/local/lib';
if (~contains(getenv('LD_RUN_PATH'), lib_dir))
  setenv('LD_RUN_PATH', [getenv('LD_RUN_PATH') ':' lib_dir]);
end

def.IncPaths    = {'../lib/include'};
def.HeaderFiles = {'enve_sfun_types.h', 'enve_sfun_interface.h'};

def.LibPaths = {lib_dir};
if ismac
  lib_name = ['../lib/dll/libenve_osx', dyn_ext];
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

def.StartFcnSpec = [ ...
  'void enve_sfun_init(', ...
  'EnveRealPar p1[1], ',  ... % Ribs number (-)
  'EnveRealPar p2[1], ', ... % Shell radius on x-axis (m)
  'EnveRealPar p3[1], ', ... % Shell curve degree for x-axis (-)
  'EnveRealPar p4[1], ', ... % Shell radius on y-axis (m)
  'EnveRealPar p5[1], ', ... % Shell curve degree for y-axis (-)
  'EnveRealPar p6[1], ', ... % Surface half width on y-axis (m)
  'EnveRealPar p7[1], ',  ... % Flat ground surface height (m)
  'EnveRealPar p8[1]) ',  ... % Flat ground surface friction scaling coefficient (-)
  ];

def.OutputFcnSpec = [ ...
  'void enve_sfun_out(', ...
  'EnveInputBus  u1[1], ', ... % Input bus containing the shell hub affine transformation matrix
  'EnveOutputBus y1[1], ', ... % Output bus containing the contact data
  'EnveRealPar   p9[1], ', ... % method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
  'EnveRealPar   p10[1]) ', ... % flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat
  ];

def.TerminateFcnSpec = [...
  'void enve_sfun_end()' ...
  ];

%% Create MEX

disp('Building MATLAB mex...');
if isfile(lib_name)
  legacy_code('generate_for_sim',def);
  legacy_code('sfcn_cmex_generate', def);
  legacy_code('sfcn_tlc_generate', def);
  legacy_code('sfcn_makecfg_generate', def);
  if block_generate
      legacy_code('slblock_generate', def, def.SFunctionName);
  end
else
  disp('ENVE is not installed, cannot create MATLAB mex.');
end
disp('Done');

disp('----------------------------- DONE -----------------------------');
