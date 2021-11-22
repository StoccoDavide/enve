
clc;
clear all;
addpath('./..');

% Load Bus names
Simulink.importExternalCTypes('./../include_sfun/sfun_types.h');

% Prepare input parameters
p1  = 0.3;
p2  = 4;
p3  = 0.3;
p4  = 4;
p5  = 0.1;
p6  = 0.3;
p7  = 4;
p8  = 0.3;
p9  = 4;
p10 = 0.1;
p11 = 5;
p12 = 1000;

p13 = 1;
p14 = 0.001;

% ENVAR for TerrainServer
rdf_path = [ pwd, '/../../../files_rdf/Eight.rdf' ];
setenv('ENVE_RDF_PATH', rdf_path);