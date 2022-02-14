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

clc;
clear all;

addpath('./include_sfun');
addpath('./src_sfun');

%% ENVE sFunction interface

disp('----------------------- SIMULATOR SFUN -----------------------');

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

def.SFunctionName    = 'sfun_ENVE_SIMULATOR';
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
                     'double p1[1], ',  ... % Ribs number
                     'double p2[1], ',  ... % Front shell radius on x axis (m)
                     'double p3[1], ',  ... % Front shell curve degree for x axis
                     'double p4[1], ',  ... % Front shell radius on y axis (m)
                     'double p5[1], ',  ... % Front shell curve degree for y axis
                     'double p6[1], ',  ... % Front shell half width on y axis (m)
                     'double p7[1], ',  ... % Rear shell radius on x axis (m)
                     'double p8[1], ',  ... % Rear shell curve degree for x axis
                     'double p9[1], ',  ... % Rear shell radius on y axis (m)
                     'double p10[1], ', ... % Rear shell curve degree for y axis
                     'double p11[1], ', ... % Rear shell half width on y axis (m)
                     'double p12[1], ', ... % Flat ground surface height (m)
                     'double p13[1])',  ... % Flat ground surface friction scaling coefficient (-)
                   ];

def.OutputFcnSpec = [ 'void sfun_out(', ...
                      'shellsRF      u1[1], ',  ... % Input bus containing the wheel hub reference frames of the four shells (tires)
                      'groundContact y1[1], ',  ... % Output bus containing the contact point reference frames of the four shells (tires)
                      'double        p14[1], ', ... % method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
                      'double        p15[1]) ', ... % flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat
                    ];
                
def.TerminateFcnSpec = 'void sfun_end()';

%% Create MEX

legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def, {} );
legacy_code('sfcn_tlc_generate', def);
legacy_code('slblock_generate', def, def.SFunctionName);

disp('---------------------------- DONE ----------------------------');
