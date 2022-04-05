
clc;
clear all;
addpath('./..');

% Load Bus names
Simulink.importExternalCTypes('./../include_sfun/sfun_types.h');

% Prepare input parameters
p1 = 5;
p2 = 0.3;
p3 = 4.0;
p4 = 4.0;
p5 = 4.0;
p6 = 0.1;

p7 = 0;
p8 = 1;

% ENVAR for TerrainServer
ground_path = [ pwd, '/../../../files_rdf/sample.rdf' ];
setenv('ENVE_GROUND_PATH', ground_path);