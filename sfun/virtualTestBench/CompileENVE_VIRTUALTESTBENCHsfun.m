% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
%                                                                     %
% The ENVE project                                                    %
%                                                                     %
% Copyright (c) 2020-2021, Matteo Larcher, Davide Stocco and          %
% Enrico Bertolazzi.                                                  %
%                                                                     %
% The ENVE project and its components are supplied under the terms of %
% the open source BSD 2-Clause License. The contents of the ENVE      %
% project and its components may not be copied or disclosed except in %
% accordance with the terms of the BSD 2-Clause License.              %
%                                                                     %
% URL: https://opensource.org/licenses/BSD-2-Clause                   %
%                                                                     %
%    Matteo Larcher                                                   %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: matteo.larcher@unitn.it                                  %
%                                                                     %
%    Davide Stocco                                                    %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: davide.stocco@unitn.it                                   %
%                                                                     %
%    Enrico Bertolazzi                                                %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: enrico.bertolazzi@unitn.it                               %
%                                                                     %
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

clc;
clear all;

addpath('./include_sfun');
addpath('./src_sfun');

%% ENVE sFunction interface

disp('------------------ VIRTUAL TEST BENCH SFUN -------------------');

Simulink.importExternalCTypes('./include_sfun/sfun_types.h');

if isunix && ~ismac
    dyn_ext = '.so';
elseif ismac
    dyn_ext = '.dylib';
else
    disp('Platform not supported');
    return;
end

def = legacy_code('initialize');

def.SFunctionName    = 'sfun_ENVE_VIRTUALTESTBENCH';
def.Options.language = 'C++';

def.IncPaths    = {'./include_sfun', './../src'};
def.SrcPaths    = {'./src_sfun', './../src'};
def.HeaderFiles = {'sfun_types.h', 'sfun_interface.h', 'sfun_shellVehicle.hh'};
def.SourceFiles = {'sfun_interface.cc', 'sfun_shellVehicle.cc'};

def.LibPaths = {'./../../lib/dll'};
lib_name = ['./../../lib/dll/libenve_osx', dyn_ext];
def.HostLibFiles = { lib_name };

%% Functions interface

def.StartFcnSpec = [ 'void sfun_init(', ...
                     'double p1[1], ',  ... % Shell radius on x axis (m) 
                     'double p2[1], ',  ... % Shell curve degree for x axis 
                     'double p3[1], ',  ... % Shell radius on y axis (m) 
                     'double p4[1], ',  ... % Shell curve degree for y axis 
                     'double p5[1], ',  ... % Surface half width on y axis (m) 
                     'double p6[1], ',  ... % Ribs number 
                     'double p7[1])',   ... % Threshold number for setup
                   ];

def.OutputFcnSpec = [ 'void sfun_out(', ...
                      'shellRF       u1[1], ', ... % Input bus containing the shell reference frame
                      'groundContact y1[1], ', ... % Output bus containing the contact point reference frame
                      'double        p8[1], ', ... % flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat
                      'double        p9[1])',  ... % Simulation time step (s)
                    ];
                
def.TerminateFcnSpec = 'void sfun_end()';

%% Create MEX

legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def, {} );
legacy_code('sfcn_tlc_generate', def);

disp('---------------------------- DONE ----------------------------');
