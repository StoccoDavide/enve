
clc;
clear all;
addpath('./..');

% Load Bus names
Simulink.importExternalCTypes('./../include_sfun/sfun_types.h');

% Prepare input parameters
p1 = 0.3;
p2 = 4;
p3 = 0.3;
p4 = 4;
p5 = 0.1;
p6 = 5;
p7 = 1000;

p8 = 1;
p9 = 0.001;

% ENVAR for TerrainServer
rdf_path = [ pwd, '/../../../files_rdf/Eight.rdf' ];
setenv('ENVE_RDF_PATH', rdf_path);